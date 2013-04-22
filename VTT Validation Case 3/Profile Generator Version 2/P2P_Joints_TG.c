#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME  P2P_Joints_TG
#define S_FUNCTION_STR  "P2P_Joints_TG"

/* ========================================================================
 * INCLUDES AND EXTERNS
 * ======================================================================== */

/* ------------------------------------------------------------------------
 * Include standard C headers
 * ------------------------------------------------------------------------ */
#include <math.h>
#include <stdio.h>

/* ------------------------------------------------------------------------
 * Include Matlab Simulink headers
 * ------------------------------------------------------------------------ */
#include "simstruc.h"

/* ------------------------------------------------------------------------
 * Include project headers
 * ------------------------------------------------------------------------ */

/* None. */

/* ========================================================================
 * DEFINES AND GLOBAL VARIABLES
 * ======================================================================== */

/* ------------------------------------------------------------------------
 * Local definitions
 * ------------------------------------------------------------------------ */
#ifndef DEBUG
#define DEBUG (0)               /* Set to 0 for released versions */
#endif

#define DEFAULT_SMALL_ACCEL     0.0001  /* used instead of zero */
#define ZERO_TOLERANCE          1.0e-9  /* used to trap very small deltas */

/* ------------------------------------------------------------------------
 * Local type definitions
 * ------------------------------------------------------------------------ */
typedef struct
{
    /* define profile shape */
    double a1;  /* acceleration, m/s^2 (or rad/s^2 or deg/s^2) */
    double a2;  /* deceleration, m/s^2 (positive) (or rad/s^2 or deg/s^2) */
    double v;   /* constant velocity, m/s (or rad/s or deg/s) */
    double t1;  /* accleration time (duration), s */
    double t2;  /* duration of constant velocity, s */
    double t3;  /* deceleration time (duration), s */
    /* keep track of initial conditions */
    double delta;
    double initPos;
    double initVel;
} jointProfile;

/* ------------------------------------------------------------------------
 * Matlab Simulink definitions
 * ------------------------------------------------------------------------ */

/* ----------
 * Parameters
 * ---------- */
#define SFCT_NUM_PARAMS         (3)
#define prm_numJoints(S)        ssGetSFcnParam(S,0)
#define prm_scaleFactor(S)      ssGetSFcnParam(S,1)
#define prm_finishTogether(S)   ssGetSFcnParam(S,2)
#define NUM_JOINTS              mxGetPr(prm_numJoints(S))[0]
#define SCALE_FACTOR            mxGetPr(prm_scaleFactor(S))[0]
#define FINISH_TOGETHER         mxGetPr(prm_finishTogether(S))[0]

/* ------
 * Inputs
 * ------ */

/* No definitions, refer to mdlInitializeSizes(). */

/* -------
 * Outputs
 * ------- */

/* No definitions, refer to mdlInitializeSizes(). */

/* ========================================================================
 * ROUTINES DECLARATION
 * ======================================================================== */
jointProfile *CreateProfile();
void InitProfile(jointProfile *jp, double start, double end, double vMax,
                 double v0, double aMax, double dMax);
double CalculateVpeak(double x, double v0, double a, double d);
void ExtendProfileTime(jointProfile *jp, double totalTime);
double SolveVelocity(jointProfile *jp, double totalTime);

/* ========================================================================
 * LOCAL ROUTINES 
 * ======================================================================== */

/* ========================================================================
 * MATLAB SFUNCTION (PUBLIC) ROUTINES 
 * ======================================================================== */

/* ------------------------------------------------------------------------
 * Name: mdlCheckParameters
 *
 * Description  :
 *      Check parameters for valid size, type and value
 *
 * Inputs:
 *      SimStruct *S : Simulink data exchange structure.
 *
 * Outputs:
 *      SimStruct *S : Simulink data exchange structure.
 *
 * Remarks:
 *      This is defined out when compiling for RTW.
 * ------------------------------------------------------------------------ */
#if defined(MATLAB_MEX_FILE)
# define MDL_CHECK_PARAMETERS
static void mdlCheckParameters(SimStruct *S)
{
      int     numJoints;
      double  scaleFactor;
      int     finishTogether;    

      /* Get each parameter */
      const mxArray *m1 = prm_numJoints(S);
      const mxArray *m2 = prm_scaleFactor(S);
      const mxArray *m3 = prm_finishTogether(S);
      
      /* Check number of joints */
      if ( (!mxIsDouble(m1)) ||
           (mxGetNumberOfElements(m1) != 1) ||
           (mxGetPr(m1)[0] < 1)           
         )
      {
          ssSetErrorStatus(S,"Number of joints (first parameter) must be a"
                  "single integer greater than 1");
          return;
      }
      numJoints = (int) mxGetPr(m1)[0];
      if DEBUG printf("Number of joints: %d\n", numJoints);
      
      /* Check scale factor */
      if ( (!mxIsDouble(m2)) ||
           (mxGetNumberOfElements(m2) != 1) ||
           (mxGetPr(m2)[0] < 0) ||
           (mxGetPr(m2)[0] > 1)
         )
      {
          ssSetErrorStatus(S, "Scale factor (second parameter) must be a"
                           "single real between 0 and 1");
          return;
      }
      scaleFactor = (double) mxGetPr(m2)[0];
      if DEBUG printf("Scale Factor: %5.3f\n", scaleFactor);
      
      /* Check Finish Flag */
      if ( (!mxIsDouble(m3)) ||
           (mxGetNumberOfElements(m3) != 1) ||
           ((mxGetPr(m3)[0] != 0) && (mxGetPr(m3)[0] != 1))
         )
      {
          ssSetErrorStatus(S, "Finish together flag (third parameter) must be"
                           "0 or 1");
          return;
      }
      finishTogether = (int) mxGetPr(m3)[0];
      if DEBUG printf("Finish together: %d (%s)\n", finishTogether, finishTogether ? "True" : "False");
  }
#endif


/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 *
 *    Call mdlCheckParameters to verify that the parameters are okay,
 *    then setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S)
{
    int i, numJoints;    
    
    ssSetNumSFcnParams(S, SFCT_NUM_PARAMS);  /* Number of expected parameters */
#if defined(MATLAB_MEX_FILE)
    if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S))
    {
        mdlCheckParameters(S);
        if (ssGetErrorStatus(S) != NULL) return;
        
    }
    else return; /* Parameter mismatch will be reported by Simulink */
    
#endif
    // Cannont change the number of joints during a simulation
    ssSetSFcnParamNotTunable(S, 0);

    /*
     * If there are no errors with the S-function parameters, we continue
     * by setting the remaining sizes. These sizes can (optionally) be a
     * function of the S-function parameters.
     */

	ssSetNumContStates(S, 0);
    // Set one state per joint
    numJoints = (int) NUM_JOINTS;
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, numJoints)) return;
    if (!ssSetNumOutputPorts(S, numJoints)) return;    
    
    for (i = 0; i < numJoints; i++)
    {
        ssSetInputPortWidth(S, i, 6);
        ssSetInputPortDirectFeedThrough(S, i, 1);
        ssSetOutputPortWidth(S, i, 2);        
    }

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 1+numJoints); // Profile initialise time + endpoint for each profile
    ssSetNumIWork(S, 0); 
    ssSetNumPWork(S, numJoints);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    
    ssSetOptions(S, 0);
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);

}



#define MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
  /* Function: mdlInitializeConditions ========================================
   * Abstract:
   *    In this function, you should initialize the continuous and discrete
   *    states for your S-function block.  The initial states are placed
   *    in the state vector, ssGetContStates(S) or ssGetRealDiscStates(S).
   *    You can also perform any other initialization activities that your
   *    S-function may require. Note, this routine will be called at the
   *    start of simulation and if it is present in an enabled subsystem
   *    configured to reset states, it will be call when the enabled subsystem
   *    restarts execution to reset the states.
   */
  static void mdlInitializeConditions(SimStruct *S)
  {
      // Create the profiles for each joint
      int               i;
      time_T            startTime;
      InputRealPtrsType uPtrs;
      InputRealPtrsType uPtrs1;
      InputRealPtrsType uPtrs2;
      double            totalTime;
      double            maxTime=0;

      if DEBUG printf("Initialising profiles...\n");
      
      // Get initialize time
      // (Time zero, subtracted from future sample times to get elapsed time)
      startTime = ssGetT(S);
      // Save in real work vector
      ssSetRWorkValue(S,0,startTime);
      
      for (i=0; i<NUM_JOINTS; i++)
      {
          jointProfile *jp;
          
          // Get pointer to input vector
          uPtrs = ssGetInputPortRealSignalPtrs(S,i);

          // Save desired endpoint - allows us to re-initialise when it changes
          ssSetRWorkValue(S,1+i,*uPtrs[1]);
          
          // Get profile pointer
          jp = (jointProfile *) ssGetPWorkValue(S, i);
          
          InitProfile(jp,   *uPtrs[0],              // start
                            *uPtrs[1],              // end                                                      
                            *uPtrs[2] * SCALE_FACTOR,    // max vel
                            *uPtrs[3],              // initial vel
                            *uPtrs[4]*SCALE_FACTOR, // acceleration
                            *uPtrs[5]*SCALE_FACTOR  // deceleration                            
                           );

          totalTime = jp->t1 + jp->t2 + jp->t3;
          if (totalTime > maxTime) maxTime = totalTime;
          
          if DEBUG
          {
              printf("Joint %d: a1=%f, a2=%f, v=%f, t1=%f, t2=%f, t3=%f, delta=%f, initVel=%f.  Total time = %f\n", i,
                     jp->a1, jp->a2, jp->v, jp->t1, jp->t2, jp->t3, jp->delta, jp->initVel, totalTime);
              fflush(stdout);
          }
      }
      // Max time over all joints
      if (FINISH_TOGETHER)          
      {
          if DEBUG
          {
              printf("Extending all profiles to total time of %f\n", maxTime);
              fflush(stdout);
          }
          for (i=0; i<NUM_JOINTS; i++)
          {
              jointProfile *jp;
              jp = (jointProfile *) ssGetPWorkValue(S, i);
              if (jp->t1 + jp->t2 + jp->t3 < maxTime)
              {
                  if DEBUG
                  {
                      printf("Extending profile for joint %i\n", i);
                      fflush(stdout);
                  }
                  ExtendProfileTime(jp, maxTime);
              }
          }// end for - profile extension
      }// end if - finish together          
  }
#endif /* MDL_INITIALIZE_CONDITIONS */

void ExtendProfileTime(jointProfile *jp, double totalTime)
{
    double newV;

    if DEBUG
    {
        printf("OLD: t1=%f, t2=%f, t3=%f, v=%f, a=%f, d=%f, v0=%f\n",
               jp->t1, jp->t2, jp->t3, jp->v, jp->a1, jp->a2, jp->initVel);
        fflush(stdout);
    }

    newV = SolveVelocity(jp, totalTime);
    
    // Check to see if we now need to decelerate, where we didn't before
    // (New v is < V0, old v wasn't)
    if ((newV < jp->initVel) && (jp->v >= jp->initVel))
    {
        jp->a1 *= -1*fabs(jp->a2);
        //jp->a2 *= -1;        
        if DEBUG printf("Initial acceleration needs to change\n");
        newV = SolveVelocity(jp, totalTime);    // Resolve velocity now that initial acceleration has changed
        //jp->a2 *= -1;                
    }
    
    jp->t1 = (newV - jp->initVel) / jp->a1;
    if (jp->t1 < 0)
    {
        jp->a1 *= -1;
        jp->t1 *= -1;
    }
    
    jp->t3 = newV / jp->a2;
    if (jp->t3 < 0)
    {
        jp->a2 *= -1;
        jp->t3 *= -1;
    }
    
    jp->t2 = totalTime - jp->t1 - jp->t3;
    jp->v  = newV;
    
    if DEBUG
    {
        printf("NEW: t1=%f, t2=%f, t3=%f, v=%f, a=%f, d=%f, v0=%f\n",
               jp->t1, jp->t2, jp->t3, jp->v, jp->a1, jp->a2, jp->initVel);
        fflush(stdout);
    }

}

double SolveVelocity(jointProfile *jp, double totalTime)
{
    // Given an existing profile, extend the total time it takes.
    // This is done by re-calculating the maximum velocity to use (Vp).
    // The velocity is calculated from the equation for total distance, Eqn 1:
    // x = V0(t1) + 0.5a(t1)^2 + Vp(t2) + 0.5d(t3)^2
    // This is very similar to the technique used in building the initial profile.
    
    double a,b,c;       // coefficients of x in ax^2+bx+c=0
    double sqop;        // square root operand
    double Vp1, Vp2;    // 2 roots of quadratic

    // The expressions for these terms come from substituting for t1, t2 and t3 in Eqn 1,
    // and then re-arranging to get a quadratic in terms of Vp.
    // Note:
    // t1 = (Vp - V0)/a     where a is acceleration
    // t3 = Vp / d          where d is deceleration
    // t2 = T - t1 - t3     where T is totalTime for the new profile

    if (jp->a1 == (-1*jp->a2))
    {
        // This condition causes a divide by zero error, but
        // it should be a valid physical choice for a1, a2
        // To get around the problem, using the following HACK
        if DEBUG
        {
            printf("Performing initial deceleration HACK, altering from %f to %f\n", jp->a1, 0.9999*jp->a1);
            fflush(stdout);
        }
        jp->a1 *= 0.9999;
    }

    
    a = -1*((1/(2*jp->a1)) + (1/(2*jp->a2)));
    b = (jp->initVel/jp->a1) + totalTime;
    c = -1*(((jp->initVel*jp->initVel)/(2*jp->a1)) + jp->delta);

    // The roots of a quadratic are
    // x = (-b +- sqrt(b^2 - 4ac))/2a
    sqop = (b*b) - (4*a*c);
    if DEBUG
    {
        printf("A = %f, B = %f, C = %f, sqop = %f\n", a, b, c, sqop);
        fflush(stdout);
    }
    if (sqop < 0)
    {
        if DEBUG
        {
            printf("PROFILE ERROR: Extending profile required imaginary number.\n");
            fflush(stdout);
        }
        return jp->v; // use existing velocity
    }
    if (a == 0)
    {
        if DEBUG
        {
            printf("PROFILE ERROR: Extending profile required division by zero.\n");
            fflush(stdout);
        }
        return jp->v;
    }    
    Vp1 = ((-1*b) + sqrt(sqop))/(2*a);
    Vp2 = ((-1*b) - sqrt(sqop))/(2*a);

    if DEBUG
    {
        printf("Vp1 = %f, Vp2 = %f\n", Vp1, Vp2);
        fflush(stdout);        
    }
    
    // Use velocity with smallest absolute value
    if (fabs(Vp1) <= fabs(Vp2))
        return Vp1;
    else
        return Vp2;    
}

  
double CalculateVpeak(double x, double v0, double a, double d)
{
    ///////////////////////////////////////////////////////////////////////////////////////////
    // DESCRIPTION:
    // ------------
    // Calculate the velocity required to arrive at position x in minimum time.
    // Do the calculations as if x is always +ve, invert velocities & accelerations
    // if x is actually -ve.
    // Eqn for position is: x = v0t1 + (at1^2)/2 + (dt3^2)/2
    // where t1 is the acceleration time and t3 is the deceleration time.
    // V0 can be either +ve or -ve.
    // Vp is the theoretical peak velocity that would be achieved if there was no
    // period of constant velocity (ie. constant acceleration followed immediately
    // by contant deceleration).
    // Some identities: a = (Vp - V0)/t1
    //                  d = Vp/t3
    // therefore:       t1 = (Vp - V0)/a
    // and              t3 = Vp /d
    // substituing these into the position equation, gives a quadratic in the form ax^2 + bx + c = 0
    // The roots of a quadratic are x = (-b +- sqrt(b^2 - 4ac)) / 2a
    // We can use this to solve for Vp in terms of a, d, V0 and x
    // the 2 roots are: Vp = (+1) sqrt[ (2d(V0^2 + 2ax)) / (d + a) ]
    // and              Vp = (-1) sqrt[ (2d(V0^2 + 2ax)) / (d + a) ]
    //
    // The followint ACII art shows x as the area under the velocity curve specified by V0, Vp, a and d:
    // 
    //    |
    //    |
    // Vp +     ^
    //    |    / \
    //    | a /   \ d
    //    |  /     \
    //    | /       \
    // V0 +/         \
    //    |     x     \
    //    |            \
    //    |             \
    //  --|-----+--------+---
    //    |  t1 |   t3   |
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // Code & comments start
    double num, den, result;
    
/*    if (v0 >= sqrt(MAXDOUBLE))
    {
        // This probably isn't necessary, and it still doesn't guarantee that num can be calculated
        // accurately.
        // Initial velocity too large to square on this machine
        printf("PROFILE ERROR: Initial velocity of %f is too large to square\n", v0);
        fflush(stdout);
        return 0.0;
    }
*/
    num = d*(v0*v0 + 2.0*a*x);
    den = d + a; // should both be +ve   
    
    // Error checking
    if (den == 0)
    {
        if DEBUG
        {
            printf("PROFILE ERROR: Divide by zero.  Both a and d should have same sign. a=%f, d=%f\n", a, d);
            fflush(stdout);
        }
        return 0.0;
    }
    result = num /den;
    if (result < 0)
    {
        if DEBUG
        {
            printf("PROFILE ERROR: Result would be imaginary.  Both a and d should have same sign. a=%f, d=%f\n", a, d);
            fflush(stdout);
        }
        // Other reason it could occur is if a < d < 0 and v0^2+2ax < 0
        return 0.0;
    }
        
    return sqrt(result); // Use +ve root
}

jointProfile *CreateProfile()
{
    // Allocate memory for profile structure
    jointProfile *jp;
    
    if ((jp = (jointProfile *) malloc(sizeof(jointProfile))) == NULL)
    {
        printf(("FATAL ERROR: Out of memory in %s BuildProfile() "
                "file %s ... quitting.\n", S_FUNCTION_STR, __FILE__));
        fflush(stdout);
        exit(-1);
    }

    return jp;
}

void InitProfile(jointProfile *jp, double start, double end, double vMax, double v0, double aMax, double dMax)
{
    // DESCRIPTION
    // -----------
    // Fill in the jointProfile structure with values that meet the criteria
    // Basically means working out the 3 times - acceleration (t1)
    //                                         - constant vel (t2)
    //                                         - deceleration (t3)
    //
    ////////////////////////////////////////////////////////////////////////////

    double          delta, x1, x2, x3;          // position variables
    double          tVmax, tVpeak;              // time variables
    double          a1, d1;                     // acceleration variables
    double          vPeak;
    double          v0c;                        // v0 checked

    
    // Save initial inputs
    jp->delta   = end - start;
    jp->initPos = start;
    jp->initVel = v0;
    
    // Building profile, approach used is to calculate corner times
    // In other words accelerate & decelerate at maximums

    // Step 0: Input checking
    a1 = (aMax==0) ? DEFAULT_SMALL_ACCEL : aMax;
    d1 = (dMax==0) ? DEFAULT_SMALL_ACCEL : dMax;


    // Step 1: Calculate position delta desired
    delta = end - start;
    if (delta < 0)
    {
        // Compute with +ve delta
        delta = fabs(delta);
        // Take v0 into account
        v0c = -1*v0;
    }
    else
    {
        v0c = v0;
    }
    
    
    // Step 2: Acceleration time
    // Choose minimum time from time when v=vMax or it's time to start decelerating.
    // The latter time is determined by when we reach the peak velocity necessary
    // for this delta.
    vPeak = CalculateVpeak(delta, v0c, aMax, dMax);
    if DEBUG
    {
        printf("vPeak = %f\n", vPeak);
        fflush(stdout);
    }
    tVmax = (vMax - v0c) / a1;
    tVpeak = (vPeak - v0c) / a1;
    
    if (tVpeak < tVmax) // choose minimum time and corresponding velocity
    {
        jp->t1 = tVpeak;
        jp->v = vPeak;
    }
    else
    {
        jp->t1 = tVmax;
        jp->v = vMax;
    }    
    // NOTE: t1 will be < 0 if v0c > vMax
    if (v0c > vMax)  // Case 3
    {
        jp->t1 = (-1.0)*tVmax;
        jp->v = vMax;
        a1 = -1.0*fabs(d1);         // We actually need to decelerate first
        // Note: could use -a1 but to be consistent with case 5, use -d1 instead.
        // It is assumed that |a1| > |d1|, so above is not optimal time choice
        if DEBUG
        {
            printf("CASE 3!\n");
            fflush(stdout);
        }       
    }
    
    if (v0c > vPeak) // Case 5.  vPeak is velocity it's possible to decelerate from without exceeding delta.
    {
        // Actually need to decelerate below zero, then accelerate
        a1 = -1.0*fabs(d1); // Using d1 for magnitude of a1 to prevent possibility of imaginary result
        d1 = -1.0*fabs(d1); // both acclerations now opposite of 'normal'
        vPeak = -1.0*CalculateVpeak(delta, v0c, a1, d1); // -ve root
        if (fabs(vPeak) > vMax) vPeak = -1.0*fabs(vMax);    // clip velocity if required            
        
        tVpeak = (vPeak - v0c) / a1;   
        jp->t1 = tVpeak;
        jp->v = vPeak;
        
        if DEBUG
        {
            printf("CASE 5! Final Recalculated Vpeak = %f\n", vPeak);
            fflush(stdout);
        }
        
    }
    
    if DEBUG
    {
        printf("tVmax = %f, tVpeak = %f, v = %f\n", tVmax, tVpeak, jp->v);
        fflush(stdout);
    }
    
    // Step 3: Deceleration time
    // Calculate time to decelerate from velocity achieved in step 2 to 0.
    jp->t3 = (double) (jp->v / d1);            // either d1 > 0, or both v & d1 < 0
    if DEBUG
    {
        printf("v = %f, t3 = %f\n", jp->v, jp->t3);
        fflush(stdout);
    }
    
    // Step 4: Contant velocity time
    // Calculate distances travelled in Steps 1 & 2, subtract from delta, coast for time
    // required to cover this distance
    x1 = v0c*(jp->t1) + (0.5)*(a1)*(jp->t1)*(jp->t1);
    x3 = (0.5)*(d1)*(jp->t3)*(jp->t3);
    x2 = delta - (x1 + x3);
    if (fabs(x2) < ZERO_TOLERANCE) x2 = 0;
    jp->t2 = (x2 / jp->v);                             // v > 0
    if DEBUG
    {
        printf("x1 = %f, x3 = %f, x2 = %f, delta =%f, t2 = %f\n", x1, x3, x2, delta, jp->t2);
        fflush(stdout);
    }

    
    jp->a1 = a1;
    jp->a2 = d1;
    if ((end - start) < 0)
    {
        jp->a1 *= -1;
        jp->a2 *= -1;
        jp->v  *= -1;
    }
    
    return;
}
  

#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
      int i;
      jointProfile *jp;
      
      for (i=0; i<NUM_JOINTS; i++)
      {
          jp = CreateProfile();
          // Store pointer in work vector
          ssSetPWorkValue(S,i,jp);          
      }
  }
#endif /*  MDL_START */



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block. Generally outputs are placed in the output vector, ssGetY(S).
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    int               i;
    InputRealPtrsType uPtrs;
    real_T            *y;
    jointProfile      *jp;

    // Check none of the inputs have changed
    for (i=0; i < (int)NUM_JOINTS; i++)
    {
        double currentInput, oldInput;
        
        // Get pointer to input vector
        uPtrs = ssGetInputPortRealSignalPtrs(S,i);
        currentInput = *uPtrs[1];
        oldInput = ssGetRWorkValue(S,i+1);
        if (currentInput != oldInput)
        {
            // input has changed, re-initialise profiles
            if DEBUG
            {
                printf("Input changed at joint %d, was %f, now %f.\n", i, oldInput, currentInput);
                fflush(stdout);
            }
            mdlInitializeConditions(S);            
            break;
        }        
    }
    
    for (i=0; i < (int)NUM_JOINTS; i++)
    {
        double      elapsed = ssGetT(S) - ssGetRWorkValue(S,0);  // Time since profile started
        double      x, x0, v, v0;
        
        // Get pointer to input vector
        uPtrs = ssGetInputPortRealSignalPtrs(S,i);
        // Get pointer to output vector
        y = ssGetOutputPortRealSignal(S,i);
        // Get pointer to joint profile structure
        jp = (jointProfile *) ssGetPWorkValue(S, i);        

        // Initialise
        x0 = jp->initPos;  // starting position
        v0 = jp->initVel;  // initial velocity
        
        // Do calculations based on time position on profile
        if ((jp->t1 < 0.0) || (jp->t2 < 0.0) || (jp->t3 < 0.0))
        {
            if (elapsed == 0) // only print error message once
            {
                if DEBUG
                {
                    printf("PROFILE ERROR: Negative time required for joint %d!\n", i);
                    printf("t1 = %e\nt2 = %e\nt3 = %e\n", jp->t1, jp->t2, jp->t3);
                    fflush(stdout);
                }
            }
            y[0] = *uPtrs[0]; // pos = start pos
            y[1] = *uPtrs[3]; // vel = start vel            
            continue;            
        }
        if (elapsed <= jp->t1)
        {
            // Const. accel only
            x = x0 + v0*elapsed + (0.5)*jp->a1*elapsed*elapsed;   // x= vt + (at^2) / 2
            v = v0 + jp->a1*elapsed;     // v = u + at, initial velocity is 4th input
            if (0) //if DEBUG
            {
                printf ("Before t1, elapsed = %f, x = %f, v = %f\n", elapsed, x, v);
                fflush(stdout);
            }
            
        }
        if ((elapsed > jp->t1) && (elapsed <= (jp->t1 + jp->t2)))
        {
            // In constant velocity region
            // Work out distance travelled during Const. accel
            x = x0 + v0*jp->t1 + (0.5)*jp->a1*jp->t1*jp->t1;
            // Add on distance so far from const. vel
            x = x + (jp->v*(elapsed - jp->t1));
            v = jp->v;
            if (0) // if DEBUG
            {
                printf ("Between t1 & t2, elapsed = %f, x = %f, v = %f\n", elapsed, x, v);
                fflush(stdout);
            }
            
        }

        if ((elapsed > (jp->t1 + jp->t2)) && (elapsed <= (jp->t1 + jp->t2 + jp->t3)))
        {
            double tt2 = jp->t1 + jp->t2; // total time to t2
            
            // In constant deceleration region
            // Work out distance travelled during Const. accel
            x = x0 + v0*jp->t1 + (0.5)*jp->a1*jp->t1*jp->t1;
            // Add on distance from const. vel            
            x = x + (jp->v*jp->t2);
            // Add on distance so far from decel.
            x = x + ( (jp->v*(elapsed - tt2)) - (0.5)*jp->a2*(elapsed - tt2)*(elapsed - tt2));
            // Reduce velocity
            v = jp->v - (jp->a2 * (elapsed - tt2));
            if (0) //if DEBUG
            {
                printf ("Between t2 & t3, elapsed = %f, x = %f, v = %f\n", elapsed, x, v);
                fflush(stdout);
            }
            
        }
        if (elapsed > (jp->t1 + jp->t2 + jp->t3))
        {
            x = *uPtrs[1]; // end point
            v = 0;
        }
        // First output is profile position
        y[0] = x;
        // Second output is profile velocity
        y[1] = v;
    }  	
}



#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
  /* Function: mdlUpdate ======================================================
   * Abstract:
   *    This function is called once for every major integration time step.
   *    Discrete states are typically updated here, but this function is useful
   *    for performing any tasks that should only take place once per
   *    integration step.
   */
  static void mdlUpdate(SimStruct *S, int_T tid)
  {
  }
#endif /* MDL_UPDATE */



#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
  /* Function: mdlDerivatives =================================================
   * Abstract:
   *    In this function, you compute the S-function block's derivatives.
   *    The derivatives are placed in the derivative vector, ssGetdX(S).
   */
  static void mdlDerivatives(SimStruct *S)
  {
  }
#endif /* MDL_DERIVATIVES */



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
    int i;
    jointProfile *jp;

    for (i=0; i<NUM_JOINTS; i++)
    {
        // Retrieve pointer from work vector
        jp = (jointProfile *) ssGetPWorkValue(S, i);        
        free(jp);
    }    
}


/*======================================================*
 * See sfuntmpl.doc for the optional S-function methods *
 *======================================================*/

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif


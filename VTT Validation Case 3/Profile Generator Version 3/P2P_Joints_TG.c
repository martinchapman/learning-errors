#include <math.h>
#include <stdlib.h>

#include "P2P_Joints_TG.h"

void DllExport P2P_Joints_TG(double Sample_Time, double Joints_Limits[4], double XYZRPYin[NUM_JOINTS], double XYZRPYfb[NUM_JOINTS], double XYZRPYout[NUM_JOINTS], double *TrajectoryComplete)
{
	int		i;	
	double	tt2;

	if(initialized == 0)
	{
		InitilizeTG(Joints_Limits, XYZRPYin, XYZRPYfb);
		initialized = 1;
	}
																																										
	// Check none of the inputs have changed
	for(i = 0; i < NUM_JOINTS; i++)
	{
		double	currentInput, oldInput;
		// Get pointer to input vector
		currentInput = XYZRPYin[i];
		oldInput = currentPosition[i];
		if(currentInput != oldInput)
		{
			// input has changed, re-initialise profiles
			InitilizeTG(Joints_Limits, XYZRPYin, XYZRPYfb);
			break;
		}
	}	

	for(i = 0; i < NUM_JOINTS; i++)
	{
		double	elapsed;
		double  x, x0, v, v0;

		if(i == 0)
		{
			startTime = startTime + Sample_Time;
			elapsed = startTime;  // Time since profile started
		}

		// Initialise
		x0 = jp[i].initPos;  // starting position
		v0 = jp[i].initVel;  // initial velocity
    
		// Do calculations based on time position on profile
		if((jp[i].t1 < 0.0) || (jp[i].t2 < 0.0) || (jp[i].t3 < 0.0))
		{
			XYZRPYout[i] = XYZRPYfb[i]; // pos = start pos			
			continue;			
		}
		
		if(elapsed <= jp[i].t1)
		{
			// Const. accel only
			x = x0 + v0 * elapsed + (0.5) * jp[i].a1 * elapsed * elapsed;   // x= vt + (at^2) / 2
			v = v0 + jp[i].a1 * elapsed;     // v = u + at, initial velocity is 4th input
			*TrajectoryComplete = -2.0;
		}
		
		if((elapsed > jp[i].t1) && (elapsed <= (jp[i].t1 + jp[i].t2)))
		{
			// In constant velocity region
			// Work out distance travelled during Const. accel
			x = x0 + v0 * jp[i].t1 + (0.5) * jp[i].a1 * jp[i].t1 * jp[i].t1;
			// Add on distance so far from const. vel
			x = x + (jp[i].v*(elapsed - jp[i].t1));
			v = jp[i].v;
			*TrajectoryComplete = -2.0;
		}
		
		if((elapsed > (jp[i].t1 + jp[i].t2)) && (elapsed <= (jp[i].t1 + jp[i].t2 + jp[i].t3)))
		{
			tt2 = jp[i].t1 + jp[i].t2; // total time to t2
			
			// In constant deceleration region
			// Work out distance travelled during Const. accel
			x = x0 + v0 * jp[i].t1 + (0.5) * jp[i].a1 * jp[i].t1 * jp[i].t1;
			// Add on distance from const. vel            
			x = x + (jp[i].v * jp[i].t2);
			// Add on distance so far from decel.
			x = x + ((jp[i].v * (elapsed - tt2)) - (0.5) * jp[i].a2 * (elapsed - tt2) * (elapsed - tt2));
			// Reduce velocity
			v = jp[i].v - (jp[i].a2 * (elapsed - tt2));
			*TrajectoryComplete = -2.0;
		}
		
		if(elapsed > (jp[i].t1 + jp[i].t2 + jp[i].t3))
		{
			x = XYZRPYin[i]; // end point
			v = 0;
			*TrajectoryComplete = 2.0;
		}
		
		// Output profile
		XYZRPYout[i] = x;		
	}
}

void InitilizeTG(double jl[4], double in[NUM_JOINTS], double fb[NUM_JOINTS])
{
	// Create the profiles for each joint
	int		i;
	double	totalTime;
	double	maxTime=0;

	// Get initialize time
	// (Time zero, subtracted from future sample times to get elapsed time)
	startTime = 0.0;

	for(i = 0; i < NUM_JOINTS; i++)
	{
		currentPosition[i] = in[i];

		InitProfile(i, fb[i],	// start
					in[i],		// end
					jl[0],		// max vel
					jl[1],		// initial vel
					jl[2],		// acceleration
					jl[3]		// deceleration
					);
		
		totalTime = jp[i].t1 + jp[i].t2 + jp[i].t3;
		
		if(totalTime > maxTime) maxTime = totalTime;
	}

	//Profile Extension	
	for(i = 0; i < NUM_JOINTS; i++)
	{		
		if((jp[i].t1 + jp[i].t2 + jp[i].t3) < maxTime)
		{				
				ExtendProfileTime(i, maxTime);
		}
	}// end for - profile extension
}

void InitProfile(int i, double start, double end, double vMax, double v0, double aMax, double dMax)
{
	// DESCRIPTION
	// -----------
	// Fill in the jointProfile structure with values that meet the criteria
	// Basically means working out the 3 times - acceleration (t1)
	//                                         - constant vel (t2)
	//                                         - deceleration (t3)
	//
	////////////////////////////////////////////////////////////////////////////

	double	delta, x1, x2, x3;          // position variables
	double	tVmax, tVpeak;              // time variables
	double	a1, d1;                     // acceleration variables
	double	vPeak;
	double	v0c;                        // v0 checked


	// Save initial inputs
	jp[i].delta   = end - start;
	jp[i].initPos = start;
	jp[i].initVel = v0;

	// Building profile, approach used is to calculate corner times
	// In other words accelerate & decelerate at maximums

	// Step 0: Input checking
	a1 = (aMax==0) ? DEFAULT_SMALL_ACCEL : aMax;
	d1 = (dMax==0) ? DEFAULT_SMALL_ACCEL : dMax;

	// Step 1: Calculate position delta desired
	delta = end - start;
	
	if(delta < 0)
	{
		// Compute with +ve delta
		delta = fabs(delta);
		// Take v0 into account
		v0c = -1 * v0;
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
	tVmax = (vMax - v0c) / a1;
	tVpeak = (vPeak - v0c) / a1;

	if(tVpeak < tVmax) // choose minimum time and corresponding velocity
	{
		jp[i].t1 = tVpeak;
		jp[i].v = vPeak;
	}
	
	else
	{
		jp[i].t1 = tVmax;
		jp[i].v = vMax;
	}
	
	// NOTE: t1 will be < 0 if v0c > vMax
	if(v0c > vMax)  // Case 3
	{
		jp[i].t1 = (-1.0)*tVmax;
		jp[i].v = vMax;
		a1 = -1.0*fabs(d1);         // We actually need to decelerate first
		// Note: could use -a1 but to be consistent with case 5, use -d1 instead.
		// It is assumed that |a1| > |d1|, so above is not optimal time choice	
	}
	
	if(v0c > vPeak) // Case 5.  vPeak is velocity it's possible to decelerate from without exceeding delta.
	{
		// Actually need to decelerate below zero, then accelerate
		a1 = -1.0*fabs(d1); // Using d1 for magnitude of a1 to prevent possibility of imaginary result
		d1 = -1.0*fabs(d1); // both acclerations now opposite of 'normal'
		vPeak = -1.0*CalculateVpeak(delta, v0c, a1, d1); // -ve root
		
		if(fabs(vPeak) > vMax) vPeak = -1.0 * fabs(vMax);    // clip velocity if required
		
		tVpeak = (vPeak - v0c) / a1;
		jp[i].t1 = tVpeak;
		jp[i].v = vPeak;
	}
	
	// Step 3: Deceleration time
	// Calculate time to decelerate from velocity achieved in step 2 to 0.
	jp[i].t3 = jp[i].v / d1;            // either d1 > 0, or both v & d1 < 0

  // Step 4: Contant velocity time
	// Calculate distances travelled in Steps 1 & 2, subtract from delta, coast for time
	// required to cover this distance
	x1 = v0c * (jp[i].t1) + (0.5) * (a1) * (jp[i].t1) * (jp[i].t1);
	x3 = (0.5)*(d1)*(jp[i].t3)*(jp[i].t3);
	x2 = delta - (x1 + x3);
	
	if (fabs(x2) < ZERO_TOLERANCE) x2 = 0;
	jp[i].t2 = (x2 / jp[i].v);                             // v > 0
	
	jp[i].a1 = a1;
	jp[i].a2 = d1;
	
	if((end - start) < 0)
	{
		jp[i].a1 *= -1;
		jp[i].a2 *= -1;
		jp[i].v  *= -1;
	}  
}

void ExtendProfileTime(int i, double totalTime)
{
	double newV;
	
	newV = SolveVelocity(i, totalTime);
	
	// Check to see if we now need to decelerate, where we didn't before
	// (New v is < V0, old v wasn't)
	if((newV < jp[i].initVel) && (jp[i].v >= jp[i].initVel))
	{
		jp[i].a1 *= -1 * fabs(jp[i].a2);
		newV = SolveVelocity(i, totalTime);    // Resolve velocity now that initial acceleration has changed
	}

	jp[i].t1 = (newV - jp[i].initVel) / jp[i].a1;
	
	if (jp[i].t1 < 0)
	{
		jp[i].a1 *= -1;
		jp[i].t1 *= -1;
	}

	jp[i].t3 = newV / jp[i].a2;
	
	if (jp[i].t3 < 0)
	{
		jp[i].a2 *= -1;
		jp[i].t3 *= -1;
	}

	jp[i].t2 = totalTime - jp[i].t1 - jp[i].t3;
	jp[i].v  = newV;
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
	
	num = d * (v0 * v0 + 2.0 * a * x);
	den = d + a; // should both be +ve   

	// Error checking
	if(den == 0)
		return 0.0;
	
	result = num /den;
	
	if(result < 0)
	{
		// Other reason it could occur is if a < d < 0 and v0^2+2ax < 0
		return 0.0;
	}
	
	return sqrt(result); // Use +ve root
}

double SolveVelocity(int i, double totalTime)
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

	// This condition causes a divide by zero error, but
	// it should be a valid physical choice for a1, a2
	// To get around the problem, using the following HACK
	if(jp[i].a1 == (-1*jp[i].a2))
		jp[i].a1 *= 0.9999;


	a = -1 * ((1 / (2 * jp[i].a1)) + (1 / (2 * jp[i].a2)));
	b = (jp[i].initVel / jp[i].a1) + totalTime;
	c = -1 * (((jp[i].initVel * jp[i].initVel)/(2 * jp[i].a1)) + jp[i].delta);

	// The roots of a quadratic are
	// x = (-b +- sqrt(b^2 - 4ac))/2a
	sqop = (b * b) - (4 * a * c);
	
	if (sqop < 0)
		return jp[i].v; // use existing velocity
	
	if (a == 0)
		return jp[i].v;
	
	Vp1 = ((-1 * b) + sqrt(sqop)) / (2 * a);
	Vp2 = ((-1 * b) - sqrt(sqop)) / (2 * a);

	// Use velocity with smallest absolute value
	if (fabs(Vp1) <= fabs(Vp2))
		return Vp1;
	
	else
		return Vp2;
}
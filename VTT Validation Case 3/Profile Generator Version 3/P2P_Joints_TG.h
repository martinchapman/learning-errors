#define DllExport __declspec( dllexport ) 

//-------------------------------------------------------------------------
#define DEFAULT_SMALL_ACCEL     0.0001  // used instead of zero
#define ZERO_TOLERANCE          1.0e-9  // used to trap very small deltas
#define NUM_JOINTS              8
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//	Local type definitions
//-------------------------------------------------------------------------
typedef struct
{
    // define profile shape
    double a1;  // acceleration, m/s^2 (or rad/s^2 or deg/s^2)
    double a2;  // deceleration, m/s^2 (positive) (or rad/s^2 or deg/s^2)
    double v;   // constant velocity, m/s (or rad/s or deg/s)
    double t1;  // accleration time (duration), s
    double t2;  // duration of constant velocity, s
    double t3;  // deceleration time (duration), s
    // keep track of initial conditions
    double delta;
    double initPos;
    double initVel;
} jointProfile;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//	Global variables declaration
//-------------------------------------------------------------------------
jointProfile	jp[NUM_JOINTS];
static double	currentPosition[NUM_JOINTS];
static double	startTime = 0.0;
static int		initialized = 0;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//	Routines declaration
//-------------------------------------------------------------------------
void InitilizeTG(double [], double [], double []);

void InitProfile(int, double, double, double, double, double, double);

double CalculateVpeak(double, double, double, double);

void ExtendProfileTime(int, double);

double SolveVelocity(int, double);
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//	Main function declaration
//-------------------------------------------------------------------------
void DllExport P2P_Joints_TG(double Sample_Time, double Joints_Limits[4], double XYZRPYin[NUM_JOINTS], double XYZRPYfb[NUM_JOINTS], double XYZRPYout[NUM_JOINTS], double *TrajectoryComplete);
//-------------------------------------------------------------------------
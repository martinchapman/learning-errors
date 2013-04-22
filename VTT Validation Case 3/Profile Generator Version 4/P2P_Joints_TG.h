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
	double a0,a1,a2,a3,a4,a5;	// spline coefficients
	double x0, xf;				// starting and final positions

} jointProfile;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//	Global variables declaration
//-------------------------------------------------------------------------
jointProfile	jp[NUM_JOINTS];
static double	currentPosition[NUM_JOINTS];
static double	elapsedTime = 0.0;
static double	endTime = 0.0;
static int		initialized = 0;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//	Main function declaration
//-------------------------------------------------------------------------
void DllExport P2P_Joints_TG(double Sample_Time, double Joints_Limits[4], double XYZRPYin[NUM_JOINTS], double XYZRPYfb[NUM_JOINTS], double XYZRPYout[NUM_JOINTS], double *TrajectoryComplete, double VelocitiesOut[NUM_JOINTS]);
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//	Routines declaration
//-------------------------------------------------------------------------
void InitilizeTG(double jl[4], double in[], double fb[]);
void SelectMovementTime(double vMax, double aMax, double XYZRPYin[], double XYZRPYfb[]);
void InitProfile(int i, double X0, double Xf);

//-------------------------------------------------------------------------
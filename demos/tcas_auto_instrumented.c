/*  -*- Last-Edit:  Fri Jan 29 11:13:27 1993 by Tarak S. Goradia; -*- */
/* $Log: tcas_v23_523.c,v $
/* Revision 1.1  2006-04-04 08:38:22  kroening
/* more
/*
 * Revision 1.2  1993/03/12  19:29:50  foster
 * Correct logic bug which didn't allow output of 2 - hf
 * */


#include <stdio.h>

#define OLEV       600		/* in feets/minute */
#define MAXALTDIFF 600		/* max altitude difference in feet */
#define MINSEP     300          /* min separation in feet */
#define NOZCROSS   100		/* in feet */
				/* variables */

// ~MDC Having this commented out is ok for the main environment, but upsets bound checkers, and vice-versa when it is in. Needs checking.
//typedef bool int;
typedef _Bool bool;

int Cur_Vertical_Sep;
int High_Confidence;
int Two_of_Three_Reports_Valid;

int Own_Tracked_Alt;
int Own_Tracked_Alt_Rate;
int Other_Tracked_Alt;

int Alt_Layer_Value;		/* 0, 1, 2, 3 */
int Positive_RA_Alt_Thresh[4];

int Up_Separation;
int Down_Separation;

				/* state variables */
int Other_RAC;			/* NO_INTENT, DO_NOT_CLIMB, DO_NOT_DESCEND */
#define NO_INTENT 0
#define DO_NOT_CLIMB 1
#define DO_NOT_DESCEND 2

int Other_Capability;		/* TCAS_TA, OTHER */
#define TCAS_TA 1
#define OTHER 2

int Climb_Inhibit;		/* true/false */

#define UNRESOLVED 0
#define UPWARD_RA 1
#define DOWNWARD_RA 2

int  ALIM();
int  Inhibit_Biased_Climb();
int   Non_Crossing_Biased_Climb();
int   Non_Crossing_Biased_Descend();
int   Own_Below_Threat();
int   Own_Above_Threat();
int  alt_sep_test();
void initialize()
{
    Positive_RA_Alt_Thresh[0] = 400;
    Positive_RA_Alt_Thresh[1] = 500;
    Positive_RA_Alt_Thresh[2] = 640;
    Positive_RA_Alt_Thresh[3] = 740;
}

int ALIM ()
{
 return Positive_RA_Alt_Thresh[Alt_Layer_Value];
}

int Inhibit_Biased_Climb ()
{	
    return (Climb_Inhibit ? Up_Separation + NOZCROSS : Up_Separation);
}

int Non_Crossing_Biased_Climb()
{
    int upward_preferred;
    int upward_crossing_situation;
    int result;

    upward_preferred = Inhibit_Biased_Climb() > Down_Separation;
    if (upward_preferred)
    {
	result = !(Own_Below_Threat()) || ((Own_Below_Threat()) && (!(Down_Separation >= ALIM())));
    }
    else
    {
	result = Own_Above_Threat() && (Cur_Vertical_Sep >= MINSEP) && (Up_Separation >= ALIM());
    }
    return result;
}

int Non_Crossing_Biased_Descend()
{
    int upward_preferred;
    int upward_crossing_situation;
    int result;

    upward_preferred = (Up_Separation + NOZCROSS) > Down_Separation;
    if (upward_preferred)
    {
	result = Own_Below_Threat() && (Cur_Vertical_Sep >= MINSEP) && (Down_Separation >= ALIM());
    }
    else
    {
	result = !(Own_Above_Threat()) || ((Own_Above_Threat()) && (Up_Separation >= ALIM()));
    }
    return result;
}

int fake0() {
	return 0;
}

int fake1() {
	return 1;
}

int Own_Below_Threat()
{
	//return nondet_int(); //(Own_Tracked_Alt < Other_Tracked_Alt); // ofer
	if (Own_Tracked_Alt < Other_Tracked_Alt) return fake0();
	else return fake1(); 
//	return (Own_Tracked_Alt < Other_Tracked_Alt); // ofer
}

int Own_Above_Threat()
{
    return (Other_Tracked_Alt < Own_Tracked_Alt);
}

int alt_sep_test()
{
    int enabled, tcas_equipped, intent_not_known;
    int need_upward_RA, need_downward_RA;
    int alt_sep;

    enabled = High_Confidence && (Own_Tracked_Alt_Rate <= OLEV)  && (Cur_Vertical_Sep > MAXALTDIFF); 
    tcas_equipped = Other_Capability == TCAS_TA;
    intent_not_known = Two_of_Three_Reports_Valid && Other_RAC == NO_INTENT;
    
    alt_sep = UNRESOLVED;
    
	if (enabled && ((tcas_equipped && intent_not_known) || !tcas_equipped))  {
		need_upward_RA = Non_Crossing_Biased_Climb() && Own_Below_Threat();
		need_downward_RA =  Non_Crossing_Biased_Descend() && Own_Above_Threat(); 
		if (need_upward_RA && need_downward_RA){
			/* unreachable: requires Own_Below_Threat and Own_Above_Threat
			to both be true - that requires Own_Tracked_Alt < Other_Tracked_Alt
			and Other_Tracked_Alt < Own_Tracked_Alt, which isn't possible */
			alt_sep = UNRESOLVED;
		}
		else {
			if (need_upward_RA){
				alt_sep = UPWARD_RA;
			}
			else {
				if (need_downward_RA){
					alt_sep = DOWNWARD_RA;
				}
				else {
					alt_sep = UNRESOLVED;
				}
			}
		}
	}
    	
    return alt_sep;
}

int main(void)
{	
  initialize();
  Cur_Vertical_Sep = nondet_int(); //860; 
  High_Confidence = 1; 
  Two_of_Three_Reports_Valid = 1; 
  Own_Tracked_Alt = nondet_int();//618; 
  Own_Tracked_Alt_Rate = nondet_int();//329; 
  Other_Tracked_Alt = nondet_int();//574; 
  Alt_Layer_Value = 3;  // ofer. was 4, which violates array bounds.
  Up_Separation = nondet_int();//893; 
  Down_Separation = nondet_int();//914; 
  Other_RAC = 0;
  Other_Capability = 2;
  Climb_Inhibit = 0; 
  
  _Learn_assert(alt_sep_test()==0);
  return 0;
}

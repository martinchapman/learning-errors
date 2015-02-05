// #anon_enum$DIMENSION_PROPAGATION=0$TYPE_PROPAGATION=1$COMPLEX_PROPAGATION=2
// file ../R2013a/simulink/include/simstruc.h line 584
enum anonymous$23 { DIMENSION_PROPAGATION=0, TYPE_PROPAGATION=1, COMPLEX_PROPAGATION=2 };

// #anon_enum$EXTLOGTASK_TRIG_ARM=0$EXTLOGTASK_INIT_EVENT=1$EXTLOGTASK_TERM_INTERMEDIATE_ONESHOT=2$EXTLOGTASK_TERM_SESSION=3
// file ../R2013a/simulink/include/simstruc.h line 685
enum anonymous$18 { EXTLOGTASK_TRIG_ARM=0, EXTLOGTASK_INIT_EVENT=1, EXTLOGTASK_TERM_INTERMEDIATE_ONESHOT=2, EXTLOGTASK_TERM_SESSION=3 };

// #anon_enum$FALLING_ZERO_CROSSING=-1$ANY_ZERO_CROSSING=0$RISING_ZERO_CROSSING=1
// file ../R2013a/simulink/include/simstruc_types.h line 114
enum anonymous$27 { FALLING_ZERO_CROSSING=-1, ANY_ZERO_CROSSING=0, RISING_ZERO_CROSSING=1 };

// #anon_enum$FRAME_INHERITED=-1$FRAME_NO=0$FRAME_YES=1
// file ../R2013a/simulink/include/sl_common_types_def.h line 26
enum anonymous$15 { FRAME_INHERITED=-1, FRAME_NO=0, FRAME_YES=1 };

// #anon_enum$MINOR_TIME_STEP=0$MAJOR_TIME_STEP=1
// file ../R2013a/simulink/include/rtw_continuous.h line 29
enum anonymous$10 { MINOR_TIME_STEP=0, MAJOR_TIME_STEP=1 };

// #anon_enum$RTPARAM_NOT_TRANSFORMED=0$RTPARAM_TRANSFORMED=1$RTPARAM_MAKE_TRANSFORMED_TUNABLE=2
// file ../R2013a/simulink/include/sl_common_types_def.h line 168
enum anonymous$59 { RTPARAM_NOT_TRANSFORMED=0, RTPARAM_TRANSFORMED=1, RTPARAM_MAKE_TRANSFORMED_TUNABLE=2 };

// #anon_enum$SIM_PAUSE=0$SIM_CONTINUE=1
// file ../R2013a/simulink/include/simstruc.h line 591
enum anonymous$22 { SIM_PAUSE=0, SIM_CONTINUE=1 };

// #anon_enum$SL_JM_BD_AUTO=0$SL_JM_BD_SPARSE_PERTURBATION=1$SL_JM_BD_FULL_PERTURBATION=2$SL_JM_BD_SPARSE_ANALYTICAL=3$SL_JM_BD_FULL_ANALYTICAL=4
// file ../R2013a/simulink/include/rtw_solver.h line 33
enum anonymous$26 { SL_JM_BD_AUTO=0, SL_JM_BD_SPARSE_PERTURBATION=1, SL_JM_BD_FULL_PERTURBATION=2, SL_JM_BD_SPARSE_ANALYTICAL=3, SL_JM_BD_FULL_ANALYTICAL=4 };

// #anon_enum$SOLVER_MODE_AUTO=0$SOLVER_MODE_SINGLETASKING=1$SOLVER_MODE_MULTITASKING=2
// file ../R2013a/simulink/include/rtw_continuous.h line 22
enum anonymous$13 { SOLVER_MODE_AUTO=0, SOLVER_MODE_SINGLETASKING=1, SOLVER_MODE_MULTITASKING=2 };

// #anon_enum$SS_DOUBLE=0$SS_SINGLE=1$SS_INT8=2$SS_UINT8=3$SS_INT16=4$SS_UINT16=5$SS_INT32=6$SS_UINT32=7$SS_BOOLEAN=8
// file ../R2013a/simulink/include/sl_types_def.h line 18
enum anonymous$17 { SS_DOUBLE=0, SS_SINGLE=1, SS_INT8=2, SS_UINT8=3, SS_INT16=4, SS_UINT16=5, SS_INT32=6, SS_UINT32=7, SS_BOOLEAN=8 };

// #anon_enum$SS_DWORK_USED_AS_DWORK=0$SS_DWORK_USED_AS_DSTATE=1$SS_DWORK_USED_AS_SCRATCH=2$SS_DWORK_USED_AS_MODE=3
// file ../R2013a/simulink/include/simstruc_types.h line 197
enum anonymous$42 { SS_DWORK_USED_AS_DWORK=0, SS_DWORK_USED_AS_DSTATE=1, SS_DWORK_USED_AS_SCRATCH=2, SS_DWORK_USED_AS_MODE=3 };

// #anon_enum$SS_MATRIX_NONE=0$SS_MATRIX_CONSTANT=1$SS_MATRIX_TIMEDEP=2$SS_MATRIX_STATEDEP=3
// file ../R2013a/simulink/include/rtw_continuous.h line 15
enum anonymous$21 { SS_MATRIX_NONE=0, SS_MATRIX_CONSTANT=1, SS_MATRIX_TIMEDEP=2, SS_MATRIX_STATEDEP=3 };

// #anon_enum$SS_RTWGEN_UNKNOWN=0$SS_RTWGEN_RTW_CODE=1$SS_RTWGEN_ACCELERATOR=2$SS_RTWGEN_MODELREFERENCE_SIM_TARGET=3$SS_RTWGEN_MODELREFERENCE_RTW_TARGET=4
// file ../R2013a/simulink/include/simstruc_types.h line 64
enum anonymous$20 { SS_RTWGEN_UNKNOWN=0, SS_RTWGEN_RTW_CODE=1, SS_RTWGEN_ACCELERATOR=2, SS_RTWGEN_MODELREFERENCE_SIM_TARGET=3, SS_RTWGEN_MODELREFERENCE_RTW_TARGET=4 };

// #anon_enum$SS_SIMMODE_NORMAL=0$SS_SIMMODE_SIZES_CALL_ONLY=1$SS_SIMMODE_RTWGEN=2$SS_SIMMODE_EXTERNAL=3
// file ../R2013a/simulink/include/simstruc_types.h line 46
enum anonymous$4 { SS_SIMMODE_NORMAL=0, SS_SIMMODE_SIZES_CALL_ONLY=1, SS_SIMMODE_RTWGEN=2, SS_SIMMODE_EXTERNAL=3 };

// tag-#anon#ST[*{V}$V$'blockIO'||*{cV}$cV$'constBlockIO'||*{V}$V$'defaultParam'||*{U8}$U8$'prevZCSigState'||*{F64}$F64$'contStates'||*{F64}$F64$'derivs'||*{V}$V$'zcSignalValues'||*{V}$V$'inputs'||*{V}$V$'outputs'||*{U8}$U8$'contStateDisabled'||U8'zCCacheNeedsReset'||U8'derivCacheNeedsReset'||U8'blkStateChange'||U40'$pad0'||*{V}$V$'dwork'|]
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.h line 889
struct anonymous$12;

// tag-#anon#ST[*{cV}$cV$'mappingInfo'||*{V}$V$'xpcData'|]
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.h line 937
struct anonymous$25;

// tag-#anon#ST[ARR4{U32}$U32$'checksums'||U32'options'||S32'numContStates'||S32'numU'||S32'numY'||S32'numSampTimes'||S32'numBlocks'||S32'numBlockIO'||S32'numBlockPrms'||S32'numDwork'||S32'numSFcnPrms'||S32'numSFcns'||S32'numIports'||S32'numOports'||S32'numNonSampZCs'||S32'sysDirFeedThru'||S32'rtwGenSfcn'|]
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.h line 912
struct anonymous$24;

// tag-#anon#ST[BF{U32}$U32$'DisableBoundsChecking'||BF{U32}$U32$'ExtModeUpload'||BF{U32}$U32$'rtwIdMustResolveToSignalObject'||BF{U32}$U32$'rtwIdDoneResolve'||BF{U32}$U32$'ensureResetForSizeVary'||BF{U32}$U32$'minMaxCheckpoint'||BF{U32}$U32$'optimizeInIR'||BF{U32}$U32$'reserved7'||BF{U32}$U32$'reserved16'|]
// file ../R2013a/simulink/include/simstruc.h line 920
struct anonymous$51;

// tag-#anon#ST[BF{U32}$U32$'alreadyWarned'||BF{U32}$U32$'reserved15'||BF{U32}$U32$'reserved16'|]
// file ../R2013a/simulink/include/simstruc.h line 2244
struct anonymous$34;

// tag-#anon#ST[BF{U32}$U32$'hasMdlDimensionsFcn'||BF{U32}$U32$'usesNumPorts'||BF{U32}$U32$'vectMode'||BF{U32}$U32$'blockReduction'||BF{U32}$U32$'treatAsAtomic'||BF{U32}$U32$'rtwcg'||BF{U32}$U32$'needAbsoluteTime'||BF{U32}$U32$'explicitFCSSCtrl'||BF{U32}$U32$'modelRefTsInhSupLevel'||BF{U32}$U32$'needElapseTime'||BF{U32}$U32$'hasSubFunctions'||BF{U32}$U32$'callsOutputInInit'||BF{U32}$U32$'disableMdlProjection'||BF{U32}$U32$'modelRefNormalModeSupport'||BF{U32}$U32$'simStateCompliance'||BF{U32}$U32$'simStateVisibility'||BF{U32}$U32$'disableMdlSlvrJacobian'||BF{U32}$U32$'isRapidAcceleratorActive'||BF{U32}$U32$'isConcurrentTasks'||BF{U32}$U32$'usesCustomCodeFcns'||BF{U32}$U32$'reserved'|]
// file ../R2013a/simulink/include/simstruc.h line 826
struct anonymous$49;

// tag-#anon#ST[BF{U32}$U32$'optimOpts'||BF{U32}$U32$'frameData'||BF{U32}$U32$'cToMergeBlk'||BF{U32}$U32$'constOutputExprInRTW'||BF{U32}$U32$'outputExprInRTW'||BF{U32}$U32$'trivialOutputExprInRTW'||BF{U32}$U32$'okToMerge'||BF{U32}$U32$'cecId'||BF{U32}$U32$'nonContPort'||BF{U32}$U32$'dimensionsMode'||BF{U32}$U32$'fedByBlockWithModesNoZCs'||BF{U32}$U32$'busMode'||BF{U32}$U32$'optimizeInIR'||BF{U32}$U32$'reserved13'|]
// file ../R2013a/simulink/include/simstruc.h line 1007
struct anonymous$5;

// tag-#anon#ST[BF{U32}$U32$'overWritable'||BF{U32}$U32$'optimOpts'||BF{U32}$U32$'frameData'||BF{U32}$U32$'contiguity'||BF{U32}$U32$'acceptExprInRTW'||BF{U32}$U32$'cinId'||BF{U32}$U32$'nonDerivPort'||BF{U32}$U32$'dimensionsMode'||BF{U32}$U32$'busMode'||BF{U32}$U32$'optimizeInIR'||BF{U32}$U32$'reserved1'||BF{U32}$U32$'reserved16'|]
// file ../R2013a/simulink/include/simstruc.h line 973
struct anonymous$2;

// tag-#anon#ST[BF{U32}$U32$'zcCacheNeedsReset'||BF{U32}$U32$'derivCacheNeedsReset'||BF{U32}$U32$'blkStateChange'||BF{U32}$U32$'reserved_1'||BF{U32}$U32$'forceSfcnExceptionHandling'||BF{U32}$U32$'inlineParameters'||BF{U32}$U32$'solverAssertCheck'||BF{U32}$U32$'minStepViolatedError'||BF{U32}$U32$'reservedone'||BF{U32}$U32$'noZCStateUpdate'||BF{U32}$U32$'computingJacobian'||BF{U32}$U32$'solverCheckingCIC'||BF{U32}$U32$'errorStatusIsMsg'||BF{U32}$U32$'timeTweakWarn'||BF{U32}$U32$'solverRequestingReset'||BF{U32}$U32$'firstInitCondCalled'||BF{U32}$U32$'sparseSlvrJacobian'||BF{U32}$U32$'frameUpgradeWarn'||BF{U32}$U32$'outputMethodComputed'||BF{U32}$U32$'reserved15'|]
// file ../R2013a/simulink/include/simstruc.h line 1653
struct anonymous$11;

// tag-#anon#ST[F64'stepSize'||U32'clockTick0'||U32'clockTickH0'||F64'stepSize0'||F64'tStart'||F64'tFinal'||F64'timeOfLastOutput'||*{V}$V$'timingData'||*{F64}$F64$'varNextHitTimesList'||EN#anon_enum$MINOR_TIME_STEP=0$MAJOR_TIME_STEP=1#{U32}$U32$'simTimeStep'||U8'stopRequestedFlag'||U24'$pad0'||*{F64}$F64$'sampleTimes'||*{F64}$F64$'offsetTimes'||*{S32}$S32$'sampleTimeTaskIDPtr'||*{S32}$S32$'sampleHits'||*{S32}$S32$'perTaskSampleHits'||*{F64}$F64$'t'||ARR1{F64}$F64$'sampleTimesArray'||ARR1{F64}$F64$'offsetTimesArray'||ARR1{S32}$S32$'sampleTimeTaskIDArray'||ARR1{S32}$S32$'sampleHitArray'||ARR1{S32}$S32$'perTaskSampleHitsArray'||U32'$pad1'||ARR1{F64}$F64$'tArray'|]
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.h line 947
struct anonymous$19;

// tag-#anon#ST[S32'sfEvent'||S8'OrbitalState_Position'||S8'OrbitalState_Velocity'||S8'OrbitalState_Attitude'||S8'OrbitalState_Time'||S8'InertialNavigation_AbsolutePosi'||S8'InertialNavigation_AbsoluteAtti'||S8'InertialNavigation_AbsoluteVelo'||S8'GPS_AbsoluteVelocity'||S8'GPS_AbsoluteTime'||S8'StarPlanetTracker_AbsoluteAttit'||S8'StarPlanetTracker_AbsolutePosit'||S8'StarPlanetTracker_AbsoluteTime'||S8'StarPlanetTracker_AbsoluteVeloc'||S8'GPS_AbsolutePosition'||S8'dockingSensor_RelativePosition'||S8'dockingSensor_RelativeVelocity'||S8'dockingSensor_RelativeAttitude'||S8'dockingSensor_targetState'||S8'thrust_status'||S8'fuel_status'||S8'DockingApproach_timer'||S8'CaptureApproach_timer'||S8'latch_status'||S8'LatchCapture_timer'||S8'dockingSensor_timer'||S8'InertialNavigation_timer'||S8'StarPlanetTracker_timer'||S8'GPS_timer'||U8'is_active_c1_DockingApproachExa'||U8'is_active_fuel'||U8'is_active_thrust'||U8'is_MissionPhaseStates'||U8'is_active_MissionPhaseStates'||U8'is_DockingApproach'||U8'is_active_DockingApproach'||U8'is_dockingSensor'||U8'is_active_dockingSensor'||U8'is_CaptureApproach'||U8'is_active_CaptureApproach'||U8'is_active_OrbitalState_Active'||U8'is_active_OrbitalState_Complex'||U8'is_OrbitalState'||U8'is_active_OrbitalState'||U8'is_OrbitalState2'||U8'is_active_OrbitalState2'||U8'is_GPS'||U8'is_active_GPS'||U8'is_StarPlanetTracker'||U8'is_active_StarPlanetTracker'||U8'is_InertialNavigation'||U8'is_active_InertialNavigation'||U8'is_LatchCaptureCheck'||U8'is_active_LatchCaptureCheck'||U8'is_latch'||U8'is_active_latch'||U8'VALID'|]
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.h line 771
struct anonymous$0;

// tag-#anon#ST[S32'sizeInBytes'||U32'$pad0'||*{S8}$S8$'pCurrVal'||*{S8}$S8$'pPrevVal'|]
// file ../R2013a/simulink/include/simstruc.h line 1593
struct anonymous$14;

// tag-#anon#ST[S32'stopExecutionFlag'||S32'isrOverrun'||ARR1{S32}$S32$'overrunFlags'||ARR1{S32}$S32$'eventFlags'||*{cS8}$cS8$'errmsg'|]
// file ../R2013a/rtw/c/grt/classic_main.c line 156
struct anonymous$31;

// tag-#anon#ST[S8'GroundTrack_OrbitalPosition'||S8'GroundTrack_OrbitalVelocity'||S8'dockVisibility_status'||U8'opticsAvailability_status'||U8'sunlight_status'||S8'GPS_satelliteVisibility_status'||U8'GPS_receiverAvailability_status'||S8'StarPlanetTracker_planetVisibil'||S8'StarPlanetTracker_starVisibilit'||U8'InertialNavigation_time'||S8'GroundTrack_Time'||S8'RealTimeClock_time'||S8'StageTransition'|]
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.h line 832
struct anonymous$1;

// tag-#anon#ST[SYM#tag-#anon#ST[U32'wordH'||U32'wordL'|]#'words'|]
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.h line 33
struct anonymous$39;

// tag-#anon#ST[SYM#tag-#anon#ST[U32'wordL'||U32'wordH'|]#'words'|]
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.h line 40
struct anonymous$45;

// tag-#anon#ST[SYM#tag-#anon#UN[F32'wordLreal'||U32'wordLuint'|]#'wordL'|]
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.h line 47
struct anonymous$41;

// tag-#anon#ST[SYM#tag-_ssSFcnModelMethods#'sFcn'|]
// file ../R2013a/simulink/include/simstruc.h line 2318
struct anonymous$16;

// tag-#anon#ST[U32'lsw'||U32'msw'|]
// file ../R2013a/rtw/c/grt/cbmc_math.c line 41
struct anonymous$32;

// tag-#anon#ST[U32'wordH'||U32'wordL'|]
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.h line 34
struct anonymous$37;

// tag-#anon#ST[U32'wordL'||U32'wordH'|]
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.h line 41
struct anonymous$43;

// tag-#anon#ST[U64'w'|]
// file ../R2013a/rtw/c/grt/cbmc_math.c line 46
struct anonymous$35;

// tag-#anon#ST[U8'CaptureApproachComplete'||U8'DockingApproachComplete'||U8'AttemptingToDock'||U8'LatchCaptureComplete'||U8'DockingApproach'||U8'ApproachOrbitComplete'||U8'FarApproachComplete'||U8'ProximityOperationsComplete'||U8'FailedApproach'||U8'JointMission'||U8'CaptureApproachFailed'|]
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.h line 849
struct anonymous$3;

// tag-#anon#UN[*{*{cS8}$cS8$}$*{cS8}$cS8$$'cptr'||*{*{S8}$S8$}$*{S8}$S8$$'ptr'|]
// file ../R2013a/simulink/include/rtw_matlogging.h line 48
union anonymous$30;

// tag-#anon#UN[*{P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$)->V}$P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$)->V$'level2'||*{P(*{F64}$F64$|*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$)->V}$P(*{F64}$F64$|*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$)->V$'level1'|]
// file ../R2013a/simulink/include/simstruc.h line 2110
union anonymous$50;

// tag-#anon#UN[*{P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$)->V}$P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$)->V$'level2'||*{P(*{F64}$F64$|*{cF64}$cF64$|*{cF64}$cF64$|*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32)->V}$P(*{F64}$F64$|*{cF64}$cF64$|*{cF64}$cF64$|*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32)->V$'level1'|]
// file ../R2013a/simulink/include/simstruc.h line 2132
union anonymous$54;

// tag-#anon#UN[*{P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32)->V}$P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32)->V$'level2'||*{P(*{F64}$F64$|*{cF64}$cF64$|*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32)->V}$P(*{F64}$F64$|*{cF64}$cF64$|*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32)->V$'level1'|]
// file ../R2013a/simulink/include/simstruc.h line 2127
union anonymous$53;

// tag-#anon#UN[*{P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32)->V}$P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32)->V$'level2'||*{P(*{F64}$F64$|*{cF64}$cF64$|*{cF64}$cF64$|*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32)->V}$P(*{F64}$F64$|*{cF64}$cF64$|*{cF64}$cF64$|*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32)->V$'level1'|]
// file ../R2013a/simulink/include/simstruc.h line 2122
union anonymous$52;

// tag-#anon#UN[*{P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32|S32)->V}$P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32|S32)->V$'mdlSetInputPortComplexSignal'||*{P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$)->V}$P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$)->V$'mdlEnable'|]
// file ../R2013a/simulink/include/simstruc.h line 2140
union anonymous$57;

// tag-#anon#UN[*{P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32|S32)->V}$P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32|S32)->V$'mdlSetInputPortWidth'||*{P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32|*{cSYM#tag-DimsInfo_tag#}$cSYM#tag-DimsInfo_tag#$)->V}$P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32|*{cSYM#tag-DimsInfo_tag#}$cSYM#tag-DimsInfo_tag#$)->V$'mdlSetInputPortDims'|]
// file ../R2013a/simulink/include/simstruc.h line 2089
union anonymous$47;

// tag-#anon#UN[*{P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32|S32)->V}$P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32|S32)->V$'mdlSetOutputPortComplexSignal'||*{P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$)->V}$P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$)->V$'mdlDisable'|]
// file ../R2013a/simulink/include/simstruc.h line 2146
union anonymous$58;

// tag-#anon#UN[*{P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32|S32)->V}$P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32|S32)->V$'mdlSetOutputPortWidth'||*{P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32|*{cSYM#tag-DimsInfo_tag#}$cSYM#tag-DimsInfo_tag#$)->V}$P(*{SYM#tag-SimStruct_tag#}$SYM#tag-SimStruct_tag#$|S32|*{cSYM#tag-DimsInfo_tag#}$cSYM#tag-DimsInfo_tag#$)->V$'mdlSetOutputPortDims'|]
// file ../R2013a/simulink/include/simstruc.h line 2094
union anonymous$48;

// tag-#anon#UN[*{SYM#tag-_ssDWorkRecord#}$SYM#tag-_ssDWorkRecord#$'sfcn'||*{V}$V$'root'|]
// file ../R2013a/simulink/include/simstruc.h line 1084
union anonymous$28;

// tag-#anon#UN[*{V}$V$'vect'||*{c*{cF64}$cF64$}$c*{cF64}$cF64$$'uPtrs'|]
// file ../R2013a/simulink/include/simstruc.h line 2234
union anonymous$29;

// tag-#anon#UN[*{c*{cS8}$cS8$}$c*{cS8}$cS8$$'cptr'||*{*{S8}$S8$}$*{S8}$S8$$'ptr'|]
// file ../R2013a/simulink/include/rtw_matlogging.h line 81
union anonymous$36;

// tag-#anon#UN[*{cS8}$cS8$'str'||*{V}$V$'msg'|]
// file ../R2013a/simulink/include/simstruc.h line 2282
union anonymous$8;

// tag-#anon#UN[*{cSYM#tag-RTWLogSignalInfo_tag#}$cSYM#tag-RTWLogSignalInfo_tag#$'cptr'||*{SYM#tag-RTWLogSignalInfo_tag#}$SYM#tag-RTWLogSignalInfo_tag#$'ptr'|]
// file ../R2013a/simulink/include/rtw_matlogging.h line 116
union anonymous$40;

// tag-#anon#UN[*{cV}$cV$'vect'||*{c*{cV}$cV$}$c*{cV}$cV$$'ptrs'|]
// file ../R2013a/simulink/include/simstruc.h line 966
union anonymous$56;

// tag-#anon#UN[F32'wordLreal'||U32'wordLuint'|]
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.h line 48
union anonymous$46;

// tag-#anon#UN[F64'value'||SYM#tag-#anon#ST[U32'lsw'||U32'msw'|]#'parts'||SYM#tag-#anon#ST[U64'w'|]#'xparts'|]
// file ../R2013a/rtw/c/grt/cbmc_math.c line 38
union anonymous$55;

// tag-#anon#UN[S32'numInputPorts'||S32'numU'|]
// file ../R2013a/simulink/include/simstruc.h line 768
union anonymous$44;

// tag-#anon#UN[S32'numOutputPorts'||S32'numY'|]
// file ../R2013a/simulink/include/simstruc.h line 761
union anonymous$38;

// tag-#anon#UN[S32'numRtp'||*{V}$V$'placeholder'|]
// file ../R2013a/simulink/include/simstruc.h line 1069
union anonymous$9;

// tag-DimsInfo_tag
// file ../R2013a/simulink/include/simstruc_types.h line 160
struct DimsInfo_tag;

// tag-RTWLogDataTypeConvert_tag
// file ../R2013a/simulink/include/rtw_matlogging.h line 21
struct RTWLogDataTypeConvert_tag;

// tag-RTWLogSignalInfo_tag
// file ../R2013a/simulink/include/rtw_matlogging.h line 36
struct RTWLogSignalInfo_tag;

// tag-SimStruct_tag
// file ../R2013a/simulink/include/simstruc.h line 141
struct SimStruct_tag;

// tag-SparseHeader_Tag
// file ../R2013a/simulink/include/simstruc_types.h line 227
struct SparseHeader_Tag;

// tag-_IO_FILE
// file /usr/include/stdio.h line 44
struct _IO_FILE;

// tag-_IO_marker
// file /usr/include/libio.h line 160
struct _IO_marker;

// tag-_RTWExtModeInfo_tag
// file ../R2013a/simulink/include/rtw_extmode.h line 17
struct _RTWExtModeInfo_tag;

// tag-_RTWLogInfo_tag
// file ../R2013a/simulink/include/rtw_matlogging.h line 77
struct _RTWLogInfo_tag;

// tag-_RTWRTModelMethodsInfo_tag
// file ../R2013a/simulink/include/rtw_continuous.h line 56
struct _RTWRTModelMethodsInfo_tag;

// tag-_rtTimingBridge_tag
// file ../R2013a/simulink/include/simstruc_types.h line 94
struct _rtTimingBridge_tag;

// tag-_ssBlkInfo
// file ../R2013a/simulink/include/simstruc.h line 1132
struct _ssBlkInfo;

// tag-_ssBlkInfo2
// file ../R2013a/simulink/include/simstruc.h line 1124
struct _ssBlkInfo2;

// tag-_ssCallSys
// file ../R2013a/simulink/include/simstruc.h line 1802
struct _ssCallSys;

// tag-_ssConstraintsInfo
// file ../R2013a/simulink/include/simstruc.h line 2074
struct _ssConstraintsInfo;

// tag-_ssDWorkAuxRecord
// file ../R2013a/simulink/include/simstruc.h line 916
struct _ssDWorkAuxRecord;

// tag-_ssDWorkRecord
// file ../R2013a/simulink/include/simstruc_types.h line 209
struct _ssDWorkRecord;

// tag-_ssInPortVarDims
// file ../R2013a/simulink/include/simstruc.h line 1097
struct _ssInPortVarDims;

// tag-_ssMassMatrixInfo
// file ../R2013a/simulink/include/simstruc.h line 2065
struct _ssMassMatrixInfo;

// tag-_ssMdlInfo
// file ../R2013a/simulink/include/simstruc.h line 1615
struct _ssMdlInfo;

// tag-_ssOutPortVarDims
// file ../R2013a/simulink/include/simstruc.h line 1105
struct _ssOutPortVarDims;

// tag-_ssPortInfo
// file ../R2013a/simulink/include/simstruc.h line 1036
struct _ssPortInfo;

// tag-_ssPortInfo2
// file ../R2013a/simulink/include/simstruc.h line 1114
struct _ssPortInfo2;

// tag-_ssPortInputs
// file ../R2013a/simulink/include/simstruc.h line 958
struct _ssPortInputs;

// tag-_ssPortOutputs
// file ../R2013a/simulink/include/simstruc.h line 998
struct _ssPortOutputs;

// tag-_ssRegDataType
// file ../R2013a/simulink/include/simstruc.h line 1848
struct _ssRegDataType;

// tag-_ssResolveCBK
// file ../R2013a/simulink/include/simstruc.h line 1819
struct _ssResolveCBK;

// tag-_ssSFcnModelMethods
// file ../R2013a/simulink/include/simstruc.h line 2082
struct _ssSFcnModelMethods;

// tag-_ssSFcnModelMethods2
// file ../R2013a/simulink/include/simstruc.h line 2172
struct _ssSFcnModelMethods2;

// tag-_ssSFcnModelMethods3
// file ../R2013a/simulink/include/simstruc.h line 2159
struct _ssSFcnModelMethods3;

// tag-_ssSFcnParams
// file ../R2013a/simulink/include/simstruc.h line 1061
struct _ssSFcnParams;

// tag-_ssSizes
// file ../R2013a/simulink/include/simstruc.h line 758
struct _ssSizes;

// tag-_ssSolverInfo_tag
// file ../R2013a/simulink/include/rtw_solver.h line 42
struct _ssSolverInfo_tag;

// tag-_ssStInfo
// file ../R2013a/simulink/include/simstruc.h line 1879
struct _ssStInfo;

// tag-_ssStates
// file ../R2013a/simulink/include/simstruc.h line 2233
struct _ssStates;

// tag-_ssStatesInfo2
// file ../R2013a/simulink/include/simstruc.h line 2225
struct _ssStatesInfo2;

// tag-_ssWork
// file ../R2013a/simulink/include/simstruc.h line 1077
struct _ssWork;

// tag-ssParamRec_tag
// file ../R2013a/simulink/include/sl_common_types_def.h line 194
struct ssParamRec_tag;

// tag-ssSparseMatrixInfo_tag
// file ../R2013a/simulink/include/simstruc.h line 737
struct ssSparseMatrixInfo_tag;

// tag-tag_RTM_DockingApproachExampl_T
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext_types.h line 20
struct tag_RTM_DockingApproachExampl_T;

#include <assert.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef IEEE_FLOAT_EQUAL
#define IEEE_FLOAT_EQUAL(x,y) ((x)==(y))
#endif
#ifndef IEEE_FLOAT_NOTEQUAL
#define IEEE_FLOAT_NOTEQUAL(x,y) ((x)!=(y))
#endif

// D_exit_internal_CaptureApproach
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 102
static void D_exit_internal_CaptureApproach(void);
// D_exit_internal_DockingApproach
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 996
static void D_exit_internal_DockingApproach(void);
// DockingAppr_OrbitalState_Active
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 277
static void DockingAppr_OrbitalState_Active(void);
// DockingAppro_InertialNavigation
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 149
static void DockingAppro_InertialNavigation(void);
// DockingAppro_MissionPhaseStates
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 1550
static void DockingAppro_MissionPhaseStates(void);
// DockingApproachExample_Ext
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2352
struct tag_RTM_DockingApproachExampl_T * DockingApproachExample_Ext(void);
// DockingApproachExample_Ext_initialize
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2176
void DockingApproachExample_Ext_initialize(void);
// DockingApproachExample_Ext_output
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2123
static void DockingApproachExample_Ext_output(void);
// DockingApproachExample_Ext_terminate
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2303
void DockingApproachExample_Ext_terminate(void);
// DockingApproachExample_Ext_update
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2153
static void DockingApproachExample_Ext_update(void);
// DockingApproach_DockingApproach
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 1136
static void DockingApproach_DockingApproach(void);
// MdlInitialize
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2337
void MdlInitialize(void);
// MdlInitializeSampleTimes
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2333
void MdlInitializeSampleTimes(void);
// MdlInitializeSizes
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2329
void MdlInitializeSizes(void);
// MdlOutputs
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2311
void MdlOutputs(signed int tid);
// MdlStart
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2341
void MdlStart(void);
// MdlTerminate
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2346
void MdlTerminate(void);
// MdlUpdate
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2320
void MdlUpdate(signed int tid);
// _Learn_assert
// file ../R2013a/rtw/c/grt/classic_main.c line 29
void _Learn_assert(_Bool);
// ceil
// file ../R2013a/rtw/c/grt/cbmc_math.c line 93
extern double ceil(double x);
// displayUsage
// file ../R2013a/rtw/c/grt/classic_main.c line 383
static void displayUsage(void);
// enter_internal_OrbitalState_Act
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 1039
static void enter_internal_OrbitalState_Act(void);
// exit
// file /usr/include/stdlib.h line 543
extern void exit(signed int);
// floor
// file ../R2013a/rtw/c/grt/cbmc_math.c line 135
extern double floor(double x);
// fmod
// file ../R2013a/rtw/c/grt/cbmc_math.c line 237
extern double fmod(double a, double n);
// fprintf
// file /usr/include/stdio.h line 356
extern signed int fprintf(struct _IO_FILE *, const char *, ...);
// nondet_double
// file ../R2013a/rtw/c/grt/classic_main.c line 490 function main
signed int nondet_double(void);
// printf
// file /usr/include/stdio.h line 362
extern signed int printf(const char *, ...);
// rtGetInf
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rtGetInf.h line 23
extern double rtGetInf(void);
// rtGetInfF
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rtGetInf.h line 24
extern float rtGetInfF(void);
// rtGetMinusInf
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rtGetInf.h line 25
extern double rtGetMinusInf(void);
// rtGetMinusInfF
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rtGetInf.h line 26
extern float rtGetMinusInfF(void);
// rtGetNaN
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rtGetNaN.c line 28
extern double rtGetNaN(void);
// rtGetNaNF
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rtGetNaN.c line 76
extern float rtGetNaNF(void);
// rtIsInf
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 49
extern unsigned char rtIsInf(double value);
// rtIsInfF
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 55
extern unsigned char rtIsInfF(float value);
// rtIsNaN
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 61
extern unsigned char rtIsNaN(double value);
// rtIsNaNF
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 67
extern unsigned char rtIsNaNF(float value);
// rt_InitInfAndNaN
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 37
extern void rt_InitInfAndNaN(unsigned long int realSize);
// rt_ODECreateIntegrationData
// file ../R2013a/rtw/c/grt/classic_main.c line 672
void rt_ODECreateIntegrationData(struct _ssSolverInfo_tag *si);
// rt_ODEUpdateContinuousStates
// file ../R2013a/rtw/c/grt/classic_main.c line 675
void rt_ODEUpdateContinuousStates(struct _ssSolverInfo_tag *si);
// rt_OneStep
// file ../R2013a/rtw/c/grt/classic_main.c line 193
static void rt_OneStep(struct tag_RTM_DockingApproachExampl_T *S);
// rt_SimGetNextSampleHit
// file ../R2013a/rtw/c/src/rt_sim.c line 278
extern double rt_SimGetNextSampleHit(void);
// rt_SimInitTimingEngine
// file ../R2013a/rtw/c/src/rt_sim.c line 87
extern const char * rt_SimInitTimingEngine(signed int rtmNumSampTimes, double rtmStepSize, double *rtmSampleTimePtr, double *rtmOffsetTimePtr, signed int *rtmSampleHitPtr, signed int *rtmSampleTimeTaskIDPtr, double rtmTStart, enum anonymous$10 *rtmSimTimeStepPtr, void **rtmTimingDataPtr);
// rt_SimUpdateDiscreteTaskSampleHits
// file ../R2013a/rtw/c/src/rt_sim.c line 332
extern void rt_SimUpdateDiscreteTaskSampleHits(signed int rtmNumSampTimes, void *rtmTimingData, signed int *rtmSampleHitPtr, double *rtmTPtr);
// rt_StartDataLogging
// file ../R2013a/rtw/c/src/rt_mock_logging.c line 5
const char * rt_StartDataLogging(struct _RTWLogInfo_tag *li, const double finalTime, const double stepSize, const char **errStatus);
// rt_StopDataLogging
// file ../R2013a/rtw/c/src/rt_mock_logging.c line 6
void rt_StopDataLogging(const char *file, struct _RTWLogInfo_tag *li);
// rt_UpdateSigLogVars
// file ../R2013a/rtw/c/src/rt_mock_logging.c line 4
void rt_UpdateSigLogVars(struct _RTWLogInfo_tag *li, double *tPtr);
// rt_UpdateTXYLogVars
// file ../R2013a/rtw/c/src/rt_mock_logging.c line 3
const char * rt_UpdateTXYLogVars(struct _RTWLogInfo_tag *li, double *tPtr);
// space_dummy_bool
// file ../R2013a/rtw/c/grt/classic_main.c line 31
void space_dummy_bool(void);
// sscanf
// file /usr/include/stdio.h line 433
extern signed int sscanf(const char *, const char *, ...);
// strcmp
// file /usr/include/string.h line 140
extern signed int strcmp(const char *, const char *);

struct anonymous$12
{
  // blockIO
  void *blockIO;
  // constBlockIO
  const void *constBlockIO;
  // defaultParam
  void *defaultParam;
  // prevZCSigState
  unsigned char *prevZCSigState;
  // contStates
  double *contStates;
  // derivs
  double *derivs;
  // zcSignalValues
  void *zcSignalValues;
  // inputs
  void *inputs;
  // outputs
  void *outputs;
  // contStateDisabled
  unsigned char *contStateDisabled;
  // zCCacheNeedsReset
  unsigned char zCCacheNeedsReset;
  // derivCacheNeedsReset
  unsigned char derivCacheNeedsReset;
  // blkStateChange
  unsigned char blkStateChange;
  // dwork
  void *dwork;
};

struct anonymous$25
{
  // mappingInfo
  const void *mappingInfo;
  // xpcData
  void *xpcData;
};

struct anonymous$24
{
  // checksums
  unsigned int checksums[4l];
  // options
  unsigned int options;
  // numContStates
  signed int numContStates;
  // numU
  signed int numU;
  // numY
  signed int numY;
  // numSampTimes
  signed int numSampTimes;
  // numBlocks
  signed int numBlocks;
  // numBlockIO
  signed int numBlockIO;
  // numBlockPrms
  signed int numBlockPrms;
  // numDwork
  signed int numDwork;
  // numSFcnPrms
  signed int numSFcnPrms;
  // numSFcns
  signed int numSFcns;
  // numIports
  signed int numIports;
  // numOports
  signed int numOports;
  // numNonSampZCs
  signed int numNonSampZCs;
  // sysDirFeedThru
  signed int sysDirFeedThru;
  // rtwGenSfcn
  signed int rtwGenSfcn;
};

struct anonymous$51
{
  // DisableBoundsChecking
  unsigned int DisableBoundsChecking : 1;
  // ExtModeUpload
  unsigned int ExtModeUpload : 1;
  // rtwIdMustResolveToSignalObject
  unsigned int rtwIdMustResolveToSignalObject : 2;
  // rtwIdDoneResolve
  unsigned int rtwIdDoneResolve : 1;
  // ensureResetForSizeVary
  unsigned int ensureResetForSizeVary : 1;
  // minMaxCheckpoint
  unsigned int minMaxCheckpoint : 2;
  // optimizeInIR
  unsigned int optimizeInIR : 1;
  // reserved7
  unsigned int reserved7 : 7;
  // reserved16
  unsigned int reserved16 : 16;
};

struct anonymous$34
{
  // alreadyWarned
  unsigned int alreadyWarned : 1;
  // reserved15
  unsigned int reserved15 : 15;
  // reserved16
  unsigned int reserved16 : 16;
};

struct anonymous$49
{
  // hasMdlDimensionsFcn
  unsigned int hasMdlDimensionsFcn : 1;
  // usesNumPorts
  unsigned int usesNumPorts : 1;
  // vectMode
  unsigned int vectMode : 4;
  // blockReduction
  unsigned int blockReduction : 1;
  // treatAsAtomic
  unsigned int treatAsAtomic : 1;
  // rtwcg
  unsigned int rtwcg : 1;
  // needAbsoluteTime
  unsigned int needAbsoluteTime : 1;
  // explicitFCSSCtrl
  unsigned int explicitFCSSCtrl : 1;
  // modelRefTsInhSupLevel
  unsigned int modelRefTsInhSupLevel : 2;
  // needElapseTime
  unsigned int needElapseTime : 1;
  // hasSubFunctions
  unsigned int hasSubFunctions : 1;
  // callsOutputInInit
  unsigned int callsOutputInInit : 1;
  // disableMdlProjection
  unsigned int disableMdlProjection : 1;
  // modelRefNormalModeSupport
  unsigned int modelRefNormalModeSupport : 2;
  // simStateCompliance
  unsigned int simStateCompliance : 4;
  // simStateVisibility
  unsigned int simStateVisibility : 1;
  // disableMdlSlvrJacobian
  unsigned int disableMdlSlvrJacobian : 1;
  // isRapidAcceleratorActive
  unsigned int isRapidAcceleratorActive : 1;
  // isConcurrentTasks
  unsigned int isConcurrentTasks : 1;
  // usesCustomCodeFcns
  unsigned int usesCustomCodeFcns : 1;
  // reserved
  unsigned int reserved : 4;
};

struct anonymous$5
{
  // optimOpts
  unsigned int optimOpts : 2;
  // frameData
  unsigned int frameData : 2;
  // cToMergeBlk
  unsigned int cToMergeBlk : 1;
  // constOutputExprInRTW
  unsigned int constOutputExprInRTW : 1;
  // outputExprInRTW
  unsigned int outputExprInRTW : 1;
  // trivialOutputExprInRTW
  unsigned int trivialOutputExprInRTW : 1;
  // okToMerge
  unsigned int okToMerge : 2;
  // cecId
  unsigned int cecId : 2;
  // nonContPort
  unsigned int nonContPort : 1;
  // dimensionsMode
  unsigned int dimensionsMode : 2;
  // fedByBlockWithModesNoZCs
  unsigned int fedByBlockWithModesNoZCs : 1;
  // busMode
  unsigned int busMode : 2;
  // optimizeInIR
  unsigned int optimizeInIR : 1;
  // reserved13
  unsigned int reserved13 : 13;
};

struct anonymous$2
{
  // overWritable
  unsigned int overWritable : 1;
  // optimOpts
  unsigned int optimOpts : 2;
  // frameData
  unsigned int frameData : 2;
  // contiguity
  unsigned int contiguity : 1;
  // acceptExprInRTW
  unsigned int acceptExprInRTW : 1;
  // cinId
  unsigned int cinId : 2;
  // nonDerivPort
  unsigned int nonDerivPort : 1;
  // dimensionsMode
  unsigned int dimensionsMode : 2;
  // busMode
  unsigned int busMode : 2;
  // optimizeInIR
  unsigned int optimizeInIR : 1;
  // reserved1
  unsigned int reserved1 : 1;
  // reserved16
  unsigned int reserved16 : 16;
};

struct anonymous$11
{
  // zcCacheNeedsReset
  unsigned int zcCacheNeedsReset : 1;
  // derivCacheNeedsReset
  unsigned int derivCacheNeedsReset : 1;
  // blkStateChange
  unsigned int blkStateChange : 1;
  // reserved_1
  unsigned int reserved_1 : 1;
  // forceSfcnExceptionHandling
  unsigned int forceSfcnExceptionHandling : 1;
  // inlineParameters
  unsigned int inlineParameters : 1;
  // solverAssertCheck
  unsigned int solverAssertCheck : 1;
  // minStepViolatedError
  unsigned int minStepViolatedError : 1;
  // reservedone
  unsigned int reservedone : 1;
  // noZCStateUpdate
  unsigned int noZCStateUpdate : 1;
  // computingJacobian
  unsigned int computingJacobian : 1;
  // solverCheckingCIC
  unsigned int solverCheckingCIC : 1;
  // errorStatusIsMsg
  unsigned int errorStatusIsMsg : 1;
  // timeTweakWarn
  unsigned int timeTweakWarn : 1;
  // solverRequestingReset
  unsigned int solverRequestingReset : 1;
  // firstInitCondCalled
  unsigned int firstInitCondCalled : 1;
  // sparseSlvrJacobian
  unsigned int sparseSlvrJacobian : 1;
  // frameUpgradeWarn
  unsigned int frameUpgradeWarn : 1;
  // outputMethodComputed
  unsigned int outputMethodComputed : 1;
  // reserved15
  unsigned int reserved15 : 13;
};

struct anonymous$19
{
  // stepSize
  double stepSize;
  // clockTick0
  unsigned int clockTick0;
  // clockTickH0
  unsigned int clockTickH0;
  // stepSize0
  double stepSize0;
  // tStart
  double tStart;
  // tFinal
  double tFinal;
  // timeOfLastOutput
  double timeOfLastOutput;
  // timingData
  void *timingData;
  // varNextHitTimesList
  double *varNextHitTimesList;
  // simTimeStep
  enum anonymous$10 simTimeStep;
  // stopRequestedFlag
  unsigned char stopRequestedFlag;
  // sampleTimes
  double *sampleTimes;
  // offsetTimes
  double *offsetTimes;
  // sampleTimeTaskIDPtr
  signed int *sampleTimeTaskIDPtr;
  // sampleHits
  signed int *sampleHits;
  // perTaskSampleHits
  signed int *perTaskSampleHits;
  // t
  double *t;
  // sampleTimesArray
  double sampleTimesArray[1l];
  // offsetTimesArray
  double offsetTimesArray[1l];
  // sampleTimeTaskIDArray
  signed int sampleTimeTaskIDArray[1l];
  // sampleHitArray
  signed int sampleHitArray[1l];
  // perTaskSampleHitsArray
  signed int perTaskSampleHitsArray[1l];
  // tArray
  double tArray[1l];
};

struct anonymous$0
{
  // sfEvent
  signed int sfEvent;
  // OrbitalState_Position
  signed char OrbitalState_Position;
  // OrbitalState_Velocity
  signed char OrbitalState_Velocity;
  // OrbitalState_Attitude
  signed char OrbitalState_Attitude;
  // OrbitalState_Time
  signed char OrbitalState_Time;
  // InertialNavigation_AbsolutePosi
  signed char InertialNavigation_AbsolutePosi;
  // InertialNavigation_AbsoluteAtti
  signed char InertialNavigation_AbsoluteAtti;
  // InertialNavigation_AbsoluteVelo
  signed char InertialNavigation_AbsoluteVelo;
  // GPS_AbsoluteVelocity
  signed char GPS_AbsoluteVelocity;
  // GPS_AbsoluteTime
  signed char GPS_AbsoluteTime;
  // StarPlanetTracker_AbsoluteAttit
  signed char StarPlanetTracker_AbsoluteAttit;
  // StarPlanetTracker_AbsolutePosit
  signed char StarPlanetTracker_AbsolutePosit;
  // StarPlanetTracker_AbsoluteTime
  signed char StarPlanetTracker_AbsoluteTime;
  // StarPlanetTracker_AbsoluteVeloc
  signed char StarPlanetTracker_AbsoluteVeloc;
  // GPS_AbsolutePosition
  signed char GPS_AbsolutePosition;
  // dockingSensor_RelativePosition
  signed char dockingSensor_RelativePosition;
  // dockingSensor_RelativeVelocity
  signed char dockingSensor_RelativeVelocity;
  // dockingSensor_RelativeAttitude
  signed char dockingSensor_RelativeAttitude;
  // dockingSensor_targetState
  signed char dockingSensor_targetState;
  // thrust_status
  signed char thrust_status;
  // fuel_status
  signed char fuel_status;
  // DockingApproach_timer
  signed char DockingApproach_timer;
  // CaptureApproach_timer
  signed char CaptureApproach_timer;
  // latch_status
  signed char latch_status;
  // LatchCapture_timer
  signed char LatchCapture_timer;
  // dockingSensor_timer
  signed char dockingSensor_timer;
  // InertialNavigation_timer
  signed char InertialNavigation_timer;
  // StarPlanetTracker_timer
  signed char StarPlanetTracker_timer;
  // GPS_timer
  signed char GPS_timer;
  // is_active_c1_DockingApproachExa
  unsigned char is_active_c1_DockingApproachExa;
  // is_active_fuel
  unsigned char is_active_fuel;
  // is_active_thrust
  unsigned char is_active_thrust;
  // is_MissionPhaseStates
  unsigned char is_MissionPhaseStates;
  // is_active_MissionPhaseStates
  unsigned char is_active_MissionPhaseStates;
  // is_DockingApproach
  unsigned char is_DockingApproach;
  // is_active_DockingApproach
  unsigned char is_active_DockingApproach;
  // is_dockingSensor
  unsigned char is_dockingSensor;
  // is_active_dockingSensor
  unsigned char is_active_dockingSensor;
  // is_CaptureApproach
  unsigned char is_CaptureApproach;
  // is_active_CaptureApproach
  unsigned char is_active_CaptureApproach;
  // is_active_OrbitalState_Active
  unsigned char is_active_OrbitalState_Active;
  // is_active_OrbitalState_Complex
  unsigned char is_active_OrbitalState_Complex;
  // is_OrbitalState
  unsigned char is_OrbitalState;
  // is_active_OrbitalState
  unsigned char is_active_OrbitalState;
  // is_OrbitalState2
  unsigned char is_OrbitalState2;
  // is_active_OrbitalState2
  unsigned char is_active_OrbitalState2;
  // is_GPS
  unsigned char is_GPS;
  // is_active_GPS
  unsigned char is_active_GPS;
  // is_StarPlanetTracker
  unsigned char is_StarPlanetTracker;
  // is_active_StarPlanetTracker
  unsigned char is_active_StarPlanetTracker;
  // is_InertialNavigation
  unsigned char is_InertialNavigation;
  // is_active_InertialNavigation
  unsigned char is_active_InertialNavigation;
  // is_LatchCaptureCheck
  unsigned char is_LatchCaptureCheck;
  // is_active_LatchCaptureCheck
  unsigned char is_active_LatchCaptureCheck;
  // is_latch
  unsigned char is_latch;
  // is_active_latch
  unsigned char is_active_latch;
  // VALID
  unsigned char VALID;
};

struct anonymous$14
{
  // sizeInBytes
  signed int sizeInBytes;
  // pCurrVal
  char *pCurrVal;
  // pPrevVal
  char *pPrevVal;
};

struct anonymous$31
{
  // stopExecutionFlag
  signed int stopExecutionFlag;
  // isrOverrun
  signed int isrOverrun;
  // overrunFlags
  signed int overrunFlags[1l];
  // eventFlags
  signed int eventFlags[1l];
  // errmsg
  const char *errmsg;
};

struct anonymous$1
{
  // GroundTrack_OrbitalPosition
  signed char GroundTrack_OrbitalPosition;
  // GroundTrack_OrbitalVelocity
  signed char GroundTrack_OrbitalVelocity;
  // dockVisibility_status
  signed char dockVisibility_status;
  // opticsAvailability_status
  unsigned char opticsAvailability_status;
  // sunlight_status
  unsigned char sunlight_status;
  // GPS_satelliteVisibility_status
  signed char GPS_satelliteVisibility_status;
  // GPS_receiverAvailability_status
  unsigned char GPS_receiverAvailability_status;
  // StarPlanetTracker_planetVisibil
  signed char StarPlanetTracker_planetVisibil;
  // StarPlanetTracker_starVisibilit
  signed char StarPlanetTracker_starVisibilit;
  // InertialNavigation_time
  unsigned char InertialNavigation_time;
  // GroundTrack_Time
  signed char GroundTrack_Time;
  // RealTimeClock_time
  signed char RealTimeClock_time;
  // StageTransition
  signed char StageTransition;
};

struct anonymous$37
{
  // wordH
  unsigned int wordH;
  // wordL
  unsigned int wordL;
};

struct anonymous$39
{
  // words
  struct anonymous$37 words;
};

struct anonymous$43
{
  // wordL
  unsigned int wordL;
  // wordH
  unsigned int wordH;
};

struct anonymous$45
{
  // words
  struct anonymous$43 words;
};

union anonymous$46
{
  // wordLreal
  float wordLreal;
  // wordLuint
  unsigned int wordLuint;
};

struct anonymous$41
{
  // wordL
  union anonymous$46 wordL;
};

union anonymous$47
{
  // mdlSetInputPortWidth
  void (*mdlSetInputPortWidth)(struct SimStruct_tag *, signed int, signed int);
  // mdlSetInputPortDims
  void (*mdlSetInputPortDims)(struct SimStruct_tag *, signed int, const struct DimsInfo_tag *);
};

union anonymous$48
{
  // mdlSetOutputPortWidth
  void (*mdlSetOutputPortWidth)(struct SimStruct_tag *, signed int, signed int);
  // mdlSetOutputPortDims
  void (*mdlSetOutputPortDims)(struct SimStruct_tag *, signed int, const struct DimsInfo_tag *);
};

union anonymous$50
{
  // level2
  void (*level2)(struct SimStruct_tag *);
  // level1
  void (*level1)(double *, struct SimStruct_tag *);
};

union anonymous$52
{
  // level2
  void (*level2)(struct SimStruct_tag *, signed int);
  // level1
  void (*level1)(double *, const double *, const double *, struct SimStruct_tag *, signed int);
};

union anonymous$53
{
  // level2
  void (*level2)(struct SimStruct_tag *, signed int);
  // level1
  void (*level1)(double *, const double *, struct SimStruct_tag *, signed int);
};

union anonymous$54
{
  // level2
  void (*level2)(struct SimStruct_tag *);
  // level1
  void (*level1)(double *, const double *, const double *, struct SimStruct_tag *, signed int);
};

union anonymous$57
{
  // mdlSetInputPortComplexSignal
  void (*mdlSetInputPortComplexSignal)(struct SimStruct_tag *, signed int, signed int);
  // mdlEnable
  void (*mdlEnable)(struct SimStruct_tag *);
};

union anonymous$58
{
  // mdlSetOutputPortComplexSignal
  void (*mdlSetOutputPortComplexSignal)(struct SimStruct_tag *, signed int, signed int);
  // mdlDisable
  void (*mdlDisable)(struct SimStruct_tag *);
};

struct _ssSFcnModelMethods
{
  // mdlInitializeSizes
  void (*mdlInitializeSizes)(struct SimStruct_tag *);
  // mdlGetInputPortWidthLevel1
  signed int (*mdlGetInputPortWidthLevel1)(struct SimStruct_tag *, signed int);
  // mdlGetOutputPortWidthLevel1
  signed int (*mdlGetOutputPortWidthLevel1)(struct SimStruct_tag *, signed int);
  // mdlSetInputPortDimensions
  union anonymous$47 mdlSetInputPortDimensions;
  // mdlSetOutputPortDimensions
  union anonymous$48 mdlSetOutputPortDimensions;
  // mdlSetInputPortDataType
  void (*mdlSetInputPortDataType)(struct SimStruct_tag *, signed int, signed int);
  // mdlSetOutputPortDataType
  void (*mdlSetOutputPortDataType)(struct SimStruct_tag *, signed int, signed int);
  // mdlInitializeSampleTimes
  void (*mdlInitializeSampleTimes)(struct SimStruct_tag *);
  // mdlSetInputPortSampleTime
  void (*mdlSetInputPortSampleTime)(struct SimStruct_tag *, signed int, double, double);
  // mdlSetOutputPortSampleTime
  void (*mdlSetOutputPortSampleTime)(struct SimStruct_tag *, signed int, double, double);
  // mdlSetWorkWidths
  void (*mdlSetWorkWidths)(struct SimStruct_tag *);
  // mdlRTW
  void (*mdlRTW)(struct SimStruct_tag *);
  // mdlInitializeConditions
  union anonymous$50 mdlInitializeConditions;
  // mdlStart
  void (*mdlStart)(struct SimStruct_tag *);
  // mdlCheckParameters
  void (*mdlCheckParameters)(struct SimStruct_tag *);
  // mdlProcessParameters
  void (*mdlProcessParameters)(struct SimStruct_tag *);
  // mdlGetTimeOfNextVarHit
  void (*mdlGetTimeOfNextVarHit)(struct SimStruct_tag *);
  // mdlOutputs
  union anonymous$52 mdlOutputs;
  // mdlUpdate
  union anonymous$53 mdlUpdate;
  // mdlDerivatives
  union anonymous$54 mdlDerivatives;
  // mdlZeroCrossings
  void (*mdlZeroCrossings)(struct SimStruct_tag *);
  // mdlTerminate
  void (*mdlTerminate)(struct SimStruct_tag *);
  // fcnInEnable
  union anonymous$57 fcnInEnable;
  // fcnOutDisable
  union anonymous$58 fcnOutDisable;
};

struct anonymous$16
{
  // sFcn
  struct _ssSFcnModelMethods sFcn;
};

struct anonymous$32
{
  // lsw
  unsigned int lsw;
  // msw
  unsigned int msw;
};

struct anonymous$35
{
  // w
  unsigned long int w;
};

struct anonymous$3
{
  // CaptureApproachComplete
  unsigned char CaptureApproachComplete;
  // DockingApproachComplete
  unsigned char DockingApproachComplete;
  // AttemptingToDock
  unsigned char AttemptingToDock;
  // LatchCaptureComplete
  unsigned char LatchCaptureComplete;
  // DockingApproach
  unsigned char DockingApproach;
  // ApproachOrbitComplete
  unsigned char ApproachOrbitComplete;
  // FarApproachComplete
  unsigned char FarApproachComplete;
  // ProximityOperationsComplete
  unsigned char ProximityOperationsComplete;
  // FailedApproach
  unsigned char FailedApproach;
  // JointMission
  unsigned char JointMission;
  // CaptureApproachFailed
  unsigned char CaptureApproachFailed;
};

union anonymous$30
{
  // cptr
  const char **cptr;
  // ptr
  char **ptr;
};

union anonymous$28
{
  // sfcn
  struct _ssDWorkRecord *sfcn;
  // root
  void *root;
};

union anonymous$29
{
  // vect
  void *vect;
  // uPtrs
  const double * const *uPtrs;
};

union anonymous$36
{
  // cptr
  const signed char * const *cptr;
  // ptr
  signed char **ptr;
};

union anonymous$8
{
  // str
  const char *str;
  // msg
  void *msg;
};

union anonymous$40
{
  // cptr
  const struct RTWLogSignalInfo_tag *cptr;
  // ptr
  struct RTWLogSignalInfo_tag *ptr;
};

union anonymous$56
{
  // vect
  const void *vect;
  // ptrs
  const void * const *ptrs;
};

union anonymous$55
{
  // value
  double value;
  // parts
  struct anonymous$32 parts;
  // xparts
  struct anonymous$35 xparts;
};

union anonymous$44
{
  // numInputPorts
  signed int numInputPorts;
  // numU
  signed int numU;
};

union anonymous$38
{
  // numOutputPorts
  signed int numOutputPorts;
  // numY
  signed int numY;
};

union anonymous$9
{
  // numRtp
  signed int numRtp;
  // placeholder
  void *placeholder;
};

struct DimsInfo_tag
{
  // width
  signed int width;
  // numDims
  signed int numDims;
  // dims
  signed int *dims;
  // nextSigDims
  struct DimsInfo_tag *nextSigDims;
};

struct RTWLogDataTypeConvert_tag
{
  // conversionNeeded
  signed int conversionNeeded;
  // dataTypeIdLoggingTo
  enum anonymous$17 dataTypeIdLoggingTo;
  // dataTypeIdOriginal
  signed int dataTypeIdOriginal;
  // bitsPerChunk
  signed int bitsPerChunk;
  // numOfChunk
  signed int numOfChunk;
  // isSigned
  unsigned int isSigned;
  // fracSlope
  double fracSlope;
  // fixedExp
  signed int fixedExp;
  // bias
  double bias;
};

struct RTWLogSignalInfo_tag
{
  // numSignals
  signed int numSignals;
  // numCols
  signed int *numCols;
  // numDims
  signed int *numDims;
  // dims
  signed int *dims;
  // isVarDims
  unsigned char *isVarDims;
  // currSigDims
  void **currSigDims;
  // currSigDimsSize
  signed int *currSigDimsSize;
  // dataTypes
  enum anonymous$17 *dataTypes;
  // complexSignals
  signed int *complexSignals;
  // frameData
  signed int *frameData;
  // labels
  union anonymous$30 labels;
  // titles
  char *titles;
  // titleLengths
  signed int *titleLengths;
  // plotStyles
  signed int *plotStyles;
  // blockNames
  union anonymous$30 blockNames;
  // stateNames
  union anonymous$30 stateNames;
  // crossMdlRef
  unsigned char *crossMdlRef;
  // dataTypeConvert
  struct RTWLogDataTypeConvert_tag *dataTypeConvert;
};

struct _ssSizes
{
  // numContStates
  signed int numContStates;
  // numDiscStates
  signed int numDiscStates;
  // out
  union anonymous$38 out;
  // in
  union anonymous$44 in;
  // mexApiInt1
  signed int mexApiInt1;
  // sysDirFeedThrough
  signed int sysDirFeedThrough;
  // numSampleTimes
  signed int numSampleTimes;
  // numSFcnParams
  signed int numSFcnParams;
  // numIWork
  signed int numIWork;
  // numRWork
  signed int numRWork;
  // numPWork
  signed int numPWork;
  // numBlocks
  signed int numBlocks;
  // numSFunctions
  signed int numSFunctions;
  // numBlockIO
  signed int numBlockIO;
  // numBlockParams
  signed int numBlockParams;
  // checksums
  unsigned int checksums[4l];
  // simStructVer
  signed int simStructVer;
  // numNonsampledZCs
  signed int numNonsampledZCs;
  // numZCEvents
  signed int numZCEvents;
  // numModes
  signed int numModes;
  // options
  unsigned int options;
  // sizeofY
  signed int sizeofY;
  // sizeofU
  signed int sizeofU;
  // sizeofBlockIO
  signed int sizeofBlockIO;
  // sizeofGlobalBlockIO
  signed int sizeofGlobalBlockIO;
  // numDWork
  signed int numDWork;
  // sizeofDWork
  signed int sizeofDWork;
  // RTWGeneratedSFcn
  signed int RTWGeneratedSFcn;
  // flags
  struct anonymous$49 flags;
  // numJacobianNzMax
  signed int numJacobianNzMax;
  // rtModel
  void *rtModel;
  // constBlockIO
  const void *constBlockIO;
  // reservedForFuture
  signed int reservedForFuture[1l];
};

struct _ssPortInfo
{
  // regNumInputPortsFcn
  signed int (*regNumInputPortsFcn)(void *, signed int);
  // regNumInputPortsFcnArg
  void *regNumInputPortsFcnArg;
  // regNumOutputPortsFcn
  signed int (*regNumOutputPortsFcn)(void *, signed int);
  // regNumOutputPortsFcnArg
  void *regNumOutputPortsFcnArg;
  // inputs
  struct _ssPortInputs *inputs;
  // outputs
  struct _ssPortOutputs *outputs;
};

struct _ssSFcnParams
{
  // dlgNum
  signed int dlgNum;
  // dlgParams
  double **dlgParams;
  // dlgAttribs
  unsigned int *dlgAttribs;
  // numRtp
  union anonymous$9 numRtp;
  // rtp
  struct ssParamRec_tag **rtp;
};

struct _ssStates
{
  // U
  union anonymous$29 U;
  // Y
  void *Y;
  // contStates
  double *contStates;
  // discStates
  double *discStates;
  // flags
  struct anonymous$34 flags;
  // reserved2
  signed int reserved2;
  // dX
  double *dX;
  // contStateDisabled
  unsigned char *contStateDisabled;
  // statesInfo2
  struct _ssStatesInfo2 *statesInfo2;
  // nonsampledZCs
  double *nonsampledZCs;
  // nonsampledZCDirs
  enum anonymous$27 *nonsampledZCDirs;
  // jacobian
  struct SparseHeader_Tag *jacobian;
  // modelMethods2
  struct _ssSFcnModelMethods2 *modelMethods2;
  // reservedSize
  signed int reservedSize;
};

struct _ssWork
{
  // iWork
  signed int *iWork;
  // rWork
  double *rWork;
  // pWork
  void **pWork;
  // modeVector
  signed int *modeVector;
  // userData
  void *userData;
  // dWork
  union anonymous$28 dWork;
  // dWorkAux
  struct _ssDWorkAuxRecord *dWorkAux;
  // reservedForFuture
  void *reservedForFuture[1l];
};

struct _ssBlkInfo
{
  // inputConnected
  signed int inputConnected;
  // outputConnected
  signed int outputConnected;
  // placementGroup
  const char *placementGroup;
  // block
  void *block;
  // blkInfo2
  struct _ssBlkInfo2 *blkInfo2;
  // absTolOffset_Obsolete
  signed int absTolOffset_Obsolete;
  // reservedForFutureInt
  signed int reservedForFutureInt;
};

struct _ssCallSys
{
  // outputs
  signed int *outputs;
  // args1
  void **args1;
  // args2
  signed int *args2;
  // fcns
  signed int (**fcns)(void *, signed int, signed int);
};

struct _ssRegDataType
{
  // arg1
  void *arg1;
  // registerFcn
  signed int (*registerFcn)(void *, const char *);
  // setSizeFcn
  signed int (*setSizeFcn)(void *, signed int, signed int);
  // getSizeFcn
  signed int (*getSizeFcn)(void *, signed int);
  // setZeroFcn
  signed int (*setZeroFcn)(void *, signed int, void *);
  // getZeroFcn
  const void * (*getZeroFcn)(void *, signed int);
  // getNameFcn
  const char * (*getNameFcn)(void *, signed int);
  // getIdFcn
  signed int (*getIdFcn)(void *, const char *);
  // setNumDWorkFcn
  signed int (*setNumDWorkFcn)(struct SimStruct_tag *, signed int);
};

struct _ssStInfo
{
  // sampleTimes
  double *sampleTimes;
  // offsetTimes
  double *offsetTimes;
  // tNext
  double tNext;
  // tNextTid
  signed int tNextTid;
  // sampleTimeTaskIDs
  signed int *sampleTimeTaskIDs;
};

struct SimStruct_tag
{
  // modelName
  const char *modelName;
  // path
  const char *path;
  // parent
  struct SimStruct_tag *parent;
  // root
  struct SimStruct_tag *root;
  // errorStatus
  union anonymous$8 errorStatus;
  // sizes
  struct _ssSizes sizes;
  // portInfo
  struct _ssPortInfo portInfo;
  // sfcnParams
  struct _ssSFcnParams sfcnParams;
  // states
  struct _ssStates states;
  // work
  struct _ssWork work;
  // blkInfo
  struct _ssBlkInfo blkInfo;
  // mdlInfo
  struct _ssMdlInfo *mdlInfo;
  // callSys
  struct _ssCallSys callSys;
  // regDataType
  struct _ssRegDataType regDataType;
  // stInfo
  struct _ssStInfo stInfo;
  // modelMethods
  struct anonymous$16 modelMethods;
  // sFunctions
  struct SimStruct_tag **sFunctions;
};

struct SparseHeader_Tag
{
  // mRows
  signed int mRows;
  // nCols
  signed int nCols;
  // nzMax
  signed int nzMax;
  // Ir
  signed int *Ir;
  // Jc
  signed int *Jc;
  // Pr
  double *Pr;
};

struct _IO_FILE
{
  // _flags
  signed int _flags;
  // _IO_read_ptr
  char *_IO_read_ptr;
  // _IO_read_end
  char *_IO_read_end;
  // _IO_read_base
  char *_IO_read_base;
  // _IO_write_base
  char *_IO_write_base;
  // _IO_write_ptr
  char *_IO_write_ptr;
  // _IO_write_end
  char *_IO_write_end;
  // _IO_buf_base
  char *_IO_buf_base;
  // _IO_buf_end
  char *_IO_buf_end;
  // _IO_save_base
  char *_IO_save_base;
  // _IO_backup_base
  char *_IO_backup_base;
  // _IO_save_end
  char *_IO_save_end;
  // _markers
  struct _IO_marker *_markers;
  // _chain
  struct _IO_FILE *_chain;
  // _fileno
  signed int _fileno;
  // _flags2
  signed int _flags2;
  // _old_offset
  signed long int _old_offset;
  // _cur_column
  unsigned short int _cur_column;
  // _vtable_offset
  signed char _vtable_offset;
  // _shortbuf
  char _shortbuf[1l];
  // _lock
  void *_lock;
  // _offset
  signed long int _offset;
  // __pad1
  void *__pad1;
  // __pad2
  void *__pad2;
  // __pad3
  void *__pad3;
  // __pad4
  void *__pad4;
  // __pad5
  unsigned long int __pad5;
  // _mode
  signed int _mode;
  // _unused2
  char _unused2[(signed long int)(sizeof(signed int) * 5) /*20l*/ ];
};

struct _IO_marker
{
  // _next
  struct _IO_marker *_next;
  // _sbuf
  struct _IO_FILE *_sbuf;
  // _pos
  signed int _pos;
};

struct _RTWExtModeInfo_tag
{
  // subSysActiveVectorAddr
  void *subSysActiveVectorAddr;
  // checksumsPtr
  unsigned int *checksumsPtr;
  // mdlMappingInfoPtr
  const void **mdlMappingInfoPtr;
  // tPtr
  void *tPtr;
  // tFinalTicks
  signed int tFinalTicks;
};

struct _RTWLogInfo_tag
{
  // logInfo
  void *logInfo;
  // logXSignalPtrs
  union anonymous$36 logXSignalPtrs;
  // logYSignalPtrs
  union anonymous$36 logYSignalPtrs;
  // sigLogSignalPtrs
  union anonymous$36 sigLogSignalPtrs;
  // logFormat
  signed int logFormat;
  // logMaxRows
  signed int logMaxRows;
  // logDecimation
  signed int logDecimation;
  // logVarNameModifier
  const char *logVarNameModifier;
  // logT
  const char *logT;
  // logX
  const char *logX;
  // logXFinal
  const char *logXFinal;
  // logY
  const char *logY;
  // logSL
  const char *logSL;
  // logXSignalInfo
  union anonymous$40 logXSignalInfo;
  // logYSignalInfo
  union anonymous$40 logYSignalInfo;
  // sigLogSignalInfo
  union anonymous$40 sigLogSignalInfo;
  // mdlLogData
  void (*mdlLogData)(void *, void *);
  // mmi
  const void *mmi;
};

struct _RTWRTModelMethodsInfo_tag
{
  // rtModelPtr
  void *rtModelPtr;
  // rtmInitSizesFcn
  void (*rtmInitSizesFcn)(void *);
  // rtmInitSampTimesFcn
  void (*rtmInitSampTimesFcn)(void *);
  // rtmStartFcn
  void (*rtmStartFcn)(void *);
  // rtmOutputsFcn
  void (*rtmOutputsFcn)(void *, signed int);
  // rtmUpdateFcn
  void (*rtmUpdateFcn)(void *, signed int);
  // rtmDervisFcn
  void (*rtmDervisFcn)(void *);
  // rtmProjectionFcn
  void (*rtmProjectionFcn)(void *);
  // rtmMassMatrixFcn
  void (*rtmMassMatrixFcn)(void *);
  // rtmForcingFunctionFcn
  void (*rtmForcingFunctionFcn)(void *);
  // rtmTerminateFcn
  void (*rtmTerminateFcn)(void *);
};

struct _rtTimingBridge_tag
{
  // nTasks
  unsigned int nTasks;
  // clockTick
  unsigned int **clockTick;
  // clockTickH
  unsigned int **clockTickH;
  // taskCounter
  unsigned int *taskCounter;
  // taskTime
  double **taskTime;
  // rateTransition
  unsigned char **rateTransition;
  // firstInitCond
  unsigned char *firstInitCond;
};

struct _ssBlkInfo2
{
  // rtwSfcnInfo
  void *rtwSfcnInfo;
  // unused
  void *unused;
  // portInfo2
  struct _ssPortInfo2 *portInfo2;
  // reservedPtrs
  void *reservedPtrs[14l];
  // reserved
  signed int reserved[16l];
};

struct _ssConstraintsInfo
{
  // numConstraints
  signed int numConstraints;
  // constraints
  double *constraints;
  // mdlConstraints
  void (*mdlConstraints)(struct SimStruct_tag *);
};

struct _ssDWorkAuxRecord
{
  // rtwIdentifier
  char *rtwIdentifier;
  // rtwStorageClass
  signed int rtwStorageClass;
  // rtwTypeQualifier
  char *rtwTypeQualifier;
  // flags
  struct anonymous$51 flags;
  // icPrmIdxPlus1
  signed int icPrmIdxPlus1;
  // bitFieldWidth
  signed int bitFieldWidth;
  // unusedInts
  signed int unusedInts[2l];
  // resolvedSignalObject
  void *resolvedSignalObject;
  // unusedPtrs
  void *unusedPtrs[3l];
};

struct _ssDWorkRecord
{
  // width
  signed int width;
  // dataTypeId
  signed int dataTypeId;
  // complexSignal
  signed int complexSignal;
  // array
  void *array;
  // name
  const char *name;
  // usedAs
  enum anonymous$42 usedAs;
};

struct _ssInPortVarDims
{
  // portVarDims
  const signed int *portVarDims;
  // reserved
  void *reserved[8l];
};

struct ssSparseMatrixInfo_tag
{
  // mRows
  signed int mRows;
  // nCols
  signed int nCols;
  // nzMax
  signed int nzMax;
  // Ir
  signed int *Ir;
  // Jc
  signed int *Jc;
  // Pr
  double *Pr;
};

struct _ssMassMatrixInfo
{
  // type
  enum anonymous$21 type;
  // info
  struct ssSparseMatrixInfo_tag info;
};

struct _ssMdlInfo
{
  // simMode
  enum anonymous$4 simMode;
  // t
  double *t;
  // sampleHits
  signed int *sampleHits;
  // tStart
  double tStart;
  // tFinal
  double tFinal;
  // timeOfLastOutput
  double timeOfLastOutput;
  // minStepSize
  double minStepSize;
  // timingData
  void *timingData;
  // simTimeStep
  enum anonymous$10 simTimeStep;
  // stopRequested
  signed int stopRequested;
  // logOutput
  signed int logOutput;
  // outputTimes
  double *outputTimes;
  // outputTimesIndex
  unsigned int outputTimesIndex;
  // numOutputTimes
  unsigned int numOutputTimes;
  // outputTimesOnly
  signed int outputTimesOnly;
  // obsoletedNeedOutputAtTPlusTol
  signed int obsoletedNeedOutputAtTPlusTol;
  // solverName
  const char *solverName;
  // variableStepSolver
  signed int variableStepSolver;
  // solverData
  void *solverData;
  // solverStopTime
  double solverStopTime;
  // stepSize
  double stepSize;
  // solverNeedsReset
  signed int solverNeedsReset;
  // mdlFlags
  struct anonymous$11 mdlFlags;
  // maxNumMinSteps
  signed int maxNumMinSteps;
  // solverRefineFactor
  signed int solverRefineFactor;
  // solverRelTol
  double solverRelTol;
  // solverAbsTol_Obsolete
  double *solverAbsTol_Obsolete;
  // maxStepSize
  double maxStepSize;
  // solverMaxOrder
  signed int solverMaxOrder;
  // fixedStepSize
  double fixedStepSize;
  // numNonContDerivSigInfos
  signed int numNonContDerivSigInfos;
  // nonContDerivSigInfos
  struct anonymous$14 *nonContDerivSigInfos;
  // solverAbsTolControl_Obsolete
  unsigned char *solverAbsTolControl_Obsolete;
  // timingBridge
  struct _rtTimingBridge_tag *timingBridge;
  // rtwLogInfo
  struct _RTWLogInfo_tag *rtwLogInfo;
  // solverInfo
  struct _ssSolverInfo_tag *solverInfo;
  // unused
  void *unused[2l];
  // mexApiVoidPtr1
  void *mexApiVoidPtr1;
  // solverExtrapolationOrder
  signed int solverExtrapolationOrder;
  // solverNumberNewtonIterations
  signed int solverNumberNewtonIterations;
  // extModeInfo
  struct _RTWExtModeInfo_tag *extModeInfo;
  // blockIO
  void *blockIO;
  // blockIOVarDims
  signed int *blockIOVarDims;
  // defaultParam
  double *defaultParam;
  // mappingInfo
  const void *mappingInfo;
  // mexApiInt2
  signed int mexApiInt2;
  // reservedString
  char reservedString[32l];
  // regInputPortDimsInfo
  signed int (*regInputPortDimsInfo)(struct SimStruct_tag *, signed int, const struct DimsInfo_tag *);
  // regOutputPortDimsInfo
  signed int (*regOutputPortDimsInfo)(struct SimStruct_tag *, signed int, const struct DimsInfo_tag *);
  // reservedForXPC
  void *reservedForXPC;
  // solverMode
  enum anonymous$13 solverMode;
  // rtwgenMode
  enum anonymous$20 rtwgenMode;
  // reservedForFutureInt
  signed int reservedForFutureInt[2l];
  // mexApiReal1
  double mexApiReal1;
  // mexApiReal2
  double mexApiReal2;
  // timeOfNextSampleHit
  double *timeOfNextSampleHit;
  // varNextHitTimesList
  double *varNextHitTimesList;
  // tNextWasAdjusted
  unsigned char *tNextWasAdjusted;
  // reservedDoubleVect
  double *reservedDoubleVect[1l];
};

struct _ssOutPortVarDims
{
  // portVarDims
  signed int *portVarDims;
  // reserved
  void *reserved[8l];
};

struct _ssPortInfo2
{
  // inputs
  struct _ssInPortVarDims *inputs;
  // outputs
  struct _ssOutPortVarDims *outputs;
  // reserved
  void *reserved[8l];
};

struct _ssPortInputs
{
  // width
  signed int width;
  // directFeedThrough
  signed int directFeedThrough;
  // dataTypeId
  signed int dataTypeId;
  // complexSignal
  signed int complexSignal;
  // signal
  union anonymous$56 signal;
  // connected
  signed int connected;
  // attributes
  struct anonymous$2 attributes;
  // sampleTime
  double sampleTime;
  // offsetTime
  double offsetTime;
  // dims
  signed int *dims;
  // bufferDstPort
  signed int bufferDstPort;
  // sampleTimeIndex
  signed int sampleTimeIndex;
  // numDims
  signed int numDims;
};

struct _ssPortOutputs
{
  // width
  signed int width;
  // dataTypeId
  signed int dataTypeId;
  // complexSignal
  signed int complexSignal;
  // signalVect
  void *signalVect;
  // connected
  signed int connected;
  // attributes
  struct anonymous$5 attributes;
  // sampleTime
  double sampleTime;
  // offsetTime
  double offsetTime;
  // dims
  signed int *dims;
  // sampleTimeIndex
  signed int sampleTimeIndex;
  // icPrmIdxPlus1
  signed int icPrmIdxPlus1;
  // numDims
  signed int numDims;
};

struct _ssResolveCBK
{
  // Resolver
  signed int (*Resolver)(const struct SimStruct_tag *, const char *, double **);
  // _slBlock
  void *_slBlock;
};

struct _ssSFcnModelMethods2
{
  // mdlProjection
  void (*mdlProjection)(struct SimStruct_tag *);
  // mdlJacobian
  void (*mdlJacobian)(struct SimStruct_tag *);
  // mdlSetInputPortFrameData
  void (*mdlSetInputPortFrameData)(struct SimStruct_tag *, signed int, enum anonymous$15);
  // strictBooleanCheckEnabledFcn
  unsigned char (*strictBooleanCheckEnabledFcn)(void *);
  // mdlSetDefaultPortDimensions
  void (*mdlSetDefaultPortDimensions)(struct SimStruct_tag *);
  // mdlSetDefaultPortDataTypes
  void (*mdlSetDefaultPortDataTypes)(struct SimStruct_tag *);
  // mdlSetDefaultPortComplexSignals
  void (*mdlSetDefaultPortComplexSignals)(struct SimStruct_tag *);
  // ConvertBuiltInDType
  unsigned char (*ConvertBuiltInDType)(signed int, unsigned char, unsigned char, const signed int, const void *, const signed int, void *);
  // resolveCBK
  struct _ssResolveCBK resolveCBK;
  // extModeLogFcn
  const char * (*extModeLogFcn)(struct SimStruct_tag *, const enum anonymous$18);
  // mdlExtModeExec
  void (*mdlExtModeExec)(struct SimStruct_tag *);
  // mdlRTWCG
  void (*mdlRTWCG)(struct SimStruct_tag *, void *);
  // mdlMassMatrix
  void (*mdlMassMatrix)(struct SimStruct_tag *);
  // unused
  void *unused;
  // mdlForcingFunction
  void (*mdlForcingFunction)(struct SimStruct_tag *);
  // mdlEnable
  void (*mdlEnable)(struct SimStruct_tag *);
  // mdlDisable
  void (*mdlDisable)(struct SimStruct_tag *);
  // mdlSimStatusChange
  void (*mdlSimStatusChange)(struct SimStruct_tag *, enum anonymous$22);
  // mdlInitializePropagationPass
  void (*mdlInitializePropagationPass)(struct SimStruct_tag *, enum anonymous$23);
  // constraintsInfo
  struct _ssConstraintsInfo *constraintsInfo;
  // modelMethods3
  struct _ssSFcnModelMethods3 *modelMethods3;
};

struct _ssSFcnModelMethods3
{
  // massMatrix
  struct _ssMassMatrixInfo massMatrix;
  // mdlInitSystemMatrices
  void (*mdlInitSystemMatrices)(struct SimStruct_tag *);
  // numSlvrJacobianNzmax
  signed int numSlvrJacobianNzmax;
  // slvrJacobianMatrix
  struct SparseHeader_Tag *slvrJacobianMatrix;
  // mdlJacobianIrJc
  void (*mdlJacobianIrJc)(struct SimStruct_tag *);
  // reservedForFuture
  void *reservedForFuture;
};

struct _ssSolverInfo_tag
{
  // rtModelPtr
  void *rtModelPtr;
  // simTimeStepPtr
  enum anonymous$10 *simTimeStepPtr;
  // solverData
  void *solverData;
  // solverName
  const char *solverName;
  // isVariableStepSolver
  unsigned char isVariableStepSolver;
  // solverNeedsReset
  unsigned char solverNeedsReset;
  // solverMode
  enum anonymous$13 solverMode;
  // solverStopTime
  double solverStopTime;
  // stepSizePtr
  double *stepSizePtr;
  // minStepSize
  double minStepSize;
  // maxStepSize
  double maxStepSize;
  // fixedStepSize
  double fixedStepSize;
  // solverShapePreserveControl
  signed int solverShapePreserveControl;
  // solverMaxConsecutiveMinStep
  signed int solverMaxConsecutiveMinStep;
  // maxNumMinSteps
  signed int maxNumMinSteps;
  // solverMaxOrder
  signed int solverMaxOrder;
  // solverConsecutiveZCsStepRelTol
  double solverConsecutiveZCsStepRelTol;
  // solverMaxConsecutiveZCs
  signed int solverMaxConsecutiveZCs;
  // solverExtrapolationOrder
  signed int solverExtrapolationOrder;
  // solverNumberNewtonIterations
  signed int solverNumberNewtonIterations;
  // solverRefineFactor
  signed int solverRefineFactor;
  // solverRelTol
  double solverRelTol;
  // unused_real_T_1
  double unused_real_T_1;
  // dXPtr
  double **dXPtr;
  // tPtr
  double **tPtr;
  // numContStatesPtr
  signed int *numContStatesPtr;
  // contStatesPtr
  double **contStatesPtr;
  // zcSignalVector
  double *zcSignalVector;
  // zcEventsVector
  unsigned char *zcEventsVector;
  // zcSignalAttrib
  unsigned char *zcSignalAttrib;
  // zcSignalVectorLength
  signed int zcSignalVectorLength;
  // reserved
  unsigned char *reserved;
  // foundContZcEvents
  unsigned char foundContZcEvents;
  // isAtLeftPostOfContZcEvent
  unsigned char isAtLeftPostOfContZcEvent;
  // isAtRightPostOfContZcEvent
  unsigned char isAtRightPostOfContZcEvent;
  // adaptiveZcDetection
  unsigned char adaptiveZcDetection;
  // numZcSignals
  signed int numZcSignals;
  // stateProjection
  unsigned char stateProjection;
  // robustResetMethod
  unsigned char robustResetMethod;
  // updateJacobianAtReset
  unsigned char updateJacobianAtReset;
  // consistencyChecking
  unsigned char consistencyChecking;
  // massMatrixType
  enum anonymous$21 massMatrixType;
  // massMatrixNzMax
  signed int massMatrixNzMax;
  // massMatrixIr
  signed int *massMatrixIr;
  // massMatrixJc
  signed int *massMatrixJc;
  // massMatrixPr
  double *massMatrixPr;
  // errStatusPtr
  const char **errStatusPtr;
  // modelMethodsPtr
  struct _RTWRTModelMethodsInfo_tag *modelMethodsPtr;
  // zcThreshold
  double zcThreshold;
  // zeroCrossAlgorithm
  signed int zeroCrossAlgorithm;
  // consecutiveZCsError
  signed int consecutiveZCsError;
  // blkStateChange
  unsigned char blkStateChange;
  // isComputingJacobian
  unsigned char isComputingJacobian;
  // solverJacobianMethodControl
  enum anonymous$26 solverJacobianMethodControl;
  // ignoredZcDiagnostic
  signed int ignoredZcDiagnostic;
  // maskedZcDiagnostic
  signed int maskedZcDiagnostic;
  // isOutputMethodComputed
  unsigned char isOutputMethodComputed;
};

struct _ssStatesInfo2
{
  // prevZCSigState
  unsigned char *prevZCSigState;
  // absTol
  double *absTol;
  // absTolControl
  unsigned char *absTolControl;
  // reservedForFutureUse
  void *reservedForFutureUse[6l];
};

struct ssParamRec_tag
{
  // name
  const char *name;
  // nDimensions
  signed int nDimensions;
  // dimensions
  signed int *dimensions;
  // dataTypeId
  signed int dataTypeId;
  // complexSignal
  unsigned char complexSignal;
  // data
  void *data;
  // dataAttributes
  const void *dataAttributes;
  // nDlgParamIndices
  signed int nDlgParamIndices;
  // dlgParamIndices
  signed int *dlgParamIndices;
  // transformed
  enum anonymous$59 transformed;
  // outputAsMatrix
  unsigned char outputAsMatrix;
};

struct tag_RTM_DockingApproachExampl_T
{
  // path
  const char *path;
  // modelName
  const char *modelName;
  // childSfunctions
  struct SimStruct_tag **childSfunctions;
  // errorStatus
  const char *errorStatus;
  // simMode
  enum anonymous$4 simMode;
  // rtwLogInfo
  struct _RTWLogInfo_tag *rtwLogInfo;
  // extModeInfo
  struct _RTWExtModeInfo_tag *extModeInfo;
  // solverInfo
  struct _ssSolverInfo_tag solverInfo;
  // solverInfoPtr
  struct _ssSolverInfo_tag *solverInfoPtr;
  // sfcnInfo
  void *sfcnInfo;
  // ModelData
  struct anonymous$12 ModelData;
  // Sizes
  struct anonymous$24 Sizes;
  // SpecialInfo
  struct anonymous$25 SpecialInfo;
  // Timing
  struct anonymous$19 Timing;
};


// DockingApproachExample_Ext_Y
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 85
struct anonymous$3 DockingApproachExample_Ext_Y;
// DockingApproachExample_Ext_DW
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 79
struct anonymous$0 DockingApproachExample_Ext_DW;
// DockingApproachExample_Ext_M
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 89
struct tag_RTM_DockingApproachExampl_T * const DockingApproachExample_Ext_M;
// DockingApproachExample_Ext_M_
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 88
struct tag_RTM_DockingApproachExampl_T DockingApproachExample_Ext_M_;
// DockingApproachExample_Ext_M
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 89
struct tag_RTM_DockingApproachExampl_T * const DockingApproachExample_Ext_M = &DockingApproachExample_Ext_M_;
// DockingApproachExample_Ext_U
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 82
struct anonymous$1 DockingApproachExample_Ext_U;
// FALSE
// file ../R2013a/rtw/c/grt/classic_main.c line 28
_Bool FALSE = 0 != 0;
// GBLbuf
// file ../R2013a/rtw/c/grt/classic_main.c line 162
static struct anonymous$31 GBLbuf;
// TRUE
// file ../R2013a/rtw/c/grt/classic_main.c line 27
_Bool TRUE = 0 == 0;
// huge_double
// file ../R2013a/rtw/c/grt/cbmc_math.c line 90
static const double huge_double = 1.0e300;
// rtInf
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 26
double rtInf;
// rtInfF
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 29
float rtInfF;
// rtMinusInf
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 27
double rtMinusInf;
// rtMinusInfF
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 30
float rtMinusInfF;
// rtNaN
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 28
double rtNaN;
// rtNaNF
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 31
float rtNaNF;
// stderr
// file /usr/include/stdio.h line 170
extern struct _IO_FILE *stderr;

// D_exit_internal_CaptureApproach
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 102
static void D_exit_internal_CaptureApproach(void)
{
  DockingApproachExample_Ext_DW.is_InertialNavigation = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_InertialNavigation = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_StarPlanetTracker = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_StarPlanetTracker = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_GPS = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_GPS = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_OrbitalState2 = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_OrbitalState2 = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_OrbitalState = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_OrbitalState = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_OrbitalState_Complex = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_OrbitalState_Active = (unsigned char)0U;
  if(DockingApproachExample_Ext_DW.is_CaptureApproach == 4)
  {
    DockingApproachExample_Ext_Y.CaptureApproachComplete = (unsigned char)1U;
    DockingApproachExample_Ext_DW.is_CaptureApproach = (unsigned char)0U;
  }

  else
    DockingApproachExample_Ext_DW.is_CaptureApproach = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_CaptureApproach = (unsigned char)0U;
}

// D_exit_internal_DockingApproach
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 996
static void D_exit_internal_DockingApproach(void)
{
  switch((signed int)DockingApproachExample_Ext_DW.is_dockingSensor)
  {
    case (signed int)(unsigned char)1U:
    {
      DockingApproachExample_Ext_DW.dockingSensor_timer = (signed char)0;
      DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)0U;
      break;
    }
    case (signed int)(unsigned char)2U:
    {
      DockingApproachExample_Ext_DW.dockingSensor_timer = (signed char)0;
      DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)0U;
      break;
    }
    default:
      DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)0U;
  }
  DockingApproachExample_Ext_DW.is_active_dockingSensor = (unsigned char)0U;
  if(DockingApproachExample_Ext_DW.is_DockingApproach == 4)
  {
    DockingApproachExample_Ext_Y.DockingApproachComplete = (unsigned char)1U;
    DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)0U;
  }

  else
    DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_DockingApproach = (unsigned char)0U;
}

// DockingAppr_OrbitalState_Active
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 277
static void DockingAppr_OrbitalState_Active(void)
{
  signed int b_previousEvent;
  if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_OrbitalState_Complex == 0U))
  {
    if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_OrbitalState == 0U))
      switch((signed int)DockingApproachExample_Ext_DW.is_OrbitalState)
      {
        case (signed int)(unsigned char)1U:
        {
          if(DockingApproachExample_Ext_DW.GPS_AbsolutePosition == 0)
          {
            if(!(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit == 0))
              goto __CPROVER_DUMP_L2;

            if(!(DockingApproachExample_Ext_U.GroundTrack_OrbitalPosition == 0))
              goto __CPROVER_DUMP_L2;

          }

          else
          {

          __CPROVER_DUMP_L2:
            ;
            if(DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity == 0)
            {
              if(!(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc == 0))
                goto __CPROVER_DUMP_L3;

              if(!(DockingApproachExample_Ext_U.GroundTrack_OrbitalVelocity == 0))
                goto __CPROVER_DUMP_L3;

            }

            else
            {

            __CPROVER_DUMP_L3:
              ;
              DockingApproachExample_Ext_DW.is_OrbitalState = (unsigned char)3U;
              DockingApproachExample_Ext_DW.OrbitalState_Position = (signed char)1;
              DockingApproachExample_Ext_DW.OrbitalState_Velocity = (signed char)1;
              DockingApproachExample_Ext_DW.OrbitalState_Attitude = (signed char)0;
              goto __CPROVER_DUMP_L5;
            }
          }
          if(DockingApproachExample_Ext_DW.GPS_AbsolutePosition == 0)
          {
            if(DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity == 0)
            {
              if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit == 0)
              {
                if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc == 0)
                {
                  if(DockingApproachExample_Ext_U.GroundTrack_OrbitalPosition == 0)
                  {
                    if(DockingApproachExample_Ext_U.GroundTrack_OrbitalVelocity == 0)
                    {
                      DockingApproachExample_Ext_DW.is_OrbitalState = (unsigned char)1U;
                      DockingApproachExample_Ext_DW.OrbitalState_Position = (signed char)0;
                      DockingApproachExample_Ext_DW.OrbitalState_Velocity = (signed char)0;
                      DockingApproachExample_Ext_DW.OrbitalState_Attitude = (signed char)0;
                    }

                  }

                }

              }

            }

          }


        __CPROVER_DUMP_L5:
          ;
          break;
        }
        case (signed int)(unsigned char)2U:
        {
          if(DockingApproachExample_Ext_U.GroundTrack_OrbitalPosition == 2)
          {
            if(!(DockingApproachExample_Ext_DW.GPS_AbsolutePosition == 2))
              goto __CPROVER_DUMP_L7;

          }

          else
          {

          __CPROVER_DUMP_L7:
            ;
            if(DockingApproachExample_Ext_U.GroundTrack_OrbitalPosition == 2)
            {
              if(!(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit == 2))
                goto __CPROVER_DUMP_L8;

            }

            else
            {

            __CPROVER_DUMP_L8:
              ;
              if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit == 2)
              {
                if(!(DockingApproachExample_Ext_DW.GPS_AbsolutePosition == 2))
                  goto __CPROVER_DUMP_L9;

              }

              else
              {

              __CPROVER_DUMP_L9:
                ;
                if(DockingApproachExample_Ext_DW.InertialNavigation_AbsolutePosi == 2)
                {
                  if(!(DockingApproachExample_Ext_U.GroundTrack_OrbitalPosition == 2))
                    goto __CPROVER_DUMP_L10;

                }

                else
                {

                __CPROVER_DUMP_L10:
                  ;
                  if(DockingApproachExample_Ext_DW.InertialNavigation_AbsolutePosi == 2)
                  {
                    if(!(DockingApproachExample_Ext_DW.GPS_AbsolutePosition == 2))
                      goto __CPROVER_DUMP_L11;

                  }

                  else
                  {

                  __CPROVER_DUMP_L11:
                    ;
                    if(DockingApproachExample_Ext_DW.InertialNavigation_AbsolutePosi == 2)
                    {
                      if(!(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit == 2))
                        goto __CPROVER_DUMP_L12;

                    }

                    else
                    {

                    __CPROVER_DUMP_L12:
                      ;
                      if(!(DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteAtti == 2))
                      {
                        if(!(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteAttit == 2))
                        {
                          if(DockingApproachExample_Ext_U.GroundTrack_OrbitalVelocity == 2)
                          {
                            if(!(DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity == 2))
                              goto __CPROVER_DUMP_L13;

                          }

                          else
                          {

                          __CPROVER_DUMP_L13:
                            ;
                            if(DockingApproachExample_Ext_U.GroundTrack_OrbitalVelocity == 2)
                            {
                              if(!(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc == 2))
                                goto __CPROVER_DUMP_L14;

                            }

                            else
                            {

                            __CPROVER_DUMP_L14:
                              ;
                              if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc == 2)
                              {
                                if(!(DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity == 2))
                                  goto __CPROVER_DUMP_L15;

                              }

                              else
                              {

                              __CPROVER_DUMP_L15:
                                ;
                                if(DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteVelo == 2)
                                {
                                  if(!(DockingApproachExample_Ext_U.GroundTrack_OrbitalVelocity == 2))
                                    goto __CPROVER_DUMP_L16;

                                }

                                else
                                {

                                __CPROVER_DUMP_L16:
                                  ;
                                  if(DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteVelo == 2)
                                  {
                                    if(!(DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity == 2))
                                      goto __CPROVER_DUMP_L17;

                                  }

                                  else
                                  {

                                  __CPROVER_DUMP_L17:
                                    ;
                                    if(DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteVelo == 2)
                                    {
                                      if(!(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc == 2))
                                        goto __CPROVER_DUMP_L18;

                                    }

                                    else
                                    {

                                    __CPROVER_DUMP_L18:
                                      ;
                                      DockingApproachExample_Ext_DW.is_OrbitalState = (unsigned char)3U;
                                      DockingApproachExample_Ext_DW.OrbitalState_Position = (signed char)1;
                                      DockingApproachExample_Ext_DW.OrbitalState_Velocity = (signed char)1;
                                      DockingApproachExample_Ext_DW.OrbitalState_Attitude = (signed char)0;
                                      goto __CPROVER_DUMP_L23;
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }

                      }

                    }
                  }
                }
              }
            }
          }
          if(!(DockingApproachExample_Ext_U.GroundTrack_OrbitalPosition == 2))
          {
            if(DockingApproachExample_Ext_DW.GPS_AbsolutePosition == 2)
              goto __CPROVER_DUMP_L20;

            if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit == 2)
              goto __CPROVER_DUMP_L20;

          }

          else
          {

          __CPROVER_DUMP_L20:
            ;
            if(!(DockingApproachExample_Ext_U.GroundTrack_OrbitalVelocity == 2))
            {
              if(DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity == 2)
                goto __CPROVER_DUMP_L21;

              if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc == 2)
                goto __CPROVER_DUMP_L21;

            }

            else
            {

            __CPROVER_DUMP_L21:
              ;
              if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteAttit == 2)
              {
                DockingApproachExample_Ext_DW.is_OrbitalState = (unsigned char)0U;
                b_previousEvent = DockingApproachExample_Ext_DW.sfEvent;
                DockingApproachExample_Ext_DW.sfEvent = 0;
                if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_InertialNavigation == 0U))
                  DockingAppro_InertialNavigation();

                DockingApproachExample_Ext_DW.sfEvent = b_previousEvent;
                DockingApproachExample_Ext_DW.is_OrbitalState = (unsigned char)2U;
                DockingApproachExample_Ext_DW.OrbitalState_Position = (signed char)2;
                DockingApproachExample_Ext_DW.OrbitalState_Velocity = (signed char)2;
                DockingApproachExample_Ext_DW.OrbitalState_Attitude = (signed char)2;
              }

            }
          }

        __CPROVER_DUMP_L23:
          ;
          break;
        }
        case (signed int)(unsigned char)3U:
        {
          if(DockingApproachExample_Ext_U.GroundTrack_OrbitalPosition == 0)
          {
            if(!(DockingApproachExample_Ext_DW.GPS_AbsolutePosition == 0))
              goto __CPROVER_DUMP_L25;

            if(!(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit == 0))
              goto __CPROVER_DUMP_L25;

            if(!(DockingApproachExample_Ext_U.GroundTrack_OrbitalVelocity == 0))
              goto __CPROVER_DUMP_L25;

            if(!(DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity == 0))
              goto __CPROVER_DUMP_L25;

            if(!(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc == 0))
              goto __CPROVER_DUMP_L25;

            DockingApproachExample_Ext_DW.is_OrbitalState = (unsigned char)1U;
            DockingApproachExample_Ext_DW.OrbitalState_Position = (signed char)0;
            DockingApproachExample_Ext_DW.OrbitalState_Velocity = (signed char)0;
            DockingApproachExample_Ext_DW.OrbitalState_Attitude = (signed char)0;
          }

          else
          {

          __CPROVER_DUMP_L25:
            ;
            if(DockingApproachExample_Ext_U.GroundTrack_OrbitalPosition == 2)
            {
              if(!(DockingApproachExample_Ext_DW.GPS_AbsolutePosition == 2))
                goto __CPROVER_DUMP_L26;

            }

            else
            {

            __CPROVER_DUMP_L26:
              ;
              if(DockingApproachExample_Ext_U.GroundTrack_OrbitalPosition == 2)
              {
                if(!(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit == 2))
                  goto __CPROVER_DUMP_L27;

              }

              else
              {

              __CPROVER_DUMP_L27:
                ;
                if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit == 2)
                {
                  if(!(DockingApproachExample_Ext_DW.GPS_AbsolutePosition == 2))
                    goto __CPROVER_DUMP_L28;

                }

                else
                {

                __CPROVER_DUMP_L28:
                  ;
                  if(DockingApproachExample_Ext_DW.InertialNavigation_AbsolutePosi == 2)
                  {
                    if(!(DockingApproachExample_Ext_U.GroundTrack_OrbitalPosition == 2))
                      goto __CPROVER_DUMP_L29;

                  }

                  else
                  {

                  __CPROVER_DUMP_L29:
                    ;
                    if(DockingApproachExample_Ext_DW.InertialNavigation_AbsolutePosi == 2)
                    {
                      if(!(DockingApproachExample_Ext_DW.GPS_AbsolutePosition == 2))
                        goto __CPROVER_DUMP_L30;

                    }

                    else
                    {

                    __CPROVER_DUMP_L30:
                      ;
                      if(DockingApproachExample_Ext_DW.InertialNavigation_AbsolutePosi == 2)
                      {
                        if(!(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit == 2))
                          goto __CPROVER_DUMP_L31;

                      }

                      else
                      {

                      __CPROVER_DUMP_L31:
                        ;
                        goto __CPROVER_DUMP_L41;
                      }
                    }
                  }
                }
              }
            }
            if(DockingApproachExample_Ext_U.GroundTrack_OrbitalVelocity == 2)
            {
              if(!(DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity == 2))
                goto __CPROVER_DUMP_L33;

            }

            else
            {

            __CPROVER_DUMP_L33:
              ;
              if(DockingApproachExample_Ext_U.GroundTrack_OrbitalVelocity == 2)
              {
                if(!(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc == 2))
                  goto __CPROVER_DUMP_L34;

              }

              else
              {

              __CPROVER_DUMP_L34:
                ;
                if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc == 2)
                {
                  if(!(DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity == 2))
                    goto __CPROVER_DUMP_L35;

                }

                else
                {

                __CPROVER_DUMP_L35:
                  ;
                  if(DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteVelo == 2)
                  {
                    if(!(DockingApproachExample_Ext_U.GroundTrack_OrbitalVelocity == 2))
                      goto __CPROVER_DUMP_L36;

                  }

                  else
                  {

                  __CPROVER_DUMP_L36:
                    ;
                    if(DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteVelo == 2)
                    {
                      if(!(DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity == 2))
                        goto __CPROVER_DUMP_L37;

                    }

                    else
                    {

                    __CPROVER_DUMP_L37:
                      ;
                      if(DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteVelo == 2)
                      {
                        if(!(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc == 2))
                          goto __CPROVER_DUMP_L38;

                      }

                      else
                      {

                      __CPROVER_DUMP_L38:
                        ;
                        goto __CPROVER_DUMP_L41;
                      }
                    }
                  }
                }
              }
            }
            if(!(DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteAtti == 2))
            {
              if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteAttit == 2)
                goto __CPROVER_DUMP_L40;

            }

            else
            {

            __CPROVER_DUMP_L40:
              ;
              DockingApproachExample_Ext_DW.is_OrbitalState = (unsigned char)4U;
              DockingApproachExample_Ext_DW.OrbitalState_Position = (signed char)2;
              DockingApproachExample_Ext_DW.OrbitalState_Velocity = (signed char)2;
              DockingApproachExample_Ext_DW.OrbitalState_Attitude = (signed char)1;
            }
          }

        __CPROVER_DUMP_L41:
          ;
          break;
        }
        case (signed int)(unsigned char)4U:
        {
          if(!(DockingApproachExample_Ext_U.GroundTrack_OrbitalPosition == 2))
          {
            if(DockingApproachExample_Ext_DW.GPS_AbsolutePosition == 2)
              goto __CPROVER_DUMP_L43;

            if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit == 2)
              goto __CPROVER_DUMP_L43;

          }

          else
          {

          __CPROVER_DUMP_L43:
            ;
            if(!(DockingApproachExample_Ext_U.GroundTrack_OrbitalVelocity == 2))
            {
              if(DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity == 2)
                goto __CPROVER_DUMP_L44;

              if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc == 2)
                goto __CPROVER_DUMP_L44;

            }

            else
            {

            __CPROVER_DUMP_L44:
              ;
              if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteAttit == 2)
              {
                DockingApproachExample_Ext_DW.is_OrbitalState = (unsigned char)0U;
                b_previousEvent = DockingApproachExample_Ext_DW.sfEvent;
                DockingApproachExample_Ext_DW.sfEvent = 0;
                if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_InertialNavigation == 0U))
                  DockingAppro_InertialNavigation();

                DockingApproachExample_Ext_DW.sfEvent = b_previousEvent;
                DockingApproachExample_Ext_DW.is_OrbitalState = (unsigned char)2U;
                DockingApproachExample_Ext_DW.OrbitalState_Position = (signed char)2;
                DockingApproachExample_Ext_DW.OrbitalState_Velocity = (signed char)2;
                DockingApproachExample_Ext_DW.OrbitalState_Attitude = (signed char)2;
              }

            }
          }
          break;
        }
        default:
          DockingApproachExample_Ext_DW.is_OrbitalState = (unsigned char)0U;
      }

    if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_OrbitalState2 == 0U))
      switch((signed int)DockingApproachExample_Ext_DW.is_OrbitalState2)
      {
        case (signed int)(unsigned char)1U:
        {
          if(!(DockingApproachExample_Ext_U.RealTimeClock_time == 2))
          {
            DockingApproachExample_Ext_DW.is_OrbitalState2 = (unsigned char)2U;
            DockingApproachExample_Ext_DW.OrbitalState_Time = (signed char)1;
          }

          else
            if(!(DockingApproachExample_Ext_U.GroundTrack_Time == 2))
            {
              if(DockingApproachExample_Ext_DW.GPS_AbsoluteTime == 2)
                goto __CPROVER_DUMP_L51;

              if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteTime == 2)
                goto __CPROVER_DUMP_L51;

            }

            else
            {

            __CPROVER_DUMP_L51:
              ;
              DockingApproachExample_Ext_DW.is_OrbitalState2 = (unsigned char)1U;
              DockingApproachExample_Ext_DW.OrbitalState_Time = (signed char)2;
            }
          break;
        }
        case (signed int)(unsigned char)2U:
        {
          if(!(DockingApproachExample_Ext_U.GroundTrack_Time == 2))
          {
            if(DockingApproachExample_Ext_DW.GPS_AbsoluteTime == 2)
              goto __CPROVER_DUMP_L54;

            if(DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteTime == 2)
              goto __CPROVER_DUMP_L54;

          }

          else
          {

          __CPROVER_DUMP_L54:
            ;
            DockingApproachExample_Ext_DW.is_OrbitalState2 = (unsigned char)1U;
            DockingApproachExample_Ext_DW.OrbitalState_Time = (signed char)2;
          }
          break;
        }
        default:
          DockingApproachExample_Ext_DW.is_OrbitalState2 = (unsigned char)0U;
      }

  }

  if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_GPS == 0U))
  {
    b_previousEvent = (signed int)DockingApproachExample_Ext_DW.GPS_timer + 1;
    if(b_previousEvent <= 6)
      DockingApproachExample_Ext_DW.GPS_timer = (signed char)b_previousEvent;

    else
      DockingApproachExample_Ext_DW.GPS_timer = (signed char)6;
    switch((signed int)DockingApproachExample_Ext_DW.is_GPS)
    {
      case (signed int)(unsigned char)1U:
      {
        if(!(DockingApproachExample_Ext_U.GPS_satelliteVisibility_status == 0))
        {
          if(DockingApproachExample_Ext_U.GPS_receiverAvailability_status == 0)
            goto __CPROVER_DUMP_L61;

          DockingApproachExample_Ext_DW.is_GPS = (unsigned char)3U;
          DockingApproachExample_Ext_DW.GPS_timer = (signed char)0;
          DockingApproachExample_Ext_DW.GPS_AbsolutePosition = (signed char)1;
          DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity = (signed char)1;
          DockingApproachExample_Ext_DW.GPS_AbsoluteTime = (signed char)1;
        }

        else
        {

        __CPROVER_DUMP_L61:
          ;
          if(!(DockingApproachExample_Ext_U.GPS_satelliteVisibility_status == 0))
          {
            if(DockingApproachExample_Ext_U.GPS_receiverAvailability_status == 0)
              goto __CPROVER_DUMP_L62;

          }

          else
          {

          __CPROVER_DUMP_L62:
            ;
            DockingApproachExample_Ext_DW.is_GPS = (unsigned char)1U;
            DockingApproachExample_Ext_DW.GPS_AbsolutePosition = (signed char)0;
            DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity = (signed char)0;
            DockingApproachExample_Ext_DW.GPS_AbsoluteTime = (signed char)0;
          }
        }
        break;
      }
      case (signed int)(unsigned char)2U:
      {
        if(DockingApproachExample_Ext_U.GPS_satelliteVisibility_status == 2)
        {
          if(DockingApproachExample_Ext_U.GPS_receiverAvailability_status == 0)
            goto __CPROVER_DUMP_L65;

          if(DockingApproachExample_Ext_U.sunlight_status != 0)
            goto __CPROVER_DUMP_L65;

        }

        else
        {

        __CPROVER_DUMP_L65:
          ;
          DockingApproachExample_Ext_DW.is_GPS = (unsigned char)3U;
          DockingApproachExample_Ext_DW.GPS_timer = (signed char)0;
          DockingApproachExample_Ext_DW.GPS_AbsolutePosition = (signed char)1;
          DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity = (signed char)1;
          DockingApproachExample_Ext_DW.GPS_AbsoluteTime = (signed char)1;
          goto __CPROVER_DUMP_L67;
        }
        if(DockingApproachExample_Ext_U.GPS_satelliteVisibility_status == 2)
        {
          if(!(DockingApproachExample_Ext_U.GPS_receiverAvailability_status == 0))
          {
            if(DockingApproachExample_Ext_U.sunlight_status == 0)
            {
              DockingApproachExample_Ext_DW.is_GPS = (unsigned char)2U;
              DockingApproachExample_Ext_DW.GPS_AbsolutePosition = (signed char)2;
              DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity = (signed char)2;
              DockingApproachExample_Ext_DW.GPS_AbsoluteTime = (signed char)2;
            }

          }

        }


      __CPROVER_DUMP_L67:
        ;
        break;
      }
      case (signed int)(unsigned char)3U:
      {
        if(DockingApproachExample_Ext_DW.GPS_timer == 6)
        {
          if(!(DockingApproachExample_Ext_U.GPS_satelliteVisibility_status == 0))
          {
            if(!(DockingApproachExample_Ext_U.GPS_receiverAvailability_status == 0))
              goto __CPROVER_DUMP_L70;

          }

          DockingApproachExample_Ext_DW.is_GPS = (unsigned char)1U;
          DockingApproachExample_Ext_DW.GPS_AbsolutePosition = (signed char)0;
          DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity = (signed char)0;
          DockingApproachExample_Ext_DW.GPS_AbsoluteTime = (signed char)0;
        }

        else
        {

        __CPROVER_DUMP_L70:
          ;
          if(DockingApproachExample_Ext_DW.GPS_timer == 6)
          {
            if(!(DockingApproachExample_Ext_U.GPS_satelliteVisibility_status == 2))
              goto __CPROVER_DUMP_L71;

            if(DockingApproachExample_Ext_U.GPS_receiverAvailability_status == 0)
              goto __CPROVER_DUMP_L71;

            if(DockingApproachExample_Ext_U.sunlight_status != 0)
              goto __CPROVER_DUMP_L71;

            DockingApproachExample_Ext_DW.is_GPS = (unsigned char)2U;
            DockingApproachExample_Ext_DW.GPS_AbsolutePosition = (signed char)2;
            DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity = (signed char)2;
            DockingApproachExample_Ext_DW.GPS_AbsoluteTime = (signed char)2;
          }

          else
          {

          __CPROVER_DUMP_L71:
            ;
            if((signed int)DockingApproachExample_Ext_DW.GPS_timer < 6)
            {
              if(!(DockingApproachExample_Ext_U.GPS_satelliteVisibility_status == 0))
              {
                if(!(DockingApproachExample_Ext_U.GPS_receiverAvailability_status == 0))
                  goto __CPROVER_DUMP_L73;

              }

            }

            else
            {

            __CPROVER_DUMP_L73:
              ;
              if(!(DockingApproachExample_Ext_U.GPS_receiverAvailability_status == 0))
              {
                if(!(DockingApproachExample_Ext_U.GPS_satelliteVisibility_status == 1))
                {
                  if(DockingApproachExample_Ext_U.sunlight_status == 0)
                    goto __CPROVER_DUMP_L75;

                }

              }

              else
              {

              __CPROVER_DUMP_L75:
                ;
                goto __CPROVER_DUMP_L77;
              }
            }
            DockingApproachExample_Ext_DW.is_GPS = (unsigned char)3U;
            DockingApproachExample_Ext_DW.GPS_timer = (signed char)0;
            DockingApproachExample_Ext_DW.GPS_AbsolutePosition = (signed char)1;
            DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity = (signed char)1;
            DockingApproachExample_Ext_DW.GPS_AbsoluteTime = (signed char)1;
          }
        }

      __CPROVER_DUMP_L77:
        ;
        break;
      }
      default:
        DockingApproachExample_Ext_DW.is_GPS = (unsigned char)0U;
    }
  }

  if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_StarPlanetTracker == 0U))
  {
    b_previousEvent = (signed int)DockingApproachExample_Ext_DW.StarPlanetTracker_timer + 1;
    if(b_previousEvent <= 6)
      DockingApproachExample_Ext_DW.StarPlanetTracker_timer = (signed char)b_previousEvent;

    else
      DockingApproachExample_Ext_DW.StarPlanetTracker_timer = (signed char)6;
    switch((signed int)DockingApproachExample_Ext_DW.is_StarPlanetTracker)
    {
      case (signed int)(unsigned char)1U:
      {
        if(!(DockingApproachExample_Ext_U.StarPlanetTracker_planetVisibil == 0))
        {
          if(DockingApproachExample_Ext_U.StarPlanetTracker_starVisibilit == 0)
            goto __CPROVER_DUMP_L83;

          if(DockingApproachExample_Ext_U.opticsAvailability_status == 0)
            goto __CPROVER_DUMP_L83;

          DockingApproachExample_Ext_DW.is_StarPlanetTracker = (unsigned char)3U;
          DockingApproachExample_Ext_DW.StarPlanetTracker_timer = (signed char)0;
          DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit = (signed char)1;
          DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc = (signed char)1;
          DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteAttit = (signed char)1;
          DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteTime = (signed char)1;
        }

        else
        {

        __CPROVER_DUMP_L83:
          ;
          if(!(DockingApproachExample_Ext_U.StarPlanetTracker_planetVisibil == 0))
          {
            if(DockingApproachExample_Ext_U.StarPlanetTracker_starVisibilit == 0)
              goto __CPROVER_DUMP_L84;

            if(DockingApproachExample_Ext_U.opticsAvailability_status == 0)
              goto __CPROVER_DUMP_L84;

          }

          else
          {

          __CPROVER_DUMP_L84:
            ;
            DockingApproachExample_Ext_DW.is_StarPlanetTracker = (unsigned char)1U;
            DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit = (signed char)0;
            DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc = (signed char)0;
            DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteAttit = (signed char)0;
            DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteTime = (signed char)0;
          }
        }
        break;
      }
      case (signed int)(unsigned char)2U:
      {
        if(!(DockingApproachExample_Ext_U.StarPlanetTracker_planetVisibil == 2))
        {
          if(DockingApproachExample_Ext_U.StarPlanetTracker_starVisibilit == 2)
            goto __CPROVER_DUMP_L87;

          if(DockingApproachExample_Ext_U.opticsAvailability_status != 0)
            goto __CPROVER_DUMP_L87;

        }

        else
        {

        __CPROVER_DUMP_L87:
          ;
          if(DockingApproachExample_Ext_U.sunlight_status == 0)
            goto __CPROVER_DUMP_L89;

        }
        DockingApproachExample_Ext_DW.is_StarPlanetTracker = (unsigned char)3U;
        DockingApproachExample_Ext_DW.StarPlanetTracker_timer = (signed char)0;
        DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit = (signed char)1;
        DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc = (signed char)1;
        DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteAttit = (signed char)1;
        DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteTime = (signed char)1;
        goto __CPROVER_DUMP_L90;

      __CPROVER_DUMP_L89:
        ;
        if(DockingApproachExample_Ext_U.StarPlanetTracker_planetVisibil == 2)
        {
          if(DockingApproachExample_Ext_U.StarPlanetTracker_starVisibilit == 2)
          {
            if(!(DockingApproachExample_Ext_U.opticsAvailability_status == 0))
            {
              if(DockingApproachExample_Ext_U.sunlight_status == 0)
              {
                DockingApproachExample_Ext_DW.is_StarPlanetTracker = (unsigned char)2U;
                DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit = (signed char)2;
                DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc = (signed char)2;
                DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteAttit = (signed char)2;
                DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteTime = (signed char)2;
              }

            }

          }

        }


      __CPROVER_DUMP_L90:
        ;
        break;
      }
      case (signed int)(unsigned char)3U:
      {
        if(DockingApproachExample_Ext_DW.StarPlanetTracker_timer == 6)
        {
          if(!(DockingApproachExample_Ext_U.StarPlanetTracker_planetVisibil == 0))
          {
            if(!(DockingApproachExample_Ext_U.StarPlanetTracker_starVisibilit == 0))
            {
              if(!(DockingApproachExample_Ext_U.opticsAvailability_status == 0))
                goto __CPROVER_DUMP_L93;

            }

          }

          DockingApproachExample_Ext_DW.is_StarPlanetTracker = (unsigned char)1U;
          DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit = (signed char)0;
          DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc = (signed char)0;
          DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteAttit = (signed char)0;
          DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteTime = (signed char)0;
        }

        else
        {

        __CPROVER_DUMP_L93:
          ;
          if(DockingApproachExample_Ext_DW.StarPlanetTracker_timer == 6)
          {
            if(!(DockingApproachExample_Ext_U.StarPlanetTracker_planetVisibil == 2))
              goto __CPROVER_DUMP_L94;

            if(!(DockingApproachExample_Ext_U.StarPlanetTracker_starVisibilit == 2))
              goto __CPROVER_DUMP_L94;

            if(DockingApproachExample_Ext_U.opticsAvailability_status == 0)
              goto __CPROVER_DUMP_L94;

            if(DockingApproachExample_Ext_U.sunlight_status != 0)
              goto __CPROVER_DUMP_L94;

            DockingApproachExample_Ext_DW.is_StarPlanetTracker = (unsigned char)2U;
            DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit = (signed char)2;
            DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc = (signed char)2;
            DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteAttit = (signed char)2;
            DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteTime = (signed char)2;
          }

          else
          {

          __CPROVER_DUMP_L94:
            ;
            if((signed int)DockingApproachExample_Ext_DW.StarPlanetTracker_timer < 6)
            {
              if(!(DockingApproachExample_Ext_U.StarPlanetTracker_planetVisibil == 0))
              {
                if(!(DockingApproachExample_Ext_U.StarPlanetTracker_starVisibilit == 0))
                {
                  if(!(DockingApproachExample_Ext_U.opticsAvailability_status == 0))
                    goto __CPROVER_DUMP_L96;

                }

              }

            }

            else
            {

            __CPROVER_DUMP_L96:
              ;
              if(!(DockingApproachExample_Ext_U.opticsAvailability_status == 0))
              {
                if(DockingApproachExample_Ext_U.sunlight_status == 0)
                {
                  if(!(DockingApproachExample_Ext_U.StarPlanetTracker_planetVisibil == 1))
                  {
                    if(!(DockingApproachExample_Ext_U.StarPlanetTracker_starVisibilit == 1))
                      goto __CPROVER_DUMP_L98;

                  }

                }

              }

              else
              {

              __CPROVER_DUMP_L98:
                ;
                goto __CPROVER_DUMP_L100;
              }
            }
            DockingApproachExample_Ext_DW.is_StarPlanetTracker = (unsigned char)3U;
            DockingApproachExample_Ext_DW.StarPlanetTracker_timer = (signed char)0;
            DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit = (signed char)1;
            DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc = (signed char)1;
            DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteAttit = (signed char)1;
            DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteTime = (signed char)1;
          }
        }

      __CPROVER_DUMP_L100:
        ;
        break;
      }
      default:
        DockingApproachExample_Ext_DW.is_StarPlanetTracker = (unsigned char)0U;
    }
  }

  if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_InertialNavigation == 0U))
    DockingAppro_InertialNavigation();

}

// DockingAppro_InertialNavigation
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 149
static void DockingAppro_InertialNavigation(void)
{
  signed int u = (signed int)DockingApproachExample_Ext_DW.InertialNavigation_timer + 1;
  if(u <= 6)
    DockingApproachExample_Ext_DW.InertialNavigation_timer = (signed char)u;

  else
    DockingApproachExample_Ext_DW.InertialNavigation_timer = (signed char)6;
  switch((signed int)DockingApproachExample_Ext_DW.is_InertialNavigation)
  {
    case (signed int)(unsigned char)1U:
    {
      if(DockingApproachExample_Ext_DW.sfEvent == 0)
      {
        DockingApproachExample_Ext_DW.is_InertialNavigation = (unsigned char)2U;
        DockingApproachExample_Ext_DW.InertialNavigation_timer = (signed char)0;
        DockingApproachExample_Ext_DW.InertialNavigation_AbsolutePosi = (signed char)2;
        DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteVelo = (signed char)2;
        DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteAtti = (signed char)2;
      }

      break;
    }
    case (signed int)(unsigned char)2U:
    {
      if(DockingApproachExample_Ext_DW.InertialNavigation_timer == 6)
      {
        DockingApproachExample_Ext_DW.is_InertialNavigation = (unsigned char)3U;
        DockingApproachExample_Ext_DW.InertialNavigation_AbsolutePosi = (signed char)1;
        DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteVelo = (signed char)1;
        DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteAtti = (signed char)1;
      }

      else
        if((signed int)DockingApproachExample_Ext_DW.InertialNavigation_timer < 6)
        {
          DockingApproachExample_Ext_DW.is_InertialNavigation = (unsigned char)2U;
          DockingApproachExample_Ext_DW.InertialNavigation_timer = (signed char)0;
          DockingApproachExample_Ext_DW.InertialNavigation_AbsolutePosi = (signed char)2;
          DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteVelo = (signed char)2;
          DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteAtti = (signed char)2;
        }

        else
          if(!(DockingApproachExample_Ext_U.InertialNavigation_time == DockingApproachExample_Ext_DW.VALID))
          {
            DockingApproachExample_Ext_DW.is_InertialNavigation = (unsigned char)1U;
            DockingApproachExample_Ext_DW.InertialNavigation_AbsolutePosi = (signed char)0;
            DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteVelo = (signed char)0;
            DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteAtti = (signed char)0;
          }

      break;
    }
    case (signed int)(unsigned char)3U:
    {
      if(DockingApproachExample_Ext_DW.sfEvent == 0)
      {
        DockingApproachExample_Ext_DW.is_InertialNavigation = (unsigned char)2U;
        DockingApproachExample_Ext_DW.InertialNavigation_timer = (signed char)0;
        DockingApproachExample_Ext_DW.InertialNavigation_AbsolutePosi = (signed char)2;
        DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteVelo = (signed char)2;
        DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteAtti = (signed char)2;
      }

      else
        if(!(DockingApproachExample_Ext_U.InertialNavigation_time == DockingApproachExample_Ext_DW.VALID))
        {
          DockingApproachExample_Ext_DW.is_InertialNavigation = (unsigned char)1U;
          DockingApproachExample_Ext_DW.InertialNavigation_AbsolutePosi = (signed char)0;
          DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteVelo = (signed char)0;
          DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteAtti = (signed char)0;
        }

      break;
    }
    default:
      DockingApproachExample_Ext_DW.is_InertialNavigation = (unsigned char)0U;
  }
}

// DockingAppro_MissionPhaseStates
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 1550
static void DockingAppro_MissionPhaseStates(void)
{
  signed int u;
  switch((signed int)DockingApproachExample_Ext_DW.is_MissionPhaseStates)
  {
    case (signed int)(unsigned char)1U:
    {
      if((signed int)DockingApproachExample_Ext_U.StageTransition == 2)
      {
        DockingApproachExample_Ext_Y.ApproachOrbitComplete = (unsigned char)1U;
        DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)11U;
      }

      break;
    }
    case (signed int)(unsigned char)2U:
    {
      if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_CaptureApproach == 0U))
      {
        u = (signed int)DockingApproachExample_Ext_DW.CaptureApproach_timer + 1;
        if(u <= 11)
          DockingApproachExample_Ext_DW.CaptureApproach_timer = (signed char)u;

        else
          DockingApproachExample_Ext_DW.CaptureApproach_timer = (signed char)11;
        switch((signed int)DockingApproachExample_Ext_DW.is_CaptureApproach)
        {
          case (signed int)(unsigned char)1U:
          {
            D_exit_internal_CaptureApproach();
            DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)3U;
            break;
          }
          case (signed int)(unsigned char)2U:
          {
            if(DockingApproachExample_Ext_DW.OrbitalState_Position == 2)
            {
              if(!(DockingApproachExample_Ext_DW.OrbitalState_Velocity == 2))
                goto __CPROVER_DUMP_L8;

              if(DockingApproachExample_Ext_DW.OrbitalState_Attitude == 0)
                goto __CPROVER_DUMP_L8;

              if(!(DockingApproachExample_Ext_DW.OrbitalState_Time == 2))
                goto __CPROVER_DUMP_L8;

              DockingApproachExample_Ext_DW.is_CaptureApproach = (unsigned char)4U;
            }

            else
            {

            __CPROVER_DUMP_L8:
              ;
              if(DockingApproachExample_Ext_DW.OrbitalState_Position == 1)
              {
                if(!(DockingApproachExample_Ext_DW.OrbitalState_Velocity == 1))
                  goto __CPROVER_DUMP_L9;

                if(!(DockingApproachExample_Ext_DW.OrbitalState_Attitude == 0))
                  goto __CPROVER_DUMP_L9;

                if(!(DockingApproachExample_Ext_DW.OrbitalState_Time == 1))
                  goto __CPROVER_DUMP_L9;

                DockingApproachExample_Ext_DW.is_CaptureApproach = (unsigned char)3U;
              }

              else
              {

              __CPROVER_DUMP_L9:
                ;
                if(!(DockingApproachExample_Ext_DW.OrbitalState_Position == 0))
                {
                  if(DockingApproachExample_Ext_DW.OrbitalState_Velocity == 0)
                    goto __CPROVER_DUMP_L10;

                  if(DockingApproachExample_Ext_DW.OrbitalState_Attitude == 0)
                    goto __CPROVER_DUMP_L10;

                  if(DockingApproachExample_Ext_DW.OrbitalState_Time == 0)
                    goto __CPROVER_DUMP_L10;

                  if(DockingApproachExample_Ext_DW.CaptureApproach_timer == 11)
                    goto __CPROVER_DUMP_L10;

                }

                else
                {

                __CPROVER_DUMP_L10:
                  ;
                  DockingApproachExample_Ext_DW.is_CaptureApproach = (unsigned char)1U;
                  DockingApproachExample_Ext_Y.CaptureApproachFailed = (unsigned char)1U;
                }
              }
            }
            break;
          }
          case (signed int)(unsigned char)3U:
          {
            if((unsigned int)DockingApproachExample_Ext_DW.thrust_status == 1U)
            {
              if(!(DockingApproachExample_Ext_DW.fuel_status == 2))
                goto __CPROVER_DUMP_L13;

              DockingApproachExample_Ext_DW.is_CaptureApproach = (unsigned char)2U;
            }

            else
            {

            __CPROVER_DUMP_L13:
              ;
              if((unsigned int)DockingApproachExample_Ext_DW.thrust_status == 1U)
              {
                if(!(DockingApproachExample_Ext_DW.fuel_status == 2))
                  goto __CPROVER_DUMP_L14;

                if(DockingApproachExample_Ext_DW.CaptureApproach_timer == 11)
                  goto __CPROVER_DUMP_L14;

              }

              else
              {

              __CPROVER_DUMP_L14:
                ;
                DockingApproachExample_Ext_DW.is_CaptureApproach = (unsigned char)1U;
                DockingApproachExample_Ext_Y.CaptureApproachFailed = (unsigned char)1U;
              }
            }
            break;
          }
          case (signed int)(unsigned char)4U:
          {
            D_exit_internal_CaptureApproach();
            DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)5U;
            DockingApproachExample_Ext_Y.DockingApproach = (unsigned char)1U;
            DockingApproachExample_Ext_Y.DockingApproachComplete = (unsigned char)0U;
            DockingApproachExample_Ext_DW.is_active_DockingApproach = (unsigned char)1U;
            if(!(DockingApproachExample_Ext_DW.is_DockingApproach == 5))
            {
              DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)5U;
              DockingApproachExample_Ext_DW.DockingApproach_timer = (signed char)0;
            }

            DockingApproachExample_Ext_DW.is_active_dockingSensor = (unsigned char)1U;
            if(!(DockingApproachExample_Ext_DW.is_dockingSensor == 1))
            {
              DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)1U;
              DockingApproachExample_Ext_DW.dockingSensor_RelativePosition = (signed char)0;
              DockingApproachExample_Ext_DW.dockingSensor_RelativeVelocity = (signed char)0;
              DockingApproachExample_Ext_DW.dockingSensor_RelativeAttitude = (signed char)0;
              DockingApproachExample_Ext_DW.dockingSensor_targetState = (signed char)0;
            }

            break;
          }
          case (signed int)(unsigned char)5U:
          {
            if(!(DockingApproachExample_Ext_DW.OrbitalState_Position == 0))
            {
              if(DockingApproachExample_Ext_DW.OrbitalState_Velocity == 0)
                goto __CPROVER_DUMP_L20;

              if(DockingApproachExample_Ext_DW.OrbitalState_Attitude == 0)
                goto __CPROVER_DUMP_L20;

              if(DockingApproachExample_Ext_DW.OrbitalState_Time == 0)
                goto __CPROVER_DUMP_L20;

              if(!((signed int)DockingApproachExample_Ext_DW.CaptureApproach_timer < 11))
                goto __CPROVER_DUMP_L20;

              DockingApproachExample_Ext_DW.is_CaptureApproach = (unsigned char)2U;
            }

            else
            {

            __CPROVER_DUMP_L20:
              ;
              if(DockingApproachExample_Ext_DW.CaptureApproach_timer == 11)
              {
                DockingApproachExample_Ext_DW.is_CaptureApproach = (unsigned char)1U;
                DockingApproachExample_Ext_Y.CaptureApproachFailed = (unsigned char)1U;
              }

            }
            break;
          }
          default:
            DockingApproachExample_Ext_DW.is_CaptureApproach = (unsigned char)0U;
        }
      }

      if(DockingApproachExample_Ext_DW.is_MissionPhaseStates == 2)
      {
        if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_OrbitalState_Active == 0U))
          DockingAppr_OrbitalState_Active();

      }

      break;
    }
    case (signed int)(unsigned char)3U:
    {
      if((signed int)DockingApproachExample_Ext_U.StageTransition == 8)
      {
        if(DockingApproachExample_Ext_DW.is_MissionPhaseStates == 3)
        {
          DockingApproachExample_Ext_Y.ApproachOrbitComplete = (unsigned char)0U;
          DockingApproachExample_Ext_Y.ProximityOperationsComplete = (unsigned char)0U;
          DockingApproachExample_Ext_Y.FarApproachComplete = (unsigned char)0U;
          DockingApproachExample_Ext_Y.CaptureApproachComplete = (unsigned char)0U;
          DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)0U;
        }

        if(!(DockingApproachExample_Ext_DW.is_MissionPhaseStates == 6))
        {
          DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)6U;
          DockingApproachExample_Ext_Y.FailedApproach = (unsigned char)1U;
        }

      }

      else
        if((signed int)DockingApproachExample_Ext_U.StageTransition == 6)
        {
          if(DockingApproachExample_Ext_DW.is_MissionPhaseStates == 3)
          {
            DockingApproachExample_Ext_Y.ApproachOrbitComplete = (unsigned char)0U;
            DockingApproachExample_Ext_Y.ProximityOperationsComplete = (unsigned char)0U;
            DockingApproachExample_Ext_Y.FarApproachComplete = (unsigned char)0U;
            DockingApproachExample_Ext_Y.CaptureApproachComplete = (unsigned char)0U;
          }

          DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)1U;
        }

      break;
    }
    case (signed int)(unsigned char)4U:
    {
      if((signed int)DockingApproachExample_Ext_U.StageTransition == 7)
        DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)3U;

      break;
    }
    case (signed int)(unsigned char)5U:
    {
      DockingApproach_DockingApproach();
      break;
    }
    case (signed int)(unsigned char)6U:
      break;
    case (signed int)(unsigned char)7U:
    {
      if((signed int)DockingApproachExample_Ext_U.StageTransition == 5)
        DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)3U;

      else
        if((signed int)DockingApproachExample_Ext_U.StageTransition == 4)
        {
          DockingApproachExample_Ext_Y.FarApproachComplete = (unsigned char)1U;
          DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)2U;
          DockingApproachExample_Ext_DW.is_active_CaptureApproach = (unsigned char)1U;
          if(!(DockingApproachExample_Ext_DW.is_CaptureApproach == 5))
          {
            DockingApproachExample_Ext_DW.is_CaptureApproach = (unsigned char)5U;
            DockingApproachExample_Ext_DW.CaptureApproach_timer = (signed char)0;
            DockingApproachExample_Ext_Y.CaptureApproachFailed = (unsigned char)0U;
          }

          DockingApproachExample_Ext_DW.is_active_OrbitalState_Active = (unsigned char)1U;
          enter_internal_OrbitalState_Act();
        }

      break;
    }
    case (signed int)(unsigned char)8U:
      break;
    case (signed int)(unsigned char)9U:
    {
      if((signed int)DockingApproachExample_Ext_U.StageTransition == 9)
        DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)4U;

      else
        if((signed int)DockingApproachExample_Ext_U.StageTransition == 10)
        {
          DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)8U;
          DockingApproachExample_Ext_Y.JointMission = (unsigned char)1U;
        }

      break;
    }
    case (signed int)(unsigned char)10U:
    {
      if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_LatchCaptureCheck == 0U))
      {
        u = (signed int)DockingApproachExample_Ext_DW.LatchCapture_timer + 1;
        if(u <= 9)
          DockingApproachExample_Ext_DW.LatchCapture_timer = (signed char)u;

        else
          DockingApproachExample_Ext_DW.LatchCapture_timer = (signed char)9;
        switch((signed int)DockingApproachExample_Ext_DW.is_LatchCaptureCheck)
        {
          case (signed int)(unsigned char)1U:
          {
            if(DockingApproachExample_Ext_DW.latch_status == 3)
            {
              DockingApproachExample_Ext_DW.is_LatchCaptureCheck = (unsigned char)3U;
              DockingApproachExample_Ext_Y.LatchCaptureComplete = (unsigned char)1U;
            }

            else
              if(!(DockingApproachExample_Ext_DW.latch_status == 2))
              {
                if(DockingApproachExample_Ext_DW.LatchCapture_timer == 8)
                  goto __CPROVER_DUMP_L48;

              }

              else
              {

              __CPROVER_DUMP_L48:
                ;
                DockingApproachExample_Ext_DW.is_LatchCaptureCheck = (unsigned char)4U;
              }
            break;
          }
          case (signed int)(unsigned char)2U:
          {
            if(DockingApproachExample_Ext_DW.latch_status == 1)
              DockingApproachExample_Ext_DW.is_LatchCaptureCheck = (unsigned char)1U;

            else
              if(DockingApproachExample_Ext_DW.LatchCapture_timer == 8)
                DockingApproachExample_Ext_DW.is_LatchCaptureCheck = (unsigned char)4U;

            break;
          }
          case (signed int)(unsigned char)3U:
          {
            DockingApproachExample_Ext_DW.is_latch = (unsigned char)0U;
            DockingApproachExample_Ext_DW.is_active_latch = (unsigned char)0U;
            DockingApproachExample_Ext_DW.is_LatchCaptureCheck = (unsigned char)0U;
            if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_LatchCaptureCheck == 0U))
            {
              DockingApproachExample_Ext_Y.AttemptingToDock = (unsigned char)0U;
              DockingApproachExample_Ext_DW.is_active_LatchCaptureCheck = (unsigned char)0U;
            }

            DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)9U;
            break;
          }
          case (signed int)(unsigned char)4U:
          {
            DockingApproachExample_Ext_DW.is_latch = (unsigned char)0U;
            DockingApproachExample_Ext_DW.is_active_latch = (unsigned char)0U;
            DockingApproachExample_Ext_DW.is_LatchCaptureCheck = (unsigned char)0U;
            if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_LatchCaptureCheck == 0U))
            {
              DockingApproachExample_Ext_Y.AttemptingToDock = (unsigned char)0U;
              DockingApproachExample_Ext_DW.is_active_LatchCaptureCheck = (unsigned char)0U;
            }

            DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)5U;
            DockingApproachExample_Ext_Y.DockingApproach = (unsigned char)1U;
            DockingApproachExample_Ext_Y.DockingApproachComplete = (unsigned char)0U;
            DockingApproachExample_Ext_DW.is_active_DockingApproach = (unsigned char)1U;
            if(!(DockingApproachExample_Ext_DW.is_DockingApproach == 1))
              DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)1U;

            DockingApproachExample_Ext_DW.is_active_dockingSensor = (unsigned char)1U;
            if(!(DockingApproachExample_Ext_DW.is_dockingSensor == 1))
            {
              DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)1U;
              DockingApproachExample_Ext_DW.dockingSensor_RelativePosition = (signed char)0;
              DockingApproachExample_Ext_DW.dockingSensor_RelativeVelocity = (signed char)0;
              DockingApproachExample_Ext_DW.dockingSensor_RelativeAttitude = (signed char)0;
              DockingApproachExample_Ext_DW.dockingSensor_targetState = (signed char)0;
            }

            break;
          }
          default:
            DockingApproachExample_Ext_DW.is_LatchCaptureCheck = (unsigned char)0U;
        }
      }

      if(DockingApproachExample_Ext_DW.is_MissionPhaseStates == 10)
      {
        if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_latch == 0U))
          switch((signed int)DockingApproachExample_Ext_DW.is_latch)
          {
            case (signed int)(unsigned char)1U:
            {
              DockingApproachExample_Ext_DW.is_latch = (unsigned char)5U;
              DockingApproachExample_Ext_DW.latch_status = (signed char)0;
              break;
            }
            case (signed int)(unsigned char)2U:
            {
              DockingApproachExample_Ext_DW.is_latch = (unsigned char)3U;
              DockingApproachExample_Ext_DW.latch_status = (signed char)3;
              break;
            }
            case (signed int)(unsigned char)3U:
            {
              DockingApproachExample_Ext_DW.is_latch = (unsigned char)5U;
              DockingApproachExample_Ext_DW.latch_status = (signed char)0;
              break;
            }
            case (signed int)(unsigned char)4U:
            {
              DockingApproachExample_Ext_DW.is_latch = (unsigned char)2U;
              DockingApproachExample_Ext_DW.latch_status = (signed char)0;
              break;
            }
            case (signed int)(unsigned char)5U:
            {
              DockingApproachExample_Ext_DW.is_latch = (unsigned char)4U;
              DockingApproachExample_Ext_DW.latch_status = (signed char)1;
              break;
            }
            default:
              DockingApproachExample_Ext_DW.is_latch = (unsigned char)0U;
          }

      }

      break;
    }
    case (signed int)(unsigned char)11U:
    {
      if((signed int)DockingApproachExample_Ext_U.StageTransition == 1)
      {
        DockingApproachExample_Ext_Y.ApproachOrbitComplete = (unsigned char)0U;
        DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)1U;
      }

      else
        if((signed int)DockingApproachExample_Ext_U.StageTransition == 3)
        {
          DockingApproachExample_Ext_Y.ProximityOperationsComplete = (unsigned char)1U;
          DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)7U;
        }

      break;
    }
    case (signed int)(unsigned char)12U:
    {
      if((signed int)DockingApproachExample_Ext_U.StageTransition == 0)
        DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)1U;

      break;
    }
    default:
      DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)0U;
  }
}

// DockingApproachExample_Ext
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2352
struct tag_RTM_DockingApproachExampl_T * DockingApproachExample_Ext(void)
{
  rt_InitInfAndNaN(sizeof(double) /*8ul*/ );
  signed int *mdlTsMap = DockingApproachExample_Ext_M->Timing.sampleTimeTaskIDArray;
  mdlTsMap[(signed long int)0] = 0;
  DockingApproachExample_Ext_M->Timing.sampleTimeTaskIDPtr = &mdlTsMap[(signed long int)0];
  DockingApproachExample_Ext_M->Timing.sampleTimes = &DockingApproachExample_Ext_M->Timing.sampleTimesArray[(signed long int)0];
  DockingApproachExample_Ext_M->Timing.offsetTimes = &DockingApproachExample_Ext_M->Timing.offsetTimesArray[(signed long int)0];
  DockingApproachExample_Ext_M->Timing.sampleTimes[(signed long int)0] = 1.0;
  DockingApproachExample_Ext_M->Timing.offsetTimes[(signed long int)0] = 0.0;
  DockingApproachExample_Ext_M->Timing.t = &DockingApproachExample_Ext_M->Timing.tArray[(signed long int)0];
  signed int *mdlSampleHits = DockingApproachExample_Ext_M->Timing.sampleHitArray;
  mdlSampleHits[(signed long int)0] = 1;
  DockingApproachExample_Ext_M->Timing.sampleHits = &mdlSampleHits[(signed long int)0];
  DockingApproachExample_Ext_M->Timing.tFinal = 300.0;
  DockingApproachExample_Ext_M->Timing.stepSize0 = 1.0;
  static struct _RTWLogInfo_tag rt_DataLoggingInfo;
  DockingApproachExample_Ext_M->rtwLogInfo = &rt_DataLoggingInfo;
  DockingApproachExample_Ext_M->rtwLogInfo->logXSignalInfo.cptr = (const struct RTWLogSignalInfo_tag *)(void *)0;
  DockingApproachExample_Ext_M->rtwLogInfo->logXSignalPtrs.cptr = (const signed char * const *)(void *)0;
  DockingApproachExample_Ext_M->rtwLogInfo->logT = "tout";
  DockingApproachExample_Ext_M->rtwLogInfo->logX = "";
  DockingApproachExample_Ext_M->rtwLogInfo->logXFinal = "";
  DockingApproachExample_Ext_M->rtwLogInfo->logSL = "";
  DockingApproachExample_Ext_M->rtwLogInfo->logVarNameModifier = "rt_";
  DockingApproachExample_Ext_M->rtwLogInfo->logFormat = 0;
  DockingApproachExample_Ext_M->rtwLogInfo->logMaxRows = 1000;
  DockingApproachExample_Ext_M->rtwLogInfo->logDecimation = 1;
  static void *rt_LoggedOutputSignalPtrs[11l] = { (void *)&DockingApproachExample_Ext_Y.CaptureApproachComplete, 
    (void *)&DockingApproachExample_Ext_Y.DockingApproachComplete, 
    (void *)&DockingApproachExample_Ext_Y.AttemptingToDock, 
    (void *)&DockingApproachExample_Ext_Y.LatchCaptureComplete, 
    (void *)&DockingApproachExample_Ext_Y.DockingApproach, 
    (void *)&DockingApproachExample_Ext_Y.ApproachOrbitComplete, 
    (void *)&DockingApproachExample_Ext_Y.FarApproachComplete, 
    (void *)&DockingApproachExample_Ext_Y.ProximityOperationsComplete, 
    (void *)&DockingApproachExample_Ext_Y.FailedApproach, 
    (void *)&DockingApproachExample_Ext_Y.JointMission, 
    (void *)&DockingApproachExample_Ext_Y.CaptureApproachFailed };
  DockingApproachExample_Ext_M->rtwLogInfo->logYSignalPtrs.cptr = (const signed char * const *)rt_LoggedOutputSignalPtrs;
  static struct RTWLogDataTypeConvert_tag rt_RTWLogDataTypeConvert[11l] = { { .conversionNeeded=0, .dataTypeIdLoggingTo=(enum anonymous$17)SS_BOOLEAN, .dataTypeIdOriginal=SS_BOOLEAN,
    .bitsPerChunk=0, .numOfChunk=0,
    .isSigned=(unsigned int)0, .fracSlope=1.0,
    .fixedExp=0, .bias=0.0 }, 
    { .conversionNeeded=0, .dataTypeIdLoggingTo=(enum anonymous$17)SS_BOOLEAN, .dataTypeIdOriginal=SS_BOOLEAN,
    .bitsPerChunk=0, .numOfChunk=0,
    .isSigned=(unsigned int)0, .fracSlope=1.0,
    .fixedExp=0, .bias=0.0 }, 
    { .conversionNeeded=0, .dataTypeIdLoggingTo=(enum anonymous$17)SS_BOOLEAN, .dataTypeIdOriginal=SS_BOOLEAN,
    .bitsPerChunk=0, .numOfChunk=0,
    .isSigned=(unsigned int)0, .fracSlope=1.0,
    .fixedExp=0, .bias=0.0 }, 
    { .conversionNeeded=0, .dataTypeIdLoggingTo=(enum anonymous$17)SS_BOOLEAN, .dataTypeIdOriginal=SS_BOOLEAN,
    .bitsPerChunk=0, .numOfChunk=0,
    .isSigned=(unsigned int)0, .fracSlope=1.0,
    .fixedExp=0, .bias=0.0 }, 
    { .conversionNeeded=0, .dataTypeIdLoggingTo=(enum anonymous$17)SS_BOOLEAN, .dataTypeIdOriginal=SS_BOOLEAN,
    .bitsPerChunk=0, .numOfChunk=0,
    .isSigned=(unsigned int)0, .fracSlope=1.0,
    .fixedExp=0, .bias=0.0 }, 
    { .conversionNeeded=0, .dataTypeIdLoggingTo=(enum anonymous$17)SS_BOOLEAN, .dataTypeIdOriginal=SS_BOOLEAN,
    .bitsPerChunk=0, .numOfChunk=0,
    .isSigned=(unsigned int)0, .fracSlope=1.0,
    .fixedExp=0, .bias=0.0 }, 
    { .conversionNeeded=0, .dataTypeIdLoggingTo=(enum anonymous$17)SS_BOOLEAN, .dataTypeIdOriginal=SS_BOOLEAN,
    .bitsPerChunk=0, .numOfChunk=0,
    .isSigned=(unsigned int)0, .fracSlope=1.0,
    .fixedExp=0, .bias=0.0 }, 
    { .conversionNeeded=0, .dataTypeIdLoggingTo=(enum anonymous$17)SS_BOOLEAN, .dataTypeIdOriginal=SS_BOOLEAN,
    .bitsPerChunk=0, .numOfChunk=0,
    .isSigned=(unsigned int)0, .fracSlope=1.0,
    .fixedExp=0, .bias=0.0 }, 
    { .conversionNeeded=0, .dataTypeIdLoggingTo=(enum anonymous$17)SS_BOOLEAN, .dataTypeIdOriginal=SS_BOOLEAN,
    .bitsPerChunk=0, .numOfChunk=0,
    .isSigned=(unsigned int)0, .fracSlope=1.0,
    .fixedExp=0, .bias=0.0 }, 
    { .conversionNeeded=0, .dataTypeIdLoggingTo=(enum anonymous$17)SS_BOOLEAN, .dataTypeIdOriginal=SS_BOOLEAN,
    .bitsPerChunk=0, .numOfChunk=0,
    .isSigned=(unsigned int)0, .fracSlope=1.0,
    .fixedExp=0, .bias=0.0 }, 
    { .conversionNeeded=0, .dataTypeIdLoggingTo=(enum anonymous$17)SS_BOOLEAN, .dataTypeIdOriginal=SS_BOOLEAN,
    .bitsPerChunk=0, .numOfChunk=0,
    .isSigned=(unsigned int)0, .fracSlope=1.0,
    .fixedExp=0, .bias=0.0 } };
  static const char *rt_LoggedOutputBlockNames[11l] = { "DockingApproachExample_Ext/CaptureApproachComplete", 
    "DockingApproachExample_Ext/DockingApproachComplete", 
    "DockingApproachExample_Ext/AttemptingToDock", 
    "DockingApproachExample_Ext/LatchCaptureComplete", 
    "DockingApproachExample_Ext/DockingApproach", 
    "DockingApproachExample_Ext/ApproachOrbitComplete", 
    "DockingApproachExample_Ext/FarApproachComplete", 
    "DockingApproachExample_Ext/ProximityOperationsComplete", 
    "DockingApproachExample_Ext/FailedApproach", 
    "DockingApproachExample_Ext/JointMission", 
    "DockingApproachExample_Ext/CaptureApproachFailed" };
  static const char *rt_LoggedOutputLabels[11l] = { "", "", "", "", "", "", "", "", "", "", "" };
  static signed int rt_LoggedOutputComplexSignals[11l] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  static enum anonymous$17 rt_LoggedOutputDataTypeIds[11l] = { (enum anonymous$17)SS_BOOLEAN, (enum anonymous$17)SS_BOOLEAN, (enum anonymous$17)SS_BOOLEAN, (enum anonymous$17)SS_BOOLEAN, (enum anonymous$17)SS_BOOLEAN, (enum anonymous$17)SS_BOOLEAN, (enum anonymous$17)SS_BOOLEAN, (enum anonymous$17)SS_BOOLEAN, (enum anonymous$17)SS_BOOLEAN, (enum anonymous$17)SS_BOOLEAN, (enum anonymous$17)SS_BOOLEAN };
  static signed int rt_LoggedCurrentSignalDimensionsSize[11l] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
  static void *rt_LoggedCurrentSignalDimensions[11l] = { (void *)0, (void *)0, (void *)0, (void *)0, (void *)0, (void *)0, (void *)0, (void *)0, (void *)0, (void *)0, (void *)0 };
  static unsigned char rt_LoggedOutputIsVarDims[11l] = { (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0 };
  static signed int rt_LoggedOutputDimensions[11l] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  static signed int rt_LoggedOutputNumDimensions[11l] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  static signed int rt_LoggedOutputWidths[11l] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  static struct RTWLogSignalInfo_tag rt_LoggedOutputSignalInfo[1l] = { { .numSignals=11, .numCols=rt_LoggedOutputWidths, .numDims=rt_LoggedOutputNumDimensions,
    .dims=rt_LoggedOutputDimensions,
    .isVarDims=rt_LoggedOutputIsVarDims, .currSigDims=rt_LoggedCurrentSignalDimensions,
    .currSigDimsSize=rt_LoggedCurrentSignalDimensionsSize,
    .dataTypes=rt_LoggedOutputDataTypeIds,
    .complexSignals=rt_LoggedOutputComplexSignals,
    .frameData=(signed int *)(void *)0,
    .labels={ .cptr=rt_LoggedOutputLabels }, .titles=(char *)(void *)0,
    .titleLengths=(signed int *)(void *)0, .plotStyles=(signed int *)(void *)0,
    .blockNames={ .cptr=rt_LoggedOutputBlockNames },
    .stateNames={ .cptr=(const char **)(void *)0 },
    .crossMdlRef=(unsigned char *)(void *)0,
    .dataTypeConvert=rt_RTWLogDataTypeConvert } };
  DockingApproachExample_Ext_M->rtwLogInfo->logYSignalInfo.cptr = rt_LoggedOutputSignalInfo;
  rt_LoggedCurrentSignalDimensions[(signed long int)0] = (void *)&rt_LoggedOutputWidths[(signed long int)0];
  rt_LoggedCurrentSignalDimensions[(signed long int)1] = (void *)&rt_LoggedOutputWidths[(signed long int)1];
  rt_LoggedCurrentSignalDimensions[(signed long int)2] = (void *)&rt_LoggedOutputWidths[(signed long int)2];
  rt_LoggedCurrentSignalDimensions[(signed long int)3] = (void *)&rt_LoggedOutputWidths[(signed long int)3];
  rt_LoggedCurrentSignalDimensions[(signed long int)4] = (void *)&rt_LoggedOutputWidths[(signed long int)4];
  rt_LoggedCurrentSignalDimensions[(signed long int)5] = (void *)&rt_LoggedOutputWidths[(signed long int)5];
  rt_LoggedCurrentSignalDimensions[(signed long int)6] = (void *)&rt_LoggedOutputWidths[(signed long int)6];
  rt_LoggedCurrentSignalDimensions[(signed long int)7] = (void *)&rt_LoggedOutputWidths[(signed long int)7];
  rt_LoggedCurrentSignalDimensions[(signed long int)8] = (void *)&rt_LoggedOutputWidths[(signed long int)8];
  rt_LoggedCurrentSignalDimensions[(signed long int)9] = (void *)&rt_LoggedOutputWidths[(signed long int)9];
  rt_LoggedCurrentSignalDimensions[(signed long int)10] = (void *)&rt_LoggedOutputWidths[(signed long int)10];
  DockingApproachExample_Ext_M->rtwLogInfo->logY = "yout";
  DockingApproachExample_Ext_M->solverInfoPtr = &DockingApproachExample_Ext_M->solverInfo;
  DockingApproachExample_Ext_M->Timing.stepSize = 1.0;
  (&DockingApproachExample_Ext_M->solverInfo)->fixedStepSize = 1.0;
  (&DockingApproachExample_Ext_M->solverInfo)->solverMode = (enum anonymous$13)SOLVER_MODE_SINGLETASKING;
  DockingApproachExample_Ext_M->ModelData.dwork = (void *)&DockingApproachExample_Ext_DW;
  DockingApproachExample_Ext_M->ModelData.inputs = (void *)&DockingApproachExample_Ext_U;
  DockingApproachExample_Ext_M->ModelData.outputs = (void *)&DockingApproachExample_Ext_Y;
  DockingApproachExample_Ext_M->Sizes.numContStates = 0;
  DockingApproachExample_Ext_M->Sizes.numY = 11;
  DockingApproachExample_Ext_M->Sizes.numU = 13;
  DockingApproachExample_Ext_M->Sizes.sysDirFeedThru = 1;
  DockingApproachExample_Ext_M->Sizes.numSampTimes = 1;
  DockingApproachExample_Ext_M->Sizes.numBlocks = 13;
  DockingApproachExample_Ext_M->Sizes.numBlockIO = 11;
  return DockingApproachExample_Ext_M;
}

// DockingApproachExample_Ext_initialize
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2176
void DockingApproachExample_Ext_initialize(void)
{
  DockingApproachExample_Ext_DW.sfEvent = -1;
  DockingApproachExample_Ext_DW.is_active_MissionPhaseStates = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_CaptureApproach = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_CaptureApproach = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_OrbitalState_Active = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_GPS = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_GPS = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_InertialNavigation = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_InertialNavigation = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_OrbitalState_Complex = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_OrbitalState = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_OrbitalState = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_OrbitalState2 = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_OrbitalState2 = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_StarPlanetTracker = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_StarPlanetTracker = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_DockingApproach = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_dockingSensor = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_LatchCaptureCheck = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_LatchCaptureCheck = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_latch = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_latch = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_fuel = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_thrust = (unsigned char)0U;
  DockingApproachExample_Ext_DW.is_active_c1_DockingApproachExa = (unsigned char)0U;
  DockingApproachExample_Ext_DW.OrbitalState_Position = (signed char)0;
  DockingApproachExample_Ext_DW.OrbitalState_Velocity = (signed char)0;
  DockingApproachExample_Ext_DW.OrbitalState_Attitude = (signed char)0;
  DockingApproachExample_Ext_DW.OrbitalState_Time = (signed char)0;
  DockingApproachExample_Ext_DW.InertialNavigation_AbsolutePosi = (signed char)0;
  DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteAtti = (signed char)0;
  DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteVelo = (signed char)0;
  DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity = (signed char)0;
  DockingApproachExample_Ext_DW.GPS_AbsoluteTime = (signed char)0;
  DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteAttit = (signed char)0;
  DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit = (signed char)0;
  DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteTime = (signed char)0;
  DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc = (signed char)0;
  DockingApproachExample_Ext_DW.GPS_AbsolutePosition = (signed char)0;
  DockingApproachExample_Ext_DW.dockingSensor_RelativePosition = (signed char)0;
  DockingApproachExample_Ext_DW.dockingSensor_RelativeVelocity = (signed char)0;
  DockingApproachExample_Ext_DW.dockingSensor_RelativeAttitude = (signed char)0;
  DockingApproachExample_Ext_DW.dockingSensor_targetState = (signed char)0;
  DockingApproachExample_Ext_DW.thrust_status = (signed char)0;
  DockingApproachExample_Ext_DW.fuel_status = (signed char)0;
  DockingApproachExample_Ext_DW.DockingApproach_timer = (signed char)0;
  DockingApproachExample_Ext_DW.CaptureApproach_timer = (signed char)0;
  DockingApproachExample_Ext_DW.latch_status = (signed char)0;
  DockingApproachExample_Ext_DW.LatchCapture_timer = (signed char)0;
  DockingApproachExample_Ext_DW.dockingSensor_timer = (signed char)0;
  DockingApproachExample_Ext_DW.InertialNavigation_timer = (signed char)0;
  DockingApproachExample_Ext_DW.StarPlanetTracker_timer = (signed char)0;
  DockingApproachExample_Ext_DW.GPS_timer = (signed char)0;
  DockingApproachExample_Ext_DW.VALID = (unsigned char)0U;
  DockingApproachExample_Ext_Y.CaptureApproachComplete = (unsigned char)0U;
  DockingApproachExample_Ext_Y.DockingApproachComplete = (unsigned char)0U;
  DockingApproachExample_Ext_Y.AttemptingToDock = (unsigned char)0U;
  DockingApproachExample_Ext_Y.LatchCaptureComplete = (unsigned char)0U;
  DockingApproachExample_Ext_Y.DockingApproach = (unsigned char)0U;
  DockingApproachExample_Ext_Y.ApproachOrbitComplete = (unsigned char)0U;
  DockingApproachExample_Ext_Y.FarApproachComplete = (unsigned char)0U;
  DockingApproachExample_Ext_Y.ProximityOperationsComplete = (unsigned char)0U;
  DockingApproachExample_Ext_Y.FailedApproach = (unsigned char)0U;
  DockingApproachExample_Ext_Y.JointMission = (unsigned char)0U;
  DockingApproachExample_Ext_Y.CaptureApproachFailed = (unsigned char)0U;
}

// DockingApproachExample_Ext_output
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2123
static void DockingApproachExample_Ext_output(void)
{
  DockingApproachExample_Ext_DW.sfEvent = -1;
  if((unsigned int)DockingApproachExample_Ext_DW.is_active_c1_DockingApproachExa == 0U)
  {
    DockingApproachExample_Ext_DW.is_active_c1_DockingApproachExa = (unsigned char)1U;
    DockingApproachExample_Ext_DW.is_active_MissionPhaseStates = (unsigned char)1U;
    DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)12U;
    DockingApproachExample_Ext_DW.is_active_thrust = (unsigned char)1U;
    DockingApproachExample_Ext_DW.is_active_fuel = (unsigned char)1U;
  }

  else
    if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_MissionPhaseStates == 0U))
      DockingAppro_MissionPhaseStates();

}

// DockingApproachExample_Ext_terminate
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2303
void DockingApproachExample_Ext_terminate(void)
{
  ;
}

// DockingApproachExample_Ext_update
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2153
static void DockingApproachExample_Ext_update(void)
{
  DockingApproachExample_Ext_M->Timing.clockTick0 = DockingApproachExample_Ext_M->Timing.clockTick0 + 1u;
  if(DockingApproachExample_Ext_M->Timing.clockTick0 == 0u)
    DockingApproachExample_Ext_M->Timing.clockTickH0 = DockingApproachExample_Ext_M->Timing.clockTickH0 + 1u;

  DockingApproachExample_Ext_M->Timing.t[(signed long int)0] = (double)DockingApproachExample_Ext_M->Timing.clockTick0 * DockingApproachExample_Ext_M->Timing.stepSize0 + (double)DockingApproachExample_Ext_M->Timing.clockTickH0 * DockingApproachExample_Ext_M->Timing.stepSize0 * 4294967296.0;
}

// DockingApproach_DockingApproach
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 1136
static void DockingApproach_DockingApproach(void)
{
  signed int u;
  if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_DockingApproach == 0U))
  {
    u = (signed int)DockingApproachExample_Ext_DW.DockingApproach_timer + 1;
    if(u <= 9)
      DockingApproachExample_Ext_DW.DockingApproach_timer = (signed char)u;

    else
      DockingApproachExample_Ext_DW.DockingApproach_timer = (signed char)9;
    switch((signed int)DockingApproachExample_Ext_DW.is_DockingApproach)
    {
      case (signed int)(unsigned char)1U:
      {
        if(DockingApproachExample_Ext_DW.dockingSensor_RelativePosition == 2)
        {
          if(!(DockingApproachExample_Ext_DW.dockingSensor_RelativeVelocity == 2))
            goto __CPROVER_DUMP_L4;

          if(!(DockingApproachExample_Ext_DW.dockingSensor_RelativeAttitude == 2))
            goto __CPROVER_DUMP_L4;

          if(!(DockingApproachExample_Ext_DW.dockingSensor_targetState == 2))
            goto __CPROVER_DUMP_L4;

          DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)4U;
        }

        else
        {

        __CPROVER_DUMP_L4:
          ;
          if(DockingApproachExample_Ext_DW.dockingSensor_RelativePosition == 1)
          {
            if(!(DockingApproachExample_Ext_DW.dockingSensor_RelativeVelocity == 1))
              goto __CPROVER_DUMP_L5;

            if(!(DockingApproachExample_Ext_DW.dockingSensor_RelativeAttitude == 1))
              goto __CPROVER_DUMP_L5;

            if(!(DockingApproachExample_Ext_DW.dockingSensor_targetState == 1))
              goto __CPROVER_DUMP_L5;

            DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)2U;
          }

          else
          {

          __CPROVER_DUMP_L5:
            ;
            if(DockingApproachExample_Ext_DW.DockingApproach_timer == 9)
              DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)3U;

            else
            {
              if(!(DockingApproachExample_Ext_DW.dockingSensor_RelativePosition == 0))
              {
                if(DockingApproachExample_Ext_DW.dockingSensor_RelativeVelocity == 0)
                  goto __CPROVER_DUMP_L7;

                if(DockingApproachExample_Ext_DW.dockingSensor_RelativeAttitude == 0)
                  goto __CPROVER_DUMP_L7;

              }

              else
              {

              __CPROVER_DUMP_L7:
                ;
                DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)3U;
                goto __CPROVER_DUMP_L9;
              }
              if(!(DockingApproachExample_Ext_DW.dockingSensor_targetState == 2))
                DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)3U;

            }
          }
        }

      __CPROVER_DUMP_L9:
        ;
        break;
      }
      case (signed int)(unsigned char)2U:
      {
        if((unsigned int)DockingApproachExample_Ext_DW.thrust_status == 1U)
        {
          if(!(DockingApproachExample_Ext_DW.fuel_status == 2))
            goto __CPROVER_DUMP_L11;

          DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)1U;
        }

        else
        {

        __CPROVER_DUMP_L11:
          ;
          if((unsigned int)DockingApproachExample_Ext_DW.thrust_status == 1U)
          {
            if(!(DockingApproachExample_Ext_DW.fuel_status == 2))
              goto __CPROVER_DUMP_L12;

            if(DockingApproachExample_Ext_DW.DockingApproach_timer == 9)
              goto __CPROVER_DUMP_L12;

          }

          else
          {

          __CPROVER_DUMP_L12:
            ;
            DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)3U;
          }
        }
        break;
      }
      case (signed int)(unsigned char)3U:
      {
        D_exit_internal_DockingApproach();
        if(DockingApproachExample_Ext_DW.is_MissionPhaseStates == 5)
          DockingApproachExample_Ext_Y.DockingApproach = (unsigned char)0U;

        DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)2U;
        DockingApproachExample_Ext_DW.is_active_CaptureApproach = (unsigned char)1U;
        DockingApproachExample_Ext_DW.is_CaptureApproach = (unsigned char)2U;
        DockingApproachExample_Ext_DW.is_active_OrbitalState_Active = (unsigned char)1U;
        enter_internal_OrbitalState_Act();
        break;
      }
      case (signed int)(unsigned char)4U:
      {
        D_exit_internal_DockingApproach();
        if(DockingApproachExample_Ext_DW.is_MissionPhaseStates == 5)
          DockingApproachExample_Ext_Y.DockingApproach = (unsigned char)0U;

        DockingApproachExample_Ext_DW.is_MissionPhaseStates = (unsigned char)10U;
        if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_LatchCaptureCheck == 1U))
        {
          DockingApproachExample_Ext_DW.is_active_LatchCaptureCheck = (unsigned char)1U;
          DockingApproachExample_Ext_Y.AttemptingToDock = (unsigned char)1U;
        }

        if(!(DockingApproachExample_Ext_DW.is_LatchCaptureCheck == 2))
        {
          DockingApproachExample_Ext_DW.is_LatchCaptureCheck = (unsigned char)2U;
          DockingApproachExample_Ext_DW.LatchCapture_timer = (signed char)0;
        }

        DockingApproachExample_Ext_DW.is_active_latch = (unsigned char)1U;
        if(!(DockingApproachExample_Ext_DW.is_latch == 5))
        {
          DockingApproachExample_Ext_DW.is_latch = (unsigned char)5U;
          DockingApproachExample_Ext_DW.latch_status = (signed char)0;
        }

        break;
      }
      case (signed int)(unsigned char)5U:
      {
        if(!(DockingApproachExample_Ext_DW.dockingSensor_RelativePosition == 0))
        {
          if(DockingApproachExample_Ext_DW.dockingSensor_RelativeVelocity == 0)
            goto __CPROVER_DUMP_L22;

          if(DockingApproachExample_Ext_DW.dockingSensor_RelativeAttitude == 0)
            goto __CPROVER_DUMP_L22;

          if(!((signed int)DockingApproachExample_Ext_DW.DockingApproach_timer < 9))
            goto __CPROVER_DUMP_L22;

          DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)1U;
        }

        else
        {

        __CPROVER_DUMP_L22:
          ;
          if(DockingApproachExample_Ext_DW.DockingApproach_timer == 9)
            DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)3U;

        }
        break;
      }
      default:
        DockingApproachExample_Ext_DW.is_DockingApproach = (unsigned char)0U;
    }
  }

  if(DockingApproachExample_Ext_DW.is_MissionPhaseStates == 5)
  {
    if(!((unsigned int)DockingApproachExample_Ext_DW.is_active_dockingSensor == 0U))
    {
      u = (signed int)DockingApproachExample_Ext_DW.dockingSensor_timer + 1;
      if(u <= 6)
        DockingApproachExample_Ext_DW.dockingSensor_timer = (signed char)u;

      else
        DockingApproachExample_Ext_DW.dockingSensor_timer = (signed char)6;
      switch((signed int)DockingApproachExample_Ext_DW.is_dockingSensor)
      {
        case (signed int)(unsigned char)1U:
        {
          if(!(DockingApproachExample_Ext_U.dockVisibility_status == 0))
          {
            if(DockingApproachExample_Ext_U.opticsAvailability_status == 0)
              goto __CPROVER_DUMP_L31;

            if(DockingApproachExample_Ext_DW.is_dockingSensor == 1)
            {
              DockingApproachExample_Ext_DW.dockingSensor_timer = (signed char)0;
              DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)0U;
            }

            if(!(DockingApproachExample_Ext_DW.is_dockingSensor == 3))
            {
              DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)3U;
              DockingApproachExample_Ext_DW.dockingSensor_RelativePosition = (signed char)1;
              DockingApproachExample_Ext_DW.dockingSensor_RelativeVelocity = (signed char)1;
              DockingApproachExample_Ext_DW.dockingSensor_RelativeAttitude = (signed char)1;
              DockingApproachExample_Ext_DW.dockingSensor_targetState = (signed char)1;
            }

          }

          else
          {

          __CPROVER_DUMP_L31:
            ;
            if(!(DockingApproachExample_Ext_U.dockVisibility_status == 0))
            {
              if(DockingApproachExample_Ext_U.opticsAvailability_status == 0)
                goto __CPROVER_DUMP_L32;

            }

            else
            {

            __CPROVER_DUMP_L32:
              ;
              if(DockingApproachExample_Ext_DW.is_dockingSensor == 1)
              {
                DockingApproachExample_Ext_DW.dockingSensor_timer = (signed char)0;
                DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)0U;
              }

              if(!(DockingApproachExample_Ext_DW.is_dockingSensor == 1))
              {
                DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)1U;
                DockingApproachExample_Ext_DW.dockingSensor_RelativePosition = (signed char)0;
                DockingApproachExample_Ext_DW.dockingSensor_RelativeVelocity = (signed char)0;
                DockingApproachExample_Ext_DW.dockingSensor_RelativeAttitude = (signed char)0;
                DockingApproachExample_Ext_DW.dockingSensor_targetState = (signed char)0;
              }

            }
          }
          break;
        }
        case (signed int)(unsigned char)2U:
        {
          if(!(DockingApproachExample_Ext_U.dockVisibility_status == 2))
          {
            if(DockingApproachExample_Ext_U.opticsAvailability_status != 0)
              goto __CPROVER_DUMP_L36;

          }

          else
          {

          __CPROVER_DUMP_L36:
            ;
            if(DockingApproachExample_Ext_U.sunlight_status == 0)
              goto __CPROVER_DUMP_L40;

          }
          if(DockingApproachExample_Ext_DW.is_dockingSensor == 2)
          {
            DockingApproachExample_Ext_DW.dockingSensor_timer = (signed char)0;
            DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)0U;
          }

          if(!(DockingApproachExample_Ext_DW.is_dockingSensor == 3))
          {
            DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)3U;
            DockingApproachExample_Ext_DW.dockingSensor_RelativePosition = (signed char)1;
            DockingApproachExample_Ext_DW.dockingSensor_RelativeVelocity = (signed char)1;
            DockingApproachExample_Ext_DW.dockingSensor_RelativeAttitude = (signed char)1;
            DockingApproachExample_Ext_DW.dockingSensor_targetState = (signed char)1;
          }

          goto __CPROVER_DUMP_L42;

        __CPROVER_DUMP_L40:
          ;
          if(DockingApproachExample_Ext_U.dockVisibility_status == 2)
          {
            if(!(DockingApproachExample_Ext_U.opticsAvailability_status == 0))
            {
              if(DockingApproachExample_Ext_U.sunlight_status == 0)
              {
                if(DockingApproachExample_Ext_DW.is_dockingSensor == 2)
                {
                  DockingApproachExample_Ext_DW.dockingSensor_timer = (signed char)0;
                  DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)0U;
                }

                if(!(DockingApproachExample_Ext_DW.is_dockingSensor == 2))
                {
                  DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)2U;
                  DockingApproachExample_Ext_DW.dockingSensor_RelativePosition = (signed char)2;
                  DockingApproachExample_Ext_DW.dockingSensor_RelativeVelocity = (signed char)2;
                  DockingApproachExample_Ext_DW.dockingSensor_RelativeAttitude = (signed char)2;
                  DockingApproachExample_Ext_DW.dockingSensor_targetState = (signed char)2;
                }

              }

            }

          }


        __CPROVER_DUMP_L42:
          ;
          break;
        }
        case (signed int)(unsigned char)3U:
        {
          if(DockingApproachExample_Ext_DW.dockingSensor_timer == 6)
          {
            if(!(DockingApproachExample_Ext_U.dockVisibility_status == 0))
            {
              if(!(DockingApproachExample_Ext_U.opticsAvailability_status == 0))
                goto __CPROVER_DUMP_L45;

            }

            DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)1U;
            DockingApproachExample_Ext_DW.dockingSensor_RelativePosition = (signed char)0;
            DockingApproachExample_Ext_DW.dockingSensor_RelativeVelocity = (signed char)0;
            DockingApproachExample_Ext_DW.dockingSensor_RelativeAttitude = (signed char)0;
            DockingApproachExample_Ext_DW.dockingSensor_targetState = (signed char)0;
          }

          else
          {

          __CPROVER_DUMP_L45:
            ;
            if((signed int)DockingApproachExample_Ext_DW.dockingSensor_timer < 6)
            {
              if(!(DockingApproachExample_Ext_U.dockVisibility_status == 2))
                goto __CPROVER_DUMP_L46;

              if(DockingApproachExample_Ext_U.opticsAvailability_status == 0)
                goto __CPROVER_DUMP_L46;

              if(DockingApproachExample_Ext_U.sunlight_status != 0)
                goto __CPROVER_DUMP_L46;

              DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)2U;
              DockingApproachExample_Ext_DW.dockingSensor_RelativePosition = (signed char)2;
              DockingApproachExample_Ext_DW.dockingSensor_RelativeVelocity = (signed char)2;
              DockingApproachExample_Ext_DW.dockingSensor_RelativeAttitude = (signed char)2;
              DockingApproachExample_Ext_DW.dockingSensor_targetState = (signed char)2;
            }

            else
            {

            __CPROVER_DUMP_L46:
              ;
              if((signed int)DockingApproachExample_Ext_DW.dockingSensor_timer < 6)
              {
                if(!(DockingApproachExample_Ext_U.dockVisibility_status == 0))
                {
                  if(!(DockingApproachExample_Ext_U.opticsAvailability_status == 0))
                    goto __CPROVER_DUMP_L48;

                }

              }

              else
              {

              __CPROVER_DUMP_L48:
                ;
                if(!(DockingApproachExample_Ext_U.opticsAvailability_status == 0))
                {
                  if(!(DockingApproachExample_Ext_U.dockVisibility_status == 1))
                  {
                    if(DockingApproachExample_Ext_U.sunlight_status == 0)
                      goto __CPROVER_DUMP_L50;

                  }

                }

                else
                {

                __CPROVER_DUMP_L50:
                  ;
                  goto __CPROVER_DUMP_L52;
                }
              }
              DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)3U;
              DockingApproachExample_Ext_DW.dockingSensor_RelativePosition = (signed char)1;
              DockingApproachExample_Ext_DW.dockingSensor_RelativeVelocity = (signed char)1;
              DockingApproachExample_Ext_DW.dockingSensor_RelativeAttitude = (signed char)1;
              DockingApproachExample_Ext_DW.dockingSensor_targetState = (signed char)1;
            }
          }

        __CPROVER_DUMP_L52:
          ;
          break;
        }
        default:
          DockingApproachExample_Ext_DW.is_dockingSensor = (unsigned char)0U;
      }
    }

  }

}

// MdlInitialize
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2337
void MdlInitialize(void)
{
  ;
}

// MdlInitializeSampleTimes
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2333
void MdlInitializeSampleTimes(void)
{
  ;
}

// MdlInitializeSizes
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2329
void MdlInitializeSizes(void)
{
  ;
}

// MdlOutputs
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2311
void MdlOutputs(signed int tid)
{
  DockingApproachExample_Ext_output();
  (void)tid;
}

// MdlStart
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2341
void MdlStart(void)
{
  DockingApproachExample_Ext_initialize();
}

// MdlTerminate
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2346
void MdlTerminate(void)
{
  DockingApproachExample_Ext_terminate();
}

// MdlUpdate
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 2320
void MdlUpdate(signed int tid)
{
  DockingApproachExample_Ext_update();
  (void)tid;
}

// ceil
// file ../R2013a/rtw/c/grt/cbmc_math.c line 93
extern double ceil(double x)
{
  signed int i0;
  signed int i1;
  signed int j0;
  unsigned int i;
  unsigned int j;
  do
  {
    union anonymous$55 ew_u;
    ew_u.value = x;
    i0 = (signed int)ew_u.parts.msw;
    i1 = (signed int)ew_u.parts.lsw;
  }
  while((_Bool)0);
  j0 = (i0 >> 20 & 0x7ff) - 0x3ff;
  if(j0 < 20)
  {
    if(j0 < 0)
    {
      if(huge_double + x > 0.0)
      {
        if(i0 < 0)
        {
          i0 = (signed int)0x80000000;
          i1 = 0;
        }

        else
          if(!((i0 | i1) == 0))
          {
            i0 = 0x3ff00000;
            i1 = 0;
          }

      }

    }

    else
    {
      i = (unsigned int)(0x000fffff >> j0);
      if((i & (unsigned int)i0 | (unsigned int)i1) == 0u)
        return x;

      if(huge_double + x > 0.0)
      {
        if(i0 > 0)
          i0 = i0 + (0x00100000 >> j0);

        i0 = i0 & (signed int)~i;
        i1 = 0;
      }

    }
  }

  else
    if(j0 > 51)
    {
      if(j0 == 0x400)
        return x + x;

      else
        return x;
    }

    else
    {
      i = (unsigned int)0xffffffff >> j0 - 20;
      if((i & (unsigned int)i1) == 0u)
        return x;

      if(huge_double + x > 0.0)
      {
        if(i0 > 0)
        {
          if(j0 == 20)
            i0 = i0 + 1;

          else
          {
            j = (unsigned int)(i1 + (1 << 52 - j0));
            if(!(j >= (unsigned int)i1))
              i0 = i0 + 1;

            i1 = (signed int)j;
          }
        }

        i1 = i1 & (signed int)~i;
      }

    }
  do
  {
    union anonymous$55 iw_u;
    iw_u.parts.msw = (unsigned int)i0;
    iw_u.parts.lsw = (unsigned int)i1;
    x = iw_u.value;
  }
  while((_Bool)0);
  return x;
}

// displayUsage
// file ../R2013a/rtw/c/grt/classic_main.c line 383
static void displayUsage(void)
{
  printf("usage: %s -tf <finaltime> -w -port <TCPport>\n", (const void *)"DockingApproachExample_Ext");
  printf("arguments:\n");
  printf("  -tf <finaltime> - overrides final time specified in Simulink (inf for no limit).\n");
  printf("  -w              - waits for Simulink to start model in External Mode.\n");
  printf("  -port <TCPport> - overrides 17725 default port in External Mode, valid range 256 to 65535.\n");
}

// enter_internal_OrbitalState_Act
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/DockingApproachExample_Ext.c line 1039
static void enter_internal_OrbitalState_Act(void)
{
  DockingApproachExample_Ext_DW.is_active_OrbitalState_Complex = (unsigned char)1U;
  DockingApproachExample_Ext_DW.is_active_OrbitalState = (unsigned char)1U;
  if(!(DockingApproachExample_Ext_DW.is_OrbitalState == 1))
  {
    DockingApproachExample_Ext_DW.is_OrbitalState = (unsigned char)1U;
    DockingApproachExample_Ext_DW.OrbitalState_Position = (signed char)0;
    DockingApproachExample_Ext_DW.OrbitalState_Velocity = (signed char)0;
    DockingApproachExample_Ext_DW.OrbitalState_Attitude = (signed char)0;
  }

  DockingApproachExample_Ext_DW.is_active_OrbitalState2 = (unsigned char)1U;
  if(!(DockingApproachExample_Ext_DW.is_OrbitalState2 == 2))
  {
    DockingApproachExample_Ext_DW.is_OrbitalState2 = (unsigned char)2U;
    DockingApproachExample_Ext_DW.OrbitalState_Time = (signed char)1;
  }

  DockingApproachExample_Ext_DW.is_active_GPS = (unsigned char)1U;
  if(!(DockingApproachExample_Ext_DW.is_GPS == 1))
  {
    DockingApproachExample_Ext_DW.is_GPS = (unsigned char)1U;
    DockingApproachExample_Ext_DW.GPS_AbsolutePosition = (signed char)0;
    DockingApproachExample_Ext_DW.GPS_AbsoluteVelocity = (signed char)0;
    DockingApproachExample_Ext_DW.GPS_AbsoluteTime = (signed char)0;
  }

  DockingApproachExample_Ext_DW.is_active_StarPlanetTracker = (unsigned char)1U;
  if(!(DockingApproachExample_Ext_DW.is_StarPlanetTracker == 1))
  {
    DockingApproachExample_Ext_DW.is_StarPlanetTracker = (unsigned char)1U;
    DockingApproachExample_Ext_DW.StarPlanetTracker_AbsolutePosit = (signed char)0;
    DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteVeloc = (signed char)0;
    DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteAttit = (signed char)0;
    DockingApproachExample_Ext_DW.StarPlanetTracker_AbsoluteTime = (signed char)0;
  }

  DockingApproachExample_Ext_DW.is_active_InertialNavigation = (unsigned char)1U;
  DockingApproachExample_Ext_DW.VALID = (unsigned char)0U;
  if(!(DockingApproachExample_Ext_DW.is_InertialNavigation == 1))
  {
    DockingApproachExample_Ext_DW.is_InertialNavigation = (unsigned char)1U;
    DockingApproachExample_Ext_DW.InertialNavigation_AbsolutePosi = (signed char)0;
    DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteVelo = (signed char)0;
    DockingApproachExample_Ext_DW.InertialNavigation_AbsoluteAtti = (signed char)0;
  }

}

// floor
// file ../R2013a/rtw/c/grt/cbmc_math.c line 135
extern double floor(double x)
{
  signed int i0;
  signed int i1;
  signed int j0;
  unsigned int i;
  unsigned int j;
  do
  {
    union anonymous$55 ew_u;
    ew_u.value = x;
    i0 = (signed int)ew_u.parts.msw;
    i1 = (signed int)ew_u.parts.lsw;
  }
  while((_Bool)0);
  j0 = (i0 >> 20 & 0x7ff) - 0x3ff;
  if(j0 < 20)
  {
    if(j0 < 0)
    {
      if(huge_double + x > 0.0)
      {
        if(i0 >= 0)
        {
          i1 = 0;
          i0 = i1;
        }

        else
          if(!((0x7fffffff & i0 | i1) == 0))
          {
            i0 = (signed int)0xbff00000;
            i1 = 0;
          }

      }

    }

    else
    {
      i = (unsigned int)(0x000fffff >> j0);
      if((i & (unsigned int)i0 | (unsigned int)i1) == 0u)
        return x;

      if(huge_double + x > 0.0)
      {
        if(i0 < 0)
          i0 = i0 + (0x00100000 >> j0);

        i0 = i0 & (signed int)~i;
        i1 = 0;
      }

    }
  }

  else
    if(j0 > 51)
    {
      if(j0 == 0x400)
        return x + x;

      else
        return x;
    }

    else
    {
      i = (unsigned int)0xffffffff >> j0 - 20;
      if((i & (unsigned int)i1) == 0u)
        return x;

      if(huge_double + x > 0.0)
      {
        if(i0 < 0)
        {
          if(j0 == 20)
            i0 = i0 + 1;

          else
          {
            j = (unsigned int)(i1 + (1 << 52 - j0));
            if(!(j >= (unsigned int)i1))
              i0 = i0 + 1;

            i1 = (signed int)j;
          }
        }

        i1 = i1 & (signed int)~i;
      }

    }
  do
  {
    union anonymous$55 iw_u;
    iw_u.parts.msw = (unsigned int)i0;
    iw_u.parts.lsw = (unsigned int)i1;
    x = iw_u.value;
  }
  while((_Bool)0);
  return x;
}

// fmod
// file ../R2013a/rtw/c/grt/cbmc_math.c line 237
extern double fmod(double a, double n)
{
  double q;
  double r;
  return r;
}

// main
// file ../R2013a/rtw/c/grt/classic_main.c line 405
signed int main(signed int argc, const char **argv)
{
  struct tag_RTM_DockingApproachExampl_T *S;
  const char *status;
  double finaltime = -2.0;
  signed int oldStyle_argc;
  const char *oldStyle_argv[5l];
  if(argc > 1)
  {
    if(!((signed int)*argv[1l] == 45))
    {
      if(argc > 3)
      {
        displayUsage();
        exit(1);
      }

      oldStyle_argc = 1;
      oldStyle_argv[(signed long int)0] = argv[(signed long int)0];
      if(argc >= 2)
      {
        oldStyle_argc = 3;
        oldStyle_argv[(signed long int)1] = "-tf";
        oldStyle_argv[(signed long int)2] = argv[(signed long int)1];
      }

      if(argc == 3)
      {
        oldStyle_argc = 5;
        oldStyle_argv[(signed long int)3] = "-port";
        oldStyle_argv[(signed long int)4] = argv[(signed long int)2];
      }

      argc = oldStyle_argc;
      argv = oldStyle_argv;
    }

  }

  double tmpDouble;
  char tmpStr2[200l];
  signed int count = 1;
  signed int parseError = (signed int)0U;
  signed int tmp_post$1;
  signed int tmp_post$2;
  while(!(count >= argc))
  {
    const char *option;
    tmp_post$1 = count;
    count = count + 1;
    option = argv[(signed long int)tmp_post$1];
    signed int return_value_strcmp$5;
    return_value_strcmp$5=strcmp(option, "-tf");
    if(return_value_strcmp$5 == 0)
    {
      if(!(count == argc))
      {
        const char *tfStr;
        tmp_post$2 = count;
        count = count + 1;
        tfStr = argv[(signed long int)tmp_post$2];
        sscanf(tfStr, "%200s", (const void *)tmpStr2);
        signed int return_value_strcmp$4;
        return_value_strcmp$4=strcmp(tmpStr2, "inf");
        if(return_value_strcmp$4 == 0)
          tmpDouble = -1.0;

        else
        {
          char tmpstr[2l];
          signed int return_value_sscanf$3;
          return_value_sscanf$3=sscanf(tmpStr2, "%lf%1s", &tmpDouble, (const void *)tmpstr);
          if(tmpDouble < 0.0 || !(return_value_sscanf$3 == 1))
          {
            printf("finaltime must be a positive, real value or inf\n");
            parseError = (signed int)1U;
            break;
          }

        }
        finaltime = (double)tmpDouble;
        argv[(signed long int)(count - 2)] = (const char *)(void *)0;
        argv[(signed long int)(count - 1)] = (const char *)(void *)0;
      }

    }

  }
  signed int return_value_nondet_double$6 = nondet_double();
  finaltime = (double)return_value_nondet_double$6;
  __CPROVER_assume(finaltime >= 0.0 || IEEE_FLOAT_EQUAL(finaltime, -1.0));
  if(!(parseError == 0))
  {
    printf("\nUsage: %s -option1 val1 -option2 val2 -option3 ...\n\n", (const void *)"DockingApproachExample_Ext");
    printf("\t-tf 20 - sets final time to 20 seconds\n");
    exit(1);
  }

  signed int i = 1;
  for( ; !(i >= argc); i = i + 1)
    if(!(argv[(signed long int)i] == (const char *)0))
    {
      printf("Unexpected command line argument: %s\n", argv[(signed long int)i]);
      exit(1);
    }

  S=DockingApproachExample_Ext();
  if(!(S->errorStatus == (const char *)0))
  {
    fprintf(stderr, "Error during model registration: %s\n", S->errorStatus);
    exit(1);
  }

  if(!(finaltime >= 0.0))
  {
    if(IEEE_FLOAT_EQUAL(finaltime, -1.000000))
      goto __CPROVER_DUMP_L16;

  }

  else
  {

  __CPROVER_DUMP_L16:
    ;
    S->Timing.tFinal = finaltime;
  }
  MdlInitializeSizes();
  MdlInitializeSampleTimes();
  status=rt_SimInitTimingEngine(S->Sizes.numSampTimes, S->Timing.stepSize, S->Timing.sampleTimes, S->Timing.offsetTimes, S->Timing.sampleHits, S->Timing.sampleTimeTaskIDPtr, S->Timing.tStart, &S->Timing.simTimeStep, &S->Timing.timingData);
  if(!(status == (const char *)0))
  {
    fprintf(stderr, "Failed to initialize sample time engine: %s\n", status);
    exit(1);
  }

  (&S->solverInfo)->solverName = "FixedStepDiscrete";
  GBLbuf.errmsg=rt_StartDataLogging(S->rtwLogInfo, S->Timing.tFinal, S->Timing.stepSize, &S->errorStatus);
  if(!(GBLbuf.errmsg == (const char *)0))
  {
    fprintf(stderr, "Error starting data logging: %s\n", GBLbuf.errmsg);
    return 1;
  }

  printf("\n** starting the model **\n");
  MdlStart();
  if(!(S->errorStatus == (const char *)0))
    GBLbuf.stopExecutionFlag = 1;

  if(IEEE_FLOAT_EQUAL(S->Timing.tFinal, -1.000000))
    printf("\n**May run forever. Model stop time set to infinity.**\n");

  while(GBLbuf.stopExecutionFlag == 0)
  {
    if(!IEEE_FLOAT_EQUAL(S->Timing.tFinal, -1.000000))
    {
      if(!(S->Timing.tFinal + -(*S->Timing.t) > *S->Timing.t * 2.220446e-16))
        break;

    }

    if(S->Timing.stopRequestedFlag != 0)
      break;

    rt_OneStep(S);
  }
  if(GBLbuf.stopExecutionFlag == 0)
  {
    if(S->Timing.stopRequestedFlag == 0)
      rt_OneStep(S);

  }

  rt_StopDataLogging("DockingApproachExample_Ext.mat", S->rtwLogInfo);
  if(!(GBLbuf.errmsg == ((const char *)NULL)))
  {
    fprintf(stderr, "%s\n", GBLbuf.errmsg);
    exit(1);
  }

  if(!(S->errorStatus == (const char *)0))
  {
    fprintf(stderr, "ErrorStatus set: \"%s\"\n", S->errorStatus);
    exit(1);
  }

  if(!(GBLbuf.isrOverrun == 0))
  {
    fprintf(stderr, "%s: ISR overrun - base sampling rate is too fast\n", (const void *)"DockingApproachExample_Ext");
    exit(1);
  }

  MdlTerminate();
  space_dummy_bool();
  _Learn_assert(0 != 0);
  return 0;
}

// rtGetInf
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rtGetInf.h line 23
extern double rtGetInf(void)
{
  unsigned long int bitsPerReal = sizeof(double) /*8ul*/  * (unsigned long int)8U;
  double inf = 0.0;
  /* tag-#anon#UN[SYM#tag-#anon#ST[SYM#tag-#anon#ST[U32'wordL'||U32'wordH'|]#'words'|]#'bitVal'||F64'fltVal'|] */
union anonymous
{
  // bitVal
  struct anonymous$45 bitVal;
  // fltVal
  double fltVal;
};

/* */
  ;
  union anonymous tmpVal;
  /* tag-#anon#UN[SYM#tag-#anon#ST[SYM#tag-#anon#ST[U32'wordH'||U32'wordL'|]#'words'|]#'bitVal'||F64'fltVal'|] */
union anonymous$33
{
  // bitVal
  struct anonymous$39 bitVal;
  // fltVal
  double fltVal;
};

/* */
  ;
  union anonymous$33 rtGetInf$$1$$2$$1$$2$$tmpVal;
  if(bitsPerReal == 32ul)
  {
    float return_value_rtGetInfF$1;
    return_value_rtGetInfF$1=rtGetInfF();
    inf = (double)return_value_rtGetInfF$1;
  }

  else
  {
    unsigned short int one = (unsigned short int)1U;
    /* #anon_enum$LittleEndian=0$BigEndian=1 */
enum anonymous$6 { LittleEndian=0, BigEndian=1 };

/* */
    ;
    enum anonymous$6 machByteOrder = (enum anonymous$6)((unsigned int)*((unsigned char *)&one) == 1U ? LittleEndian : BigEndian);
    switch((signed int)machByteOrder)
    {
      case LittleEndian:
      {
        tmpVal.bitVal.words.wordH = 0x7FF00000U;
        tmpVal.bitVal.words.wordL = 0x00000000U;
        inf = tmpVal.fltVal;
        break;
      }
      case BigEndian:
      {
        rtGetInf$$1$$2$$1$$2$$tmpVal.bitVal.words.wordH = 0x7FF00000U;
        rtGetInf$$1$$2$$1$$2$$tmpVal.bitVal.words.wordL = 0x00000000U;
        inf = rtGetInf$$1$$2$$1$$2$$tmpVal.fltVal;
      }
    }
  }
  return inf;
}

// rtGetInfF
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rtGetInf.h line 24
extern float rtGetInfF(void)
{
  struct anonymous$41 infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

// rtGetMinusInf
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rtGetInf.h line 25
extern double rtGetMinusInf(void)
{
  unsigned long int bitsPerReal = sizeof(double) /*8ul*/  * (unsigned long int)8U;
  double minf = 0.0;
  /* tag-#anon#UN[SYM#tag-#anon#ST[SYM#tag-#anon#ST[U32'wordL'||U32'wordH'|]#'words'|]#'bitVal'||F64'fltVal'|] */
union anonymous
{
  // bitVal
  struct anonymous$45 bitVal;
  // fltVal
  double fltVal;
};

/* */
  ;
  union anonymous rtGetMinusInf$$1$$2$$1$$1$$tmpVal;
  /* tag-#anon#UN[SYM#tag-#anon#ST[SYM#tag-#anon#ST[U32'wordH'||U32'wordL'|]#'words'|]#'bitVal'||F64'fltVal'|] */
union anonymous$33
{
  // bitVal
  struct anonymous$39 bitVal;
  // fltVal
  double fltVal;
};

/* */
  ;
  union anonymous$33 tmpVal;
  if(bitsPerReal == 32ul)
  {
    float return_value_rtGetMinusInfF$1;
    return_value_rtGetMinusInfF$1=rtGetMinusInfF();
    minf = (double)return_value_rtGetMinusInfF$1;
  }

  else
  {
    unsigned short int one = (unsigned short int)1U;
    /* rtGetMinusInf::1::2::tag-machByteOrdert */
enum machByteOrdert$0 { LittleEndian=0, BigEndian=1 };

/* */
    ;
    enum machByteOrdert$0 machByteOrder = (enum machByteOrdert$0)((unsigned int)*((unsigned char *)&one) == 1U ? LittleEndian : BigEndian);
    switch((signed int)machByteOrder)
    {
      case LittleEndian:
      {
        rtGetMinusInf$$1$$2$$1$$1$$tmpVal.bitVal.words.wordH = 0xFFF00000U;
        rtGetMinusInf$$1$$2$$1$$1$$tmpVal.bitVal.words.wordL = 0x00000000U;
        minf = rtGetMinusInf$$1$$2$$1$$1$$tmpVal.fltVal;
        break;
      }
      case BigEndian:
      {
        tmpVal.bitVal.words.wordH = 0xFFF00000U;
        tmpVal.bitVal.words.wordL = 0x00000000U;
        minf = tmpVal.fltVal;
      }
    }
  }
  return minf;
}

// rtGetMinusInfF
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rtGetInf.h line 26
extern float rtGetMinusInfF(void)
{
  struct anonymous$41 minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

// rtGetNaN
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rtGetNaN.c line 28
extern double rtGetNaN(void)
{
  unsigned long int bitsPerReal = sizeof(double) /*8ul*/  * (unsigned long int)8U;
  double nan = 0.0;
  /* tag-#anon#UN[SYM#tag-#anon#ST[SYM#tag-#anon#ST[U32'wordL'||U32'wordH'|]#'words'|]#'bitVal'||F64'fltVal'|] */
union anonymous
{
  // bitVal
  struct anonymous$45 bitVal;
  // fltVal
  double fltVal;
};

/* */
  ;
  union anonymous tmpVal;
  /* tag-#anon#UN[SYM#tag-#anon#ST[SYM#tag-#anon#ST[U32'wordH'||U32'wordL'|]#'words'|]#'bitVal'||F64'fltVal'|] */
union anonymous$33
{
  // bitVal
  struct anonymous$39 bitVal;
  // fltVal
  double fltVal;
};

/* */
  ;
  union anonymous$33 rtGetNaN$$1$$2$$1$$2$$tmpVal;
  if(bitsPerReal == 32ul)
  {
    float return_value_rtGetNaNF$1;
    return_value_rtGetNaNF$1=rtGetNaNF();
    nan = (double)return_value_rtGetNaNF$1;
  }

  else
  {
    unsigned short int one = (unsigned short int)1U;
    /* #anon_enum$LittleEndian=0$BigEndian=1 */
enum anonymous$6 { LittleEndian=0, BigEndian=1 };

/* */
    ;
    enum anonymous$6 machByteOrder = (enum anonymous$6)((unsigned int)*((unsigned char *)&one) == 1U ? LittleEndian : BigEndian);
    switch((signed int)machByteOrder)
    {
      case LittleEndian:
      {
        tmpVal.bitVal.words.wordH = 0xFFF80000U;
        tmpVal.bitVal.words.wordL = 0x00000000U;
        nan = tmpVal.fltVal;
        break;
      }
      case BigEndian:
      {
        rtGetNaN$$1$$2$$1$$2$$tmpVal.bitVal.words.wordH = 0x7FFFFFFFU;
        rtGetNaN$$1$$2$$1$$2$$tmpVal.bitVal.words.wordL = 0xFFFFFFFFU;
        nan = rtGetNaN$$1$$2$$1$$2$$tmpVal.fltVal;
      }
    }
  }
  return nan;
}

// rtGetNaNF
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rtGetNaN.c line 76
extern float rtGetNaNF(void)
{
  struct anonymous$41 nanF = { .wordL={ .wordLreal=(float)0 } };
  unsigned short int one = (unsigned short int)1U;
  /* rtGetNaNF::1::tag-machByteOrdert */
enum machByteOrdert { LittleEndian=0, BigEndian=1 };

/* */
  ;
  enum machByteOrdert machByteOrder = (enum machByteOrdert)((unsigned int)*((unsigned char *)&one) == 1U ? LittleEndian : BigEndian);
  switch((signed int)machByteOrder)
  {
    case LittleEndian:
    {
      nanF.wordL.wordLuint = 0xFFC00000U;
      break;
    }
    case BigEndian:
      nanF.wordL.wordLuint = 0x7FFFFFFFU;
  }
  return nanF.wordL.wordLreal;
}

// rtIsInf
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 49
extern unsigned char rtIsInf(double value)
{
  return (unsigned char)(IEEE_FLOAT_EQUAL(value, rtInf) || IEEE_FLOAT_EQUAL(value, rtMinusInf) ? 1U : 0U);
}

// rtIsInfF
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 55
extern unsigned char rtIsInfF(float value)
{
  return (unsigned char)(IEEE_FLOAT_EQUAL(value, rtInfF) || IEEE_FLOAT_EQUAL(value, rtMinusInfF) ? 1U : 0U);
}

// rtIsNaN
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 61
extern unsigned char rtIsNaN(double value)
{
  return (unsigned char)(IEEE_FLOAT_NOTEQUAL(value, value) ? 1U : 0U);
}

// rtIsNaNF
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 67
extern unsigned char rtIsNaNF(float value)
{
  return (unsigned char)(IEEE_FLOAT_NOTEQUAL(value, value) ? 1U : 0U);
}

// rt_InitInfAndNaN
// file ../Stateflow/DockingApproachExample_Ext_grt_rtw/rt_nonfinite.c line 37
extern void rt_InitInfAndNaN(unsigned long int realSize)
{
  (void)realSize;
  rtNaN=rtGetNaN();
  rtNaNF=rtGetNaNF();
  rtInf=rtGetInf();
  rtInfF=rtGetInfF();
  rtMinusInf=rtGetMinusInf();
  rtMinusInfF=rtGetMinusInfF();
}

// rt_ODECreateIntegrationData
// file ../R2013a/rtw/c/grt/classic_main.c line 672
void rt_ODECreateIntegrationData(struct _ssSolverInfo_tag *si)
{
  /* 0 != 0 */
  assert(0 != 0);
}

// rt_ODEUpdateContinuousStates
// file ../R2013a/rtw/c/grt/classic_main.c line 675
void rt_ODEUpdateContinuousStates(struct _ssSolverInfo_tag *si)
{
  /* 0 != 0 */
  assert(0 != 0);
}

// rt_OneStep
// file ../R2013a/rtw/c/grt/classic_main.c line 193
static void rt_OneStep(struct tag_RTM_DockingApproachExampl_T *S)
{
  double tnext;
  signed int tmp_post$1 = GBLbuf.isrOverrun;
  GBLbuf.isrOverrun = GBLbuf.isrOverrun + 1;
  if(!(tmp_post$1 == 0))
  {
    GBLbuf.stopExecutionFlag = 1;
    return;
  }

  if(!(S->errorStatus == (const char *)0))
  {
    GBLbuf.stopExecutionFlag = 1;
    return;
  }

  tnext=rt_SimGetNextSampleHit();
  (&S->solverInfo)->solverStopTime = tnext;
  MdlOutputs(0);
  GBLbuf.errmsg=rt_UpdateTXYLogVars(S->rtwLogInfo, S->Timing.t);
  if(!(GBLbuf.errmsg == (const char *)0))
  {
    GBLbuf.stopExecutionFlag = 1;
    return;
  }

  rt_UpdateSigLogVars(S->rtwLogInfo, S->Timing.t);
  MdlUpdate(0);
  rt_SimUpdateDiscreteTaskSampleHits(S->Sizes.numSampTimes, S->Timing.timingData, S->Timing.sampleHits, S->Timing.t);
  GBLbuf.isrOverrun = GBLbuf.isrOverrun - 1;
}

// rt_SimGetNextSampleHit
// file ../R2013a/rtw/c/src/rt_sim.c line 278
extern double rt_SimGetNextSampleHit(void)
{
  return (double)-1;
}

// rt_SimInitTimingEngine
// file ../R2013a/rtw/c/src/rt_sim.c line 87
extern const char * rt_SimInitTimingEngine(signed int rtmNumSampTimes, double rtmStepSize, double *rtmSampleTimePtr, double *rtmOffsetTimePtr, signed int *rtmSampleHitPtr, signed int *rtmSampleTimeTaskIDPtr, double rtmTStart, enum anonymous$10 *rtmSimTimeStepPtr, void **rtmTimingDataPtr)
{
  (void)rtmNumSampTimes;
  (void)rtmStepSize;
  (void)rtmSampleTimePtr;
  (void)rtmOffsetTimePtr;
  (void)rtmSampleHitPtr;
  (void)rtmSampleTimeTaskIDPtr;
  (void)rtmSimTimeStepPtr;
  (void)rtmTimingDataPtr;
  if(IEEE_FLOAT_NOTEQUAL(rtmTStart, 0.0))
    return "Start time must be zero for real-time systems.  For non-zero start times you must use the Simulink solver module";

  else
    return (const char *)(void *)0;
}

// rt_SimUpdateDiscreteTaskSampleHits
// file ../R2013a/rtw/c/src/rt_sim.c line 332
extern void rt_SimUpdateDiscreteTaskSampleHits(signed int rtmNumSampTimes, void *rtmTimingData, signed int *rtmSampleHitPtr, double *rtmTPtr)
{
  (void)rtmNumSampTimes;
  (void)rtmTimingData;
  (void)rtmSampleHitPtr;
  (void)rtmTPtr;
  return;
}

// rt_StartDataLogging
// file ../R2013a/rtw/c/src/rt_mock_logging.c line 5
const char * rt_StartDataLogging(struct _RTWLogInfo_tag *li, const double finalTime, const double stepSize, const char **errStatus)
{
  return ((const char *)NULL);
}

// rt_StopDataLogging
// file ../R2013a/rtw/c/src/rt_mock_logging.c line 6
void rt_StopDataLogging(const char *file, struct _RTWLogInfo_tag *li)
{
  ;
}

// rt_UpdateSigLogVars
// file ../R2013a/rtw/c/src/rt_mock_logging.c line 4
void rt_UpdateSigLogVars(struct _RTWLogInfo_tag *li, double *tPtr)
{
  ;
}

// rt_UpdateTXYLogVars
// file ../R2013a/rtw/c/src/rt_mock_logging.c line 3
const char * rt_UpdateTXYLogVars(struct _RTWLogInfo_tag *li, double *tPtr)
{
  return ((const char *)NULL);
}

// space_dummy_bool
// file ../R2013a/rtw/c/grt/classic_main.c line 31
void space_dummy_bool(void)
{
  _Bool local_true = TRUE;
  _Bool local_false = FALSE;
  if(!(local_true == (_Bool)0))
    local_false = !(local_true != (_Bool)0);

}


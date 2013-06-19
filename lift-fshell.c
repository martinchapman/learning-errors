#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

//int input();

void __CrestInt(int * var) {
	int x; // ofer
  *var = x;//input();
}

int ctrl_io_in[10] ;
int ctrl_io_out[4] ;
int ctrl_io_led[14] ;
void io_init(void) ;
int levelPos[14]  ;
int one_level  ;
int cntValid  ;
int cnt  ;
int level  ;
int loadLevel  ;
int loadPending  ;
int loadSensor  ;
int cmd  ;
int timMotor  ;
int timImp  ;
int directionUp  ;
int lastImp  ;
int dbgCnt  ;
int endCnt  ;
int checkRun(void) ;
void waitForMotorStart(void) ;
void doCmd(void) ;
void doImpuls(int val , int motor , int reset ) ;
void checkCmd(void) ;
void checkLevel(void) ;
void ctrl_loop(void) ;
extern void __CrestInt(int *x )  ;
int newLevel  ;
void ctrl_init(void) 
{ int i ;
  int tmp ;
  int tmp___0 ;
  int tmp___1 ;
  int tmp___2 ;
  int tmp___3 ;
  int tmp___4 ;
  int tmp___5 ;
  int tmp___6 ;
  int tmp___7 ;
  int tmp___8 ;
  int tmp___9 ;
  int tmp___10 ;
  int tmp___11 ;
  int tmp___12 ;
  int tmp___13 ;
  int tmp___14 ;

  {
  i = 0;
  io_init();
  __CrestInt(& cntValid);
  __CrestInt(& cnt);
  __CrestInt(& cmd);
  __CrestInt(& timMotor);
  __CrestInt(& timImp);
  __CrestInt(& directionUp);
  __CrestInt(& lastImp);
  __CrestInt(& loadLevel);
  __CrestInt(& loadPending);
  __CrestInt(& loadSensor);
  tmp = i;
  i ++;
  __CrestInt(& levelPos[tmp]);
  tmp___0 = i;
  i ++;
  __CrestInt(& levelPos[tmp___0]);
  tmp___1 = i;
  i ++;
  __CrestInt(& levelPos[tmp___1]);
  tmp___2 = i;
  i ++;
  __CrestInt(& levelPos[tmp___2]);
  tmp___3 = i;
  i ++;
  __CrestInt(& levelPos[tmp___3]);
  tmp___4 = i;
  i ++;
  __CrestInt(& levelPos[tmp___4]);
  tmp___5 = i;
  i ++;
  __CrestInt(& levelPos[tmp___5]);
  tmp___6 = i;
  i ++;
  __CrestInt(& levelPos[tmp___6]);
  tmp___7 = i;
  i ++;
  __CrestInt(& levelPos[tmp___7]);
  tmp___8 = i;
  i ++;
  __CrestInt(& levelPos[tmp___8]);
  tmp___9 = i;
  i ++;
  __CrestInt(& levelPos[tmp___9]);
  tmp___10 = i;
  i ++;
  __CrestInt(& levelPos[tmp___10]);
  tmp___11 = i;
  i ++;
  __CrestInt(& levelPos[tmp___11]);
  tmp___12 = i;
  i ++;
  __CrestInt(& levelPos[tmp___12]);
  tmp___13 = i;
  i ++;
  __CrestInt(& levelPos[tmp___13]);
  tmp___14 = i;
  i ++;
  __CrestInt(& levelPos[tmp___14]);
  one_level = levelPos[1];
  return;
}
}
void ctrl_loop(void) 
{ int checkLevel_i ;
  int checkLevel_middle ;
  int run ;

  {
  checkLevel_i = 0;
  checkLevel_middle = 0;
  run = 0;
  if (cmd == 0) {
    if (loadPending) {
      if (ctrl_io_in[2]) {
        cmd = 1;
      }
    } else {
      if (ctrl_io_in[4]) {
        if (! ctrl_io_in[1]) {
          if (level != 14) {
            cmd = 3;
          }
        }
      } else {
        if (ctrl_io_in[5]) {
          if (! ctrl_io_in[2]) {
            if (level != 1) {
              cmd = 4;
            }
          }
        } else {
          if (ctrl_io_in[8]) {
            if (loadLevel != 0) {
              if (level < loadLevel) {
                cmd = 1;
              } else {
                cmd = 2;
              }
            } else {
              cmd = 2;
            }
            loadPending = 1;
            loadSensor = 0;
          } else {
            if (ctrl_io_in[6]) {
              if (! ctrl_io_in[1]) {
                cmd = 1;
              }
            } else {
              if (ctrl_io_in[7]) {
                if (! ctrl_io_in[2]) {
                  cmd = 2;
                }
              }
            }
          }
        }
      }
    }
    if (cmd != 0) {
      timMotor = 50;
    }
  } else {
    if (ctrl_io_in[0]) {
      if (! lastImp) {
        if (ctrl_io_out[0]) {
          if (directionUp) {
            cnt ++;
          } else {
            cnt --;
          }
        } else {
          if (timImp > 0) {
            if (directionUp) {
              cnt ++;
            } else {
              cnt --;
            }
          }
        }
      }
    }
    if (ctrl_io_in[2]) {
      cnt = 0;
      cntValid = 1;
    }
    lastImp = ctrl_io_in[0];
    if (timImp > 0) {
      timImp --;
      if (timImp == 0) {
        if (cmd != 0) {
          cmd = 0;
        }
      }
    }
    if (timMotor > 0) {
      timMotor --;
      if (cmd == 3) {
        directionUp = 1;
      } else {
        if (cmd == 1) {
          directionUp = 1;
        }
      }
      ctrl_io_out[1] = directionUp;
      if (! cntValid) {
        cnt = 0;
        if (cmd == 3) {
          endCnt = one_level;
        } else {
          endCnt = - one_level;
        }
      } else {
        endCnt = cnt;
        newLevel = -99;
        if (cmd == 3) {
          newLevel = level + 1;
        } else {
          if (cmd == 4) {
            newLevel = level - 1;
          }
        }
        newLevel --;
        if (newLevel >= 0) {
          if (newLevel < 14) {
            endCnt = levelPos[newLevel];
          }
        }
      }
    } else {
      run = 0;
      if (cmd == 3) {
        if (cnt < endCnt - 1) {
          if (! ctrl_io_in[1]) {
            run = 1;
            goto RETURN_checkRun;
          }
        }
      } else {
        if (cmd == 4) {
          if (cnt > endCnt + 1) {
            if (! ctrl_io_in[2]) {
              run = 1;
              goto RETURN_checkRun;
            }
          }
        } else {
          if (cmd == 1) {
            if (loadPending) {
              if (ctrl_io_in[3]) {
                loadLevel = level;
                loadPending = 0;
                run = 0;
                goto RETURN_checkRun;
              }
            }
            if (! ctrl_io_in[1]) {
              run = 1;
              goto RETURN_checkRun;
            }
            loadPending = 0;
          } else {
            if (cmd == 2) {
              if (loadPending) {
                if (loadSensor) {
                  if (! ctrl_io_in[3]) {
                    loadSensor = 0;
                    loadPending = 0;
                    loadLevel = level;
                    run = 0;
                    goto RETURN_checkRun;
                  }
                }
                loadSensor = ctrl_io_in[3];
              }
              if (! ctrl_io_in[2]) {
                run = 1;
                goto RETURN_checkRun;
              }
            }
          }
        }
      }
      run = 0;
      RETURN_checkRun: 
      if (ctrl_io_out[0]) {
        if (! run) {
          cmd = 99;
          timImp = 50;
        }
      }
      ctrl_io_out[0] = run;
    }
  }
  checkLevel_middle = one_level >> 2;
  if (cntValid) {
    level = 1;
    while (level < 14) {
      if (cnt < levelPos[level] - checkLevel_middle) {
        break;
      }
      level ++;
    }
  } else {
    level = 0;
  }
  checkLevel_i = 0;
  while (checkLevel_i < 14) {
    ctrl_io_led[checkLevel_i] = checkLevel_i == level - 1;
    checkLevel_i ++;
  }
  ctrl_io_led[13] = (dbgCnt & 128) != 0;
  dbgCnt ++;
  return;
}
}
int ctrl_io_in[10]  ;
int ctrl_io_out[4]  ;
int ctrl_io_analog[4]  ;
int ctrl_io_led[14]  ;
int ctrl_dly1  ;
int ctrl_dly2  ;
int volatile   simio_in  ;
int volatile   simio_out  ;
int volatile   simio_led  ;
int volatile   simio_adc1  ;
int volatile   simio_adc2  ;
int volatile   simio_adc3  ;
void ctrl_get_vals(void) ;
void ctrl_set_vals(void) ;
void io_init(void) 
{ 

  {
  __CrestInt(& ctrl_dly1);
  __CrestInt(& ctrl_dly2);
  return;
}
}
void ctrl_set_vals(void) 
{ int val ;
  int i ;

  {
  val = 0;
  i = 3;
  while (i >= 0) {
    val <<= 1;
    if (ctrl_io_out[i]) {
      val |= 1;
    }
    i --;
  }
  simio_out = (int volatile   )val;
  i = 13;
  while (i >= 0) {
    val <<= 1;
    if (ctrl_io_led[i]) {
      val |= 1;
    }
    i --;
  }
  simio_led = (int volatile   )val;
  return;
}
}
void ctrl_get_vals(void) 
{ int i ;
  int in0 ;
  int in1 ;
  int in2 ;

  {
  i = 0;
  in0 = (int )simio_in;
  in1 = ctrl_dly1;
  in2 = ctrl_dly2;
  ctrl_dly2 = ctrl_dly1;
  ctrl_dly1 = in0;
  while (i < 10) {
    ctrl_io_in[i] = ((in0 & 1) + (in1 & 1)) + (in2 & 1) > 1;
    in0 >>= 1;
    in1 >>= 1;
    in2 >>= 1;
    i ++;
  }
  ctrl_io_analog[0] = (int )simio_adc1;
  ctrl_io_analog[1] = (int )simio_adc2;
  ctrl_io_analog[2] = (int )simio_adc3;
  _Learn_assert(ctrl_io_analog[2] > 0);
//	__CPROVER_assert(ctrl_io_analog[2] > 0, "");
  return;
}
}
void controller(void) 
{ 

  {
  ctrl_get_vals();
  ctrl_loop();
  ctrl_set_vals();
  return;
}
}
int main(void) 
{ 

  {
  ctrl_init();
  controller();
  return (0);
}
}

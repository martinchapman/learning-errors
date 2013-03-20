@echo off
IF "%3" == "m" (echo #define membership > mode.c) else (echo #define conjecture > mode.c)
goto-cl %1.c
goto-instrument --function-enter _Learn_function_enter --dump-c %1.exe a.c
cbmc -Iansi-c-lib --unwind %2 --no-unwinding-assertions --xml-ui a.c > tmp
grep ERROR tmp
IF %errorlevel% == 0 echo ERROR in output of CBMC
IF NOT "%3" == "m" (grep -A 3 "<identifier>c::_Learn_ce_length</identifier>" tmp | grep "<value>" | tail -n 1 |  tr -d "<value>"/,\{\}  > model.txt ) 
grep -A 3 "<identifier>c::_Learn_b</identifier>" tmp | grep "<value>" | tail -n 1 |  tr -d "<value>"/,\{\}  >> model.txt
rem grep -q FAILURE tmp   // this is done inside online.cpp, because the return value does not always go through once it is in a batch file
exit /B %errorlevel% 
@echo off
IF "%2" == "m" (echo #define membership > mode.c) else (echo #define conjecture > mode.c)
cbmc --unwind 8 --no-unwinding-assertions --xml-ui %1 > tmp
grep -A 3 "<identifier>c::_Learn_b</identifier>" tmp | grep "<value>" | tail -n 1 |  tr -d "<value>"/,\{\}  > model.txt
grep -q FAILURE tmp
exit /b %errorlevel% 
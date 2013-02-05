@echo off
IF "%1" == "m" (echo #define membership > mode.c) else (echo #define conjecture > mode.c)
cbmc --unwind 5 --no-unwinding-assertions --xml-ui try_membership.c > tmp
grep -A 3 "<identifier>c::_Learn_b</identifier>" tmp | grep "<value>" | tail -n 1 |  tr -d "<value>"/\{\}
grep FAILURE tmp
exit /b %errorlevel% 
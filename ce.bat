@echo off
REM from this we figure if this is a negative (0) or positive (1) feedback:
echo -1 > model.txt
grep -A 5 "display_name=\"Assert::feedback\"" %1 | tail -n 1 | sed -e s/"<value>"// -e s/"<\/value>"// > model.txt
REM from this we figure the length of the CE
grep -A 5 "identifier=\"_Learn_ce_length\"" %1 | grep "<value>" | tail -n 1 | tr -d "<value>/{}," >> model.txt
REM from this we figure the actual CE
grep -A 5 "identifier=\"_Learn_b\"" %1 | grep "<value>" | tail -n 1 | tr -d "<value>/{},"  >> model.txt
exit /B %errorlevel% 
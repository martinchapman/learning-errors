@echo off
REM from this we figure if this is a negative (0) or positive (1) feedback:
grep -A 1 "<display_name>check_conjecture::assert_condition</display_name>" tmpfile | tail -n 1 | grep -c FALSE > model.txt
REM from this we figure the length of the CE
grep -A 3 "<identifier>c::_Learn_ce_length</identifier>" %1 | grep "<value>" | tail -n 1 |  tr -d "<value>"/,\{\}  >> model.txt  
REM from this we figure the actual CE
grep -A 3 "<identifier>c::_Learn_b</identifier>" %1 | grep "<value>" | tail -n 1 |  tr -d "<value>"/,\{\}  >> model.txt
exit /B %errorlevel% 
@echo off
IF NOT "%2" == "m" (grep -A 3 "<identifier>c::_Learn_ce_length</identifier>" %1 | grep "<value>" | tail -n 1 |  tr -d "<value>"/,\{\}  > model.txt ) 
grep -A 3 "<identifier>c::_Learn_b</identifier>" %1 | grep "<value>" | tail -n 1 |  tr -d "<value>"/,\{\}  >> model.txt
exit /B %errorlevel% 
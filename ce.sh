#!/bin/bash
#from this we figure if this is a negative (0) or positive (1) feedback
echo -1 > model.txt

# version 4.7
#grep -A 1 "<display_name>Assert::feedback</display_name>" $1 | tail -n 1 | sed -e s/"<value>"// -e s/"<\/value>"// > model.txt
# version 4.9
#grep -A 5 "display_name=\"c::Assert::feedback\"" $1 | tail -n 1 | sed -e s/"<value>"// -e s/"<\/value>"// > model.txt
# version 5.0
grep -A 5 "display_name=\"Assert::feedback\"" $1 | tail -n 1 | sed -e s/"<value>"// -e s/"<\/value>"// > model.txt

#from this we figure the length of the CE
# version 4.7
#grep -A 3 "<identifier>c::_Learn_ce_length</identifier>" $1 | grep "<value>" | tail -n 1 | tr -d "<value>/{}," >> model.txt
# version 4.9
#grep -A 5 "identifier=\"c::_Learn_ce_length\"" $1 | grep "<value>" | tail -n 1 | tr -d "<value>/{}," >> model.txt
# version 5.0
grep -A 5 "identifier=\"_Learn_ce_length\"" $1 | grep "<value>" | tail -n 1 | tr -d "<value>/{}," >> model.txt


#from this we figure the actual CE
# version 4.7
#grep -A 3 "<identifier>c::_Learn_b</identifier>" $1 | grep "<value>" | tail -n 1 | tr -d "<value>/{},"  >> model.txt
# version 4.9
#grep -A 5 "identifier=\"c::_Learn_b\"" $1 | grep "<value>" | tail -n 1 | tr -d "<value>/{},"  >> model.txt
# version 5.0
grep -A 5 "identifier=\"_Learn_b\"" $1 | grep "<value>" | tail -n 1 | tr -d "<value>/{},"  >> model.txt
result=$?
exit $result

#!/bin/bash
#from this we figure if this is a negative (0) or positive (1) feedback
echo -1 > model.txt

# version 4.7
#grep -A 3 "<identifier>c::Assert::[^:]*::local_feedback.*</identifier>" $1 | tail -n 1 | sed -e s/"<value>"// -e s/"<\/value>"// > model.txt
# version 4.9
#grep -A 5 "identifier=\"c::Assert::[^:]*::local_feedback.*\"" $1 | tail -n 1 | sed -e s/"<value>"// -e s/"<\/value>"// > model.txt
#version 5.0
#grep -A 5 "identifier=\"Assert::[^:]*::local_feedback.*\"" $1 | tail -n 1 | sed -e s/"<value>"// -e s/"<\/value>"// > model.txt
grep -A 4 "identifier=\"Assert::[^:]*::local_feedback.*\"" $1 | tail -n 1 | sed -e s/"<full_lhs_value>"// -e s/"<\/full_lhs_value>"// > model.txt

#from this we figure the length of the CE
# version 4.7
#grep -A 3 "<identifier>c::_Learn_ce_length.*</identifier>" $1 | grep "<value>" | tail -n 1 | tr -d "<value>/{}," >> model.txt
# version 4.9
#grep -A 5 "identifier=\"c::_Learn_ce_length.*\"" $1 | grep "<value>" | tail -n 1 | tr -d "<value>/{}," >> model.txt
# version 5.0
#grep -A 5 "identifier=\"_Learn_ce_length.*\"" $1 | grep "<value>" | tail -n 1 | tr -d "<value>/{}," >> model.txt
grep -A 4 "identifier=\"_Learn_ce_length.*\"" $1 | grep "<full_lhs_value>" | tail -n 1 | tr -d "<full_lhs_value>/{}," >> model.txt


word_length=`cat word_length`
#version 4.7
#identifier=`grep "<identifier>c::_Learn_b\\[0\\].*</identifier>" $1 | tail -n 1`
#version 4.9
#identifier=`grep "identifier=\"c::_Learn_b\\[0\\].*\"" $1 | tail -n 1`
#if [ "$identifier" == "" ]; then
#   echo "EMPTY"
#fi
#suffix=${identifier:`expr index "$identifier" "#"`}
#index=${suffix:0:`expr index "${suffix}" "\""`-1}
# Version 4.9
#tmp=`grep -A 5 "identifier=\"c::_Learn_b\\[0\\]\"" $1 | grep "<full_lhs_value>" | tail -n 1 | tr -d "<full_lhs_value>/{}," | xargs`
# Version 5.0
tmp=`grep -A 4 "identifier=\"_Learn_b\\[0\\]\"" $1 | grep "<full_lhs_value>" | tail -n 1 | tr -d "<full_lhs_value>/{}," | xargs`
result=$?
word="    "
for (( c=0; c<=$word_length; c++ ))
do
  # version 4.9
  #tmp=`grep -A 5 "identifier=\"c::_Learn_b\\[$c\\]#[^\"]*\"" $1 | grep "<full_lhs_value>" | tail -n 1 | tr -d "<full_lhs_value>/{}," | xargs`
  # version 5.0
  tmp=`grep -A 4 "identifier=\"_Learn_b\\[$c\\]#[^\"]*\"" $1 | grep "<full_lhs_value>" | tail -n 1 | tr -d "<full_lhs_value>/{}," | xargs`
  if [ -z "$tmp" ]; then
    word="$word 0"
  else
    word="$word $tmp"
  fi
done
echo "$word" >> model.txt

exit $result

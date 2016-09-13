#! /bin/bash

OKBLUE="\033[94m";
END_COLOR="\033[0m";
OKGREEN="\033[92m";
ERROR_RED="\033[91m";

gcc *.c *.h -fprofile-arcs -ftest-coverage -Wall -g

if [ $? -eq 0 ]
then
  printf $OKGREEN'Compile Successful'$END_COLOR'\n'
else
  printf $ERROR_RED'Compile failed'$END_COLOR'\n'
fi

TEST_DIR=./test_cases/
TEST_INPUT_MASK=*.inp
for f in $TEST_DIR$TEST_INPUT_MASK
do
  echo "Processing $f file..."
  # take action on each file. $f store current file name
  output=$(./a.out < $f )

  #uses basename to pull off extension and replace with .out
  outputFilename=`basename "$f" ".inp"`.expectedout
  expectedOutput=$(cat $TEST_DIR$outputFilename)
  if [ "$output" == "$expectedOutput" ] ; then
        printf "\t$f TEST PASSED!!!\n"
  else
        printf "\t"$ERROR_COLOR"Test failed!!!\n"
        printf "\tOutput          = \'$output\'\n"
        printf "\tExpected Output = \'$expectedOutput\'"$END_COLOR"\n"
        exit 1244
  fi

done

printf $OKBLUE"ALL TESTS COMPLETED SUCCESSFULLY \n\n"$END_COLOR
printf "************************\n"
gcov main.c 
printf "************************\n"



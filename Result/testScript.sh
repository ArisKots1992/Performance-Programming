#!/bin/bash
# I created this script in order to check the correctness of my tests with the correct results
# the dat***_original where produced by just running the original code with no change at all
if [ "$(./diff-output output.dat100_original output.dat100)" == "$(./diff-output output.dat100_original output.dat100_original)" ] &&
 [ "$(./diff-output output.dat200_original output.dat200)" == "$(./diff-output output.dat200_original output.dat200_original)" ] &&
[ "$(./diff-output output.dat300_original output.dat300)" == "$(./diff-output output.dat300_original output.dat300_original)" ] &&
[ "$(./diff-output output.dat400_original output.dat400)" == "$(./diff-output output.dat400_original output.dat400_original)" ] &&
[ "$(./diff-output output.dat500_original output.dat500)" == "$(./diff-output output.dat500_original output.dat500_original)" ]; then
echo
echo "PASSED"
echo
else
echo
echo "FAILED"
echo
fi

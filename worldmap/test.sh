TESTCASE=6-66
g++ -O2 code.cpp worldmap/graders/grader.cpp
./a.out <worldmap/tests/$TESTCASE.in >.tmp.out && ./check.out worldmap/tests/$TESTCASE.in worldmap/tests/$TESTCASE.out .tmp.out && rm .tmp.out
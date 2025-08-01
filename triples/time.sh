
# g++ -O2 code.cpp grader.cpp &&
python3 gen.py >.in &&
time ./a.out <.in > .res
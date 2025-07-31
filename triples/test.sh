
g++ -O2 code.cpp grader.cpp &&
python3 gen.py >.in &&
./bf.out <.in >.ans &&
./a.out <.in > .res &&
diff -q .res .ans &&
rm .in .ans .res
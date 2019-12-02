#!/bin/bash

./generator < tests/test1.m > outputTest1.c && gcc -o test1 outputTest1.c && ./test1
./generator < tests/test2.m > outputTest2.c && gcc -o test2 outputTest2.c && ./test2
./generator < tests/test3.m > outputTest3.c && gcc -o test3 outputTest3.c && ./test3
./generator < tests/test4.m > outputTest4.c && gcc -o test4 outputTest4.c && ./test4
./generator < tests/test5.m > outputTest5.c && gcc -o test5 outputTest5.c && ./test5


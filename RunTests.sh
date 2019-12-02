#!/bin/bash

./generator < tests/test1.m > output.c && gcc -o test1 output.c && ./test1
./generator < tests/test2.m > output.c && gcc -o test2 output.c && ./test2
./generator < tests/test3.m > output.c && gcc -o test3 output.c && ./test3
./generator < tests/test4.m > output.c && gcc -o test4 output.c && ./test4
./generator < tests/test5.m > output.c && gcc -o test5 output.c && ./test5


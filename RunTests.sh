#!/bin/bash
./generator < tests/test1.m > generatedCode/outputTest1.c && gcc -o executableTests/test1 generatedCode/outputTest1.c && ./executableTests/test1
./generator < tests/test2.m > generatedCode/outputTest2.c && gcc -o executableTests/test2 generatedCode/outputTest2.c && ./executableTests/test2
./generator < tests/test3.m > generatedCode/outputTest3.c && gcc -o executableTests/test3 generatedCode/outputTest3.c && ./executableTests/test3
./generator < tests/test4.m > generatedCode/outputTest4.c && gcc -o executableTests/test4 generatedCode/outputTest4.c && ./executableTests/test4
./generator < tests/test5.m > generatedCode/outputTest5.c && gcc -o executableTests/test5 generatedCode/outputTest5.c && ./executableTests/test5
./generator < tests/test6.m > generatedCode/outputTest6.c && gcc -o executableTests/test6 generatedCode/outputTest6.c && ./executableTests/test6
./generator < tests/test7.m > generatedCode/outputTest7.c && gcc -o executableTests/test7 generatedCode/outputTest7.c && ./executableTests/test7
./generator < tests/test8.m > generatedCode/outputTest8.c && gcc -o executableTests/test8 generatedCode/outputTest8.c && ./executableTests/test8

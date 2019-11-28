# TLA
Creating our own programming language

#How to compile LEX and YACC
##YACC
Run:
```
yacc -d file.y
```
The -d generates the y.tab.h header file
The rest generates the y.tab.c (actual generated parser)

##LEX
Run:
```
lex file.l
gcc -lfl lex.yy.c
```

##Compile together
```
gcc lex.yy.c y.tab.c -o executable
./executable
```
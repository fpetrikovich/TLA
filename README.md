# TLA
Creating our own programming language

# How to compile the project
## Compile Yacc, Lex, project and tests:
```
make clean
make all
chmod +x RunTests.sh
```
## Run Tests
```
./RunTests.sh
```

### Git Structure
The LEX file is scanner.l
The YACC file is yacc.y
The tests are found in the folder named test. After running the bash script RunTests.sh, the generated C code will by in the generatedCode folder. The executable files will be found in the executableTests folder. 
The report can be found in the document folder.

all:
	yacc -d yacc.y -Wconflicts-rr
	lex scanner.l
	gcc lex.yy.c y.tab.c codeTranslator.c tokenFunctions.c -o generator
clean:
	rm generator

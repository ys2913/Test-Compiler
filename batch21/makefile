stage1exe: driver.c semantic.o symboltable.o parser.o lexer.o
	gcc -g -o stage1exe driver.c semantic.o symboltable.o parser.o lexer.o
semantic.o: semantic.c
	gcc -g -c semantic.c -lm
symboltable.o: symboltable.c
	gcc -g -c symboltable.c -lm
parser.o: parser.c
	gcc -g -c parser.c -lm
lexer.o: lexer.c
	gcc -g -c lexer.c -lm
clean:
	rm -f driver.o parser.o lexer.o

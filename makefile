# Group 15
# Alex Mathai - 2016A7PS0339P
# Sarthak Agarwal - 2016A7PS0135P
# Sanchit Shrivastava - 2016A7PS0072P
# Aman Sanghi - 2016A7PS0024P

all: ast.o lexer.o parser.o symboltable.o codegen.o
	gcc -o toycompiler driver.c parser.o lexer.o ast.o symboltable.o codegen.o

codegen.o: codegen.c symboltable.h codegen.h
	gcc -c symboltable.h codegen.h codegen.c

parser.o: parser.c parser.h parserDef.h lexer.h lexerDef.h ast.h astDef.h
	gcc -c parser.h parserDef.h parser.c

lexer.o: lexer.c lexer.h lexerDef.h
	gcc -c lexer.h lexerDef.h lexer.c

ast.o: ast.c ast.h astDef.h 
	gcc -c ast.h astDef.h ast.c
	
symboltable.o: symboltable.c symboltable.h symboltabledef.h
	gcc -c symboltable.h symboltable.c symboltabledef.h

clean:
	rm *.o
	rm *.h.gch
	rm toycompiler

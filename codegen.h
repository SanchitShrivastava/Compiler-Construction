// Group 15
// Alex Mathai - 2016A7PS0339P
// Sarthak Agarwal - 2016A7PS0135P
// Sanchit Shrivastava - 2016A7PS0072P
// Aman Sanghi - 2016A7PS0024P

#ifndef CODEGEN
#define CODEGEN

#include <stdio.h>
#include "astDef.h"

void printNewline(FILE*fp);
void printDecimalNumber(FILE* fp);
void printNegPos(FILE*fp);
void takeUserInput(FILE* fp);
void DeclareglobalVariablesInBss(FILE* fp);
void DeclaremainVariablesInBss(FILE* fp);
int findarithmetic(FILE *fp,astNode* stmt);
void booleanfinder(FILE *fp,astNode* stmt);
void generatecode(FILE* fp,astNode* stmt);
void codegenerator(FILE* fp, ASTM* tree);

#endif
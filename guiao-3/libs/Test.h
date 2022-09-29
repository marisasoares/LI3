//#include "sg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>
#include "Controller.h"

int main();

int compareFile(FILE *file1, FILE *file2);

void teste(int time, int f, int i);

void querie_test(char *line, SGC sgc, FILE *newfile, char *filename);

void parseTestes(SGC sgc);

void test_query1(LISTAUSERS lu, FILE *newfile, char *filename);

void test_query2(FILE *newfile, LISTACOMMITS lc, LISTAREPOS lr, char *filename);

void test_query3(LISTAUSERS lu, LISTACOMMITS lc, FILE *newfile, char *filename);

void test_query4(LISTAUSERS lu, LISTACOMMITS lc, FILE *newfile, char *filename);

void test_query5(char* line, FILE *newfile, LISTACOMMITS lc, LISTAUSERS lu, char *filename);

void test_query6(char *line, FILE* newfile, LISTAREPOS lr, LISTACOMMITS lc, LISTAUSERS lu, char *filename);

void test_query7(char* line, FILE *newfile, LISTACOMMITS lc, LISTAREPOS lr, char *filename);

void test_query8(char *line, LISTAREPOS lr, FILE *newfile, char *filename);

void test_query9(char* line, FILE *newfile, LISTACOMMITS lc, LISTAUSERS lu, LISTAREPOS lr, char *filename);

void test_query10(char* line, FILE *newfile, LISTACOMMITS lc, LISTAUSERS lu, char *filename);

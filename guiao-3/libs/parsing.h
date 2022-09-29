#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void getFollowList(char* line, int list[]);

int exists(int N, int following[], int size);

int verificarDataAux(int ano, int mes, int dia, int h, int m, int s);

int verificarData(char *fields);

int isNumber(char *string);

int isInt(char* fields);

int getFollow(char* string);

int validaLista(char* fields, int f);

char *aspas(char *line);
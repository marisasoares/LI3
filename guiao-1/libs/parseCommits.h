#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "parseRepos.h"

int adicionarC(char* line, LISTAREPOS lr, LISTAUSERS u);

void adicionarCommits(LISTAUSERS u, LISTAREPOS r);

int linhaValidaCommits(char *line);

void parseCommits();

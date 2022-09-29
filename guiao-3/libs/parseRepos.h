#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "catalogoUsers.h"
#include "catalogoRepos.h"
#include "catalogoCommits.h"

int adicionarR(char* line, LISTAREPOS lr, LISTAUSERS u);

void adicionarRepos(LISTAUSERS u, LISTAREPOS l);

int linhaValidaRepos(char *line);

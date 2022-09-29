#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "parseCommits.h"

int adicionarU(char *line, LISTAUSERS l);

void adicionarUsers(LISTAUSERS lu);

int linhaValida(char *line);

void parseUsers();

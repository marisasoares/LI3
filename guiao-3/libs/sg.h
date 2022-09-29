#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "parseUsers.h"

typedef struct sgc *SGC;

SGC initSGC();

LISTAREPOS getLRepos();

LISTACOMMITS getLCommits();

LISTAUSERS getLUsers();

SGC load_sgc();

void free_sgc(SGC sgc);
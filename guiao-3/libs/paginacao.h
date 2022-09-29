#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "catalogoUsers.h"
#include "catalogoRepos.h"
#include "catalogoCommits.h"
#include "UI.h"

void check_scanf(int error);

void paginacao(GList *lista, int N, int q, GHashTable *l2);

int toPage(GList *lista, int linhas_init, int linhas_end, int N, int q, GHashTable *l2);
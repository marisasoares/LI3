#include "repos.h"
#include <glib.h>

typedef struct lRepos{
    GHashTable *repos;
}*LISTAREPOS;

LISTAREPOS initListaRepos();

void addRepos(LISTAREPOS l, REPOS r);


#include <glib.h>

typedef struct lRepos{
    GHashTable *repos;
}*LISTAREPOS;

typedef struct repos{
    int id;
    int owner_id;
    char* language;
    char* data;
    char* description;
  
} *REPOS;

LISTAREPOS initListaRepos();

void addRepos(LISTAREPOS l, REPOS r);

REPOS initRepos(int id, int owner, char* lang, char* d, char *desc);

int getIDR(REPOS r);

int getOwner(REPOS r);

char* getLanguage(REPOS r);

char* getDate(REPOS r);

char* getDescription(REPOS r);

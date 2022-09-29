
#include <glib.h>

typedef struct lRepos *LISTAREPOS;

typedef struct repos *REPOS;

LISTAREPOS initListaRepos();

void addRepos(LISTAREPOS l, REPOS r);

REPOS initRepos(int id, int owner, char* lang, char* d, char *desc);

int getIDR(REPOS r);

int getOwner(REPOS r);

char* getLanguage(REPOS r);

char* getDate(REPOS r);

char* getDescription(REPOS r);

GHashTable *get_catalogoRepos(LISTAREPOS l);

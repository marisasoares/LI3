//CATALAOGO COMMITS

#include <glib.h>

typedef struct lCommits *LISTACOMMITS;

typedef struct commit *COMMIT;

LISTACOMMITS initListaCommits();

void addCommit(LISTACOMMITS l, COMMIT u, int i);

COMMIT initCommit(int repo, int author, int commiter, char* d, int m);

int getRepo(COMMIT c);

int getAuthor(COMMIT c);

int getCommiter(COMMIT c);

char *getDateCommit(COMMIT c);

int getMessage(COMMIT c);

GHashTable *get_catalogoCommits(LISTACOMMITS l);
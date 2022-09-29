//CATALAOGO COMMITS

#include <glib.h>

typedef struct lCommits{
    GHashTable *commit;
} *LISTACOMMITS;

typedef struct commit{
    int repo_id;
    int author_id;
    int commiter_id;
    char* date;
    char* message;
  
} *COMMIT;

LISTACOMMITS initListaCommits();

void addCommit(LISTACOMMITS l, COMMIT u, int i);

COMMIT initCommit(int repo, int author, int commiter, char* d, char* m);

int getRepo(COMMIT c);

int getAuthor(COMMIT c);

int getCommiter(COMMIT c);

char *getDateCommit(COMMIT c);

char *getMessage(COMMIT c);

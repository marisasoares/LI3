
#include <glib.h>

typedef struct lUsers{
    GHashTable *user;
} *LISTAUSERS;

typedef struct user{
    int id;
    char* username;
    char* type;
    int friends[100000];
    int n_amigos;
    int n_commits;
} *USER;

LISTAUSERS initListaUsers();

void addUser(LISTAUSERS l, USER u);

USER initUser(int id, char* uname, char* tipo);

int getID(USER u);

char* getType(USER u);

int* cloneFriends(int friends[], int N);

int* getFriends(USER u);

int getNAmigos(USER u);

int getNCommits(USER u);

char* getUsername(USER u);



#include "user.h"
#include <glib.h>

typedef struct lUsers{
    GHashTable *user;
} *LISTAUSERS;

LISTAUSERS initListaUsers();

void addUser(LISTAUSERS l, USER u);

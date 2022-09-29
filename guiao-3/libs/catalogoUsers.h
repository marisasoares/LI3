#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>
#include "../libs/parsing.h"

typedef struct lUsers *LISTAUSERS;

typedef struct user *USER;

LISTAUSERS initListaUsers();

void addUser(LISTAUSERS l, USER u);

USER initUser(int id, char* uname, char* tipo);

int getID(USER u);

char* getType(USER u);

int* cloneFriends(int friends[], int N);

int* getFriends(USER u);

int *getFriendList(USER u);

int getNAmigos(USER u);

int getNCommits(USER u);

void incCommits(USER u);
void setCommits(USER u, int n);

char* getUsername(USER u);

GHashTable *get_catalogoUsers(LISTAUSERS l);

void getFriendsList(int followers[], int fsize, int following[], int fsize2, USER u);



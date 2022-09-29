#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/catalogoUsers.h"



LISTAUSERS initListaUsers(){
    LISTAUSERS l = malloc(sizeof(struct lUsers));
    l->user = g_hash_table_new (NULL,NULL);
    return l;
}

void addUser(LISTAUSERS l, USER u){
    g_hash_table_insert(l->user, getID(u), u);
} 

USER initUser(int id, char* uname, char* tipo){
	USER u = malloc(sizeof(struct user));
	u->id = id;
	u->username = uname;
    u->type = tipo;
    u->n_commits = 0;
    u->n_amigos=0;

	return u;
}

int getID(USER u){
	return u->id;
}

char* getUsername(USER u){
	return strdup(u->username);
}

char* getType(USER u){
    return strdup(u->type);
}

int* cloneFriends(int friends[], int N){
    int friendsclone[N];
    for(int i=0; i<N; i++){
        friendsclone[i] = friends[i];
    }
    return friendsclone;
}

int *getFriends(USER u){
    return cloneFriends(u->friends, u->n_amigos);
}

int getNAmigos(USER u){
    return u->n_amigos;
}

int getNCommits(USER u){
    return u->n_commits;
}

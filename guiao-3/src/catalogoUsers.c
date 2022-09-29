#include "../libs/catalogoUsers.h"

struct lUsers{
    GHashTable *user;
};

struct user{
    int id;
    char* username;
    char* type;
    int friends[100000];
    int n_amigos;
    int n_commits;
};

LISTAUSERS initListaUsers(){
    LISTAUSERS l = malloc(sizeof(struct lUsers));
    l->user = g_hash_table_new (NULL, NULL);
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

int *getFriendList(USER u){
    return u->friends;
}

int getNAmigos(USER u){
    return u->n_amigos;
}

int getNCommits(USER u){
    return u->n_commits;
}

void incCommits(USER u){
    u->n_commits++;
}
void setCommits(USER u, int n){
    u->n_commits = n;
}

GHashTable *get_catalogoUsers(LISTAUSERS l){
    return l->user;
}


void getFriendsList(int followers[], int fsize, int following[], int fsize2, USER u){
    for(int i=0, f=0; i<fsize; i++){
        if(exists(followers[i], following, fsize2)) {
            u->friends[u->n_amigos++] = followers[i];
            f++;
        }
    }
}

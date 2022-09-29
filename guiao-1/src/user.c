#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../libs/user.h"

#define ID_SIZE 23
#define MAX_USERNAME_SIZE 50



USER initUser(int id, char* uname){
	USER u = malloc(sizeof(struct user));
	u->id = id;
	u->username = uname;
	return u;
}


int getID(USER u){
	return u->id;
}

char* getUsername(USER u){
	return strdup(u->username);
}


void removeUser(USER u){
    free(u->id);
    free(u->username);
    free(u);
}

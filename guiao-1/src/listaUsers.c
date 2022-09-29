#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/listaUsers.h"


LISTAUSERS initListaUsers(){
    LISTAUSERS l = malloc(sizeof(struct lUsers));
    l->user = g_hash_table_new (NULL,NULL);
    return l;
}

void addUser(LISTAUSERS l, USER u){
    g_hash_table_insert(l->user, u->id, u);
} 

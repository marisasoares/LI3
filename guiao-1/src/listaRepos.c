#include "../libs/listaRepos.h"


LISTAREPOS initListaRepos(){
    LISTAREPOS l = malloc(sizeof(struct lRepos));
    l->repos = g_hash_table_new (NULL,NULL);
    return l;
}

void addRepos(LISTAREPOS l, REPOS r){
    g_hash_table_insert(l->repos, r->id, r);
}  

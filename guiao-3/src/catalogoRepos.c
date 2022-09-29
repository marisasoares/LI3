#include "../libs/catalogoRepos.h"

struct lRepos{
    GHashTable *repos;
};

struct repos{
    int id;
    int owner_id;
    char* language;
    char* data;
    char* description;

};

LISTAREPOS initListaRepos(){
    LISTAREPOS l = malloc(sizeof(struct lRepos));
    l->repos = g_hash_table_new (NULL, NULL);
    return l;
}

void addRepos(LISTAREPOS l, REPOS r){
    g_hash_table_insert(l->repos, r->id, r);
}  

REPOS initRepos(int id, int owner, char* lang, char* d, char *desc){
	REPOS r = malloc(sizeof(struct repos));
	r->id = id;
	r->owner_id = owner;
    r->language = lang;
    r->data = d;
    r->description = desc;

	return r;
}

int getIDR(REPOS r){
	return r->id;
}

int getOwner(REPOS r){
	return r->owner_id;
}

char* getLanguage(REPOS r){
    return strdup(r->language);
}

char* getDate(REPOS r){
    return strdup(r->data);
}

char* getDescription(REPOS r){
    return strdup(r->description);
}

GHashTable *get_catalogoRepos(LISTAREPOS l){
    return l->repos;
}

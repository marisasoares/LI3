#include "../libs/catalogoCommits.h"

struct lCommits{
    GHashTable *commit;
};

struct commit{
    int repo_id;
    int author_id;
    int commiter_id;
    char* date;
    int message;

};

LISTACOMMITS initListaCommits(){
    LISTACOMMITS l = malloc(sizeof(struct lCommits));
    l->commit = g_hash_table_new (NULL, NULL);
    return l;
}

void addCommit(LISTACOMMITS l, COMMIT c, int i){
    g_hash_table_insert(l->commit, i, c);
}  

COMMIT initCommit(int repo, int author, int commiter, char* d, int m){
	COMMIT c = malloc(sizeof(struct commit));
	c->repo_id = repo;
	c->author_id = author;
    c->commiter_id = commiter;
    c->date = d;
    c->message = m;
	return c;
}

int getRepo(COMMIT c){
    return c->repo_id;
}

int getAuthor(COMMIT c){
    return c->author_id;
}

int getCommiter(COMMIT c){
    return c->commiter_id;
}

char *getDateCommit(COMMIT c){
    return strdup(c->date);
}

int getMessage(COMMIT c){
    return c->message;
}

GHashTable *get_catalogoCommits(LISTACOMMITS l){
    return l->commit;
}

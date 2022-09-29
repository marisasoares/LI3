
#include "../libs/sg.h"

struct sgc{
    LISTAREPOS lr;
    LISTAUSERS lu;
    LISTACOMMITS lc;  
};


SGC initSGC(){
    SGC new = (SGC) malloc(sizeof(struct sgc));
    new->lr = initListaRepos();
    new->lu = initListaUsers();
    new->lc = initListaCommits();
    return new;
}

LISTAREPOS getLRepos(SGC sgc){
    return sgc->lr;
}

LISTACOMMITS getLCommits(SGC sgc){
    return sgc->lc;
}

LISTAUSERS getLUsers(SGC sgc){
    return sgc->lu;
}

SGC load_sgc(){
    //inicializar catalogos
    SGC sgc = initSGC();

    adicionarUsers(getLUsers(sgc));
    adicionarRepos(getLUsers(sgc), getLRepos(sgc));
    adicionarCommits(getLUsers(sgc), getLRepos(sgc), getLCommits(sgc));

    return sgc;
}

void free_sgc(SGC sgc){
    free(sgc->lr);
    free(sgc->lu);
    free(sgc->lc);
    free(sgc);
}
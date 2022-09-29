#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/queries.h"

#define BUFF_SIZE 5000


void query1(LISTAUSERS lu, FILE *newfile){
    GHashTable *u = get_catalogoUsers(lu);
    GList *llu = g_hash_table_get_values(u);
    int bot=0, organization=0, user = 0;
   
    for (; llu != NULL; llu = llu->next){

        if(strcmp("Bot", getType(llu->data)) == 0) bot++;

        else if(strcmp("Organization", getType(llu->data)) == 0) organization++;

        else user++;
    
    }

    if(newfile == NULL){
        printf("Bot : %d\n", bot);
        printf("Organization: %d\n", organization);
        printf("User: %d\n", user);
    }else{
        fprintf(newfile, "Bot : %d\n", bot);
        fprintf(newfile, "Organization: %d\n", organization);
        fprintf(newfile, "User: %d\n", user);
    }

}

void query2(FILE *newfile, LISTACOMMITS lc, LISTAREPOS lr){
    LISTAUSERS lista = initListaUsers();
    GHashTable *lista_user = get_catalogoUsers(lista);
    GHashTable *c = get_catalogoCommits(lc);
    GList *llc = g_hash_table_get_values(c);
    int colaboradores = 0;
    int repositorios = 0;
    double avg;

    for(; llc != NULL; llc = llc->next){
        int author = getAuthor(llc->data);
        int commiter = getCommiter(llc->data);

        if(!g_hash_table_lookup(lista_user, author)){
            g_hash_table_insert(lista_user, author, NULL);
            colaboradores++;
        }

        if(!g_hash_table_lookup(lista_user, commiter)){
            g_hash_table_insert(lista_user, commiter, NULL);
            colaboradores++;
        }
    }
        GHashTable *r = get_catalogoRepos(lr);
        repositorios = g_hash_table_size(r);
        
        avg = (double)colaboradores/(double)repositorios;

        if(newfile == NULL){
            printf("%.2f", avg);
        
        }else{
            fprintf(newfile, "%.2f", avg);
        }
          
}

void query3(LISTAUSERS lu, LISTACOMMITS lc, FILE *newfile){
    GHashTable *lcommit = get_catalogoCommits(lc);
    GList* llc = g_hash_table_get_values(lcommit);
    GHashTable* llr = g_hash_table_new(NULL, NULL);
    GHashTable *luser = get_catalogoUsers(lu);
    
    for(; llc != NULL; llc = llc->next){
        USER a = g_hash_table_lookup(luser, getAuthor(llc->data));
        USER c = g_hash_table_lookup(luser, getCommiter(llc->data));
        if(strcmp(getType(a),"Bot") == 0){
            int repo_id = getRepo(llc->data);
            if(!g_hash_table_lookup(llr, repo_id)) 
                g_hash_table_insert(llr, repo_id, NULL);

        }
         if(getAuthor(llc->data) != getCommiter(llc->data) && strcmp(getType(c),"Bot") == 0){
            int repo_id = getRepo(llc->data);
            if(!g_hash_table_lookup(llr, repo_id)) 
                g_hash_table_insert(llr, repo_id, NULL);

        }
    }
    if(newfile == NULL) printf("%d", g_hash_table_size(llr));
    else fprintf(newfile, "%d", g_hash_table_size(llr));
}

void query4(LISTAUSERS lu, LISTACOMMITS lc, FILE *newfile){
    GHashTable *lcommit = get_catalogoCommits(lc);
    GHashTable *luser = get_catalogoUsers(lu);

    double commits = g_hash_table_size(lcommit);
    double users = g_hash_table_size(luser);

    double avg = commits/users;

    if(newfile == NULL)  printf("%f", avg);
    else fprintf(newfile,"%f", avg);
}

//-----------------------------------------------------------------------------------

void acrescentaN_commits(LISTAUSERS lu, LISTACOMMITS lc, char *dataI, char *dataF){
    GHashTable *lcommit = get_catalogoCommits(lc);
    GList *llc = g_hash_table_get_values(lcommit);
    GHashTable *luser = get_catalogoUsers(lu);
    for (; llc != NULL; llc = llc->next){
        if (strcmp(getDateCommit(llc->data), dataI) > 0 && strcmp(getDateCommit(llc->data), dataF) < 0){
            if(getAuthor(llc->data) == getCommiter(llc->data)){

                USER u = g_hash_table_lookup(luser, getAuthor(llc->data));
                incCommits(u);
            }
            else{
                USER u1 = g_hash_table_lookup(luser, getAuthor(llc->data));
                USER u2 = g_hash_table_lookup(luser, getCommiter(llc->data));
                incCommits(u1);
                incCommits(u2);
            }
        }
    }
}

GCompareFunc comparaNCommits(USER u1, USER u2){
    int r;
    int n = getNCommits(u1);
    int m = getNCommits(u2);
    if (n < m)
        r = 1;
    else if (n == m)
        r = 0;
    else r = -1;
    return r;
}

//----------------------------------------------------------------------------------

void query5(char* line, FILE *newfile, LISTACOMMITS lc, LISTAUSERS lu){
    char *fields = strdup(line);
    char *temp, *resto;
    int N;
    char *dataI, *dataF;
    int i = 0;
    for (i = 0; (temp = (strsep(&fields, " "))) != NULL && i < 4; i++){
        switch(i){
            case 1:
                N = strtol(temp, &resto, 10);
                break;
            case 2:
                dataI = strdup(temp);
                break;
            case 3:
                dataF = strdup(temp);
                break;
        }
    }

    acrescentaN_commits(lu, lc, dataI, dataF);
    GHashTable *luser = get_catalogoUsers(lu);

    GList *lista = g_hash_table_get_values(luser);
    lista = g_list_sort(lista, comparaNCommits);

    if(newfile == NULL){
        /*while(N>0){
            printf("%d;", getID(lista->data));
            printf("%s;", getUsername(lista->data));
            printf("%d\n", getNCommits(lista->data));
            lista = lista->next;
            N--;
        }*/
        paginacao(lista, N, 5, NULL);
    }
    else{
        while(N>0){
            fprintf(newfile, "%d;", getID(lista->data));
            fprintf(newfile, "%s;", getUsername(lista->data));
            fprintf(newfile, "%d", getNCommits(lista->data));
            fprintf(newfile, "\n");
            lista = lista->next;
            N--;
        }
    }
}

//-----------------------------------------------

void procuraLinguagem(LISTAREPOS lr, LISTACOMMITS lc, LISTAUSERS lu, char* linguagem){
    GHashTable *lcommit = get_catalogoCommits(lc);
    GHashTable *lrepos = get_catalogoRepos(lr);
    GHashTable *luser = get_catalogoUsers(lu);
    GList *llc = g_hash_table_get_values(lcommit);
    
    for (; llc != NULL; llc = llc->next){
        int repo = getRepo(llc->data);
        

        REPOS r = g_hash_table_lookup(lrepos, repo);

        if(strcmp(getLanguage(r), linguagem) == 0){
            int author = getAuthor(llc->data);
            int commiter = getCommiter(llc->data);
            if(author == commiter){
                USER u = g_hash_table_lookup(luser, author);
                incCommits(u);
            }else{
                USER u2 = g_hash_table_lookup(luser, commiter);
                incCommits(u2);
            }
        }
    }
}

//-----------------------------------------------

void query6(char *line, FILE* newfile, LISTAREPOS lr, LISTACOMMITS lc, LISTAUSERS lu){
    char *fields = strdup(line);
    char *temp, *resto;
    int N;
    char *linguagem;
    int i = 0;
    for (i = 0; (temp = (strsep(&fields, " "))) != NULL && i < 3; i++){
        switch(i){
            case 1:
                N = strtol(temp, &resto, 10);
                break;
            case 2:
                linguagem = strdup(temp);
                break;
        }
    }
    //procura a linguagem
    procuraLinguagem(lr, lc, lu, linguagem);

    GHashTable *luser = get_catalogoUsers(lu);

    GList *lista = g_hash_table_get_values(luser);
    lista = g_list_sort(lista, comparaNCommits);
    
    if(newfile == NULL){
        /*
        printf("%d;", getID(lista->data));
            printf("%s;", getUsername(lista->data));
            printf("%d\n", getNCommits(lista->data));
            lista = lista->next;
            N--;
        */
        paginacao(lista,N,6,NULL);
    }
    else{
        while(N>0){
            fprintf(newfile, "%d;", getID(lista->data));
            fprintf(newfile, "%s;", getUsername(lista->data));
            fprintf(newfile, "%d", getNCommits(lista->data));
            fprintf(newfile, "\n");
            lista = lista->next;
            N--;
        }
    }
}

//----------------------------------------------------------------------------

int existeCommit(GList *Commits, int id){
    int r=0;
    for(; Commits != NULL; Commits->next){
            if(getRepo(Commits->data) == id) r = 1;
    }
    return r;
}

//----------------------------------------------------------------------------

void query7(char* line, FILE *newfile, LISTACOMMITS lc, LISTAREPOS lr){
    GHashTable *lcommit = get_catalogoCommits(lc);

    char *fields = strdup(line);
    char *temp ;
    for(int i=0; i<2; i++)
        temp = strsep(&fields, " ");

    char *data= strdup(temp);

    GList *llc = g_hash_table_get_values(lcommit);

    LISTAREPOS r = initListaRepos();


    GHashTable *lrepos = get_catalogoRepos(lr);
    GHashTable *newr = get_catalogoRepos(r);

    for(; llc != NULL; llc = llc->next){
        if (strcmp(getDateCommit(llc->data), data) > 0){
            int repo_id = getRepo(llc->data);
            REPOS repo = g_hash_table_lookup(lrepos, repo_id);

            if(!g_hash_table_lookup(newr, repo_id)){
                g_hash_table_insert(newr, repo_id, repo);

            }
        }     
    }

    GList *Repos = g_hash_table_get_values(lrepos);
    
    if(newfile == NULL){
        /*for(; Repos != NULL; Repos = Repos->next){
            if(!g_hash_table_lookup(newr, getIDR(Repos->data))){
                printf( "%d;", getIDR(Repos->data));
                printf( "%s", getDescription(Repos->data));
            }
        }
        */
        paginacao(Repos,g_list_length(Repos),7, newr);

    }else{

    for(; Repos != NULL; Repos = Repos->next){
        if(!g_hash_table_lookup(newr, getIDR(Repos->data))){
            fprintf(newfile, "%d;", getIDR(Repos->data));
            fprintf(newfile, "%s", getDescription(Repos->data));
            fprintf(newfile, "\n");
            }
        }
    }
}


GCompareFunc comparaLang(NLang l1, NLang l2){
    if(l1->n_ocorr < l2->n_ocorr)
        return 1;
    if(l1->n_ocorr == l2->n_ocorr)
        return 0;
    else return (-1);
}

void query8(char *line, LISTAREPOS lr, FILE *newfile){
    GHashTable *lrepos = get_catalogoRepos(lr);
    char *arg = strdup(line);
    int N;
    char *sobra, *d, *temp;
 
    for(int i=0; (temp=(strsep(&arg, " "))) != NULL && i<3; i++){
        switch (i){
            case 1:
                N = strtol(temp, &sobra,10);   
                break;
            case 2: 
                d = strdup(temp);
                break;
        }
    }

    GList* listaRepos = g_hash_table_get_values(lrepos);
    GList* novaRepos = NULL;
    //GList* listanova = NULL;
    GHashTable* listaNova = g_hash_table_new(NULL, NULL);

    for(; listaRepos != NULL; listaRepos=listaRepos->next){
        if(strcmp(getDate(listaRepos->data),d) > 0){

            if(g_hash_table_lookup(listaNova, getLanguage(listaRepos->data))){
                NLang n = g_hash_table_lookup(listaNova, getLanguage(listaRepos->data));
                n->n_ocorr++;
            }else{     
                NLang nodo = malloc(sizeof(struct query8));
                nodo->lang = getLanguage(listaRepos->data);
                nodo->n_ocorr = 1;
                
                g_hash_table_insert(listaNova, getLanguage(listaRepos->data), nodo); 
            }
        } 
    }

    novaRepos = g_hash_table_get_values(listaNova);
    novaRepos = g_list_sort(novaRepos, comparaLang);

    GList* langsorted = NULL;

    for(; novaRepos != NULL; novaRepos=novaRepos->next){
        langsorted = g_list_insert(langsorted, ((NLang) (novaRepos->data))->lang, -1);
    }
    

    if(newfile == NULL){
        /*
        while(N>0){
            printf("%s", ((NLang) (novaRepos->data))->lang);
            //fprintf(newfile, "%s", novaRepos->data);
            printf("\n");
            novaRepos = novaRepos->next;
        N--;
        }
        */
        paginacao(langsorted,N,8,NULL);        
    }else{
        while(N>0){
            fprintf(newfile, "%s", langsorted->data);
            //fprintf(newfile, "%s", novaRepos->data);
            fprintf(newfile, "\n");
            langsorted = langsorted->next;
            N--;
        }
    }
    
   
}

void query9(char* line, FILE *newfile, LISTACOMMITS lc, LISTAUSERS lu, LISTAREPOS lr){
    GHashTable *lcommit = get_catalogoCommits(lc);
    GHashTable *luser = get_catalogoUsers(lu);
    GHashTable *lrepos = get_catalogoRepos(lr);
    GList *listaCommits = g_hash_table_get_values(lcommit);
    GList *c = listaCommits;

    for (; c != NULL; c = c->next){
        int author = getAuthor(c->data);
        int commiter = getCommiter(c->data);
        USER u = g_hash_table_lookup(luser, author);
        int repo = getRepo(c->data);
        REPOS r = g_hash_table_lookup(lrepos, repo);
        int owner = getOwner(r);
        USER o = g_hash_table_lookup(luser, owner);
        if(exists(owner, getFriendList(u), getNAmigos(u)))
            incCommits(u);
            
        if(author != commiter) {
            USER comit = g_hash_table_lookup(luser, commiter);
            if(exists(owner, getFriendList(comit), getNAmigos(comit)))
                incCommits(comit);
        }
    }

    GList *lusers = g_hash_table_get_values(luser);
    lusers = g_list_sort(lusers, comparaNCommits);

    char* arg = strdup(line);
    char* temp, *resto;
    for(int i=0; i<2; i++){
        temp = strsep(&arg, " ");
    }

    int N = strtol(temp, &resto, 10);

    if(newfile == NULL){
        /*while(N>0){
            printf("%d;", getID(lusers->data));
            printf("%s\n", getUsername(lusers->data));
            lusers = lusers->next;
            N--;
        paginacao()*/
        paginacao(lusers, N, 9, NULL);
    }else{
        while(N>0){
            fprintf(newfile, "%d;", getID(lusers->data));
            fprintf(newfile, "%s", getUsername(lusers->data));
            fprintf(newfile, "\n");
            lusers = lusers->next;
            N--;
        }
    }
    

}


void initUsers(LISTAUSERS lu){
    GHashTable *luser = get_catalogoUsers(lu);
    GList *lista = g_hash_table_get_keys(luser);

    for(; lista != NULL; lista=lista->next){
        USER u = g_hash_table_lookup(luser, lista->data);
        setCommits(u, 0);
    }

}


int comparaMess(COMMIT m1, COMMIT m2){
    int mess1 =  getMessage(m1);
    int mess2 =  getMessage(m2);
    if(mess1 < mess2)
        return 1;
    if(mess1 == mess2)
        return 0;
    else return (-1);
}


void query10(char* line, FILE *newfile, LISTACOMMITS lc, LISTAUSERS lu){

    GList *lista = g_hash_table_get_values(get_catalogoCommits(lc));

    lista = g_list_sort(lista, comparaMess);

    char* arg = strdup(line);
    char* temp, *resto;
    for(int i=0; i<2; i++){
        temp = strsep(&arg, " ");
    }

    int N = strtol(temp, &resto, 10);

    if(newfile ==NULL) {
        /*while(N>0){
            int id = getCommiter(lista->data);
            USER u = g_hash_table_lookup(get_catalogoUsers(lu), id);
            printf("%d;",id);
            printf("%s;",getUsername(u));
            printf("%d;",strlen(getMessage(lista->data)));
            printf("%d\n",getRepo(lista->data));
            lista = lista->next;
            N--;
        }*/
        GHashTable* lusers = get_catalogoUsers(lu);
        paginacao(lista, N, 10,lusers);
    }else{
        while(N>0){
            int id = getCommiter(lista->data);
            USER u = g_hash_table_lookup(get_catalogoUsers(lu), id);
            fprintf(newfile, "%d;",id);
            fprintf(newfile, "%s;",getUsername(u));
            fprintf(newfile, "%d;",getMessage(lista->data));
            fprintf(newfile, "%d\n",getRepo(lista->data));
            lista = lista->next;
            N--;
        }
    }
}



void querie(char *line, SGC sgc, FILE *newfile){
    char *fields = strdup(line);
    char *temp; 
    clock_t start=0,end=0;
    temp=(strsep(&fields, " "));
    char *resto;
    int q = strtol(temp, &resto, 10);

    switch (q){
        case 1:
            start = clock();
            query1(getLUsers(sgc), newfile);
            end = clock();
            printf("query1 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            break;
        case 2:
            start = clock(); 
            query2(newfile, getLCommits(sgc), getLRepos(sgc));
            end = clock();
            printf("query2 = %f\n", (double)(end-start)/CLOCKS_PER_SEC); 
            break;
        case 3:
            start = clock();
            query3(getLUsers(sgc), getLCommits(sgc), newfile);
            end = clock();
            printf("query3 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            break;
        case 4:
            start = clock();
            query4(getLUsers(sgc), getLCommits(sgc), newfile);
            end = clock();
            printf("query4 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            break;
        case 5:
            start = clock();
            query5(line, newfile, getLCommits(sgc), getLUsers(sgc));
            end = clock();
            printf("query5 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            initUsers(getLUsers(sgc));
            break;
        case 6: 
            start = clock();
            query6(line, newfile, getLRepos(sgc), getLCommits(sgc), getLUsers(sgc));
            end = clock();
            printf("query6 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            initUsers(getLUsers(sgc));
            break;
        case 7:
            start = clock();
            query7(line, newfile, getLCommits(sgc), getLRepos(sgc));
            end = clock();
            printf("query7 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            break;
        case 8:
            start = clock();
            query8(line, getLRepos(sgc), newfile);
            end = clock();
            printf("query8 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            break;
        case 9:
            start = clock();
            query9(line, newfile, getLCommits(sgc), getLUsers(sgc), getLRepos(sgc));
            end = clock();
            printf("query9 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            break;
        case 10:
            start = clock();
            query10(line, newfile, getLCommits(sgc), getLUsers(sgc));
            end = clock();
            printf("query10 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            break;
        }

}


void parseQueries(char* ficheiro, SGC sgc){
    FILE *f = fopen (ficheiro, "r+");
    char* file = malloc(sizeof(char)*BUFF_SIZE);
    int i=1;

    while(fgets(file, BUFF_SIZE, f)){
        char *temp = strdup(file);
        char * line = strdup(strsep(&temp, "\n"));
        char* filename = malloc(100);
        sprintf(filename, "saida/commands%d_output.txt", i);
        FILE *newfile = fopen(filename, "w+");
        querie(line, sgc, newfile);    
        i++;   
        fclose(newfile);
        //free(filename);
    }

    free(file);
    fclose(f);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/queries.h"

#define BUFF_SIZE 5000


void query1(LISTAUSERS lu, FILE *newfile){
    GList *llu = g_hash_table_get_values(lu->user);
    int bot=0, organization=0, user = 0;
   
    for (; llu != NULL; llu = llu->next){

        if(strcmp("Bot", getType(llu->data)) == 0) bot++;

        else if(strcmp("Organization", getType(llu->data)) == 0) organization++;

        else user++;
    
    }
        fprintf(newfile, "Bot : %d\n", bot);
        fprintf(newfile, "Organization: %d\n", organization);
        fprintf(newfile, "User: %d\n", user);
     
    
}

void query2(FILE *newfile, LISTACOMMITS lc, LISTAREPOS lr){
    LISTAUSERS lista = initListaUsers();
    GList *llc = g_hash_table_get_values(lc->commit);
    int colaboradores = 0;
    int repositorios = 0;
    double avg;

    for(; llc != NULL; llc = llc->next){
        int author = getAuthor(llc->data);
        int commiter = getCommiter(llc->data);

        if(!g_hash_table_lookup(lista->user, author)){ 
            g_hash_table_insert(lista->user, author, NULL); 
            colaboradores++;
        }

        if(!g_hash_table_lookup(lista->user, commiter)){
            g_hash_table_insert(lista->user, commiter, NULL); 
            colaboradores++;
        }
    }
        
        repositorios = g_hash_table_size(lr->repos);
        
        avg = (double)colaboradores/(double)repositorios;

        fprintf(newfile, "%.2f", avg);
         
}

void query3(LISTAUSERS lu, LISTACOMMITS lc, FILE *newfile){
    GList* llc = g_hash_table_get_values(lc->commit);
    GHashTable* llr = g_hash_table_new(NULL, NULL);
    
    for(; llc != NULL; llc = llc->next){
        USER a = g_hash_table_lookup(lu->user, getAuthor(llc->data));
        USER c = g_hash_table_lookup(lu->user, getCommiter(llc->data));
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
    fprintf(newfile, "%d", g_hash_table_size(llr));
}

void query4(LISTAUSERS lu, LISTACOMMITS lc, FILE *newfile){
    double commits = g_hash_table_size(lc->commit);
    double users = g_hash_table_size(lu->user);

    double avg = commits/users;

    fprintf(newfile,"%f", avg);
}

//-----------------------------------------------------------------------------------

void acrescentaN_commits(LISTAUSERS lu, LISTACOMMITS lc, char *dataI, char *dataF){
    GList *llc = g_hash_table_get_values(lc->commit);
    
    for (; llc != NULL; llc = llc->next){
        if (strcmp(getDateCommit(llc->data), dataI) > 0 && strcmp(getDateCommit(llc->data), dataF) < 0){
            if(getAuthor(llc->data) == getCommiter(llc->data)){
                USER u = g_hash_table_lookup(lu->user, getAuthor(llc->data));
                u->n_commits++;
            }
            else{
                USER u1 = g_hash_table_lookup(lu->user, getAuthor(llc->data));
                USER u2 = g_hash_table_lookup(lu->user, getCommiter(llc->data));
                u1->n_commits++;
                u2->n_commits++;
            }
        }
    }
}

GCompareFunc comparaNCommits(USER u1, USER u2){
    int r;
    if (u1->n_commits < u2->n_commits)
        r = 1;
    else if (u1->n_commits == u2->n_commits)
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

    GList *lista = g_hash_table_get_values(lu->user);
    lista = g_list_sort(lista, comparaNCommits);

    while(N>0){
        fprintf(newfile, "%d;", getID(lista->data));
        fprintf(newfile, "%s;", getUsername(lista->data));
        fprintf(newfile, "%d", getNCommits(lista->data));
        fprintf(newfile, "\n");
        lista = lista->next;
        N--;
    }

}

//-----------------------------------------------

void procuraLinguagem(LISTAREPOS lr, LISTACOMMITS lc, LISTAUSERS lu, char* linguagem){
    GList *llc = g_hash_table_get_values(lc->commit);
    
    for (; llc != NULL; llc = llc->next){
        int repo = getRepo(llc->data);
        

        REPOS r = g_hash_table_lookup(lr->repos, repo);

        if(strcmp(getLanguage(r), linguagem) == 0){
            int author = getAuthor(llc->data);
            int commiter = getCommiter(llc->data);
            if(author == commiter){
                USER u = g_hash_table_lookup(lu->user, author);
                u->n_commits++;
            }else{
                USER u2 = g_hash_table_lookup(lu->user, commiter);
                u2->n_commits++;
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

    GList *lista = g_hash_table_get_values(lu->user);
    lista = g_list_sort(lista, comparaNCommits);
    
    while(N>0){
        fprintf(newfile, "%d;", getID(lista->data));
        fprintf(newfile, "%s;", getUsername(lista->data));
        fprintf(newfile, "%d", getNCommits(lista->data));
        fprintf(newfile, "\n");
        lista = lista->next;
        N--;
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
    char *fields = strdup(line);
    char *temp ;
    for(int i=0; i<2; i++)
        temp = strsep(&fields, " ");

    char *data= strdup(temp);

    GList *llc = g_hash_table_get_values(lc->commit);

    LISTAREPOS r = initListaRepos();

    for(; llc != NULL; llc = llc->next){
        if (strcmp(getDateCommit(llc->data), data) > 0){
            int repo_id = getRepo(llc->data);
            REPOS repo = g_hash_table_lookup(lr->repos, repo_id); 

            if(!g_hash_table_lookup(r->repos, repo_id)){ 
                g_hash_table_insert(r->repos, repo_id, repo);

            }
        }     
    }

    GList *Repos = g_hash_table_get_values(lr->repos);

    for(; Repos != NULL; Repos = Repos->next){
        if(!g_hash_table_lookup(r->repos, getIDR(Repos->data))){
            fprintf(newfile, "%d;", getIDR(Repos->data));
            fprintf(newfile, "%s", getDescription(Repos->data));
            fprintf(newfile, "\n");
        }
    }
}


GCompareFunc comparaLang(NLang l1, NLang l2){
    if(l1->n_ocorr < l2->n_ocorr)
        return 1;
    if(l1->n_ocorr == l2->n_ocorr)
        return 0;
    else return -1;
}

GCompareFunc compara(int l1, int l2){
    if(l1 < l2)
        return 1;
    if(l1 == l2)
        return 0;
    else return -1;
}

void query8(char *line, LISTAREPOS lr, FILE *newfile){
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

    GList* listaRepos = g_hash_table_get_values(lr->repos);
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
    
    while(N>0){
        fprintf(newfile, "%s", ((NLang) (novaRepos->data))->lang);
        //fprintf(newfile, "%s", novaRepos->data);
        fprintf(newfile, "\n");
        novaRepos = novaRepos->next;
        N--;
    }
   
}

void query9(char* line, FILE *newfile, LISTACOMMITS lc, LISTAUSERS lu, LISTAREPOS lr){
    GList *listaCommits = g_hash_table_get_values(lc->commit);
    GList *c = listaCommits;

    for (; c != NULL; c = c->next){
        int author = getAuthor(c->data);
        int commiter = getCommiter(c->data);
        USER u = g_hash_table_lookup(lu->user, author);
        int repo = getRepo(c->data);
        REPOS r = g_hash_table_lookup(lr->repos, repo);
        int owner = getOwner(r);
        USER o = g_hash_table_lookup(lu->user, owner);
        if(exists(owner, u->friends, getNAmigos(u)))
            u->n_commits++; 
            
        if(author != commiter) {
            USER comit = g_hash_table_lookup(lu->user, commiter);
            if(exists(owner, comit->friends, getNAmigos(comit))) 
                comit->n_commits++;               
        }
    }

    GList *lusers = g_hash_table_get_values(lu->user);
    lusers = g_list_sort(lusers, comparaNCommits);

    char* arg = strdup(line);
    char* temp, *resto;
    for(int i=0; i<2; i++){
        temp = strsep(&arg, " ");
    }

    int N = strtol(temp, &resto, 10);

    while(N>0){
        fprintf(newfile, "%d;", getID(lusers->data));
        fprintf(newfile, "%s", getUsername(lusers->data));
        fprintf(newfile, "\n");
        lusers = lusers->next;
        N--;
    }

}


void initUsers(LISTAUSERS lu){
    GList *lista = g_hash_table_get_keys(lu->user);

    for(; lista != NULL; lista=lista->next){
        USER u = g_hash_table_lookup(lu->user, lista->data);
        u->n_commits = 0;
    }

}


GCompareFunc comparaMess(COMMIT m1, COMMIT m2){
    if(strlen(m1->message) < strlen(m2->message))
        return 1;
    if(strlen(m1->message) == strlen(m2->message))
        return 0;
    else return -1;
}


void query10(char* line, FILE *newfile, LISTACOMMITS lc, LISTAUSERS lu){

    GList *lista = g_hash_table_get_values(lc->commit);

    lista = g_list_sort(lista, comparaMess);

    char* arg = strdup(line);
    char* temp, *resto;
    for(int i=0; i<2; i++){
        temp = strsep(&arg, " ");
    }

    int N = strtol(temp, &resto, 10);

    while(N>0){
        int id = getCommiter(lista->data);
        USER u = g_hash_table_lookup(lu->user, id);
        fprintf(newfile, "%d;",id);
        fprintf(newfile, "%s;",getUsername(u));
        fprintf(newfile, "%d;",strlen(getMessage(lista->data)));
        fprintf(newfile, "%d\n",getRepo(lista->data));
        lista = lista->next;
        N--;
    }
}



void querie(char *line, LISTAUSERS lu, LISTAREPOS lr, LISTACOMMITS lc, FILE *newfile){
    char *fields = strdup(line);
    char *temp; 
    clock_t start=0,end=0;
    temp=(strsep(&fields, " "));
    char *resto;
    int q = strtol(temp, &resto, 10);

    switch (q){
        case 1:
            start = clock();
            query1(lu, newfile);
            end = clock();
            printf("query1 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            break;
        case 2:
            start = clock(); 
            query2(newfile, lc, lr);
            end = clock();
            printf("query2 = %f\n", (double)(end-start)/CLOCKS_PER_SEC); 
            break;
        case 3:
            start = clock();
            query3(lu, lc, newfile);
            end = clock();
            printf("query3 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            break;
        case 4:
            start = clock();
            query4(lu, lc, newfile);
            end = clock();
            printf("query4 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            break;
        case 5:
            start = clock();
            query5(line, newfile, lc, lu);
            end = clock();
            printf("query5 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            initUsers(lu);
            break;
        case 6: 
            start = clock();
            query6(line, newfile, lr, lc, lu);
            end = clock();
            printf("query6 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            initUsers(lu);
            break;
        case 7:
            start = clock();
            query7(line, newfile, lc, lr);
            end = clock();
            printf("query7 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            break;
        case 8:
            start = clock();
            query8(line, lr, newfile);
            end = clock();
            printf("query8 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            break;
        case 9:
            start = clock();
            query9(line, newfile, lc, lu, lr);
            end = clock();
            printf("query9 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            break;
        case 10:
            start = clock();
            query10(line, newfile, lc, lu);
            end = clock();
            printf("query10 = %f\n", (double)(end-start)/CLOCKS_PER_SEC);
            break;
        }

}


void parseQueries(char* ficheiro, LISTAUSERS lu, LISTAREPOS lr, LISTACOMMITS lc){
    FILE *f = fopen (ficheiro, "r+");;
    char* file = malloc(sizeof(char)*BUFF_SIZE);
    int i=1;

    while(fgets(file, BUFF_SIZE, f)){
        char *temp = strdup(file);
        char * line = strdup(strsep(&temp, "\n"));
        char* filename = malloc(100);
        sprintf(filename, "saida/commands%d_output.txt", i);
        FILE *newfile = fopen(filename, "w+");
        querie(line, lu, lr, lc, newfile);    
        i++;   
        fclose(newfile);
    }

    
    fclose(f);
}

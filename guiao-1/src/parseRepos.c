#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../libs/parseRepos.h"



#define BUFF_SIZE 100000

int linhaValidaRepos(char *line){
    char *fields = strdup(line);
    char *temp; 
    int i=0, r=1;
    for(i=0; (temp=(strsep(&fields, ";"))) != NULL && i<14; i++){
        if(strcmp(temp,"") == 0){ i=14; r=0;}
        switch (i){
            case 0:
                r = isInt(temp); 
                if (r==0) i=14;
                break;
            case 1: 
                r = isInt(temp); 
                if (r==0) i=14;
                break;
            case 4:
                if((strcmp(temp, "True")!=0) && (strcmp(temp, "False")!=0)) {r=0; i=10;}
                break;
            case 8:
                r = verificarData(temp);
                if (r==0) i=14;
                break;
            case 9:
                r = verificarData(temp);
                if (r==0) i=14;
                break;    
            case 10: 
                r = isInt(temp); 
                if (r==0) i=14;
                break;
            case 11: 
                r = isInt(temp); 
                if (r==0) i=14;
                break;
            case 12: 
                r = isInt(temp); 
                if (r==0) i=14;
                break;
            case 13: 
                r = isInt(temp); 
                if (r==0) i=14;
                break;
        }
    }
    
    return r;
}



void parseRepos(){
    FILE *f = fopen ("entrada/repos.csv", "r+");;
    char* file = malloc(sizeof(char)*BUFF_SIZE);
    
    int i=0;
    FILE *newfile = fopen("saida/repos-ok.csv", "w+");

    while(fgets(file, BUFF_SIZE, f)){
        char *temp = strdup(file);
        char * line = strdup((strsep(&temp, "\n")));
        if(i==0) fprintf(newfile, line);
        else if(linhaValidaRepos(line)){ 
            line = aspas(line);
            fprintf(newfile, line);
        }
        i++;
    }

    fclose(newfile);
    fclose(f);
}

int adicionarR(char *line, LISTAREPOS lr, LISTAUSERS u){
    char *fields = strdup(line);
    char *temp, *resto; 
    int id, owner_id, r=1;
    for(int i=0; (temp=(strsep(&fields, ";"))) != NULL && i<2; i++){
        switch (i){
            case 0:
                id = strtol(temp,&resto,10);
                break;
            case 1: 
                owner_id = strtol(temp,&resto,10);
                break;
            }
    }
    REPOS repos = initRepos(id, owner_id);
    if(g_hash_table_lookup(lr->repos, id) == NULL && g_hash_table_lookup(u->user, owner_id)){
        addRepos(lr,repos);
    }else r=0;

    return r;

}

void adicionarRepos(LISTAUSERS u, LISTAREPOS l){
    FILE *f = fopen ("saida/repos-ok.csv", "r+");;
    char* file = malloc(sizeof(char)*BUFF_SIZE);
    int i=0;
    FILE *newfile = fopen("saida/repos-final.csv", "w+");

    while(fgets(file, BUFF_SIZE, f)){
        char *temp = strdup(file);
        char *line = strdup((strsep(&temp, "\n")));
        if(i==0) fprintf(newfile, line);
        else if(adicionarR(line, l, u)) fprintf(newfile, line);

        
        i++;
    }

    fclose(newfile);
    fclose(f);
}

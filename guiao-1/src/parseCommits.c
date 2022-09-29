#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <glib.h>
#include "../libs/parseCommits.h"

#define BUFF_SIZE 10000

int linhaValidaCommits(char *line){
    char *fields = strdup(line);
    char *temp; 
    int i=0, r=1;
    for(i=0; (temp=(strsep(&fields, ";"))) != NULL && i<4; i++){
         if(strcmp(temp,"") == 0){ i=4; r=0;}
        switch (i){
            case 0:
                r = isInt(temp); 
                if (r==0) i=4;
                break;
            case 1: 
                r = isInt(temp); 
                if (r==0) i=4;
                break;
            case 2:
                r = isInt(temp); 
                if (r==0) i=4;
                break;
            case 3:
                r = verificarData(temp);
                break;
        }
    }
    
    return r;
}



void parseCommits(){
    FILE *f = fopen ("entrada/commits.csv", "r+");;
    char* file = malloc(sizeof(char)*BUFF_SIZE);
    
    int i=0;
    FILE *newfile = fopen("saida/commits-ok.csv", "w+");

    while(fgets(file, BUFF_SIZE, f)){
        char *temp = strdup(file);
        char * line = strdup((strsep(&temp, "\n")));
        if(i==0) fprintf(newfile, line);
        else if(linhaValidaCommits(line)){ 
            line = aspas(line);
            fprintf(newfile, line);
        }
        i++;
    }

    fclose(newfile);
    fclose(f);
}



int adicionarC(char *line, LISTAREPOS lr, LISTAUSERS u){
    char *fields = strdup(line);
    char *temp, *resto; 
    int repo_id, author_id, committer_id, r=1;

    for(int i=0; (temp=(strsep(&fields, ";"))) != NULL && i<3; i++){
        switch (i){
            case 0:
                repo_id = strtol(temp,&resto,10);
                break;
            case 1: 
                author_id = strtol(temp,&resto,10);
                break;
            case 2:
                committer_id = strtol(temp,&resto,10);
                break;
            }
    }
    
    if(g_hash_table_lookup(lr->repos, repo_id) && g_hash_table_lookup(u->user, author_id) && g_hash_table_lookup(u->user, committer_id)){
       
    }else r=0;

    return r;

}

void adicionarCommits(LISTAUSERS u, LISTAREPOS r){
    FILE *f = fopen ("saida/commits-ok.csv", "r+");
    char* file = malloc(sizeof(char)*BUFF_SIZE);
    int i=0;
    FILE *newfile = fopen("saida/commits-final.csv", "w+");

    while(fgets(file, BUFF_SIZE, f)){
        char *temp = strdup(file);
        char *line = strdup((strsep(&temp, "\n")));
        if(i==0) fprintf(newfile, line);
        else if(adicionarC(line, r, u)) fprintf(newfile, line);

        
        i++;
    }

    fclose(newfile);
    fclose(f);
}

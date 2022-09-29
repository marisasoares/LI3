#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <glib.h>
#include "../libs/parseUsers.h"


#define BUFF_SIZE 5000

int linhaValida(char *line){
    char *fields = strdup(line);
    char *temp; 
    int i=0, r=1, followers, following;
    for(i=0; (temp=(strsep(&fields, ";"))) != NULL && i<10; i++){
        if(strcmp(temp,"") == 0){ i=10; r=0;}
        switch (i){
            case 0:
                r = isInt(temp); 
                if (r==0) i=10;
                break;
            case 2: 
                if((strcmp(temp, "User")!=0) && (strcmp(temp, "Organization")!=0) && (strcmp(temp, "Bot")!=0)) {r=0; i=10;}
                break;
            case 3:
                r = verificarData(temp);
                if (r==0) i=10;
                break;
            case 4:
                r = isInt(temp);
                if (r) followers=getFollow(temp);
                else i=10;
                break;
            case 5:
                r = validaLista(temp, followers);
                if (r==0) i=10;
                break;
            case 6:
                r = isInt(temp);
                if (r) following=getFollow(temp);
                else i=10;
                break;
            case 7:
                r = validaLista(temp, following);
                if (r==0) i=10;
                break;
            case 8:
                r = isInt(temp);
                if (r==0) i=10;
                break;
            case 9:
                r = isInt(temp);
                break;
        }
    }
    return r;
}

void parseUsers(){
    FILE *f = fopen ("entrada/users.csv", "r+");;
    char* file = malloc(sizeof(char)*BUFF_SIZE);
    
    int i=0;
    FILE *newfile = fopen("saida/users-ok.csv", "w+");

    while(fgets(file, BUFF_SIZE, f)){
        char *temp = strdup(file);
        char * line = strdup((strsep(&temp, "\n")));
        if(i==0) fprintf(newfile, line);
        else if(linhaValida(line)){ fprintf(newfile, line);
        }
        
        i++;
    }

    fclose(newfile);
    fclose(f);
}

int adicionarU(char *line, LISTAUSERS l){
    char *fields = strdup(line);
    char *temp, *resto; 
    int id, r=1;
    char *username;
    for(int i=0; (temp=(strsep(&fields, ";"))) != NULL && i<2; i++){
        switch (i){
            case 0:
                id = strtol(temp,&resto,10);
                break;
            case 1: 
                username = strdup(temp);
                break;
            }
    }
    USER u = initUser(id, username);
    if(g_hash_table_lookup(l->user, id) == NULL) addUser(l,u);
    else r=0;
    return r;
}

void adicionarUsers(LISTAUSERS l){
    FILE *f = fopen ("saida/users-ok.csv", "r+");;
    char* file = malloc(sizeof(char)*BUFF_SIZE);
    int i=0;
    FILE *newfile = fopen("saida/users-final.csv", "w+");

    while(fgets(file, BUFF_SIZE, f)){
        char *temp = strdup(file);
        char *line = strdup((strsep(&temp, "\n")));
        if(i==0) fprintf(newfile, line);
        else if (adicionarU(line, l)) fprintf(newfile, line);
    
        i++;
    }

    fclose(newfile);
    fclose(f);
}

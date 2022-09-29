#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <glib.h>
#include "../libs/parseUsers.h"


#define BUFF_SIZE 200000

void getFriendsList(int followers[], int fsize, int following[], int fsize2, USER u){
    for(int i=0, f=0; i<fsize; i++){
        if(exists(followers[i], following, fsize2)) {
            u->friends[u->n_amigos++] = followers[i]; 
            f++;
        }
    }
} 


int adicionarU(char *line, LISTAUSERS l){
    char *fields = strdup(line);
    char *temp, *resto; 
    int id, r=1;
    char *username, *type;
    int followers =0, following=0;
    int followers_list[100000];
    int following_list[100000];
    for(int i=0; (temp=(strsep(&fields, ";"))) != NULL && i<8; i++){
        switch (i){
            case 0:
                id = strtol(temp,&resto,10);
                break;
            case 1: 
                username = strdup(temp);
                break;
            case 2:
                type = strdup(temp);
                break;
            case 4:
                followers = strtol(temp, &resto, 10);
                break;
            case 5:
                getFollowList(temp, followers_list);
                break;
            case 6:
                following = strtol(temp, &resto, 10);
                break;
            case 7:
                getFollowList(temp, following_list);
                break;
            }
    }
    
    USER u = initUser(id, username, type);
    getFriendsList(followers_list, followers, following_list, following, u);
    
    if(g_hash_table_lookup(l->user, id) == NULL) addUser(l,u);
    else r=0;
    return r;
} 

void adicionarUsers(LISTAUSERS l){
    FILE *f = fopen ("entrada/users-g2.csv", "r+");
    char* file = malloc(sizeof(char)*BUFF_SIZE);
    

    while(fgets(file, BUFF_SIZE, f)){
        char *temp = strdup(file);
        char *line = strdup((strsep(&temp, "\n")));
        adicionarU(line, l);
    
    }

   
}

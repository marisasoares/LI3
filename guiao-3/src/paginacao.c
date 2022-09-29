#include "../libs/paginacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void check_scanf(int error) {
  if (error == EOF) {
    perror("failed to read user input");
    exit(1);
  }
}

void paginacao(GList *lista, int N, int q, GHashTable *l2){
    int linhasmax = 24;  //standard value for lines in terminal
    int l = 0;
    char keypressed[1];
    int page, atual = 1;
    int M = N;
    
    double total =  ceil( (double) N/24);
    

    N = toPage(lista,l, linhasmax, N, q, l2);
    menu_page(atual,total);
    printf("N = %d\n",N);

    check_scanf(scanf("%s",keypressed));
    while(strcmp(keypressed,"e") != 0){ // e - exit
        if(strcmp(keypressed,"p") == 0){ // p - proxima
            l += linhasmax;
            linhasmax += linhasmax;
            toPage(lista,l,linhasmax, N, q, l2);
            atual++;
            N = M - (atual*24);
            menu_page(atual,total);
            printf("N = %d\n",N);
        }
        else if(strcmp(keypressed,"a") == 0){ // a - anterior
            l = l - 24;
            linhasmax = linhasmax - 24;
            toPage(lista,l,linhasmax, N, q, l2);
            atual--;
            N = M - (atual*24);
            menu_page(atual,total);
            printf("N = %d\n",N);
        } 
        else if(strcmp(keypressed,"s") == 0){// s - saltar 
            check_scanf(scanf("%d",&page));
            l = (page-1) * 24;
            linhasmax = ((page-1) * 24) + 24;
            N = M - l;
            toPage(lista, l, linhasmax, N, q, l2);
            atual = page;
            menu_page(atual,total);
        }
        check_scanf(scanf("%s",keypressed));
    }
}

int toPage(GList *lista, int linhas_init, int linhas_end, int N, int q, GHashTable *table){


    if(q == 5 || q == 6){
        header_5();
        for(int j = linhas_init; j < linhas_end && N>0; j++){
            printf("%d |", getID(g_list_nth_data(lista, j)));
            printf("%s |", getUsername(g_list_nth_data(lista, j)));
            printf("%d\n", getNCommits(g_list_nth_data(lista, j)));
            N--;
        }

    }

    if(q == 7){
        header_7();
        for(int j = linhas_init; j < linhas_end; j++){
            if(!g_hash_table_lookup(table, getIDR(g_list_nth_data(lista, j)))){
                printf( "%d |", getIDR(g_list_nth_data(lista, j)));
                printf( "%s\n", getDescription(g_list_nth_data(lista, j)));
                N--;
            }
        }
    }

    if(q == 8){
        header_8();
        for(int j = linhas_init; j < linhas_end && N>0; j++){
            printf("%s", (g_list_nth_data(lista, j)));
            printf("\n");
            N--;
        }
    }

    if(q == 9){
        header_9();
        for(int j = linhas_init; j < linhas_end && N>0; j++){
            printf("%d |", getID(g_list_nth_data(lista, j)));
            printf("%s\n", getUsername(g_list_nth_data(lista, j)));
            N--;
        }

    }

    if(q == 10){
        header_10();
        for(int j = linhas_init; j < linhas_end && N>0; j++){
            int id = getCommiter(g_list_nth_data(lista, j));
            USER u = g_hash_table_lookup(table, id);
            printf("%d |",id);
            printf("%s |",getUsername(u));
            printf("%d |",getMessage(g_list_nth_data(lista, j)));
            printf("%d\n",getRepo(g_list_nth_data(lista, j)));
            N--;
        }

    }
   
    return N;
    
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../libs/parsing.h"


int verificarDataAux(int ano, int mes, int dia, int h, int m, int s){
    int r=1;
   
    if(ano>=2005 && ano<=2021){
        if(mes>=1 && mes<=12){
            if(dia<7 && mes<=4 && ano<=2005)
                r=0;
            else if(dia>7 && mes>=11 && ano>=2021) 
                r=0;
            else if((dia>=1 && dia<=31) && (mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12))
                r=1;
            else if((dia>=1 && dia<=30) && (mes==4 || mes==6 || mes==9 || mes==11))
                r=1;
            else if((dia>=1 && dia<=28) && (mes==2))
                r=1;
            else if(dia==29 && mes==2 && (ano%400==0 ||(ano%4==0 && ano%100!=0)))
                r=1;
            else r=0;      
        }
        else r=0;
    }
    else r=0;
    
    if(h<0 || h>23) r=0;
    if(m>59 || m<0) r=0;
    if(s>59 || s<0) r=0;

    return r;

}

int verificarData(char *fields){
    char * data = strdup(fields);
    char *resto;
    char num[4];
    int i=0, n=0, c=0, ano, mes, dia, h, m, s;

    if(strstr(data, "-") == NULL || strstr(data, ":") == NULL)
        return 0;
    else if(strlen(data) >20) return 0;

    for(i=0; data[i] != '\0'; i++){
        if(data[i] == '-' || data[i] == ' ' || data[i] == ':'){ 
            switch (c){
                case 0:
                    ano = strtol(num,&resto,10);
                    break;
                case 1:
                    mes = strtol(num,&resto,10);
                    break;
                case 2:
                    dia = strtol(num,&resto,10);
                    break;
                case 3:
                    h = strtol(num,&resto,10);
                    break;
                case 4:
                    m = strtol(num,&resto,10);
                    break;
            }
            memset(num,'\0', 4);
            n=0;
            c++;
        }
        else if(!isdigit(data[i])) return 0;
        else {
            num[n] = data[i];
            n++;
        }
 
    }
    s = strtol(num,&resto,10);
                    
    return verificarDataAux(ano,mes,dia,h,m,s);
}


int isNumber(char *string){
    
    int r=0;
    for(int i=0; string[i] != '\0'; i++){
        if(isdigit(string[i])) r=1;
        else break;
    }
    return r;
}

int isInt(char* fields){
    char* string = strdup(fields);
    char* left;
    int r=0;
    
    if(isNumber(string)){
        int num=strtod(string, &left);
       
        if(num%1 == 0 && num>=0) r=1;
    }

    return r;
}

int getFollow(char* string){
    char *resto;
    return strtol(string,&resto,10);
}

int validaLista(char* fields, int f){
    char *lista = strdup(fields);
    char num[10];
    int r=1, c=0, cont=0;
    if(strlen(fields) == 2 && strstr(fields, "[") && strstr(fields, "]")) r=1;
    else if (strlen(fields) > 2 && strstr(fields, "[") && strstr(fields, "]")) {
        for(int i=1; lista[i] != '\0' && lista[i] != ']'; i++){
            if(lista[i] != ',' || lista[i] != ' '){
                num[c] = lista[i];
            }
            else{
                if(!isInt(num)) return 0;
                memset(num,'\0', 10);
                c=0;
                cont++;
            }
        }
    }else r=0;
    if(cont != f) r=0;
    return r;
}

char *aspas(char *line){
    for(int i=0; line[i] != '\0'; i++){
        if(line[i] == '"'){
            line[i] = '\"';
        }
        if(line[i] == '%') line[i] = ' ';
    }
   
    return line;
}

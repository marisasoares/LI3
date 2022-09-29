#include "parsing.h"
#include <time.h>
#include "sg.h"
#include "paginacao.h"
#include "parseUsers.h"

void query1(LISTAUSERS lu, FILE *newfile);

void query2(FILE *newfile, LISTACOMMITS lc, LISTAREPOS lr);

void query3(LISTAUSERS lu, LISTACOMMITS lc, FILE *newfile);

void query4(LISTAUSERS lu, LISTACOMMITS lc, FILE *newfile);

void acrescentaN_commits(LISTAUSERS lu, LISTACOMMITS lc, char *dataI, char *dataF);

GCompareFunc comparaNCommits(USER u1, USER u2);

void query5(char* line, FILE *newfile, LISTACOMMITS lc, LISTAUSERS lu);

void procuraLinguagem(LISTAREPOS lr, LISTACOMMITS lc, LISTAUSERS lu, char* linguagem);

void query6(char* line, FILE *newfile, LISTAREPOS lr, LISTACOMMITS lc, LISTAUSERS lu);

int existeCommit(GList *Commits, int id);

void query7(char* line, FILE *newfile, LISTACOMMITS lc, LISTAREPOS lr);

typedef struct query8{
    char* lang;
    int n_ocorr;
} *NLang;

GCompareFunc comparaLang(NLang l1, NLang l2);

void query8(char *line, LISTAREPOS lr, FILE *newfile);

void query9(char* line, FILE *newfile, LISTACOMMITS lc, LISTAUSERS lu, LISTAREPOS lr);

void initUsers(LISTAUSERS lu);

int comparaMess(COMMIT m1, COMMIT m2);


void query10(char* line, FILE *newfile, LISTACOMMITS lc, LISTAUSERS lu);


void querie(char *line, SGC sgc, FILE *newfile);


void parseQueries(char* ficheiro, SGC sgc);

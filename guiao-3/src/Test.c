#include "../libs/Test.h"

#define BUFF_SIZE 5000

int main(){

	SGC sgc = load_sgc();

	parseTestes(sgc);
	free_sgc(sgc);
	return 0;
}

int compareFile(FILE *file1, FILE *file2){
   char ch1 = getc(file1);
   char ch2 = getc(file2);
   int error = 0;
   while (ch1 != EOF && ch2 != EOF){
      if (ch1 != ch2){
         error++;
      }
      ch1 = getc(file1);
      ch2 = getc(file2);
   }
   return error;
}

void teste(int time, int f,int i){
	if (time <= 5 && f == 0) printf("Na query %d - Teste válido\n", i);
	if (time > 5 && f == 0) printf("Na query %d - Testes corretos, mas excedeu o tempo\n", i);
	if (time <= 5 && f != 0) printf("Na query %d - Tempo válido, mas testes incorretos\n", i);
	if (time > 5 && f != 0) printf("Na query %d - Teste inválido\n", i);
}

void test_query1(LISTAUSERS lu, FILE *newfile, char* filename){
	FILE* expected_file;
	FILE* file; 

	clock_t start = clock();
	query1(lu,newfile);
	clock_t end = clock();
	double time = ((double)(end - start) / CLOCKS_PER_SEC);

	//comparação de ficheiros 

	file = fopen(filename,"r+");
	expected_file = fopen("entrada/expected_file1.txt", "r+");
 	/* fopen() return NULL if unable to open file in given mode. */
    	if (file == NULL || expected_file == NULL){
        	printf("\nUnable to open file.\n");
        	exit(EXIT_FAILURE);
    	}
	int f = compareFile(file,expected_file);
	teste(time,f,1);
}

void test_query2(FILE *newfile, LISTACOMMITS lc, LISTAREPOS lr, char* filename){
	FILE* expected_file;
	FILE* file; 
	
	clock_t start = clock();
	query2(newfile,lc, lr);
	clock_t end = clock();
	double time = ((double)(end - start) / CLOCKS_PER_SEC);

	//comparação de ficheiros 

	file = fopen(filename,"r+");
	expected_file = fopen("entrada/expected_file2.txt", "r+");
 	/* fopen() return NULL if unable to open file in given mode. */
    	if (file == NULL || expected_file == NULL){
        	printf("\nUnable to open file.\n");
        	exit(EXIT_FAILURE);
    	}
	int f = compareFile(file,expected_file);
	teste(time,f,2);
}

void test_query3(LISTAUSERS lu, LISTACOMMITS lc, FILE *newfile, char* filename){
	FILE* expected_file;
	FILE* file; 

	clock_t start = clock();
	query3(lu, lc, newfile);
	clock_t end = clock();
	double time = ((double)(end - start) / CLOCKS_PER_SEC);

	//comparação de ficheiros 

	file = fopen(filename,"r+");
	expected_file = fopen("entrada/expected_file3.txt", "r+");
 	/* fopen() return NULL if unable to open file in given mode. */
    	if (file == NULL || expected_file == NULL){
        	printf("\nUnable to open file.\n");
        	exit(EXIT_FAILURE);
    	}
	int f = compareFile(file,expected_file);
	teste(time,f,3);
}

void test_query4(LISTAUSERS lu, LISTACOMMITS lc, FILE *newfile, char* filename){
	FILE* expected_file;
	FILE* file; 
	
	clock_t start = clock();
	query4(lu, lc, newfile);
	clock_t end = clock();
	double time = ((double)(end - start) / CLOCKS_PER_SEC);

	//comparação de ficheiros 

	file = fopen(filename,"r+");
	expected_file = fopen("entrada/expected_file4.txt", "r+");
 	/* fopen() return NULL if unable to open file in given mode. */
    	if (file == NULL || expected_file == NULL){
        	printf("\nUnable to open file.\n");
        	exit(EXIT_FAILURE);
    	}
	int f = compareFile(file,expected_file);
	teste(time,f,4);
}

void test_query5(char* line, FILE *newfile, LISTACOMMITS lc, LISTAUSERS lu, char* filename){
	FILE* expected_file;
	FILE* file; 

	clock_t start = clock();
	query5(line, newfile, lc, lu);
	clock_t end = clock();
	double time = ((double)(end - start) / CLOCKS_PER_SEC);

	//comparação de ficheiros 

	file = fopen(filename,"r+");
	expected_file = fopen("entrada/expected_file5.txt", "r+");
 	/* fopen() return NULL if unable to open file in given mode. */
    	if (file == NULL || expected_file == NULL){
        	printf("\nUnable to open file.\n");
        	exit(EXIT_FAILURE);
    	}
	int f = compareFile(file,expected_file);
	teste(time,f,5);
}

void test_query6(char *line, FILE* newfile, LISTAREPOS lr, LISTACOMMITS lc, LISTAUSERS lu, char* filename){
	FILE* expected_file;
	FILE* file; 
	
	clock_t start = clock();
	query6(line, newfile, lr, lc, lu);
	clock_t end = clock();
	double time = ((double)(end - start) / CLOCKS_PER_SEC);

	//comparação de ficheiros 

	file = fopen(filename,"r+");
	expected_file = fopen("entrada/expected_file6.txt", "r+");
 	/* fopen() return NULL if unable to open file in given mode. */
    	if (file == NULL || expected_file == NULL){
        	printf("\nUnable to open file.\n");
        	exit(EXIT_FAILURE);
    	}
	int f = compareFile(file,expected_file);
	teste(time,f,6);
}

void test_query7(char* line, FILE *newfile, LISTACOMMITS lc, LISTAREPOS lr, char* filename){
	FILE* expected_file;
	FILE* file; 

	clock_t start = clock();
	query7(line, newfile, lc, lr);
	clock_t end = clock();
	double time = ((double)(end - start) / CLOCKS_PER_SEC);

	//comparação de ficheiros 

	file = fopen(filename,"r+");
	expected_file = fopen("entrada/expected_file7.txt", "r+");
 	/* fopen() return NULL if unable to open file in given mode. */
    	if (file == NULL || expected_file == NULL){
        	printf("\nUnable to open file.\n");
        	exit(EXIT_FAILURE);
    	}
	int f = compareFile(file,expected_file);
	teste(time,f,7);
}

void test_query8(char *line, LISTAREPOS lr, FILE *newfile, char *filename){
	FILE* expected_file;
	FILE* file; 
	
	clock_t start = clock();
	query8(line, lr, newfile);
	clock_t end = clock();
	double time = ((double)(end - start) / CLOCKS_PER_SEC);

	//comparação de ficheiros 

	file = fopen(filename,"r+");
	expected_file = fopen("entrada/expected_file8.txt", "r+");
 	/* fopen() return NULL if unable to open file in given mode. */
    	if (file == NULL || expected_file == NULL){
        	printf("\nUnable to open file.\n");
        	exit(EXIT_FAILURE);
    	}
	int f = compareFile(file,expected_file);
	teste(time,f,8);
}

void test_query9(char* line, FILE *newfile, LISTACOMMITS lc, LISTAUSERS lu, LISTAREPOS lr, char* filename){
	FILE* expected_file;
	FILE* file; 

	clock_t start = clock();
	query9(line, newfile, lc, lu, lr);
	clock_t end = clock();
	double time = ((double)(end - start) / CLOCKS_PER_SEC);

	//comparação de ficheiros 

	file = fopen(filename,"r+");
	expected_file = fopen("entrada/expected_file9.txt", "r+");
 	/* fopen() return NULL if unable to open file in given mode. */
    	if (file == NULL || expected_file == NULL){
        	printf("\nUnable to open file.\n");
        	exit(EXIT_FAILURE);
    	}
	int f = compareFile(file,expected_file);
	teste(time,f,9);
}

void test_query10(char* line, FILE *newfile, LISTACOMMITS lc, LISTAUSERS lu, char *filename){
	FILE* expected_file;
	FILE* file; 
	
	clock_t start = clock();
	query10(line, newfile, lc, lu);
	clock_t end = clock();
	double time = ((double)(end - start) / CLOCKS_PER_SEC);

	//comparação de ficheiros 

	file = fopen(filename,"r+");
	expected_file = fopen("entrada/expected_file10.txt", "r+");
 	/* fopen() return NULL if unable to open file in given mode. */
    	if (file == NULL || expected_file == NULL){
        	printf("\nUnable to open file.\n");
        	exit(EXIT_FAILURE);
    	}
	int f = compareFile(file,expected_file);
	teste(time,f,10);
}

void querie_teste(char *line, SGC sgc, FILE *newfile, char *filename){
    char *fields = strdup(line);
    char *temp; 
    clock_t start=0,end=0;
    temp=(strsep(&fields, " "));
    char *resto;
    int q = strtol(temp, &resto, 10);

    switch (q){
        case 1:
            test_query1(getLUsers(sgc), newfile, filename);
            break;
        case 2: 
            test_query2(newfile, getLCommits(sgc), getLRepos(sgc), filename);
            break;
        case 3:
            test_query3(getLUsers(sgc), getLCommits(sgc), newfile, filename);
            break;
        case 4:
            test_query4(getLUsers(sgc), getLCommits(sgc), newfile, filename);
            break;
        case 5:
            test_query5(line, newfile, getLCommits(sgc), getLUsers(sgc), filename);
            initUsers(getLUsers(sgc));
            break;
        case 6: 
            test_query6(line, newfile, getLRepos(sgc), getLCommits(sgc), getLUsers(sgc), filename);
            initUsers(getLUsers(sgc));
            break;
        case 7:
            test_query7(line, newfile, getLCommits(sgc), getLRepos(sgc), filename);
            break;
        case 8:
            //test_query8(line, getLRepos(sgc), newfile, filename);
            break;
        case 9:
            test_query9(line, newfile, getLCommits(sgc), getLUsers(sgc), getLRepos(sgc), filename);
            break;
        case 10:
            test_query10(line, newfile, getLCommits(sgc), getLUsers(sgc), filename);   
            break;
        }

}


void parseTestes(SGC sgc){
    FILE *f = fopen ("entrada/test_commands.txt", "r+");
    char* file = malloc(sizeof(char)*BUFF_SIZE);
    int i=1;

    while(fgets(file, BUFF_SIZE, f)){
        char *temp = strdup(file);
        char * line = strdup(strsep(&temp, "\n"));
        char* filename = malloc(100);
        sprintf(filename, "saida/commands%d_output.txt", i);
        FILE *newfile = fopen(filename, "w+");
        querie_teste(line, sgc, newfile, filename);    
        i++;   
        fclose(newfile);
    }

    //free(file);
	//free(filename);
    fclose(f);
}

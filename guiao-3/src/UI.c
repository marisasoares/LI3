#include "../libs/UI.h"

void menu(){ 

	printf("\n\n |-----------------------------------------------------------------------------|");
	printf("\n | 1 - Quantidade de bots, organizacoes e utilizadores.                        |");
	printf("\n |-----------------------------------------------------------------------------|");
	printf("\n | 2 - Numero medio de colaboradores por repo.                                 |");
	printf("\n |-----------------------------------------------------------------------------|");
	printf("\n | 3 - Quantidade de repositorios com bots                                     |");
	printf("\n | ----------------------------------------------------------------------------|");
	printf("\n | 4 - Quantidade media de commits por user                                    |");
	printf("\n | ----------------------------------------------------------------------------|");
	printf("\n | 5 - Top N de users mais ativos num intervalo de datas                       |");
	printf("\n | ----------------------------------------------------------------------------|");
	printf("\n | 6 - Top N de utilizadores com mais commits em repositorios de uma linguagem |");
	printf("\n | ----------------------------------------------------------------------------|");
	printf("\n | 7 - Quais os repositorios inativos a partir de uma determinada data         |");
	printf("\n | ----------------------------------------------------------------------------|");
	printf("\n | 8 - top N de linguagens mais utilizadas a partir de uma determinada data    |");
	printf("\n | ----------------------------------------------------------------------------|");
	printf("\n | 9 - top N de users com mais commits em repositorios cujo owner e um amigo   |");
	printf("\n | ----------------------------------------------------------------------------|");
	printf("\n | 10 - top N de users com as maiores mensagens de commit por repositorio      |");
	printf("\n | ----------------------------------------------------------------------------|");
	printf("\n | 0 - Fechar Programa                                                         |");
	printf("\n | ----------------------------------------------------------------------------|");
	printf("\n\n Escolha uma opcao: ");
}

void menu_page(int atual,double total){
	printf("          Pagina %d de %d\n", atual, (int) total);
	printf("  p -> proxima pagina\n");
	printf("  a -> pagina anterior\n");
	printf("  s -> saltar para pagina\n");
}

void header_5(){
	char* id = "ID";
	char* login = "Login";
	char* comited = "Commit_qtty1";
	char* bar = "|";
	printf("%s%5s%5s%5s%5s%5s\n",bar,id,bar,login,bar,comited);
}

void header_7(){
	char* repo = "Repo";
	char* desc = "Descricao";
	char* bar = "|";
	printf("%s%5s%5s%5s\n",bar,repo,bar,desc);
}
void header_8(){
	char* lang = "Lang";
	printf("%s\n",lang);
}

void header_9(){
	char* id = "ID";
	char* login = "Login";
	char* bar = "|";
	printf("%s%5s%5s%5s\n",bar,id,bar,login);
}

void header_10(){
	char* id = "ID";
	char* login = "Login";
	char* comited = "Commit_msg_size";
	char* repo = "Repo_id";
	char* bar = "|";
	printf("%s%5s%5s%5s%5s%5s%5s%5s\n",bar,id,bar,login,bar,comited,bar,repo);
}
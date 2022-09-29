#include "../libs/Controller.h"

void controller(char* arg, SGC sgc){
	if (strcmp(arg, "entrada/commands.txt") == 0){
		parseQueries(arg, sgc); // parseQueries(argv[1], lu, lr, lc); meter lu,lr,lc em sg
	}else{
		interpretador(sgc);
	}
	
}


void interpretador (SGC sgc){
	
	int opt;
	char* line =malloc(50);
	char N[4], d_ini[10], d_fim[10], lang[20];
	
	menu();
	check_scanf(scanf("%d",&opt));
	while(opt != 0){
		switch(opt){
			case 1 : 
				query1(getLUsers(sgc), NULL);
		 		break;
			case 2 : 
				query2(NULL,getLCommits(sgc), getLRepos(sgc));
		 		break;
			case 3 : 
				query3(getLUsers(sgc), getLCommits(sgc), NULL);
		 		break;
			case 4 : 
				query4(getLUsers(sgc), getLCommits(sgc), NULL);
		 		break;
			case 5 :
				strcat(line, "5");
				strcat(line, " "); 
				printf ("Qual o total desejado de users? \n");
				check_scanf(scanf("%s", N));
				strcat(line, N);
				strcat(line, " ");
				printf ("Qual a data inicial (YYYY-MM-DD)? \n");
				check_scanf(scanf("%s", d_ini));
				strcat(line, d_ini);
				strcat(line, " ");
				printf ("Qual a data final (YYYY-MM-DD)? \n");
				check_scanf(scanf("%s", d_fim));
				strcat(line, d_fim);
				query5(line, NULL, getLCommits(sgc), getLUsers(sgc));
				
		 		break;
			case 6 :
				strcat(line, "6");
				strcat(line, " "); 
				printf ("Qual o total desejado de users? \n");
				check_scanf(scanf("%s", N));
				strcat(line, N);
				strcat(line, " ");
				printf ("Qual a linguagem? \n");
				check_scanf(scanf("%s", lang));
				strcat(line, lang);
				query6(line, NULL, getLRepos(sgc), getLCommits(sgc), getLUsers(sgc));
		 		break;
			case 7 :
				strcat(line, "7");
				strcat(line, " ");  
				printf ("Qual a data (YYYY-MM-DD)? \n");
				check_scanf(scanf("%s", d_ini));
				strcat(line, d_ini);
				query7(line, NULL, getLCommits(sgc), getLRepos(sgc));
		 		break;
			case 8 :
				strcat(line, "8");
				strcat(line, " ");  
				printf ("Qual o total desejado de linguagens? \n");
				check_scanf(scanf("%s", N));
				strcat(line, N);
				strcat(line, " ");
				printf ("Qual a data inicial (YYYY-MM-DD)? \n");
				check_scanf(scanf("%s", d_ini));	
				strcat(line, d_ini);
				query8(line, getLRepos(sgc), NULL);
		 		break;
			case 9 :
				strcat(line, "9");
				strcat(line, " "); 
				printf ("Qual o total desejado de users? \n");
				check_scanf(scanf("%s", N));
				strcat(line, N);
				query9(line, NULL, getLCommits(sgc), getLUsers(sgc), getLRepos(sgc));
		 		break;
			case 10 :
				strcat(line, "10");
				strcat(line, " "); 
				printf ("Qual o total desejado de users? \n");
				check_scanf(scanf("%s", N));
				strcat(line, N);
				query10(line, NULL, getLCommits(sgc), getLUsers(sgc));
		 		break;
			case 0: 
				printf("\nExiting...\n");
				exit(0);
				break;
			default: 
				printf("\nInvalid Option\n");
				break;
		}
		menu();
		check_scanf(scanf("%d",&opt));
		line[0] = '\0';
	}

}
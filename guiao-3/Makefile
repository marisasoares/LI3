FLAGS= -std=c99 -O2 -D_GNU_SOURCE -ggdb3  
PKG = `pkg-config --cflags --libs glib-2.0` `pkg-config --libs glib-2.0`
COMPILER=gcc
HEADERS=libs
SRC=src
OBJ=obj

all: main parseUsers parseCommits parseRepos catalogoUsers catalogoRepos catalogoCommits parsing queries sg UI Controller paginacao Test guiao-3 test

main: $(SRC)/main.c $(HEADERS)/main.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/main.o $(PKG) -c $(SRC)/main.c

parseUsers: $(SRC)/parseUsers.c $(HEADERS)/parseUsers.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/parseUsers.o $(PKG) -c $(SRC)/parseUsers.c

parseCommits: $(SRC)/parseCommits.c $(HEADERS)/parseCommits.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/parseCommits.o $(PKG) -c $(SRC)/parseCommits.c

parseRepos: $(SRC)/parseRepos.c $(HEADERS)/parseRepos.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/parseRepos.o $(PKG) -c $(SRC)/parseRepos.c

catalogoUsers: $(SRC)/catalogoUsers.c $(HEADERS)/catalogoUsers.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/catalogoUsers.o $(PKG) -c $(SRC)/catalogoUsers.c

catalogoRepos: $(SRC)/catalogoRepos.c $(HEADERS)/catalogoRepos.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/catalogoRepos.o $(PKG) -c $(SRC)/catalogoRepos.c

catalogoCommits: $(SRC)/catalogoCommits.c $(HEADERS)/catalogoCommits.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/catalogoCommits.o $(PKG) -c $(SRC)/catalogoCommits.c

parsing: $(SRC)/parsing.c $(HEADERS)/parsing.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/parsing.o $(PKG) -c $(SRC)/parsing.c
	
queries: $(SRC)/queries.c $(HEADERS)/queries.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/queries.o $(PKG) -c $(SRC)/queries.c	

sg:  $(SRC)/sg.c $(HEADERS)/sg.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/sg.o $(PKG) -c $(SRC)/sg.c

UI: $(SRC)/UI.c $(HEADERS)/UI.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/UI.o $(PKG) -c $(SRC)/UI.c

Controller: $(SRC)/Controller.c $(HEADERS)/Controller.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/Controller.o $(PKG) -c $(SRC)/Controller.c

paginacao: $(SRC)/paginacao.c $(HEADERS)/paginacao.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/paginacao.o $(PKG) -c $(SRC)/paginacao.c

Test: $(SRC)/Test.c $(HEADERS)/Test.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/Test.o $(PKG) -c $(SRC)/Test.c



guiao-3: $(SRC)/main.c $(OBJ)/main.o $(OBJ)/parseUsers.o $(OBJ)/parseCommits.o $(OBJ)/parseRepos.o $(OBJ)/catalogoUsers.o $(OBJ)/catalogoRepos.o $(OBJ)/catalogoCommits.o $(OBJ)/parsing.o $(OBJ)/sg.o $(OBJ)/UI.o $(OBJ)/Controller.o $(OBJ)/paginacao.o
	$(COMPILER) $(FLAGS) $(OBJ)/parseUsers.o $(OBJ)/parseCommits.o $(OBJ)/parseRepos.o $(OBJ)/catalogoUsers.o $(OBJ)/catalogoRepos.o $(OBJ)/catalogoCommits.o $(OBJ)/main.o $(OBJ)/parsing.o $(OBJ)/queries.o $(OBJ)/sg.o $(OBJ)/UI.o $(OBJ)/Controller.o $(OBJ)/paginacao.o $(PKG) -o guiao-3

test: $(OBJ)/parseUsers.o $(OBJ)/parseCommits.o $(OBJ)/parseRepos.o $(OBJ)/catalogoUsers.o $(OBJ)/catalogoRepos.o $(OBJ)/catalogoCommits.o $(OBJ)/parsing.o $(OBJ)/sg.o $(OBJ)/UI.o $(OBJ)/Controller.o $(OBJ)/Test.o $(OBJ)/paginacao.o
	$(COMPILER) $(FLAGS) $(OBJ)/parseUsers.o $(OBJ)/parseCommits.o $(OBJ)/parseRepos.o $(OBJ)/catalogoUsers.o $(OBJ)/catalogoRepos.o $(OBJ)/catalogoCommits.o $(OBJ)/parsing.o $(OBJ)/queries.o $(OBJ)/sg.o $(OBJ)/UI.o $(OBJ)/Controller.o $(OBJ)/Test.o $(OBJ)/paginacao.o $(PKG) -o test

memcheck:
	valgrind --leak-check=yes -s ./guiao-3

clean:
	rm -rf $(OBJ)/*.o guiao-3

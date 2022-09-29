FLAGS= -std=c99 -O2 -D_GNU_SOURCE -ggdb3  
PKG = `pkg-config --cflags --libs glib-2.0` `pkg-config --libs glib-2.0`
COMPILER=gcc
HEADERS=libs
SRC=src
OBJ=obj

all: main parseUsers parseCommits parseRepos catalogoUsers catalogoRepos catalogoCommits parsing queries guiao-2

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


guiao-2: $(SRC)/main.c $(OBJ)/main.o $(OBJ)/parseUsers.o $(OBJ)/parseCommits.o $(OBJ)/parseRepos.o $(OBJ)/catalogoUsers.o $(OBJ)/catalogoRepos.o $(OBJ)/catalogoCommits.o $(OBJ)/parsing.o
	$(COMPILER) $(FLAGS) $(OBJ)/parseUsers.o $(OBJ)/parseCommits.o $(OBJ)/parseRepos.o $(OBJ)/catalogoUsers.o $(OBJ)/catalogoRepos.o $(OBJ)/catalogoCommits.o $(OBJ)/main.o $(OBJ)/parsing.o $(OBJ)/queries.o $(PKG) -o guiao-2
	
memcheck:
	valgrind --leak-check=yes -s ./guiao-2

clean:
	rm -rf $(OBJ)/*.o guiao-2

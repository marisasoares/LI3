FLAGS= -std=c99 -Wall -Wextra -Wpedantic -Wvariadic-macros -Wlong-long -O2 -D_GNU_SOURCE -ggdb3  
PKG = `pkg-config --cflags --libs glib-2.0` `pkg-config --libs glib-2.0`
LIBS= 
COMPILER=gcc
HEADERS=libs
SRC=src
OBJ=obj

all: main parseUsers parseCommits parseRepos listaUsers listaRepos user repos parsing guiao-1

main: $(SRC)/main.c $(HEADERS)/main.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/main.o $(PKG) -c $(SRC)/main.c

parseUsers: $(SRC)/parseUsers.c $(HEADERS)/parseUsers.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/parseUsers.o $(PKG) -c $(SRC)/parseUsers.c

parseCommits: $(SRC)/parseCommits.c $(HEADERS)/parseCommits.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/parseCommits.o $(PKG) -c $(SRC)/parseCommits.c

parseRepos: $(SRC)/parseRepos.c $(HEADERS)/parseRepos.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/parseRepos.o $(PKG) -c $(SRC)/parseRepos.c

listaUsers: $(SRC)/listaUsers.c $(HEADERS)/listaUsers.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/listaUsers.o $(PKG) -c $(SRC)/listaUsers.c

listaRepos: $(SRC)/listaRepos.c $(HEADERS)/listaRepos.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/listaRepos.o $(PKG) -c $(SRC)/listaRepos.c

user: $(SRC)/user.c $(HEADERS)/user.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/user.o $(PKG) -c $(SRC)/user.c

repos: $(SRC)/repos.c $(HEADERS)/repos.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/repos.o $(PKG) -c $(SRC)/repos.c

parsing: $(SRC)/parsing.c $(HEADERS)/parsing.h
	$(COMPILER) $(FLAGS) -o $(OBJ)/parsing.o $(PKG) -c $(SRC)/parsing.c

	
guiao-1: $(SRC)/main.c $(OBJ)/main.o $(OBJ)/parseUsers.o $(OBJ)/parseCommits.o $(OBJ)/parseRepos.o $(OBJ)/listaUsers.o $(OBJ)/listaRepos.o $(OBJ)/user.o $(OBJ)/repos.o $(OBJ)/parsing.o
	$(COMPILER) $(FLAGS) $(OBJ)/parseUsers.o $(OBJ)/parseCommits.o $(OBJ)/parseRepos.o $(OBJ)/listaUsers.o $(OBJ)/listaRepos.o $(OBJ)/user.o $(OBJ)/repos.o $(OBJ)/main.o $(OBJ)/parsing.o $(PKG) -o guiao-1
	
memcheck:
	valgrind --leak-check=yes -s ./guiao-1

clean:
	rm -rf $(OBJ)/*.o guiao-1

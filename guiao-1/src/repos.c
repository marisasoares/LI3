//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../libs/repos.h"



REPOS initRepos(int id, int owner){
	REPOS r = malloc(sizeof(struct repos));
	r->id = id;
	r->owner_id = owner;
	return r;
}


int getIDR(REPOS r){
	return r->id;
}

int getOwner(REPOS r){
	return r->owner_id;
}


void removeRepos(REPOS r){
    free(r->id);
    free(r->owner_id);
    free(r);
}

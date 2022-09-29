


typedef struct repos{
    int id;
    int owner_id;

} *REPOS;

REPOS initRepos(int id, int owner);

int getIDR(REPOS r);

int getOwner(REPOS r);

void removeRepos(REPOS r);
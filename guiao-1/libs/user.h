typedef struct user{
    int id;
    char* username;
} *USER;

USER initUser(int id, char* uname);

int getID(USER u);

char* getUsername(USER u);

/*GHashTable getFollowers(USER u)*/

void removeUser(USER u);
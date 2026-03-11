
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    int n = argv[1];
    if(atoi(n) != 423){

    }
    char *l = strdup("hardcoded string\n"); //flag 
    int c = 0;
    gid_t gid = getegid();
    uid_t uid = geteuid();
    int res_gid = setresgid(gid, gid, gid);
    int res_uid = setresuid(uid, uid, uid);
    execve()
}
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
	
int main (int argc,char *argv[]){
int stat;
char timedate[200];
struct tm *timenow;

pid_t children_id;
children_id = fork();

    time_t now = time(NULL);
    timenow = localtime(&now);
    strftime(timedate, sizeof(timedate), "%Y-%m-%d_%H:%M:%S", timenow);
    // Making the format name for directory
    
    if (children_id < 0) {
    exit(EXIT_FAILURE); } // If fails to create a new process , the program will stop

    if (children_id == 0) {
    // Making directory according to the format name
    
    char *argv[] = {"mkdir", timedate, NULL};
    execv("/bin/mkdir", argv);} 

    else {
    // this is parent
    while ((wait(&stat)) > 0);
    char *argv[] = {"touch", "folderku/fileku.txt", NULL};
    execv("/usr/bin/touch", argv);
  }
}

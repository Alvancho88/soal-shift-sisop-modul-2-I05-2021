#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>
#include <signal.h>

//3a
int MakeDirectory();

//3b
int Download(char timedate[]);

//3c
void Cipher(char message[], int key);
void MakeTXT(char message[], char timedate[]);
void MakeZIP(char timedate[]);

//3d, 3e
void MakeKiller(int argN, char **argV, int pid);


// 3a
int MakeDirectory(){
	char timedate[150];
	int status;
	time_t t;
	pid_t child_id;
	child_id = fork();
	t = time(NULL);
  	
	strftime(timedate, sizeof(timedate), "%Y-%m-%d_%H:%M:%S", localtime(&t));
	if(child_id < 0)
		exit(EXIT_FAILURE);
	if (child_id == 0){	
  		
		char *argv[] = {"mkdir", timedate, NULL};
		execv("/bin/mkdir", argv);}
	else if(child_id > 0 && wait(&status) > 0){
		pid_t child_id2;
		child_id2 = fork();
		if(child_id2 < 0)
			exit(EXIT_FAILURE);
		if (child_id2 == 0){
			pid_t child_id3;
			child_id3 = fork();
		if(child_id3 < 0)
				exit(EXIT_FAILURE);
		if (child_id3 == 0){	
				
  				short gambar = 1;
				while(gambar <= 10){
					int z = Download(timedate);
					if(z == 7){
						gambar++;
						sleep(5);}}}
			else if(child_id3 > 0 && wait(&status) > 0){
				char message[20] = {"Download Success"};
				int key = 5;
				Cipher(message, key);
				MakeTXT(message, timedate);
				MakeZIP(timedate);}
			kill(getpid(),SIGTERM);}
		else{
			return 10;}}}

//3b
int Download(char timedate[]){
	
	char temp[150];
  	char path[150]={};
  	char url[150]={};
	pid_t child_id;
	child_id = fork();
	time_t t;
	t = time(NULL);
	
	strftime(temp, sizeof(temp), "%Y-%m-%d_%H:%M:%S", localtime(&t));
	
  	strcat(path, timedate);
  	strcat(path,"/");
  	strcat(path, temp);
  	
  	int SIZE = (((int)t)%1000)+50;
  	
  	sprintf(url, "https://picsum.photos/%d/%d", SIZE, SIZE); 
	if(child_id < 0)
		exit(EXIT_FAILURE);
	if (child_id == 0){
		
		char *argv[] = {"wget",url , "-qO", path, NULL};
  		execv("/bin/wget", argv);
  		kill(getpid(),SIGTERM);}
	else{
		return 7;}}

//3c
void Cipher(char message[], int key){
	
	char ch;
	int i;
	for(i = 0; message[i] != '\0'; ++i){
		ch = message[i];
 
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + key;
 			
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;}
			message[i] = ch;}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + key;
 			
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;}
			message[i] = ch;}}}

void MakeTXT(char message[], char timedate[]){
	
	FILE *file1;
	char path [150] = {}; 
	
	strcat(path, timedate);
  	strcat(path,"/");
  	strcat(path, "status.txt");
  	file1 = fopen(path, "w");
  	
  	fputs(message, file1);
  	fclose(file1);}

void MakeZIP(char timedate[]){
	
	char *argv[] = {"zip", "-r" , "-m", timedate, timedate, NULL};
  	execv("/bin/zip", argv);}

//3d
void MakeKiller(int argN, char **argV, int pid){
	
	pid_t child_id;
	child_id = fork();
	int status;
	if(child_id < 0)
		exit(EXIT_FAILURE);
	if (child_id == 0){
		//3e	
		FILE *file1 = fopen("killer.sh", "w");
		if (argN == 2 && strcmp(argV[1], "-z") == 0){
			
			fprintf(file1, "#!/bin/bash\nkillall -9 ranoracok\nrm \"$0\"");}
		else if (argN == 2 && strcmp(argV[1], "-x") == 0){
			
			fprintf(file1, "#!/bin/bash\nkill %d\nrm \"$0\"", pid);}
		fclose(file1);}
	else if(child_id > 0 && wait(&status) > 0){
	
		char *argv[] = {"chmod", "+x", "killer.sh", NULL};
        	execv("/bin/chmod", argv);}}

int main(int argN, char **argV) {
	pid_t pid, sid;       
	pid = fork(); 
	    
  	if (pid < 0) {
    		exit(EXIT_FAILURE);}

  	if (pid > 0) {
  	  	exit(EXIT_SUCCESS);}
		umask(0);

  	sid = setsid();
  	if (sid < 0) {
  	 	exit(EXIT_FAILURE);}
  	close(STDIN_FILENO);
  	close(STDOUT_FILENO);
  	close(STDERR_FILENO);
  	MakeKiller(argN, argV, (int) getpid()+1);
	while(1){
		int a = MakeDirectory();
		if (a == 10){	
			sleep(40);}}}

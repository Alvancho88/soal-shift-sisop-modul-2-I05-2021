#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define Folder_Count 3

void function_delete_folders(pid_t child_id, int * status, char * directory_name[]) {

	if((child_id = fork()) == 0){
		char *argv[] = {"rm", "-r", directory_name[0], directory_name[1], directory_name[2], NULL};
        	execv("/bin/rm", argv);
	}
	while(wait(status) > 0);
	//r=remove directories and their contents recursively

}

void function_move_files(struct dirent * directory_entry, int * status, char directory_name[], char stevany_directory_name[]) {

	pid_t child_move = fork();
	if(child_move == 0 && (strcmp(directory_entry->d_name, ".") == 0 || strcmp(directory_entry->d_name, "..") == 0)){
		exit(EXIT_SUCCESS);
	}

	if(child_move == 0) {
        	char path_file[256];

        	strcpy(path_file, directory_name);
        	strcat(path_file, "/");
        	strcat(path_file, directory_entry->d_name);

        	char *argv[] = {"mv", path_file, stevany_directory_name, NULL};
        	execv("/bin/mv", argv);
	}
	while(wait(status) > 0);
}

void function_search_folder_and_move_files(int * status, char directory_name[], char stevany_directory_name[]) {

	DIR * directory = opendir(directory_name);
	struct dirent * directory_entry;

	if (directory != NULL) {
		while ((directory_entry = readdir(directory))){
			function_move_files(directory_entry, status, directory_name, stevany_directory_name);		
		}
		(void) closedir (directory);
	} 
	else {
		perror ("Directory access denied");
	}

}

void function_make_folders(pid_t child_id, int * status, char *directory_name[], char *stevany_directory_name[]) {

	//Making a new folder for each file extension by calling fork so that child will execute mkdir command
	if((child_id = fork()) == 0){
		char *argv[] = {"mkdir", "-p", stevany_directory_name[0], stevany_directory_name[1], stevany_directory_name[2], NULL};
		execv("/bin/mkdir", argv);
	}
	while(wait(status) > 0);
	//-p=no error if existing, make parent directories as needed

}

void Zip_Birthday_Folders(pid_t child_id, int * status, char *stevany_directory_name[], char zip_name[]) {

	//Zip Folders on Stefany's Birthday
	if((child_id = fork()) == 0) {
        	char *argv[] = {"zip", "-rm", zip_name, stevany_directory_name[0], stevany_directory_name[1], stevany_directory_name[2], NULL};
        	execv("/bin/zip", argv);
	}
	while(wait(status) > 0);
	//m=Move the specified files into the zip archive,r=Travel the directory structure recursively;
}

void function_download_and_unzip(pid_t child_id, int * status) {

	//Download Zip Files
        if((child_id = fork()) > 0){

		char *argv[] = {"wget", "--no-check-certificate", 
		"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download"
		, "-O", "Fylm_for_Stevany.zip" , NULL};

		execv("/bin/wget", argv);

	}
	else if ((child_id = fork()) == 0){

		char *argv[] = {"wget", "--no-check-certificate", 
		"https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download"
		, "-O", "Musyik_for_Stevany.zip" , NULL};

		execv("/bin/wget", argv);
	}
	else{

		char *argv[] = {"wget", "--no-check-certificate", 
		"https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"
		, "-O", "Pyoto_for_Stevany.zip" , NULL};

		execv("/bin/wget", argv);
	}
	while(wait(status) > 0);
	//Makes wget to continue despite verification failure, but it still will complain - without that option set wget would simply stop once verification failed.

	//Unzip into files
        if((child_id = fork()) > 0){
		char *argv[] = {"unzip", "Fylm_for_Stevany.zip", NULL};
		execv("/bin/unzip", argv);
	}
	else if((child_id = fork()) == 0){
		char *argv[] = {"unzip", "Musyik_for_Stevany.zip", NULL};
		execv("/bin/unzip", argv);
	}
	else{
		char *argv[] = {"unzip", "Pyoto_for_Stevany.zip", NULL};
		execv("/bin/unzip", argv);
	}
	while(wait(status) > 0);

}

void Main_Function(pid_t child_id, char *stevany_directory_name[]) {

	int status;
	
	char *directory_name[] = {"Film", "Musik", "Foto"};

	function_make_folders(child_id, &status, directory_name, stevany_directory_name);

	function_download_and_unzip(child_id, &status);

	for(int i=0; i<Folder_Count; i++){
        	function_search_folder_and_move_files(&status, directory_name[i], stevany_directory_name[i]);
	}

	function_delete_folders(child_id, &status, directory_name);

}

int Birthday_Date_Check(int day, int month) {

	//Check date to be more efficient
	const int birthday_month = 3;
	const int birthday_day = 9;

	return birthday_day == day && birthday_month == month;
}

void Daemon_Function_Call(int * status) {

	pid_t child_id;
	char *stevany_directory_name[] = {"Fylm", "Musyik", "Pyoto"};

	const unsigned sleep_time = 1;
	const int birthday_hour = 22;
	const int birthday_minute = 22;

	while (1) {

        	time_t now = time(NULL);
        	struct tm * nowLocal = localtime(&now);

		//If Birthday_day_month_hour_and_minute is on 09 April Pukul 22.22 WIB, then zip all folders
		if(Birthday_Date_Check(nowLocal->tm_mday, nowLocal->tm_mon) && birthday_hour == nowLocal->tm_hour && birthday_minute == nowLocal->tm_min && nowLocal->tm_sec == 0){
			Zip_Birthday_Folders(child_id, status, stevany_directory_name, "Lopyu_Stevany.zip");
		}
		//Else if 6 hour before run the Main_Function
        	else if(Birthday_Date_Check(nowLocal->tm_mday, nowLocal->tm_mon) && birthday_hour - 6 == nowLocal->tm_hour && birthday_minute == nowLocal->tm_min && nowLocal->tm_sec == 0){
			Main_Function(child_id,stevany_directory_name);
		}
        	while(wait(status) > 0);

        sleep(sleep_time);
	}
}

int main() {

	//Fork the Parent Process and turn off the Parent Process
	pid_t child_id, sid;
	int status;
	const char active_directory[] = "/home/alvancho/Documents/IO5/Shift_2/Question_1";

	if((child_id = fork()) > 0){
		exit(EXIT_SUCCESS);
	}

	//Create a Unique Session ID
	sid = setsid();
	if (sid < 0 || chdir(active_directory)){
		exit(EXIT_FAILURE);
	}

	//Changing the File Mode
	umask(0);

	//Close the Standard File Descriptor
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	//Run the Daemon
	Daemon_Function_Call(&status);
	return 0;
}

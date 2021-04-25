#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <syslog.h>
#include <wait.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define Folder_Count 3

int File_Move();
int Birthday_Zip();

void Function_Download(char download_link[], char file_name[]) {

	char *argv[] = {"wget", "--no-check-certificate",
			download_link,
			"-O", file_name, "-q", NULL};
	execv("/bin/wget", argv);

}

void Function_Unzip(char file_name[]) {

	char *argv[] = {"unzip", "-qq", file_name, NULL};
	execv("/bin/unzip", argv);

}

void Function_Make_Folders(pid_t child_id, int * status, char *directory_name[], char *stevany_directory_name[]) {

	if((child_id = fork()) == 0) {
		char *argv[] = {"mkdir", "-p", stevany_directory_name[0], stevany_directory_name[1],stevany_directory_name[2], NULL};
		execv("/bin/mkdir", argv);
	}
	while(wait(status) > 0);

}

void Function_Download_and_Unzip(pid_t child_id, int * status, char *file_name[]) {

	char *download_links[] = {
	"https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download",
        "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
        "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download"};
    
	for(int i=0; i<Folder_Count; i++) {
        	if((child_id = fork()) == 0){
			Function_Download(download_links[i], file_name[i]);
		}
		while(wait(status) > 0);

		if((child_id = fork()) == 0){
			Function_Unzip(file_name[i]);
		}
		while(wait(status) > 0);
	}

}

void Main_Function(pid_t child_id, char *stevany_directory_name[]) {

	int status;
	char *file_name[] = {"FILM.zip", "MUSIK.zip", "FOTO.zip"};
	char *directory_name[] = {"FILM", "MUSIK", "FOTO"};

	Function_Make_Folders(child_id, &status, directory_name, stevany_directory_name);
	Function_Download_and_Unzip(child_id, &status, file_name);

	File_Move();

        //char *argv_2[] = {"find", ".", "-name", "*.mp4", "-exec", "mv", "{}", "/home/alvancho/Documents/IO5/Shift_2/Question_1/Fylm/", ";", NULL};
        //execv("/usr/bin/find", argv_2);
        //char *argv_3[] = {"find", ".", "-name", "*.mp3", "-exec", "mv", "{}", "/home/alvancho/Documents/IO5/Shift_2/Question_1/Musyik/", ";", NULL};
        //execv("/usr/bin/find", argv_3);

}

int Birthday_Date_Check(int day, int month) {

	//Check date to be more efficient
	const int birthday_month = 3;
	const int birthday_day = 9;

	return birthday_day == day && birthday_month == month;
}

void Daemon_Function (int * status) {

	pid_t child_id;
	char *stevany_directory_name[] = {"Fylm", "Musyik", "Pyoto"};
	const unsigned sleep_time = 1;
	const int birthday_hour = 22;
	const int birthday_minute = 22;

	while (1) {
	
        if (time(NULL) == 1617960120){
            child_id = fork();
        }
        if (child_id < 0){
            exit(EXIT_FAILURE);
        }
        if (child_id == 0){
            Main_Function(child_id,stevany_directory_name);
        }
        else if (time(NULL) == 1617981720){
            while ((wait(&status)) > 0);
            Birthday_Zip();
        }
        	while(wait(status) > 0);

        sleep(sleep_time);
	}
}

int main() {

	const char workingDir[] = "/home/alvancho/Documents/IO5/Shift_2/Question_1";
	pid_t child_id, sid;
	int status;
    
	if((child_id = fork()) > 0){
        	exit(EXIT_SUCCESS);
	}

	umask(0);

	sid = setsid();
	if (sid < 0 || chdir(workingDir)){
		exit(EXIT_FAILURE);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	Daemon_Function(&status);
	return 0;
}

int File_Move (){
    pid_t child_id;
    int status;
    child_id = fork();
    if (child_id < 0){
        exit(EXIT_FAILURE);
    }
    if (child_id == 0){
        pid_t child_id_2;
        int status_2;
        child_id_2 = fork();
        if (child_id_2 < 0){
            exit(EXIT_FAILURE);
        }
        if (child_id_2 == 0){
            char *argv[] = {"find", ".", "-name", "*.jpg", "-exec", "mv", "{}", "/home/alvancho/Documents/IO5/Shift_2/Question_1/Pyoto/", ";", NULL};
            execv("/usr/bin/find", argv);
        }
        else{
            char *argv[] = {"find", ".", "-name", "*.mp3", "-exec", "mv", "{}", "/home/alvancho/Documents/IO5/Shift_2/Question_1/Musyik/", ";", NULL};
            execv("/usr/bin/find", argv);
        }
    }
    else{
        char *argv[] = {"find", ".", "-name", "*.mp4", "-exec", "mv", "{}", "/home/alvancho/Documents/IO5/Shift_2/Question_1/Fylm/", ";", NULL};
        execv("/usr/bin/find", argv);
    }
}

int Birthday_Zip (){
    pid_t child_id;
    int status;
    child_id = fork();
    if (child_id < 0){
        exit(EXIT_FAILURE);
    }
    if (child_id == 0){
        char *argv[] = {"zip", "-r", "Lopyu_Stevany", "Fylm/", "Musyik/", "Pyoto/", NULL};
        execv("/usr/bin/zip", argv);
    }
    else{
        while ((wait(&status)) > 0);
        char *argv[] = {"rm", "-r", "FILM", "MUSIK", "FOTO", "Fylm", "Musyik", "Pyoto", NULL};
        execv("/usr/bin/rm", argv);
    }
}

/*Command Note:
find -name pattern
find - search for files in a directory hierarchy
Base of file name
-exec command
Execute command; true if 0 status is returned.

mkdir
mkdir - make directories
-p, --parents
No error if existing, make parent directories as needed

wget
Wget - The non-interactive network downloader.
-O file
The documents will not be written to the appropriate files, but all will be concatenated together and written to file.
-q
Turn off Wget's output.

zip
zip - package and compress (archive) files
-r
Travel the directory structure recursively;

unzip
unzip - list, test and extract compressed files in a ZIP archive
-q
perform operations quietly (-qq = even quieter)
*/

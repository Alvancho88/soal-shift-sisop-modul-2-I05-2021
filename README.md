# soal-shift-sisop-modul-2-I05-2021
Repository for Second Operating System Lab Work

**Rafi Akbar Rafsanjani - 05111942000004**

**Agustinus Aldi Irawan Rahardja - 05111942000010**

**Muhammad Rafi Hayla Arifa - 05111942000014**

# Question 1
Once upon a time, there was a steven who lived a mediocre live. Steven had a girlfriend, but they have broken up before getting together. 
When he was thinking about his ex, he always watches https://www.youtube.com/watch?v=568DH_9CMKI to relieve his sadness. 

In the meantime, Steven hates SISOP Course very much like no other, Few hours after breaking up with his girlfriend, he found another  woman named Stevany, 
but Stevany is the opposite of him because she likes SISOP course very much. Steven wanted to look good at SISOP course to impress her.

On her birthday, he wanted to give her a zip file containing all things that she likes. He wanted the zip to be organized by making a new folder for each file extension. 
(a) Because she likes the letter Y so much, He wanted the name of the folder as Musyik for mp3, Fylm for mp4, and Pyoto for jpg 
(b) For music, he downloads it from the link below, so are the cases for films and photos. 
(c) he didn’t want the folder to contain the zip files so he extracts the files first after downloading it. 
(d) moving it to the folder that has been made (only the files).
(e) When it’s her birthday, all folder will be zipped with the name Lopyu_Stevany.zip and all the folders will be deleted. (Only the zip remains).
(f) To make his life easier, he wants all of the above to run automatically 6 hours before her birthday (except for point e of course)

Steven is asking your help who is the greatest of the greats of sisop master to help get her heart. Help him!!!

Note:
Stevany’s birthday : 09 April Pukul 22.22 WIB
All points are run by 1 script on the background, that includes downloading the zip file. So you just need to run 1 script and change the time and date to check the result.

```
Preview :
https://drive.google.com/drive/folders/1NzRiPPoVlR_H8P51cxN4jaceeFQGk4un
*watch it in 720p.. ಠ‿ಠ

```

You are not allowed to use system(), mkdir(), dan rename() (functions in C) .... FORBIDDENNN!!
You are not allowed to use cron !!!
Use fork and exec
Link

```
Photo:
https://drive.google.com/file/d/1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD/view
Music :
https://drive.google.com/file/d/1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J/view
Film : 
https://drive.google.com/file/d/1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp/view
```

Tips :
Use wait and sleep method
To download the zip file that are needed, you can use this command :

```
wget --no-check-certificate "https://drive.google.com/uc?id=(ID-FILE)&export=download" -O Nama_untuk_filenya.ext

```

example

```
Wget --no-check-certificate "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download" -O Musik_for_Stevany.zip
```

**Source Code**

**Can be seen in the above folder (soal1)**

**Explanation**
-----
a.) Here we are asked to simply make a folder with names of Musyik, Fylm, and Pyoto
note: we cannot use mkdir() in c, but there is a way to go around it and that is by using fork() and execv()
We can use them to call for mkdir much like using system but more safely, since system() is risky.

```
void function_make_folders(pid_t child_id, int * status, char *directory_name[], char *stevany_directory_name[]) {

	//Making a new folder for each file extension by calling fork so that child will execute mkdir command
	if((child_id = fork()) == 0){
		char *argv[] = {"mkdir", "-p", stevany_directory_name[0], stevany_directory_name[1], stevany_directory_name[2], NULL};
		execv("/bin/mkdir", argv);
	}
	while(wait(status) > 0);
	//-p=no error if existing, make parent directories as needed

}
```

b.) 
Then we need to use the same method to downloads files in zip from the given links
We will use fork and execv again this time
Although this time it's more tricky since I haven't suceed in always be able to download it
```
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
```

c.) 
We need to extract the files from the zip that has been downloaded
We can use the same method that is fork and exec for this one on the same function after we download the files
```
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
```

d.) 
Now, we need to move the files to the folder that has been made
First we need to search the folder

```
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
```

Then we move the files using a created function
```
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
```

e.) 
We are asked to zipped all the folders with the name Lopyu_Stevanny.zip and then delete the folders on her birthday
We will create a function to check if it's Stevanny birthday date or not
```
int Birthday_Date_Check(int day, int month) {

	//Check date to be more efficient
	const int birthday_month = 3;
	const int birthday_day = 9;

	return birthday_day == day && birthday_month == month;
}
```

Then, we will continue to create the Daemon to run the program automatically
```
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
```

Where if it is the date of her birthday and on the right time, it will execute the function to zip all the folders into one
```
void Zip_Birthday_Folders(pid_t child_id, int * status, char *stevany_directory_name[], char zip_name[]) {

	//Zip Folders on Stefany's Birthday
	if((child_id = fork()) == 0) {
        	char *argv[] = {"zip", "-rm", zip_name, stevany_directory_name[0], stevany_directory_name[1], stevany_directory_name[2], NULL};
        	execv("/bin/zip", argv);
	}
	while(wait(status) > 0);
	//m=Move the specified files into the zip archive,r=Travel the directory structure recursively;
}
```

f.) 
The function to operate all of the above task must run 6 hour before her birthday
We must use Daemon to help automatically run the program
Already explained on the above

extra.)
Main function to call everything 6 hour before Stevanny's Birthday
```
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
```

This is the main from the whole program and where the program start
We just do the basic things for Daemon setup then call the function
```
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
```

-----
**Problem Found**
1.) I'm not used to Linux environment, so it is a bit harsh in the beginning
2.) It's very hard to code using c languange in nano, so I prefer code it in dev c++ or visual studio or notepad then check it on linux terminal
3.) To check if the outpot is right or wrong takes too many times (time-consuming)
4.) Somehow the download can end up working but most often not working
5.) Daemon sometimes doesn't work, but sometimes works too...weird...

**Documentation**

![Screenshot from 2021-04-09 16-26-49](https://user-images.githubusercontent.com/61174498/115116010-9c9d6f80-9fc1-11eb-9529-41d0ba6690f8.png)

![Screenshot from 2021-04-09 22-27-14](https://user-images.githubusercontent.com/61174498/115116015-a2935080-9fc1-11eb-9372-d0dda1b5a3b0.png)

# Question 2

Loba works in a famous pet shop, one day he got a zip containing lots of pets photos and he was ordered to categorize the photos of these pets. Loba finds it difficult to do his work manually, moreover there is the possibility that he will be ordered to do the same thing multiple times. You are Loba's best friend and he is asking for your help to help with his work.

**a)  First, the program needs to extract the given zip into the folder ```“/home/[user]/modul2/petshop”```. Because Loba's boss is careless, the zip may contain unimportant folders, so the program must be able to distinguish between files and folders so that it can process files that should be worked on and delete unnecessary folders.**

**Source Code**

```
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>
#include <string.h>

int main()
{
    pid_t make_folder_child_id;
    int make_folder_status;

    make_folder_child_id = fork();

    if(make_folder_child_id < 0)
    {
        exit(EXIT_FAILURE); // if the program failed, then the program will stop
    }

    if(make_folder_child_id == 0)
    {
        char *mkdir[] = {"mkdir", "-p", "/home/rafihayla/modul2/petshop", NULL};
        execv("/bin/unzip", mkdir);
    }
    
    else
    {
        while((wait(&make_folder_status)) > 0);
        pid_t unzip_child_id;
        int unzip_status;

        unzip_child_id = fork();

        if(unzip_child_id < 0)
        {
            exit(EXIT_FAILURE); // if the program failed, then the program will stop
        }

        if(unzip_child_id == 0)
        {
            char *unzip[] = {"unzip", "/home/rafihayla/Downloads/pets.zip", "-d", "/home/rafihayla/modul2/petshop", NULL};
            execv("/bin/unzip", unzip);
        }

        else
        {
            while((wait(&unzip_status)) > 0);
            pid_t delete_unnecessary_directory_child_id;
            int delete_unnecessary_folders_status;

            delete_unnecessary_directory_child_id = fork();

            if(delete_unnecessary_directory_child_id < 0)
            {
                exit(EXIT_FAILURE); // if the program failed, then the program will stop
            }

            if(delete_unnecessary_directory_child_id == 0)
            {
                DIR *dir;
                struct dirent *input;
                dir = opendir("/home/rafihayla/modul2/petshop");

                while((input = readdir(dir)) != NULL)
                {
                    if(strcmp(input -> d_name, ".")  && strcmp(input -> d_name, "..") )
                    {
                        if(input -> d_type == DT_DIR)
                        {
                            pid_t delete_unnecessary_child_id;
                            int delete_unnecessary_status;

                            delete_unnecessary_child_id = fork();

                            if(delete_unnecessary_child_id < 0)
                            {
                                exit(EXIT_FAILURE); // if the program failed, then the program will stop
                            }

                            if(delete_unnecessary_child_id == 0)
                            {
                                char unnecessary[50];
                                sprintf(unnecessary, "/home/rafihayla/modul2/petshop/%s", input -> d_name);
                                char *delete[] = {"rm", "-r", unnecessary, NULL};
                                execv("/bin/rm", delete);
                            }
                        }

                    }
                }
            }
        }
    }
} 
```

**Explanation**

Based on my understanding, before we start the program. We must download the zip file first and we can put it just in the downloads folder. Then, here comes  the program. So, the first thing we need to do, create a directory that has been tought before which is ```"/home/[user]/modul2/petshop"```. Then, the next step, we need to extract the pet.zip file from the downloads folders ```("/home/rafihayla/Downloads")``` to our directory ```("/home/rafihayla/modul2/petshop")```. After we finished extracting the file. We have unneeded folders overthere. That's what we want to delete it. So, we need to check the folder in the ```"/home/rafihayla/modul2/petshop"``` using the ```DT_DIR``` to check folders. If we found the unneeded folders. Then we delete it.

**Problem Found**

For me, there are some syntax that i never knew before. It was very new for me. So, sometimes it was really confusing and frustating.

**Documentation**

<img width="1168" alt="Screen Shot 2021-04-25 at 14 59 32" src="https://user-images.githubusercontent.com/74056954/115985668-20b1b180-a5d7-11eb-95e2-a8998a157273.png">


# Question 3

Ranora is an Informatics Engineering student who is currently undergoing an internship at a well-known company called "FakeKos Corp.", a company engaged in data security. Because Ranora is still an apprentice, the workload is not as big as the workload of the company's permanent workers. On Ranora's first day of work, Ranora's apprentice tutor gave her the task of making a program.

**a)Ranora must create a C program which every 40 seconds creates a directory with a name according to the timestamp [YYYY-mm-dd_HH:ii:ss].

**Source Code**

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

**Explanation**

So in question number 3a, we are told to create a new directory using exec.c as in Module 2. 
First, we declare the variables used. After that we create a place to create the date in the format year, month, day, hour, minute, and second. Because we want to match the time we use localtime. We use the strftime function to change the format as specified. This problem isn't really finished yet because it hasn't created a new directory every 40 seconds. But it has succeeded in creating a directory if we run the program.

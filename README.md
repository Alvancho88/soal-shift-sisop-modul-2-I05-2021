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
void Function_Make_Folders(pid_t child_id, int * status, char *directory_name[], char *stevany_directory_name[]) {

	if((child_id = fork()) == 0) {
		char *argv[] = {"mkdir", "-p", stevany_directory_name[0], stevany_directory_name[1],stevany_directory_name[2], NULL};
		execv("/bin/mkdir", argv);
	}
	while(wait(status) > 0);

}
```

b.) 
Then we need to use the same method to downloads files in zip from the given links
We will use fork and execv again this time
```
void Function_Download(char download_link[], char file_name[]) {

	char *argv[] = {"wget", "--no-check-certificate",
			download_link,
			"-O", file_name, "-q", NULL};
	execv("/bin/wget", argv);

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
```

c.) 
We need to extract the files from the zip that has been downloaded
We can use the same method that is fork and exec for this one on the same function after we download the files
```
void Function_Unzip(char file_name[]) {

	char *argv[] = {"unzip", "-qq", file_name, NULL};
	execv("/bin/unzip", argv);

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
```

d.) 
Now, we need to move the files to the folder that has been made
(note: For Pictures, only .jpg files are moved)

```
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
```

Where if it is the date of her birthday and on the right time, it will execute the function to zip all the folders into one
And remove the folders
```
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
```

f.) 
The function to operate all of the above task must run 6 hour before her birthday
We must use Daemon to help automatically run the program
Already explained on the above
Daemon Function
```
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
```

Extra.)
Main function to call everything 6 hour before Stevanny's Birthday
```
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
```

This is the main from the whole program and where the program start
We just do the basic things for Daemon setup then call the function
```
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
```

Header and Declaration
```
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
```

-----
**Problem Found**
1.) I'm not used to Linux environment, so it is a bit harsh in the beginning
2.) It's very hard to code using c languange in nano, so I prefer code it in dev c++ or visual studio or notepad then check it on linux terminal
3.) To check if the outpot is right or wrong takes too many times (time-consuming)
4.) Somehow the download can end up working but most often not working
5.) Daemon sometimes doesn't work, but sometimes works too...weird...

**Documentation**

Initial Condition:
![Screenshot from 2021-04-09 16-21-41](https://user-images.githubusercontent.com/61174498/115992366-962d7a00-a5f7-11eb-8172-8fc684eef4a3.png)

Progress (Making Folder):
![Screenshot from 2021-04-09 16-22-02](https://user-images.githubusercontent.com/61174498/115992384-ab0a0d80-a5f7-11eb-9a5a-1aed3789d653.png)

Progress ABCD Done:
![Screenshot from 2021-04-09 16-22-14](https://user-images.githubusercontent.com/61174498/115992397-bbba8380-a5f7-11eb-99c5-1a431e54df33.png)

Birthday Zip Done:
![Screenshot from 2021-04-09 22-22-03](https://user-images.githubusercontent.com/61174498/115992406-c8d77280-a5f7-11eb-86ca-ba4913db7086.png)

Terminal View:
![Screenshot from 2021-04-09 22-23-53](https://user-images.githubusercontent.com/61174498/115992411-d260da80-a5f7-11eb-91f0-fcd897084acb.png)

Zip Content:
![Screenshot from 2021-04-09 16-23-02](https://user-images.githubusercontent.com/61174498/115992419-e3a9e700-a5f7-11eb-832e-d494efc7d66d.png)

![Screenshot from 2021-04-09 16-23-09](https://user-images.githubusercontent.com/61174498/115992423-e73d6e00-a5f7-11eb-9a26-596f7d662626.png)

![Screenshot from 2021-04-09 16-23-17](https://user-images.githubusercontent.com/61174498/115992427-ec022200-a5f7-11eb-9962-32d5c24b54b4.png)

Folders Content:
![Screenshot from 2021-04-09 16-22-24](https://user-images.githubusercontent.com/61174498/115992438-f9b7a780-a5f7-11eb-8153-9f77c79b894d.png)

![Screenshot from 2021-04-09 16-22-29](https://user-images.githubusercontent.com/61174498/115992445-ff14f200-a5f7-11eb-8ff2-f5f210acd230.png)

![Screenshot from 2021-04-09 16-22-34](https://user-images.githubusercontent.com/61174498/115992449-03410f80-a5f8-11eb-8db4-677c3cda34de.png)

Done

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

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
```
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
```
```
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
			
```

**Explanation**
First, we must first create the main function that uses the daemon so that when the program is run it can perform other commands. To keep the program running, we can use while (1) to create a directory for 40 seconds by calling the MakeDirectory function followed by sleep (40).

Then after that we call the fork function and after it is broken down we run mkdir to create the directory as specified. So that other processes don't take a lot of time (40 seconds), we break the process and its parent again with return.

![image](https://user-images.githubusercontent.com/61174498/115994547-a9454780-a601-11eb-9fbf-8fd6a8b3d364.png)

**b)Each directory is filled with 10 images downloaded from https://picsum.photos/, where each image will be downloaded every 5 seconds. Each downloaded image will be named with a timestamp format [YYYY-mm-dd_HH:ii:ss] and the image is square with the size (n% 1000) + 50 pixels where n is the Unix Epoch time.

**Source Code**
```
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
```
```
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
```
**Explanation**
First of all, we have to split the child process from Problem 3a into two function processes. Then follow by using sleep (5) to download an image every 5 seconds.
First of all, we have to split the child process from Problem 3a into two function processes. Then follow by using sleep (5) to download an image every 5 seconds. After downloading the image every 5 seconds, we format the name according to the current time. After that, we create a path that contains the destination folder and the name of the image that was downloaded earlier. Then, we calculate the size for the obtained image. Don't forget to add the image size to the url to download the image. The final step, we just need to download the image according to the url and path that was created earlier.

![image](https://user-images.githubusercontent.com/61174498/115994581-db56a980-a601-11eb-8ad2-b0226ec578a5.png)

**c)After the directory has been filled with 10 images, the program will create a file "status.txt", which contains the message "Download Success" which is encrypted with the Caesar Cipher technique and with shift 5. Caesar Cipher is a simple encryption technique which can perform encryption. string according to the shift / key that we specify. For example, the letter "A" will be encrypted with shift 4 it will become "E". Because Ranora is a perfectionist and neat person, he wants after the file is created, the directory will be zipped and the directory will be deleted, leaving only the zip file.

**Source Code**
```
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
```
**Explanation**
The first thing to do is to continue the program from Problem 3b which comes from the MakeDirectory function. In the Cipher () function, each letter in the message is shifted as many as keys. Then in the MakeTXT function we create a path containing the folder name and the file name status.txt. Then we create a file with an encrypted path into that file. Furthermore, in the MakeZIP function, the directory containing 10 images will be zipped. After that delete the zipped directory file with the arguments.

![image](https://user-images.githubusercontent.com/61174498/115994602-ec071f80-a601-11eb-8804-edfbc019e506.png)

![image](https://user-images.githubusercontent.com/61174498/115994613-f2959700-a601-11eb-8893-57b665be20f7.png)

**d&e)To make it easier to control the program, the Ranora apprentice supervisor wants the program to produce an executable "Killer" program, where the program will terminate all running program processes and will run itself after the program is run. Because Ranora is interested in something new, Ranora has an idea for the "Killer" program that was made, it must be a bash program.The Ranora apprentice supervisor also wants the main program created by Ranora to run in two modes. To activate the first mode, the program must be executed with the -z argument, and when it is executed in the first mode, the main program will immediately execute all its operations when the Killer program is run. Meanwhile, to activate the second mode, the program must be run with the -x argument, and when run in the second mode, the main program will stop allowing the processes in each directory that are still running until it is finished (The directory that has been created will download the image to completion and create a txt file, then zip and delete the directory).

**Source Code**
```
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
```
**Explanation**
The first thing to do is to call the MakeKiller () function on the main function. The MakeKiller function will break the process in two. The -x process will catch the program in real time. The -z process will click the program after the image in the last directory has finished downloading. After that we use MakeKiller to change the killer file to make it executable.

![image](https://user-images.githubusercontent.com/61174498/115994620-fc1eff00-a601-11eb-85e2-1f96611f6d30.png)

![image](https://user-images.githubusercontent.com/61174498/115994628-03460d00-a602-11eb-886d-a9635a77e1ca.png)


# soal-shift-sisop-modul-2-I05-2021
Repository for Second Operating System Lab Work

**Rafi Akbar Rafsanjani - 05111942000004**

**Agustinus Aldi Irawan Rahardja - 05111942000010**

**Muhammad Rafi Hayla Arifa - 05111942000014**

# Question 2

Loba works in a famous pet shop, one day he got a zip containing lots of pets photos and he was ordered to categorize the photos of these pets. Loba finds it difficult to do his work manually, moreover there is the possibility that he will be ordered to do the same thing multiple times. You are Loba's best friend and he is asking for your help to help with his work.

**a)  First, the program needs to extract the given zip into the folder ```“/home/[user]/modul2/petshop”```. Because Loba's boss is careless, the zip may contain unimportant folders, so the program must be able to distinguish between files and folders so that it can process files that should be worked on and delete unnecessary folders.**

**Source Code**

```#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    pid_t unzip_child_id;
    int unzip_status;

    unzip_child_id = fork();

    if(unzip_child_id < 0)
    {
        exit(EXIT_FAILURE); // if the program failed, then the program will stop
    }

    if(unzip_child_id == 0)
    {
        char *unzip[] = {"unzip", "/home/rafihayla/modul2/petshop/pets.zip", NULL};
        execv("/bin/unzip", unzip);
    }

    else
    {
        while((wait(&unzip_status)) > 0);
        pid_t child_id;
        int status;

        child_id = fork();

        if(child_id < 0)
        {
            exit(EXIT_FAILURE); // if the program failed, then the program will stop
        }

        if(child_id == 0)
        {
            char *deletezip[] = {"rm", "/home/rafihayla/modul2/petshop/pets.zip", NULL};
            execv("/bin/rm", deletezip);
        }
        
        else
        {
            while((wait(&status)) > 0);
            pid_t child2_id;
            int status2;

            child2_id = fork();

            if(child2_id < 0)
            {
                exit(EXIT_FAILURE); // if the program failed, then the program will stop
            }

            if(child2_id == 0)
            {
                char *deletedirectory1[] = {"rm", "-r", "/home/rafihayla/modul2/petshop/apex_cheats", NULL};
                execv("/bin/rm", deletedirectory1);
            }

            else
            {
                while((wait(&status2)) > 0);
                pid_t child3_id;
                int status3;

                child3_id = fork();

                if(child3_id < 0)
                {
                    exit(EXIT_FAILURE); // if the program failed, then the program will stop
                }

                if(child3_id == 0)
                {
                    char *deletedirectory2[] = {"rm", "-r", "/home/rafihayla/modul2/petshop/musics", NULL};
                    execv("/bin/rm", deletedirectory2);
                }

                else
                {
                    while((wait(&status3)) > 0);
                    pid_t child4_id;
                    int status4;

                    child4_id = fork();

                    if(child4_id < 0)
                    {
                        exit(EXIT_FAILURE); // if the program failed, then the program will stop
                    }

                    if(child4_id == 0)
                    {
                        char *deletedirectory3[] = {"rm", "-r", "/home/rafihayla/modul2/petshop/unimportant_files", NULL};
                         execv("/bin/rm", deletedirectory3);
                    }
                }
            }
        }         
    }
}
```

**Explanation**

Based on my understanding, before we start the program. The first thing we need to do is we need to preapre the folder with the directory ```"/home/[user]/modul2/petshop"```. Then, the next step is to download the zip file which is ```pets.zip``` and we move the zip file in to the folder that we already prepared before. Now, we begin the program. Of course, we need to extract the ```pets.zip``` first as a child process. After that, we will wait for the program to extracting the file and when it's done, now we remove the unnecessary files or folders. The unnecessary files or folders include the ```pets.zip, apex_cheats, musics, and unimportant_files```. Why we also need to remove the ```pets.zip``` file? Because we don't need the zip file anymore because we already extracted it before. Back to the topic, so the first parent process is removing the ```pets.zip``` file. Then to remove the other files, we make it somehow like a nested. We make the parent of the removing the zip file process which is removing the ```apex_cheats``` folder and so on so forth.

**Problem Found**

I don't know why if i only make 1 child process and 1 parent process:

  child process: extracting the zip file
  
  parent process: removing all the unnecessary file and folders
  
If i run the program, the program only the delete the zip file and the apex_cheats folder. It won't delete the remaining unneccessary file (musics and unimportant_files).

**Documentation**

<img width="467" alt="Screen Shot 2021-04-17 at 20 01 34" src="https://user-images.githubusercontent.com/74056954/115114161-fa2cbe80-9fb7-11eb-9ff4-322021dd6bd2.png">

<img width="513" alt="Screen Shot 2021-04-17 at 20 02 10" src="https://user-images.githubusercontent.com/74056954/115114175-0749ad80-9fb8-11eb-8b30-c19f570b99f7.png">

<img width="510" alt="Screen Shot 2021-04-17 at 20 02 50" src="https://user-images.githubusercontent.com/74056954/115114180-0f095200-9fb8-11eb-9c29-7db4f3ddb2ac.png">

<img width="1301" alt="Screen Shot 2021-04-17 at 20 11 07" src="https://user-images.githubusercontent.com/74056954/115114371-24cb4700-9fb9-11eb-9b1a-cd616dcd2db5.png">



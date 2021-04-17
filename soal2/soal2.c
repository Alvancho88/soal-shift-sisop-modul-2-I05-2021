#include <stdio.h>
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
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

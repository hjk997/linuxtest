#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUF 256

//ls 코드
int ls(char *argv)
{
   DIR *dir, *tempDir;
   struct dirent *directory;
   struct stat file_state;

   char current[MAX_BUF];
   char temp[MAX_BUF];

   memset(temp, 0, MAX_BUF);      
   memset(current, 0, MAX_BUF);      
   strcpy(temp, argv);
   
   //printf(temp);

   if( (dir = opendir(temp)) < 0)
   {
      perror("opendir");
      exit(1);
   }
   
   //항목 읽기 시작
   while( (directory = readdir(dir)) != NULL)
   {
      if(!strncmp(directory->d_name, ".", 1) || !strcmp(directory->d_name, ".."))
        {
            continue;
        }
      sprintf(current, "%s/%s", temp, directory->d_name);
      printf("%s\n", current);

      if(lstat(current, &file_state) < 0)
      {
         perror("stat");
         exit(1);
      }

      if(S_ISDIR(file_state.st_mode))
      {
         ls(current);
      }
   }
}

void main(int argc, char *argv[])
{
   
   if(argc<2)
   {
      fprintf(stderr, "Usage: file_dir dirname\n");
      exit(1);
   }
         
   ls(argv[1]); 
   
}


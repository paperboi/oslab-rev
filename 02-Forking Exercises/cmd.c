#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

FILE *fp;
int count=0;

void  parse(char *line, char **argv)
{
     while (*line != '\0') 
     {                                       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';               /* replace white spaces with 0    */
          *argv++ = line;                    /* save the argument position     */
          while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n') 
               line++;                       /* skip the argument until ...    */
     }
     *argv = '\0';                           /* mark the end of argument list  */
}

void  execute(char **argv, FILE *fp)
{
     pid_t  pid;
     int    status, flag=0;

     if ((pid = fork()) < 0)
     {                                       /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0)
     {                                       /* for the child process:         */
          if (*argv[0]=='!')
          {
               flag=1;
               int t=strlen(argv[0]);
               char temp1[5], temp2[5];
               strcpy(temp1, argv[0]);
               if (temp1[1]=='!')
               {
                    char readline[1024];
                    fseek(fp, -sizeof(readline), SEEK_END);
<<<<<<< HEAD
=======
                    // fscanf(fp, "%s", readline);
>>>>>>> 6a9b68666e2f82d3a894dc986c5458ffff700822
                    fread(&readline, sizeof(readline), 1, fp);
                    printf("%s\n", readline);
               }
               else
               {
                    strncpy(temp2, temp1+1, t-1);
                    int num=atoi(temp2);
                    if (num<=count)
                         for (int i = 0; i < num; ++i)
                         {
                              char readline[1024];
                              fseek(fp, -((i+1)*sizeof(readline)), SEEK_END);
<<<<<<< HEAD
=======
                              // fscanf(fp, "%s\n", readline);
>>>>>>> 6a9b68666e2f82d3a894dc986c5458ffff700822
                              fread(&readline, sizeof(readline), 1, fp);
                              printf("%s\n", readline);
                         }
                    else
                         printf("*** ERROR: The number doesn't exist!\n");
               }
          }

          if (execvp(*argv, argv) < 0)
          {                                  /* execute the command            */
               if (flag==1)
                    exit(0);
               else
               {
                    printf("*** ERROR: exec failed\n");
                    exit(1);
               }
          }

     }
     else
     {                                       /* for the parent:                */
          while (wait(&status) != pid)       /* wait for completion            */
               ;
          char readline[1024];
          strcpy(readline, *argv);
          fwrite(readline, 1, sizeof(readline), fp);
          count++;
     }
}

int  main()
{
     char  line[1024];                       /* the input line                 */
     char  *argv[64];                        /* the command line argument      */

     FILE *fp=fopen("history.txt", "w+");

     while (1)
     {                                       /* repeat until done ....         */
          printf("Shell -> ");               /*   display a prompt             */
          gets(line);                        /*   read in the command line     */
          printf("\n");
          parse(line, argv);                 /*   parse the line               */
          if (strcmp(argv[0], "exit") == 0)  /* is it an "exit"?               */
          {
               fclose(fp);
               exit(0);                      /*   exit if it is                */
          }
          execute(argv, fp);                     /* otherwise, execute the command */
     }
<<<<<<< HEAD
=======
     fclose(fp);
>>>>>>> 6a9b68666e2f82d3a894dc986c5458ffff700822
     return 0;
}

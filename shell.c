# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# define delimeters " \t\r\n\a"
void terminalCommandsLoop ();
char* read_command();
 char **tokenizer(char *command_line);
int commandExecution(char **arguments);
 int main (int argc,char **argv)
 {
     terminalCommandsLoop();
     return 0;
 }
 void terminalCommandsLoop ()
 {
     char *command_line;
     char **arguments;
     int state;
     while(1)
     {
         printf(">");
         command_line=read_command();
         arguments=tokenizer(command_line);
         state=commandExecution(arguments);
         free(command_line);
         free(arguments);
         if(!state)
           {
               break;
           }
     }    
 }
 char* read_command()
 {
     char *command_line=NULL;
     ssize_t buffer_size=0;
      ssize_t characters;
     if (getdelim(&command_line,&buffer_size,'\n',stdin)==-1)
     {
            if(feof(stdin))
            {
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("getdelim error\n");
                    exit(EXIT_FAILURE);
            }
     }
     return command_line;
 }    
 char **tokenizer(char *command_line)
 {
       int buffer_size=128;
       int index=0;
       char **tokens=malloc(sizeof(char*) * buffer_size);
       char *token, **copy_of_tokens;
       if(!tokens)
       {
           fprintf(stderr,"allocation error\n");
           exit(EXIT_FAILURE);
       }
       token=strtok(command_line,delimeters);
       while(token !=NULL)
       {
           tokens[index]=token;
           index++;
           if(index>=buffer_size)
           {
               buffer_size+=buffer_size;
               copy_of_tokens=tokens;
               tokens=realloc(tokens,sizeof(char*) * buffer_size);
               if (!tokens)
               {
                   free(copy_of_tokens);
                   fprintf(stderr,"allocation error\n");
                   exit(EXIT_FAILURE);
               }    
           }
           token=strtok(NULL,delimeters);
       }
       tokens[index]=NULL;
       return tokens;
 } 
int commandExecution(char **arguments)
{
    pid_t pid;
    int state;
    const char *ampersand;
  ampersand = "&";
  int *background =0;
  int index=0;
while (arguments[index]!=NULL)
{
      if (strcmp(arguments[index], ampersand) == 0)
      {
          background=1;
      }
      if(strcmp(arguments[0], "exit") == 0) 
      {
          exit(0);
      }
}

  // If we find an ampersand as the last argument, set a flag.
 
    found_amp = true;
    pid=fork();
    if (pid==0)
    {
        if (execvp(arguments[0],arguments)==-1)
        {
                    perror("child process creation error");
        }
        exit(EXIT_FAILURE);
        
    }

    else if(pid<0)
    {
        perror("error forking");
    }
    else
    {
        do {
            waitpid(pid,&state,WUNTRACED);
        }
        while (!WIFEXITED(state) && !WIFSIGNALED(state));  
    }
    FILE *f;
    f=fopen("process.log","a+");
    if(f==NULL)
    {
        fprintf(f,"something is wrong\n");
    }
        return 1;
    
}


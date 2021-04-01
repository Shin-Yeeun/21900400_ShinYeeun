#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#define _CRT_SECURE_NO_WARNINGS  

int pipes[2];

void child_proc_tar(char * file, char *input){
  pid_t target_pid ;
  int value = atoi(input);
  target_pid = fork() ;
  if (target_pid == 0) {
    execl("/usr/bin/gcc", "gcc", "-o", "target",file,  (char *)NULL);
  }

  else {
    wait(0);
    //freopen("input.txt", "r", stdout);
    execl("./target","target",input,(char *)NULL);
    
  }
  
}
void child_proc_sol(char * file,char * input){
  pid_t solution_pid;
  solution_pid = fork();

  
 
  if(solution_pid == 0){
    execl("/usr/bin/gcc", "gcc", "-o", "solution", file, (char *) NULL);
  }
  else{
    //freopen("input.txt","r",stdout);
    execl("./solution","solution",input,(char*)NULL);
  }
  
}


int main(int argc, char * args[]){
    for(int i=0; i<argc; i++){
    printf("args[%d] : %s\n",i,args[i]);
  }
  
  pid_t child_p; 
  int exit_code ;
  DIR * input;
  struct dirent *elem;
  char * put;
  char *input_file[10];
  input = opendir(args[2]);

  
 //printf("%s",put);  
  if(input !=NULL){
    int i=0;
    while(elem = readdir(input)){

           input_file[i]=elem->d_name;
           printf("file[%d] :%s\n", i,input_file[i]);
           i++;
      } 
  }
  else printf("No directory!\n");
  
  pid_t child_pid ;
  for(int i=1; i<=10; i++){
  char * filename =input_file[i];
  // printf("%s\n",filename);
  FILE* pFile = fopen("input.txt", "rt");
 

  char str[50];
  fgets(str,50, pFile);
  char string[50];
  //printf("%s\n",str);
  
  char buf[225] ;
  
  
  pipe(pipes);


  child_p  = fork();
  if(child_p ==0){
  write(pipes[1],str,sizeof(str)) ;
  child_proc_tar(args[4],str);
  }
  else{
  read(pipes[0], buf, sizeof(str)); 
  printf("pipe: %s\n",buf);

  wait(&exit_code) ; 
  child_proc_sol(args[5],buf); 

  }
  

  }
  closedir(input);
  exit(0) ;
  
}
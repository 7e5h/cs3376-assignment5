#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h>
int main(int argc, char **argv){ 
int status;
int lsChildPid;
int grepChildPid;
char *ls_args[] = {"ls", "-ltr", NULL}; 
char *grep_args[] = {"grep", "3376", NULL};
char *wc_args[] = {"wc","-l",NULL};
// create one pipe to send the output of "ls" process to "grep" process 
int lsPipe[2];
int grepPipe[2];
pipe(lsPipe);
pipe(grepPipe);
	// fork the first child (to execute cat) 
if((lsChildPid = fork()) == -1){
	perror("Error creating a child process"); 
	exit(1);
}
if((grepChildPid = fork())==-1){
	perror("Error creating grep child process");
	exit(1);
}
if (grepChildPid==0){//This should call grep and pass to wc
	dup2(grepPipe[0],0);
	dup2(lsPipe[1],1);
	close(lsPipe[0]);
	close(lsPipe[1]);
	close(grepPipe[0]);
	close(grepPipe[1]);
	execvp(*grep_args,grep_args);
	exit(0);
}
else if (lsChildPid == 0) {//This should call ls and pass to grep
	
    dup2(grepPipe[1], 1);
    close(grepPipe[1]);
    close(grepPipe[0]);
    close(lsPipe[0]);
    close(lsPipe[1]);
    execvp(*ls_args, ls_args);
    exit(0);
  }
  else {//this should call wc and print
      dup2(lsPipe[0], 0);
      //close all pipes (very important!); end we're using was safely copied
      close(lsPipe[0]);
      close(lsPipe[1]);
	close(grepPipe[0]);
	close(grepPipe[1]);
	execvp(*wc_args,wc_args);
  
  }

 return(0);
 }

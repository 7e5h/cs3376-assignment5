//Written by:	Sam Britton
//Class:	CS 3376
//Date:		4/7/2017
//Desc:		The program takes inputs and, using multiple processes, simulates the pipe command in linux.
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char **argv){ 
int count = 0;
int status;
int pipes[4][2];
int child[4];
// create one pipe to send the output of "ls" process to "grep" process 
if(argc >6||argc<2){
	perror("error");
	exit(1);
}
for(int i = 0;i<4;i++){
	pipe(pipes[i]);
}
char *params[5][4];
for(int i = 0;i<5;i++){
	params[i][0] = "cat";
	params[i][1] = NULL;
	params[i][2] = NULL;
	params[i][3] = NULL;
}
for(int i = 1;i<argc;i++){
    char *p;
    p = strtok(argv[i]," ");
    int count = 0;
    while(p!=NULL){
	params[i-1][count] = p;
	p = strtok (NULL," ");
	count++;
    }
}


 for(int i= 0; i < 4; ++i) {
   if ((child[i] = fork()) < 0) {
       perror("fork");
           abort();
   } 
   else if(child[i] == 0) {
	if(i!=3)//The last child must use stdout
	{
		dup2(pipes[i+1][1],1);//map output
	}
	dup2(pipes[i][0],0);//get input from its pipe
	for(int x = 0;x<4;x++)
		for(int y = 0;y<2;y++)
			close(pipes[x][y]);
	execvp(params[i+1][0],params[i+1]);
        exit(0);
    }	
 }
//Only the parent should live here
dup2(pipes[0][1],1);
	for(int x = 0;x<4;x++)
		for(int y = 0;y<2;y++)
			close(pipes[x][y]);
execvp(params[0][0],params[0]);//Calls the first command
 return(0);

 }





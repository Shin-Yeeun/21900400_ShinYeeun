#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char ** args){
int value;
value = atoi(args[1]);
 printf("sol : %d\n",value);
return 0;
}
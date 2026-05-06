#include<stdio.h>
#include<sys/shm.h>
int main(){
int shmid;
char *str;
shmid=shmget(2345,1024,0666|IPC_CREAT);
str=(char*) shmat(shmid,NULL,0);
printf("%s",str);
return 0;
}

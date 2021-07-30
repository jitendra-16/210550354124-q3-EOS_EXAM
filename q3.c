#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#define SIZE 64

int main()
{
   unsigned char buff[SIZE];
   unsigned char buff1[SIZE];
   int pfd[2];
   int pfdr[2];
   pid_t id;
   pid_t id1;
   id=fork();

   if(0==id)
   {
       printf("child\n");
       close(pfd[1]);
       read(pfd[0],buff,SIZE);
       printf("child:got data from beg:%s\n",buff);
       
       close(pfdr[0]);
       write(pfdr[1],"ok\n",3);
       close(pfdr[1]);
       close(pfd[0]);
   }

   if(id>0)
   {
     id1=fork();
     if(id1>0)
     {
         printf("parent\n");
         close(pfd[0]);
         write(pfd[1],"asdf\n", 5);
         close (pfd[1]);

         close(pfdr[1]);
         read(pfdr[0],buff1,SIZE);
         printf("parent get:%s\n",buff1);
         close(pfdr[0]);  


     }
     else if(id1==0)
     {
       printf("child1\n");
       close(pfd[1]);
       read(pfd[0],buff,SIZE);
       printf("child1:got data end: %s\n",buff);
       

       close(pfdr[0]);
       write(pfdr[1],"ok\n",3);
       close(pfdr[1]);
       close (pfd[0]);
     }

     return 0;
   }
}
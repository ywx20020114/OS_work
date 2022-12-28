#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


// 5个理发师，40名顾客，4个沙发               店里最多20人
sem_t customers,barbers,mutex,wanttosit,pay,over,cash_r;
int waiting=0;

void *barber_1(void*arg)
{
   while(1){
   sem_wait(&customers);
   sem_wait(&mutex);
   sem_post(&barbers);
   sem_post(&mutex);
   printf("2013852ywx的理发店：1号理发师开始理发\n");
   sleep(10);
   sem_post(&over);
   sem_wait(&pay);
   sem_wait(&cash_r);
   printf("2013852ywx的理发店：1号理发师为客人结帐\n");
   sem_post(&cash_r); 
   waiting--;

   }
}
void *barber_2(void*arg)
{
   while(1){
   sem_wait(&customers);
   sem_wait(&mutex);
   sem_post(&barbers);
   sem_post(&mutex);
   printf("2013852ywx的理发店：2号理发师开始理发\n");
   sleep(10);
   sem_post(&over);
   sem_wait(&pay);
   sem_wait(&cash_r);
   printf("2013852ywx的理发店：2号理发师为客人结帐\n");
   sem_post(&cash_r);
   waiting--;
   }
}
void *barber_3(void*arg)
{
   while(1){
   sem_wait(&customers);
   sem_wait(&mutex);
   sem_post(&barbers);
   sem_post(&mutex);
   printf("2013852ywx的理发店：3号理发师开始理发\n");
   sleep(10);
    sem_post(&over);
   sem_wait(&pay);
   sem_wait(&cash_r);
   printf("2013852ywx的理发店：3号理发师为客人结帐\n");
   sem_post(&cash_r);
   waiting--;
   }
}

void *barber_4(void*arg)
{
   while(1){
   sem_wait(&customers);
   sem_wait(&mutex);
   sem_post(&barbers);
   sem_post(&mutex);
   printf("2013852ywx的理发店：4号理发师开始理发\n");
   sleep(10);
    sem_post(&over);
   sem_wait(&pay);
   sem_wait(&cash_r);
   printf("2013852ywx的理发店：4号理发师为客人结帐\n");
   sem_post(&cash_r);
   waiting--;
   }
}


void *barber_5(void*arg)
{
   while(1){
   sem_wait(&customers);
   sem_wait(&mutex);
   sem_post(&barbers);
   sem_post(&mutex);
   printf("2013852ywx的理发店：5号理发师开始理发\n");
   sleep(10);
    sem_post(&over);
   sem_wait(&pay);
   sem_wait(&cash_r);
   printf("2013852ywx的理发店：5号理发师为客人结帐\n");
   sem_post(&cash_r);
   waiting--;
   }
}


void *customer_i(int b)
{
  printf("%d号客人来了!\n",b+1);
  sem_wait(&mutex);
  if(waiting<20)
 {  
     waiting++;
     sem_post(&mutex);
     sem_post(&customers);
     switch(waiting){
     case 0 ... 5:
    {
     sem_wait(&barbers);
     printf("%d号客人正在理发\n",b+1);
     sem_wait(&over);
     printf("%d号客人去结帐\n",b+1);
     sem_post(&pay);
     break;
    }
     case 6 ... 9:
      {
        sem_wait(&wanttosit);
        printf("%d号客人去沙发等待\n",b+1); 
       sem_wait(&barbers);
       sem_post(&wanttosit);
       printf("%d号客人正在理发\n",b+1);
       sem_wait(&over);
       printf("%d号客人去结帐\n",b+1);
       sem_post(&pay);
      break;
      }
     default :
       {
       printf("%d号客人站着等待\n",b+1);
        sem_wait(&wanttosit);
       printf("%d号客人去沙发等待\n",b+1); 
       sem_wait(&barbers);
       sem_post(&wanttosit);
       printf("%d号客人正在理发\n",b+1);
       sem_wait(&over);
       printf("%d号客人去结帐\n",b+1);
       sem_post(&pay);
       break;
      }
      }
      }
      else 
       {
       printf("无位置，%d号客人离开\n",b+1);
        sem_post(&mutex);
       
        } 

}

int main()
{
	int sg1,sg2,sg3,sg4,sg5,sg6,sg7;
    pthread_t barber1,barber2,barber3,barber4,barber5,customer[40];
	sg1=sem_init(&mutex,0,1);
	sg2=sem_init(&customers,0,0);
    sg3=sem_init(&barbers,0,0);
    sg4=sem_init(&wanttosit,0,4);
    sg5=sem_init(&over,0,0);
    sg6=sem_init(&pay,0,0);
    sg7=sem_init(&cash_r,0,1);
    pthread_create(&barber1,NULL,(void *)barber_1,NULL); 
    pthread_create(&barber2,NULL,(void *)barber_2,NULL); 
    pthread_create(&barber3,NULL,(void *)barber_3,NULL); 
    pthread_create(&barber4,NULL,(void *)barber_4,NULL); 
    pthread_create(&barber5,NULL,(void *)barber_5,NULL); 
        
    for(int i=0;i<=39;i++)
    {      
            pthread_create(&customer[i],NULL,(void *)customer_i,i); 
            sleep(1);
    }
    
            pthread_join(barber1,NULL);
            pthread_join(barber2,NULL);
            pthread_join(barber3,NULL);

    for(int k=0;k<=39;k++)
    {    
            pthread_join(customer[k],NULL);
    }
         
        
      
    sleep(2);
	return 0;

}

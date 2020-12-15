#include<stdio.h>
#include<string.h>

struct job{
    char name[10];      
    int arrivetime;
    int starttime;      //작업 시작타임 
    int bursttime;       
    int runtime;        //作业周转时间
    int endtime;      
    int waittime; 
};



void fcfs(struct job jobs[50],int n);
void sjf(struct job jobs[50],int n);
void result(struct job jobs[50],int n);
void set_process(struct job jobs[50],int n);

int main()
{
    struct job jobs[50];
    int n,i; 

    n=5;
    set_process(jobs,n);

    fcfs(jobs,n);
    printf(">>FCFS\n");
    result(jobs,n);


    sjf(jobs,n);
    printf(">>SJF：\n");
    result(jobs,n);
}

void fcfs(struct job jobs[50],int n)
{
   int i; 

   for(i=0;i<n;i++)
   {
    if(i==0) {  //첫 순서 
       jobs[i].starttime=jobs[i].arrivetime;
       jobs[i].runtime=jobs[i].bursttime; 
       jobs[i].endtime=jobs[i].starttime+jobs[i].bursttime;
       jobs[i].waittime=0;    
    }
    else if(jobs[i].starttime>jobs[i-1].endtime){       
       jobs[i].starttime=jobs[i].arrivetime;
       jobs[i].runtime=jobs[i].bursttime;  
       jobs[i].endtime=jobs[i].starttime+jobs[i].runtime; 
       jobs[i].waittime=jobs[i].starttime-jobs[i].arrivetime;
    }
    else{                                       
       jobs[i].starttime=jobs[i-1].endtime;
       jobs[i].runtime=jobs[i].bursttime; 
       jobs[i].endtime=jobs[i].starttime+jobs[i].runtime;
       jobs[i].waittime=jobs[i].starttime-jobs[i].arrivetime;
    }
   }
}

void sjf(struct job jobs[50],int n)
{
   int i=0,b=0;
   char temp[10];
   int min;            
   for(i=0;i<n-1;i++) 
      {
          if(jobs[i].arrivetime>jobs[i+1].arrivetime)
          {   
              min=jobs[i].arrivetime;
              jobs[i].starttime=jobs[i+1].arrivetime;
              jobs[i+1].starttime=min;

              strcpy(temp,jobs[i].name);
              strcpy(jobs[i].name,jobs[i+1].name);
              strcpy(jobs[i+1].name,temp);
          }
      }      
             

   jobs[0].endtime=jobs[0].arrivetime+jobs[0].bursttime;
   jobs[0].runtime=jobs[0].bursttime;


    for(i=1;i<n;i++)
    {
        if(jobs[i].arrivetime>jobs[0].endtime) ; 
            else b=b+1;  
    }

    for(i=1;i<=b-1;i++)
    {
        if(jobs[i].bursttime>jobs[i+1].bursttime)
        { 
          min=jobs[i].arrivetime;
          jobs[i].arrivetime=jobs[i+1].arrivetime;
          jobs[i+1].arrivetime=min;
                  
          min=jobs[i].bursttime;
          jobs[i].bursttime=jobs[i+1].bursttime;
          jobs[i+1].bursttime=min;

          strcpy(temp,jobs[i].name);            
          strcpy(jobs[i].name,jobs[i+1].name);
          strcpy(jobs[i+1].name,temp);
        }                
    }

    for(i=1;i<n;i++)
    {
      if(jobs[i].arrivetime>jobs[i-1].endtime)
      {                                        
        jobs[i].starttime=jobs[i].arrivetime;
        jobs[i].endtime=jobs[i].starttime+jobs[i].bursttime; 
        jobs[i].runtime=jobs[i].bursttime;
      }
      else
      {
         jobs[i].starttime=jobs[i-1].endtime;
         jobs[i].endtime=jobs[i-1].endtime+jobs[i].bursttime;
         jobs[i].runtime=jobs[i].bursttime; 
      }
      jobs[i].waittime=jobs[i].starttime-jobs[i].arrivetime;
    }
}

void result(struct job jobs[50],int n)
{
    int i;
    double averruntime;
    double averwaittime;
    int sum_runtime=0;
    double  sum_waittime=0.00;
    printf("name\tarrive\tstart\trun\t    end\t   wait\n");
    for(i=0;i<n;i++)
    {
    printf("%s\t     %d\t     %d\t    %d\t    %d\t    %d\n",jobs[i].name,jobs[i].arrivetime,jobs[i].starttime,jobs[i].bursttime,jobs[i].endtime,jobs[i].waittime);
    
    sum_runtime=sum_runtime+jobs[i].runtime;
    sum_waittime=sum_waittime+jobs[i].waittime;
    }
    averruntime=sum_runtime*1.0/n;
    averwaittime=sum_waittime*1.000/n;
    printf("평균 waittime:%.2f \n",averwaittime);
    printf("\n");
}

void set_process(struct job jobs[50],int n){
    strcpy(jobs[0].name,"p1");
    jobs[0].arrivetime=0;
    jobs[0].bursttime=10;

    strcpy(jobs[1].name,"p2");
    jobs[1].arrivetime=1;
    jobs[1].bursttime=29;

    strcpy(jobs[2].name,"p3");
    jobs[2].arrivetime=2;
    jobs[2].bursttime=3;

    strcpy(jobs[3].name,"p4");
    jobs[3].arrivetime=3;
    jobs[3].bursttime=7;

    strcpy(jobs[4].name,"p5");
    jobs[4].arrivetime=4;
    jobs[4].bursttime=12; 

    for(int i=0;i<n;i++){
      printf("%s \t %d \t %d\n",jobs[i].name,jobs[i].arrivetime,jobs[i].bursttime);
    }
    printf("\n");  
}

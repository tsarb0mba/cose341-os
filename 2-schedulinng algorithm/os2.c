#include<stdio.h>
#include<string.h>

struct job{
    char name[10];      //作业的名字
    int arrivetime;
    int starttime;      //作业到达系统时间
    int bursttime;       //作业服务时间
    int runtime;        //作业周转时间
    int endtime;        //作业结束时间
    int waittime;    //带权周转时间
 
};

void fcfs(struct job jobs[50],int n);
void sjf(struct job jobs[50],int n);
void result(struct job jobs[50],int n);
void set_process(struct job jobs[50],int n);

int main()
{
    struct job jobs[50];
    int n,i; //n个作业

/**
    printf("输入作业个数:");
    scanf("%d",&n);
    printf("输入每个作业的作业名,到达时间,服务时间:\n");
    for(i=0;i<n;i++)
    {
        scanf("%s",jobs[i].name); //作业名
        scanf("%d",&jobs[i].starttime);//到达时间
        scanf("%d",&jobs[i].bursttime);//运行（服务时间）时间
    }
    printf("\n");
    printf("作业名\t到达系统时间\t运行时间\n");
    for(i=0;i<n;i++)
    {
    printf("%s\t      %d\t         %d\n",jobs[i].name,jobs[i].starttime,jobs[i].bursttime);
    }
**/
    n=5;
    set_process(jobs,n);

    fcfs(jobs,n);
    printf("先来先服务（FCFS）算法运行结果：\n");
    result(jobs,n);


    sjf(jobs,n);
    printf("最短作业优先算法（SJF）运行结果：\n");
    result(jobs,n);

    return 0;
}

void fcfs(struct job jobs[50],int n)
{
   int i; 

   for(i=0;i<n;i++)
   {
    if(i==0) {      //第一个进程
       jobs[i].starttime=jobs[i].arrivetime;
       jobs[i].runtime=jobs[i].bursttime; //周转时间=服务时间
       jobs[i].endtime=jobs[i].starttime+jobs[i].bursttime;//结束时间=到达时间+服务时间
       jobs[i].waittime=0;    
    }
    else if(jobs[i].starttime>jobs[i-1].endtime){            //第i个进程到达系统时，第i-1个进程已运行完毕
       jobs[i].starttime=jobs[i].arrivetime;
       jobs[i].runtime=jobs[i].bursttime;  
       jobs[i].endtime=jobs[i].starttime+jobs[i].runtime; 
       jobs[i].waittime=jobs[i].starttime-jobs[i].arrivetime;
    }
    else{                                                   //第i个进程到达系统时，第i-1个进程未运行完毕
       jobs[i].starttime=jobs[i-1].endtime;
       jobs[i].runtime=jobs[i].bursttime; //周转时间=服务时间+前一个的结束时间-到达时间
       jobs[i].endtime=jobs[i].starttime+jobs[i].runtime;//结束时间=到达时间+周转时间
       jobs[i].waittime=jobs[i].starttime-jobs[i].arrivetime;
    }
   }
}

void sjf(struct job jobs[50],int n)
{
   int i=0,b=0;
   char temp[10];
   int min;            
   for(i=0;i<n-1;i++) //按作业到达系统时间进行排序，最早到达的排在最前面 
      {
          if(jobs[i].arrivetime>jobs[i+1].arrivetime)
          {   //把到达时间早的赋值到min
              min=jobs[i].arrivetime;
              jobs[i].starttime=jobs[i+1].arrivetime;
              jobs[i+1].starttime=min;

        //把到达时间早的赋值到min
              min=jobs[i].arrivetime;
              jobs[i].arrivetime=jobs[i+1].arrivetime;
              jobs[i+1].arrivetime=min;

              strcpy(temp,jobs[i].name);
              strcpy(jobs[i].name,jobs[i+1].name);
              strcpy(jobs[i+1].name,temp);//在temp数组中排序
          }
      }                      

   jobs[0].endtime=jobs[0].arrivetime+jobs[0].bursttime;//结束时间=到达时间+服务时间
   jobs[0].runtime=jobs[0].bursttime;//周转时间=服务时间


    for(i=1;i<n;i++)
    {
        if(jobs[i].arrivetime>jobs[0].endtime) ;  //作业到达系统时，第0个作业还在运行
            else b=b+1;        //用b统计需等待作业0运行的作业个数
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

          strcpy(temp,jobs[i].name);             //将第二个参数的值复制给第一个参数，返回第一个参数
          strcpy(jobs[i].name,jobs[i+1].name);
          strcpy(jobs[i+1].name,temp);
        }                 //按最短运行时间排序
    }

    for(i=1;i<n;i++)
    {
      if(jobs[i].arrivetime>jobs[i-1].endtime)
      {                                         //第i个进程到达系统时，第i-1个进程已运行完毕
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
    printf("平均带权周转时间:%.3f \n",averwaittime);
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

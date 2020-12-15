#include<stdio.h>
#include<stdlib.h>

#define circletime 5

typedef struct PCB {
    int id;
    int arrivetime;
    int runtime;
    int counttime;//남은 시간 
    int aetime;//끝날 시간
    int waittime;
    struct PCB* next;
}*task, pcb;

pcb* creattask(int x, int y, int z) {
    task newtask = (task)malloc(sizeof(pcb));
    newtask->id = x;
    newtask->arrivetime = y;
    newtask->runtime = z;
    newtask->counttime = z;
    newtask->aetime = y;
    newtask->next = NULL;
    return newtask;
}
void deltask(pcb* n, int x) {
    task d;
    if (n != NULL) {
        while (n->next->id != x) {
            n = n->next;
        }
        d = n->next;
        n->next = d->next;
        free(d);
    }
}
void count(pcb* n, int t) {  //q는 기록용,
    pcb* q, * p,* last;
    int totalwait=0;
    int qp = 0; //
    int qt[6]={0,0,0,0,0,0};//wait에 쓰려고, 번호를 이름으로 지었기에...실제로는 qt[1~6]을 쓸 예정
    int temp = t; //개수기록 
    float time = 0; //시간기록 
    while (t != 0) {
        p = n->next;
        q = p;
        while (p != NULL) { //제일 먼저 도착
            if (p->aetime < q->aetime) {
                q = p;
            }
            p = p->next;
        }
        p = n->next;
        last = p;

        while (p != NULL) { //가장 마지막에 도착 
            if (p->aetime > last->aetime) {
                last = p;
            }
            p = p->next;
        }
        if(temp==0) qt[q->id]=q->arrivetime;
        q->waittime=time-qt[q->id];//wait시간

        if (time < q->aetime)
            time = q->aetime;

        totalwait+=q->waittime;//wait시간 총합

        printf("p%d\t %.0f ->", q->id,time);

        //남은 시간의 따라 계산 
        if (q->counttime <= circletime) {
            time =time + q->counttime;
            q->counttime = 0;
        }
        else {
            q->counttime = q->counttime - circletime;
            q->aetime = last->aetime + circletime;
            time = time + circletime;
        }

        qt[q->id]=time;//해당 프로세스 이번 턴의 종료시간 기록

        printf("%.0f\twaittime=%d\n",time,q->waittime);

        //해당 프로세스 완성시 출력 
        if (q->counttime == 0) {
            printf(">>p%d종료\n", q->id);
            deltask(n, q->id);
            --t;
        }
    }
    printf("\n");
    printf("평균waittime %.2f \n", (float)totalwait/ temp);
}
int main() {
    int n, i, y, z;
    char name[5];
    task tail = NULL;
    task head = NULL;
    //printf("총 프로세스 개수:");
    //scanf("%d", &n);
    n=5;
    tail = (task)malloc(sizeof(pcb));
    head = tail;
    
    /**for (i = 1; i <= n; i++) {
        printf("%d번 프로세스의 arrivetime과 brusttime을 입력:", i);
        scanf("%d %d", &y, &z);
        tail->next = creattask(i, y, z);
        tail = tail->next;
    }
    **/
    tail->next = creattask(1,0,10);
    tail = tail->next;

    tail->next = creattask(2,1,29);
    tail = tail->next;

    tail->next = creattask(3,2,3);
    tail = tail->next;

    tail->next = creattask(4,3,7);
    tail = tail->next;

    tail->next = creattask(5,4,12);
    tail= tail->next;

    count(head, n);
    return 0;
}
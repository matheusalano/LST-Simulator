#include <stdio.h>

#define MAX_N 26
#define MAX_T 2048

enum state_options {
    READY, DONE, DELAYED
};

typedef enum state_options states;

typedef struct {
  char id;
  char id_d;
  int c;
  int p;
  int d;

  int c_left;
  int slack;
  states s;
} TASK;

int main() {
  TASK tasks[MAX_N];
  int n, t, i;
  char grade[MAX_T+1];
  int num_preemp, num_trocas_cont;

  while (1) {
    // LEITURA
    scanf("%d%d", &n, &t);
    if (n==0 || t==0)
       break;
    for (i=0; i<n; ++i) {
       tasks[i].id = 'A'+i;
       tasks[i].id_d = 'a'+i;
       scanf("%d%d%d", &(tasks[i].c), &(tasks[i].p), &(tasks[i].d) );

       tasks[i].c_left = tasks[i].c;
       tasks[i].slack = tasks[i].d - tasks[i].c;
       tasks[i].s = READY;
    }
    // SIMULACAO
    num_preemp = 0;
    num_trocas_cont = 0;

    for (i = 0; i < t; i++) {
        int lst = 0;

        for (int j=0; j<n; j++) { //Varre as tarefas e salva aquela disponivel com menor slack
          if ((tasks[j].slack < tasks[lst].slack) && (tasks[j].s != DONE)) {
            lst = j;
          }
        }

        // printf("LST:%d \n", lst);

        for (int j=0; j<n; j++) { //Quando for a menor tarefa, faz algo. Senao, faz algo.
        printf("\nAQUI 60");
          if (j == lst) {
            printf("\nAQUI 62");
            if (tasks[j].s == DONE) {
              printf("\nAQUI 64");
              grade[i] = '.';
              if (grade[i - 1] != '.') {
                printf("\nAQUI 65");
                num_preemp++;
              }
            } else {
              printf("\nAQUI 71");
              tasks[j].c_left--;
              if (tasks[j].s == DELAYED) {
                printf("\nAQUI 74");
                grade[i] = tasks[j].id_d;
              } else {
                printf("\nAQUI 77\n");
                grade[i] = tasks[j].id;
              }
            }
          } else {
            printf("\nAQUI 82");
            if (tasks[j].s != DONE) {
              printf("\nAQUI 84");
              tasks[j].slack--;
            }
          }
        }

        for (int j=0; j<n; j++) {
            if ((tasks[j].c_left > 0) && (i%tasks[j].d == 0)) {
              tasks[j].s = DELAYED;              
            }
            else if (tasks[j].c_left == 0) {
              tasks[j].s = DONE;
            }
            if ((i%tasks[j].p == 0) && (tasks[j].s != DELAYED)) {
              tasks[j].c_left = tasks[j].c;
              tasks[j].slack = tasks[j].d - tasks[j].c;
              tasks[j].s = READY;
            }
        }
    }

    grade[t] = '\0';
    
    // RESULTADOS
    printf("%s\n%d %d\n\n", grade, num_preemp, num_trocas_cont);
    return 0;
  }
  return 0;
}
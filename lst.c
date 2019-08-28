#include <stdio.h>

#define MAX_N 26
#define MAX_T 2048

enum state_options {
    READY, DONE
};

typedef enum state_options states;

typedef struct {
  char id;
  int c;
  int p;
  int d;
  int slack;
  states s;
} TASK;

int main() {
  TASK tasks[MAX_N];
  int n, t, i, j;
  char grade[MAX_T+1];
  int num_preemp, num_trocas_cont;

  while (1) {
    // LEITURA
    scanf("%d%d", &n, &t);
    if (n==0 || t==0)
       break;
    for (i=0; i<n; ++i) {
       tasks[i].id = 'A'+i;
       scanf("%d%d%d", &(tasks[i].c), &(tasks[i].p), &(tasks[i].d) );
       tasks[i].slack = tasks[i].d - tasks[i].c; //SLACK tá certo?
    }
    // SIMULACAO
    num_preemp = 0;
    num_trocas_cont = 0;

    for (i = 0; i < t; i++) {
        int lst = 0;

        for (j=0; j<n; ++j) { //Varre as tarefas e salva aquela com menor slack
            if (tasks[j].slack < tasks[lst].slack) {
                lst = j;
            }
        }

        for (j=0; j<n; ++j) { //Quando for a menor tarefa, faz algo. Senao, faz algo.
            if (j == lst) {
                
            } else {

            }
        }

        grade[i] = '.';
    }

    grade[t] = '\0';
    
    // RESULTADOS
    printf("%s\n%d %d\n\n", grade, num_preemp, num_trocas_cont);
  }
  return 0;
}
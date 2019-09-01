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

int indexOfTaskByID(TASK t[], int n, char id) {
  for (int i=0; i < n; i++) {
    if (t[i].id == id || t[i].id_d == id) {
      return i;
    }
  }
  return -1;
}

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
      for (int j=0; j<n; j++) {
        if ((tasks[j].c_left > 0) && (i%tasks[j].d == 0) && i > 0) {
          tasks[j].s = DELAYED;              
        }
        else if (tasks[j].c_left == 0) {
          tasks[j].s = DONE;
        }
        if ((i%tasks[j].p == 0) && (tasks[j].s != DELAYED) && i > 0) {
          tasks[j].c_left = tasks[j].c;
          tasks[j].slack = tasks[j].d - tasks[j].c;
          tasks[j].s = READY;
        }
      }

        int lst = 0;

        for (int j=0; j<n; j++) {
          if (tasks[j].s != DONE) {
            lst = j;
            break;
          }
        }

        for (int j=0; j<n; j++) { //Varre as tarefas e salva aquela disponivel com menor slack
          if ((tasks[j].slack < tasks[lst].slack) && (tasks[j].s != DONE)) {
            lst = j;
          }
        }

        for (int j=0; j<n; j++) { //Quando for a menor tarefa, faz algo. Senao, faz algo.
          if (j == lst) {
            if (tasks[j].s == DONE) {
              grade[i] = '.';
              if (grade[i - 1] != '.') {
                num_preemp++;
                num_trocas_cont++;
              }
            } else {
              tasks[j].c_left = tasks[j].c_left - 1;
              if ((grade[i - 1] != tasks[j].id) && (tasks[indexOfTaskByID(tasks, n, grade[i - 1])].c_left > 0)) { num_preemp++; }
              if (tasks[j].s == DELAYED) {
                grade[i] = tasks[j].id_d;
              } else {
                if (grade[i - 1] == tasks[j].id_d) { num_trocas_cont++; }
                if (grade[i - 1] != tasks[j].id && grade[i - 1] != tasks[j].id_d) { num_trocas_cont++; }
                grade[i] = tasks[j].id;
              }
            }
          } else {
            if (tasks[j].s != DONE) {
              tasks[j].slack--;
            }
          }
        }
    }

    grade[t] = '\0';
    
    // RESULTADOS
    printf("%s\n%d %d\n\n", grade, num_trocas_cont, num_preemp);
  }
  return 0;
}
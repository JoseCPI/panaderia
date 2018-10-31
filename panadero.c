//Hecho por Jose Pimienta
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>
#include <time.h>


#define n 15// numero de procesos
int choosing[n]={}; // variable global para tener el choosing de n threads
int number [n]={}; // variable global para tener el numero de prioridad

int Max(){
    int i;
    int nmax=0;

    for(i=0;i<n;i++){
        if(nmax<number[i]) nmax=number[i];
    }
    return nmax;
}


//Algoritmo de la panaderia
void *panadero(void *arg){
    int j, i;
    i = *((int *) arg);

    do{
        choosing[i] = 1;
        number[i]=Max()+1;////elejir el numero maximo en la lista
        choosing[i] = 0;

        for(j=0; j<n; j++){
            while(choosing[j]);
            while(number[j]!=0 && (number[j]<number[i] || (number[j]==number[i] && j<i)));
        }

        //Seccion Critica
        printf("proceso: (%i). Turno (%i)\n", i, number[i]);
        //termino seccion
        Sleep(rand() % 10);

        number[i]=0;

        //remainder section
        Sleep(rand() % 10);

    }while(1);

}

int main(){
    srand(time(NULL));

    pthread_t procesos[n];

    int i;

    for(i=0; i<n; i++){

        int *arg = malloc(sizeof(*arg));
        if (arg == NULL) exit(EXIT_FAILURE);

        *arg = i;
        pthread_create(&procesos[i], NULL, panadero, arg);
    }

    pthread_exit(NULL);

}



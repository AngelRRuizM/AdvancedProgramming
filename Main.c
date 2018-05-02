#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int choice;

    char* normal = (char*)malloc(sizeof(int)*100);
    char* multithreaded = (char*)malloc(sizeof(int)*100);
    char* ext = (char*)malloc(sizeof(int)*100);
    char*filename = (char*)malloc(sizeof(int)*100);
    
    normal = "BacktrackingQueens";
    multithreaded = "MultithreadBTQueens";

    printf("Este programa resuelve el problema de las n reinas.\n");
    printf("Puedes encontrar y ver la primera solución o  encontrar en nuúmero total de soluciones.\n");
    printf("Para un tablero nxn.\n\n");

    do{
        printf("Para encontrar la primera solución ingresa 1.\nPara encontrar el total de soluciones ingresa 2.\nPara salir ingresa 0.\n");
        printf("Tu elección: ");
        scanf("%d", &choice);

        if(choice == 0){
            break;
        }

        if(choice < 1 || choice > 2){
            printf("Las opciones van de 0 a 2.\n\n");
            continue;
        }

        if(choice == 1)
            ext =  ".out";
        else
            ext = "Count.out";

        do{
            printf("\nAhora puedes escoger si tu programa correrá en un thread o en múltiples threads.\n");
            printf("Los programas con múltiples threads usualmente terminan más rápido.\n");
            printf("Para correrlo en un thread ingresa 1\nPara correrlo en múltiples threads ingresa 2\n");
            printf("Tu elección: ");
            scanf("%d", &choice);
            
            if(choice < 1 || choice > 2){
                printf("Las opciones son 1 o 2.\n\n");
                continue;
            }    

            if(choice == 1)
                sprintf(filename, "%s%s", normal, ext);
            else
                sprintf(filename, "%s%s", multithreaded, ext);

            execl(filename, filename, (char *)0);
            printf("Failed");
                
            printf("%s\n\n", filename);
        } while(choice < 1 || choice > 2);
    }while(choice != 0);
}
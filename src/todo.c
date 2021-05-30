#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct TaskData {
    int id;
    char description[50];
    char status[6];
};

void printMenuPrincipal() {
    system("cls");
    printf("MENU PRINCIPAL:\n");
    printf("\t1. Registro de tareas\n");
    printf("\t2. Actualizacion de tareas\n");
    printf("\t3. Reporte de estado actual\n");
    printf("\t0. Salir\n");
    printf("Seleccione una opcion: ");    
}

void registroTareas() {
    struct TaskData task;
    FILE *archivo;
    bool taskStatusOk = false;
    system("cls");
    printf("REGISTRO DE TAREAS:\n");
    printf("\tIngrese el id de la tarea: ");
    scanf("%d", &task.id);
    fflush(stdin);
    printf("\tIngrese la descripcion de la tarea: ");
    fgets(task.description, sizeof task.description, stdin);
    fflush(stdin);
    printf("\tIngrese el status de la tarea: ");
    while(!taskStatusOk){
        fgets(task.status, sizeof task.status, stdin);
        fflush(stdin);
        if (strcmp(task.status, "Done\n\0")  == 0) {
            task.status[4] = ' ';
        }
        if (!(strcmp(task.status, "To do") == 0 || strcmp(task.status, "Doing")  == 0 || strcmp(task.status, "Done ")  == 0)){
            printf("\tEl status no es correcto, ingrese el status de la tarea (To do, Doing, Done): ");
        } else {
            taskStatusOk = true;
        }
    }
    if ((strcmp(task.status, "To do") == 0 || strcmp(task.status, "Doing")  == 0 || strcmp(task.status, "Done ")  == 0) && strlen(task.description) > 0) {
        printf("\nTodo se ve Ok");
        archivo = fopen("Tasks001.txt", "ab");
        fwrite(&task, sizeof task, 1, archivo);
        fclose(archivo);
    }
}

void updateTareas(){
    int id = -1;
    struct TaskData task;
    FILE *archivo;
    system("cls");
    printf("ACTUALIZACION DE TAREAS\n");
    printf("\tIngrese el id de la tarea: ");
    scanf("%d", &id);
    archivo = fopen("Tasks001.txt", "r+b");
    while (fread(&task, sizeof task, 1, archivo)) {
        printf("\nid: %d", task.id);
        printf("\nDescripcion: %s", task.description);
        printf("\nStatus: %s", task.status);
        if (task.id == id) {
            printf("\nid: %d", task.id);
            printf("\nDescripcion: %s", task.description);
            printf("\nStatus: %s", task.status);
            printf("\tIngrese el nuevo status de la tarea: ");
            fflush(stdin);
            fgets(task.status, sizeof task.status, stdin);
            fflush(stdin);
            if (strcmp(task.status, "Done\n\0")  == 0) {
                task.status[4] = ' ';
            }
            fseek(archivo, -sizeof(task), SEEK_CUR);
            if ((strcmp(task.status, "To do") == 0 || strcmp(task.status, "Doing")  == 0 || strcmp(task.status, "Done ")  == 0) && strlen(task.description) > 0) {
                printf("\nid: %d", task.id);
                printf("\nDescripcion: %s", task.description);
                printf("\nStatus: %s", task.status);
                printf("\nTodo se ve Ok");
                fwrite(&task, sizeof(task), 1, archivo);
                break;
            }
        }
    }
    fclose(archivo);
    fflush(stdin);
    getchar();
}

void reporteTareas(){
    struct TaskData task;
    FILE *archivo;
    system("cls");
    printf("REPORTE DE ESTADO ACTUAL\n");
    archivo = fopen("Tasks001.txt", "r");
    while (fread(&task, sizeof task, 1, archivo)) {
        if (strcmp(task.status, "To do") == 0){
            printf("id: %d \t descripcion: %s \t status: %s\n", task.id, task.description, task.status);
        }
    }
    fclose(archivo);
    archivo = fopen("Tasks001.txt", "r");
    while (fread(&task, sizeof task, 1, archivo)) {
        if (strcmp(task.status, "Doing") == 0){
            printf("id: %d \t descripcion: %s \t status: %s\n", task.id, task.description, task.status);
        }
    }
    fclose(archivo);
    archivo = fopen("Tasks001.txt", "r");
    while (fread(&task, sizeof task, 1, archivo)) {
        if (strcmp(task.status, "Done ") == 0){
            printf("id: %d \t descripcion: %s \t status: %s\n", task.id, task.description, task.status);
        }
    }
    fclose(archivo);
    getchar();
}

int main(int argc, char const *argv[])
{
    int opcion = -1;
    while (opcion != 0) {
        printMenuPrincipal();
        scanf("%i", &opcion);
        fflush(stdin);
        switch (opcion)
        {
            case 1:
                registroTareas();
                break;
            case 2:
                updateTareas();
                break;
            case 3:
                reporteTareas();
                break;
            default:
                break;
        }
    }
    return 0;
}
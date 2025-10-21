# Task-Management-
A minimal and easy to use task management software 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LEN 100
#define FILE_NAME "tasks.txt"

void logo();
void loadTasks(char tasks[][MAX_LEN], int *count, int done[]);
void saveTasks(char tasks[][MAX_LEN], int count, int done[]);
void addTask(char tasks[][MAX_LEN], int *count);
void viewTasks(char tasks[][MAX_LEN], int done[], int count);
void markTaskDone(char tasks[][MAX_LEN], int done[], int count);
void deleteTask(char tasks[][MAX_LEN], int done[], int *count);

int main() {
    char tasks[MAX_TASKS][MAX_LEN];
    int done[MAX_TASKS] = {0};
    int count = 0;
    int choice;

    loadTasks(tasks, &count, done);
    logo();

    while (1) {
        printf("\n---------------------------------------------\n");
        printf("                noèsis.p Menu\n");
        printf("---------------------------------------------\n");
        printf("1. Add a Task\n");
        printf("2. View Tasks\n");
        printf("3. Mark Task as Done\n");
        printf("4. Delete Task\n");
        printf("5. Exit (Save & Quit)\n");
        printf("---------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            addTask(tasks, &count);
            break;
        case 2:
            viewTasks(tasks, done, count);
            break;
        case 3:
            markTaskDone(tasks, done, count);
            break;
        case 4:
            deleteTask(tasks, done, &count);
            break;
        case 5:
            saveTasks(tasks, count, done);
            printf("\nYour tasks are saved successfully!\n");
            printf("Thanks for using noèsis.p\n");
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void logo() {
    printf("\n\n\n");
    printf("=============================================\n");
    printf("                 noèsis.p                   \n");
    printf("=============================================\n");
}

void loadTasks(char tasks[][MAX_LEN], int *count, int done[]) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) return;
    while (fscanf(file, "%[^;];%d\n", tasks[*count], &done[*count]) != EOF) {
        (*count)++;
    }
    fclose(file);
}

void saveTasks(char tasks[][MAX_LEN], int count, int done[]) {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) return;
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s;%d\n", tasks[i], done[i]);
    }
    fclose(file);
}

void addTask(char tasks[][MAX_LEN], int *count) {
    if (*count >= MAX_TASKS) {
        printf("List full! Cannot add more tasks.\n");
        return;
    }
    printf("Enter task: ");
    fgets(tasks[*count], MAX_LEN, stdin);
    tasks[*count][strcspn(tasks[*count], "\n")] = '\0';
    (*count)++;
    printf("Task added successfully!\n");
}

void viewTasks(char tasks[][MAX_LEN], int done[], int count) {
    if (count == 0) {
        printf("No tasks to show.\n");
        return;
    }
    printf("\nYour To-Do List:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. [%c] %s\n", i + 1, done[i] ? '✔' : ' ', tasks[i]);
    }
}

void markTaskDone(char tasks[][MAX_LEN], int done[], int count) {
    int taskNo;
    if (count == 0) {
        printf("No tasks available.\n");
        return;
    }
    viewTasks(tasks, done, count);
    printf("\nEnter task number to mark done: ");
    scanf("%d", &taskNo);
    if (taskNo < 1 || taskNo > count) {
        printf("Invalid task number.\n");
        return;
    }
    done[taskNo - 1] = 1;
    printf("Task marked as done!\n");
}

void deleteTask(char tasks[][MAX_LEN], int done[], int *count) {
    int taskNo;
    if (*count == 0) {
        printf("No tasks to delete.\n");
        return;
    }
    viewTasks(tasks, done, *count);
    printf("\nEnter task number to delete: ");
    scanf("%d", &taskNo);
    if (taskNo < 1 || taskNo > *count) {
        printf("Invalid number.\n");
        return;
    }

    for (int i = taskNo - 1; i < *count - 1; i++) {
        strcpy(tasks[i], tasks[i + 1]);
        done[i] = done[i + 1];
    }
    (*count)--;
    printf("Task deleted successfully!\n");
}

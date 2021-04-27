#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char string[25];
typedef struct User User;

struct User {
    unsigned long int uid;
    string name;
    int age;
    string city;
    struct User *friend_list;
};

void banner();
void mainmenu();

void usermenu();
void adduser();
void searchuser();
void edituser();
void displayuser();
void removeuser();

void friendmenu();
void displayfriendgraph();
void ;

void quit();

int main() {
    banner();

    int pass;
    scanf("%d", &pass);
    if (pass != 13) {
        printf("403 ACCESS DENIED!");
        exit(0);
    }

    mainmenu();
    quit();
}

void banner() {
    system("clear");

    printf("     *********************************       \n");
    printf("     *********************************       \n");
    printf("     **                             **       \n");
    printf("     **           Friends           **       \n");
    printf("     **            Book             **       \n");
    printf("     **                             **       \n");
    printf("     **           Team 13           **       \n");
    printf("     **                             **       \n");
    printf("     *********************************       \n");
    printf("     *********************************       \n");
    printf("\n");
}

void mainmenu() {
    system("clear");

    int ch;

    do {
        printf("     *********************************       \n");
        printf("     *********************************       \n");
        printf("     **                             **       \n");
        printf("     **           Friends           **       \n");
        printf("     **            Book             **       \n");
        printf("     **                             **       \n");
        printf("     **                             **       \n");
        printf("     **          Main Menu          **       \n");
        printf("     **                             **       \n");
        printf("     **     1. User Management      **       \n");
        printf("     **   2. Friends Management     **       \n");
        printf("     **                             **       \n");
        printf("     **    0. Exit Friends Book     **       \n");
        printf("     **                             **       \n");
        printf("     *********************************       \n");
        printf("     *********************************       \n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            usermenu();
            break;
        case 2:
            friendmenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            system("sleep 1");
            mainmenu();
        }
    } while (ch <= 2);
}

void usermenu() {
    system("clear");

    int ch;

    do {
        printf("     *********************************       \n");
        printf("     *********************************       \n");
        printf("     **                             **       \n");
        printf("     **           Friends           **       \n");
        printf("     **            Book             **       \n");
        printf("     **                             **       \n");
        printf("     **                             **       \n");
        printf("     **       User Management       **       \n");
        printf("     **                             **       \n");
        printf("     **         1. Register         **       \n");
        printf("     **        2. Unregister        **       \n");
        printf("     **                             **       \n");
        printf("     **  9. Back to the Main Menu   **       \n");
        printf("     **    0. Exit Friends Book     **       \n");
        printf("     **                             **       \n");
        printf("     *********************************       \n");
        printf("     *********************************       \n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            adduser();
            break;
        case 2:
            removeuser();
            break;
        case 9:
            mainmenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            system("sleep 1");
            usermenu();
        }
    } while (ch <= 9);
}

void friendmenu() {
    system("clear");
}

void quit() {
    system("clear");

    printf("Thank You for visiting us at https://friendsbook.co.in\n");
    exit(0);
}
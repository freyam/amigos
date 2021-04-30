#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "friendsbook.h"

Graph *g;

int main() {
    banner();

    char pass;
    scanf("%c", &pass);
    if (pass != '\'') {
        system("clear");
        printf("403 ACCESS DENIED!\n");
        exit(0);
    }

    g = createGraph(10);

    mainmenu();
    quit();
}

void banner() {
    system("clear");

    printf("  *********************************  \n");
    printf("  *********************************  \n");
    printf("  **                             **  \n");
    printf("  **           Friends           **  \n");
    printf("  **            Book             **  \n");
    printf("  **                             **  \n");
    printf("  **           Team 13           **  \n");
    printf("  **                             **  \n");
    printf("  *********************************  \n");
    printf("  *********************************  \n");
    printf("\n");
}

void mainmenu() {
    system("clear");

    int ch;
    do {
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("  **                             **  \n");
        printf("  **           Friends           **  \n");
        printf("  **            Book             **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **          Main Menu          **  \n");
        printf("  **                             **  \n");
        printf("  **     1. User Management      **  \n");
        printf("  **     2. Friend Management    **  \n");
        printf("  **                             **  \n");
        printf("  **    0. Exit Friends Book     **  \n");
        printf("  **                             **  \n");
        printf("  *********************************  \n");
        printf("  *********************************  \n");
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
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("  **                             **  \n");
        printf("  **           Friends           **  \n");
        printf("  **            Book             **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **       User Management       **  \n");
        printf("  **                             **  \n");
        printf("  **        1. Register          **  \n");
        printf("  **        2. Search            **  \n");
        printf("  **        3. Edit              **  \n");
        printf("  **        4. Display           **  \n");
        printf("  **        5. Unregister        **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **  9. Back to the Main Menu   **  \n");
        printf("  **    0. Exit Friends Book     **  \n");
        printf("  **                             **  \n");
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        User u;
        switch (ch) {
        case 1:
            adduser(g);
            break;
        case 2:
            searchuser(g);
            break;
        case 3:
            edituser(g);
            break;
        case 4:
            displayuser(g);
            break;
        case 5:
            removeuser(g);
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

    int ch;
    do {
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("  **                             **  \n");
        printf("  **           Friends           **  \n");
        printf("  **            Book             **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **      Friend Management      **  \n");
        printf("  **                             **  \n");
        printf("  **       1. Recommend          **  \n");
        printf("  **       2. Check Status       **  \n");
        printf("  **       3. Display Graph      **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **  9. Back to the Main Menu   **  \n");
        printf("  **    0. Exit Friends Book     **  \n");
        printf("  **                             **  \n");
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            recommendfriend();
            break;
        case 2:
            checkfriend();
            break;
        case 3:
            displayfriendgraph();
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

void quit() {
    system("clear");
    printf("Thank You for visiting us at https://friendsbook.co.in!\n");
    exit(0);
}
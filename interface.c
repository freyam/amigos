#include "amigos.h"

extern Graph *g;
extern Heap *h;

void banner() {
    system("clear");

    printf("  *********************************  \n");
    printf("  *********************************  \n");
    printf("  **                             **  \n");
    printf("  **            Amigos           **  \n");
    printf("  **                             **  \n");
    printf("  *********************************  \n");
    printf("  *********************************  \n");
    printf("\n");
}

void mainMenu() {
    system("clear");

    int ch;
    do {
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("  **                             **  \n");
        printf("  **            Amigos           **  \n");
        printf("  **                             **  \n");
        printf("  **          Main Menu          **  \n");
        printf("  **                             **  \n");
        printf("  **     1. User Management      **  \n");
        printf("  **     2. Friend Management    **  \n");
        printf("  **                             **  \n");
        printf("  **       0. Exit Amigos        **  \n");
        printf("  **                             **  \n");
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            userMenu();
            break;
        case 2:
            friendMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            mainMenu();
        }
    } while (ch <= 2);
}

void userMenu() {
    system("clear");

    int ch;
    do {
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("  **                             **  \n");
        printf("  **            Amigos           **  \n");
        printf("  **                             **  \n");
        printf("  **       User Management       **  \n");
        printf("  **                             **  \n");
        printf("  **        1. Register          **  \n");
        printf("  **        2. Search            **  \n");
        printf("  **        3. Edit              **  \n");
        printf("  **        4. Display           **  \n");
        printf("  **        5. Unregister        **  \n");
        printf("  **                             **  \n");
        printf("  **  9. Back to the Main Menu   **  \n");
        printf("  **       0. Exit Amigos        **  \n");
        printf("  **                             **  \n");
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            adduser(g, h);
            break;
        case 2:
            searchMenu(g);
            break;
        case 3:
            editMenu(g);
            break;
        case 4:
            displayUsers(g);
            break;
        case 5:
            removeMenu(g);
            break;
        case 7:
            importData(g);
            break;
        case 9:
            mainMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            userMenu();
        }
    } while (ch <= 9);
}

void searchMenu(Graph *g) {
    system("clear");

    int ch;
    do {
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("  **                             **  \n");
        printf("  **            Amigos           **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **       User Management       **  \n");
        printf("  **                             **  \n");
        printf("  **         Search User         **  \n");
        printf("  **                             **  \n");
        printf("  **     1. Search by UID        **  \n");
        printf("  **     2. Search by Name       **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **  9. Back to the User Menu   **  \n");
        printf("  **       0. Exit Amigos        **  \n");
        printf("  **                             **  \n");
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            searchUID(g);
            break;
        case 2:
            searchName(g);
            break;
        case 9:
            userMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            searchMenu(g);
        }
    } while (ch <= 9);
}

void editMenu(Graph *g) {
    system("clear");

    int ch;
    do {
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("  **                             **  \n");
        printf("  **            Amigos           **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **       User Management       **  \n");
        printf("  **                             **  \n");
        printf("  **          Edit User          **  \n");
        printf("  **                             **  \n");
        printf("  **       1. Edit by UID        **  \n");
        printf("  **       2. Edit by Name       **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **  9. Back to the User Menu   **  \n");
        printf("  **       0. Exit Amigos        **  \n");
        printf("  **                             **  \n");
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            editUID(g);
            break;
        case 2:
            editName(g);
            break;
        case 9:
            userMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            editMenu(g);
        }
    } while (ch <= 9);
}

void removeMenu(Graph *g) {
    system("clear");

    int ch;
    do {
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("  **                             **  \n");
        printf("  **            Amigos           **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **       User Management       **  \n");
        printf("  **                             **  \n");
        printf("  **        Remove User          **  \n");
        printf("  **                             **  \n");
        printf("  **    1. Remove by UID         **  \n");
        printf("  **    2. Remove by Name        **  \n");
        printf("  **                             **  \n");
        printf("  **                             **  \n");
        printf("  **  9. Back to the User Menu   **  \n");
        printf("  **       0. Exit Amigos        **  \n");
        printf("  **                             **  \n");
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            removeUID(g, h);
            break;
        case 2:
            removeName(g, h);
            break;
        case 9:
            userMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            searchMenu(g);
        }
    } while (ch <= 9);
}

void friendMenu() {
    system("clear");

    int ch;
    do {
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("  **                             **  \n");
        printf("  **            Amigos           **  \n");
        printf("  **                             **  \n");
        printf("  **      Friend Management      **  \n");
        printf("  **                             **  \n");
        printf("  **       1. Recommend          **  \n");
        printf("  **       2. Check Status       **  \n");
        printf("  **       3. Display Graph      **  \n");
        printf("  **       4. Display Network    **  \n");
        printf("  **                             **  \n");
        printf("  **  9. Back to the Main Menu   **  \n");
        printf("  **       0. Exit Amigos        **  \n");
        printf("  **                             **  \n");
        printf("  *********************************  \n");
        printf("  *********************************  \n");
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            recommendFriends(g);
            break;
        case 2:
            checkFriendship(g);
            break;
        case 3:
            displayFriendships(g);
            break;
        case 4:
            displayAdjacencyList(g);
            system("dot -Tpng data/graphviz.dot -o data/friendship-g.png && xdg-open data/friendship-g.png");
            break;
        case 9:
            mainMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            userMenu();
        }
    } while (ch <= 9);
}

void quit() {
    system("clear");
    printf("Thank You for visiting us at https://amigos.com/\n");
    exit(0);
}
#include "amigos.h"

extern Graph *g;
extern Heap *h;

void banner() {
    clrscr;

    printf("  *********************************  \n");
    printf("  *********************************  \n");
    printf("  **                             **  \n");
    printf("  **            Amigos           **  \n");
    printf("  **                             **  \n");
    printf("  *********************************  \n");
    printf("  *********************************  \n");
    printf("\n");
}

void mainmenu() {
    clrscr;

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
            usermenu();
            break;
        case 2:
            friendmenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            mainmenu();
        }
    } while (ch <= 2);
}

void usermenu() {
    clrscr;

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
            searchusermenu(g);
            break;
        case 3:
            editusermenu(g);
            break;
        case 4:
            displayusers(g);
            break;
        case 5:
            removeusermenu(g);
            break;
        case 7:
            autofill(g);
            break;
        case 9:
            mainmenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            usermenu();
        }
    } while (ch <= 9);
}

void searchusermenu(Graph *g) {
    clrscr;

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
            searchuserbyuid(g);
            break;
        case 2:
            searchuserbyname(g);
            break;
        case 9:
            usermenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            searchusermenu(g);
        }
    } while (ch <= 9);
}

void editusermenu(Graph *g) {
    clrscr;

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
            edituserbyuid(g);
            break;
        case 2:
            edituserbyname(g);
            break;
        case 9:
            usermenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            editusermenu(g);
        }
    } while (ch <= 9);
}

void removeusermenu(Graph *g) {
    clrscr;

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
            removeuserbyuid(g, h);
            break;
        case 2:
            removeuserbyname(g, h);
            break;
        case 9:
            usermenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            searchusermenu(g);
        }
    } while (ch <= 9);
}

void friendmenu() {
    clrscr;

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
            recommendfriend(g);
            break;
        case 2:
            checkfriend(g);
            break;
        case 3:
            displayFriendshipGraph(g);
            break;
        case 9:
            mainmenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            usermenu();
        }
    } while (ch <= 9);
}

void quit() {
    clrscr;
    printf("Thank You for visiting us at https://amigos.com/\n");
    exit(0);
}
#include "amigos.h"

extern FriendNetwork *network;
extern Heap *token;

#define RESET "\033[0m"
#define RED "\033[1m\033[31m"
#define YELLOW "\033[1m\033[33m"
#define BLUE "\033[1m\033[34m"
#define GREEN "\033[1m\033[32m"

// Provides the User Interface for the Welcome Banner
void banner() {
    system("clear");

    printf(BLUE);
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf("  **                                  **  \n");
    printf("  **              Amigos              **  \n");
    printf("  **                                  **  \n");
    printf("  **************************************  \n");
    printf("  **************************************  \n");
    printf(RESET);
    printf("\n");
}

// Provides the User Interface for the Main Menu
void mainMenu() {
    system("clear");

    int ch;
    do {
        printf(BLUE);
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf("  **                                  **  \n");
        printf("  **              Amigos              **  \n");
        printf("  **                                  **  \n");
        printf("  **            Main Menu             **  \n");
        printf("  **                                  **  \n");
        printf("  **       1. User Management         **  \n");
        printf("  **       2. Friend Management       **  \n");
        printf("  **                                  **  \n");
        printf("  **         0. Exit Amigos           **  \n");
        printf("  **                                  **  \n");
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf(RESET);
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch >= 100)
            error();

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
    } while (ch <= 100);
}

// Provides the User Interface for the User Menu
void userMenu() {
    system("clear");

    int ch;
    do {
        printf(RED);
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf("  **                                  **  \n");
        printf("  **              Amigos              **  \n");
        printf("  **                                  **  \n");
        printf("  **          User Management         **  \n");
        printf("  **                                  **  \n");
        printf("  **        1. Register User          **  \n");
        printf("  **        2. Search User            **  \n");
        printf("  **        3. Edit User              **  \n");
        printf("  **        4. Display User           **  \n");
        printf("  **        5. Unregister User        **  \n");
        printf("  **                                  **  \n");
        printf("  **     9. Back to the Main Menu     **  \n");
        printf("  **          0. Exit Amigos          **  \n");
        printf("  **                                  **  \n");
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf(RESET);
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch >= 100)
            error();

        switch (ch) {
        case 1:
            addUser();
            break;
        case 2:
            searchUserMenu();
            break;
        case 3:
            editUserMenu();
            break;
        case 4:
            displayUserDatabase();
            break;
        case 5:
            removeUserMenu();
            break;
        case 7:
            importData();
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
    } while (ch <= 100);
}

// Provides the User Interface for the Search User Menu
void searchUserMenu() {
    system("clear");

    int ch;
    do {
        printf(RED);
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf("  **                                  **  \n");
        printf("  **              Amigos              **  \n");
        printf("  **                                  **  \n");
        printf("  **          User Management         **  \n");
        printf("  **                                  **  \n");
        printf("  **            Search User           **  \n");
        printf("  **                                  **  \n");
        printf("  **      1. Search User by UID       **  \n");
        printf("  **      2. Search User by Name      **  \n");
        printf("  **                                  **  \n");
        printf("  **     9. Back to the User Menu     **  \n");
        printf("  **          0. Exit Amigos          **  \n");
        printf("  **                                  **  \n");
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf(RESET);
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch >= 100)
            error();

        switch (ch) {
        case 1:
            searchUserUID();
            break;
        case 2:
            searchUserName();
            break;
        case 9:
            userMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            searchUserMenu();
        }
    } while (ch <= 100);
}

// Provides the User Interface for the Edit User Menu
void editUserMenu() {
    system("clear");

    int ch;
    do {
        printf(RED);
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf("  **                                  **  \n");
        printf("  **              Amigos              **  \n");
        printf("  **                                  **  \n");
        printf("  **          User Management         **  \n");
        printf("  **                                  **  \n");
        printf("  **            Edit User             **  \n");
        printf("  **                                  **  \n");
        printf("  **       1. Edit User by UID        **  \n");
        printf("  **       2. Edit User by Name       **  \n");
        printf("  **                                  **  \n");
        printf("  **     9. Back to the User Menu     **  \n");
        printf("  **          0. Exit Amigos          **  \n");
        printf("  **                                  **  \n");
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf(RESET);
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch >= 100)
            error();

        switch (ch) {
        case 1:
            editUserUID();
            break;
        case 2:
            editUserName();
            break;
        case 9:
            userMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            editUserMenu();
        }
    } while (ch <= 100);
}

// Provides the User Interface for the Remove User Menu
void removeUserMenu() {
    system("clear");

    int ch;
    do {
        printf(RED);
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf("  **                                  **  \n");
        printf("  **              Amigos              **  \n");
        printf("  **                                  **  \n");
        printf("  **          User Management         **  \n");
        printf("  **                                  **  \n");
        printf("  **            Remove User           **  \n");
        printf("  **                                  **  \n");
        printf("  **      1. Remove User by UID       **  \n");
        printf("  **      2. Remove User by Name      **  \n");
        printf("  **                                  **  \n");
        printf("  **                                  **  \n");
        printf("  **     9. Back to the User Menu     **  \n");
        printf("  **          0. Exit Amigos          **  \n");
        printf("  **                                  **  \n");
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf(RESET);
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch >= 100)
            error();

        switch (ch) {
        case 1:
            removeUserUID();
            break;
        case 2:
            removeUserName();
            break;
        case 9:
            userMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            searchUserMenu();
        }
    } while (ch <= 100);
}

// Provides the User Interface for the Friends Menu
void friendMenu() {
    system("clear");

    int ch;
    do {
        printf(YELLOW);
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf("  **                                  **  \n");
        printf("  **              Amigos              **  \n");
        printf("  **                                  **  \n");
        printf("  **         Friend Management        **  \n");
        printf("  **                                  **  \n");
        printf("  **      1. Add Friendship           **  \n");
        printf("  **      2. Recommend Friends        **  \n");
        printf("  **      3. Check Friendship         **  \n");
        printf("  **      4. Display Friendships      **  \n");
        printf("  **      5. Remove Friendship        **  \n");
        printf("  **                                  **  \n");
        printf("  **     9. Back to the Main Menu     **  \n");
        printf("  **          0. Exit Amigos          **  \n");
        printf("  **                                  **  \n");
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf(RESET);
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch >= 100)
            error();

        switch (ch) {
        case 1:
            addFriendMenu();
            break;
        case 2:
            recommendFriendsMenu();
            break;
        case 3:
            checkFriendMenu();
            break;
        case 4:
            displayFriendsMenu();
            break;
        case 5:
            removeFriendMenu();
            break;
        case 9:
            mainMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            friendMenu();
        }
    } while (ch <= 100);
}

// Provides the User Interface for the Add Friend Menu
void addFriendMenu() {
    system("clear");

    int ch;
    do {
        printf(YELLOW);
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf("  **                                  **  \n");
        printf("  **              Amigos              **  \n");
        printf("  **                                  **  \n");
        printf("  **         Friend Management        **  \n");
        printf("  **                                  **  \n");
        printf("  **          Add Friendship          **  \n");
        printf("  **                                  **  \n");
        printf("  **    1. Add Friendship by UIDs     **  \n");
        printf("  **    2. Add Friendship by Names    **  \n");
        printf("  **                                  **  \n");
        printf("  **    9. Back to the Friend Menu    **  \n");
        printf("  **          0. Exit Amigos          **  \n");
        printf("  **                                  **  \n");
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf(RESET);
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch >= 100)
            error();

        switch (ch) {
        case 1:
            addFriendshipUID();
            break;
        case 2:
            addFriendshipName();
            break;
        case 9:
            friendMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            friendMenu();
        }
    } while (ch <= 100);
}

// Provides the User Interface for the Recommend Friend Menu
void recommendFriendsMenu() {
    system("clear");

    int ch;
    do {
        printf(YELLOW);
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf("  **                                  **  \n");
        printf("  **              Amigos              **  \n");
        printf("  **                                  **  \n");
        printf("  **         Friend Management        **  \n");
        printf("  **                                  **  \n");
        printf("  **         Recommend Friends        **  \n");
        printf("  **                                  **  \n");
        printf("  **      1. To a New User            **  \n");
        printf("  **      2. To an Existing User      **  \n");
        printf("  **                                  **  \n");
        printf("  **    9. Back to the Friend Menu    **  \n");
        printf("  **          0. Exit Amigos          **  \n");
        printf("  **                                  **  \n");
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf(RESET);
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch >= 100)
            error();

        switch (ch) {
        case 1:
            recommendFriendsNewUser();
            break;
        case 2:
            recommendFriendsExistingUser();
            break;
        case 9:
            friendMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            friendMenu();
        }
    } while (ch <= 100);
}

// Provides the User Interface for the Check Friend Menu
void checkFriendMenu() {
    system("clear");

    int ch;
    do {
        printf(YELLOW);
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf("  **                                  **  \n");
        printf("  **              Amigos              **  \n");
        printf("  **                                  **  \n");
        printf("  **         Friend Management        **  \n");
        printf("  **                                  **  \n");
        printf("  **         Check Friendship         **  \n");
        printf("  **                                  **  \n");
        printf("  **    1. Check Friendship by UID    **  \n");
        printf("  **    2. Check Friendship by Name   **  \n");
        printf("  **                                  **  \n");
        printf("  **    9. Back to the Friend Menu    **  \n");
        printf("  **          0. Exit Amigos          **  \n");
        printf("  **                                  **  \n");
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf(RESET);
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch >= 100)
            error();

        switch (ch) {
        case 1:
            checkFriendshipUID();
            break;
        case 2:
            checkFriendshipName();
            break;
        case 9:
            friendMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            friendMenu();
        }
    } while (ch <= 100);
}

// Provides the User Interface for the Display Friend Menu
void displayFriendsMenu() {
    system("clear");

    int ch;
    do {
        printf(YELLOW);
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf("  **                                  **  \n");
        printf("  **              Amigos              **  \n");
        printf("  **                                  **  \n");
        printf("  **         Friend Management        **  \n");
        printf("  **                                  **  \n");
        printf("  **        Display Friendships       **  \n");
        printf("  **                                  **  \n");
        printf("  **    1. Display Adjacency List     **  \n");
        printf("  **    2. Display Friends Network    **  \n");
        printf("  **                                  **  \n");
        printf("  **    9. Back to the Friend Menu    **  \n");
        printf("  **          0. Exit Amigos          **  \n");
        printf("  **                                  **  \n");
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf(RESET);
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch >= 100)
            error();

        switch (ch) {
        case 1:
            displayFriendshipNetwork();
            break;
        case 2:
            ViewFriendshipNetwork();
            break;
        case 9:
            friendMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            friendMenu();
        }
    } while (ch <= 100);
}

// Provides the User Interface for the Remove Friend Menu
void removeFriendMenu() {
    system("clear");

    int ch;
    do {
        printf(YELLOW);
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf("  **                                  **  \n");
        printf("  **              Amigos              **  \n");
        printf("  **                                  **  \n");
        printf("  **         Friend Management        **  \n");
        printf("  **                                  **  \n");
        printf("  **         Remove Friendship        **  \n");
        printf("  **                                  **  \n");
        printf("  **   1. Remove Friendship by UIDs   **  \n");
        printf("  **   2. Remove Friendship by Names  **  \n");
        printf("  **                                  **  \n");
        printf("  **    9. Back to the Friend Menu    **  \n");
        printf("  **          0. Exit Amigos          **  \n");
        printf("  **                                  **  \n");
        printf("  **************************************  \n");
        printf("  **************************************  \n");
        printf(RESET);
        printf("\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        if (ch >= 100)
            error();

        switch (ch) {
        case 1:
            removeFriendshipUID();
            break;
        case 2:
            removeFriendshipName();
            break;
        case 9:
            friendMenu();
            break;
        case 0:
            quit();
        default:
            printf("Invalid Choice!\n");
            friendMenu();
        }
    } while (ch <= 100);
}

// Provides the User Interface for the Error Screen
void error() {
    system("clear");
    printf(BLUE);
    printf("Critical Error! Bootstrapping the Program.\n");
    printf("Visit us again at https://amigos.com/\n");
    printf(RESET);
    exit(EXIT_FAILURE);
}

// Provides the User Interface for the Exit Screen
void quit() {
    system("clear");
    printf(GREEN);
    printf("Application Exited Successfully\n");
    printf("Thank You for visiting us at https://amigos.com/\n");
    printf(RESET);
    exit(EXIT_SUCCESS);
}
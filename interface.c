#include "amigos.h"

extern Graph *g;
extern Heap *h;

void banner() {
	system("clear");

	printf("  **************************************  \n");
	printf("  **************************************  \n");
	printf("  **                                  **  \n");
	printf("  **              Amigos              **  \n");
	printf("  **                                  **  \n");
	printf("  **************************************  \n");
	printf("  **************************************  \n");
	printf("\n");
}

void mainMenu() {
	system("clear");

	int ch;
	do {
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
	} while (ch <= 100);
}

void userMenu() {
	system("clear");

	int ch;
	do {
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
		printf("\n");

		printf("Enter your choice: ");
		scanf("%d", &ch);

		switch (ch) {
		case 1:
			addUser(g, h);
			break;
		case 2:
			searchUserMenu(g);
			break;
		case 3:
			editUserMenu(g);
			break;
		case 4:
			displayUserDatabase(g);
			break;
		case 5:
			removeUserMenu(g);
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
	} while (ch <= 100);
}

void searchUserMenu(Graph *g) {
	system("clear");

	int ch;
	do {
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
		printf("\n");

		printf("Enter your choice: ");
		scanf("%d", &ch);

		switch (ch) {
		case 1:
			searchUserUID(g);
			break;
		case 2:
			searchUserName(g);
			break;
		case 9:
			userMenu();
			break;
		case 0:
			quit();
		default:
			printf("Invalid Choice!\n");
			searchUserMenu(g);
		}
	} while (ch <= 100);
}

void editUserMenu(Graph *g) {
	system("clear");

	int ch;
	do {
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
		printf("\n");

		printf("Enter your choice: ");
		scanf("%d", &ch);

		switch (ch) {
		case 1:
			editUserUID(g);
			break;
		case 2:
			editUserName(g);
			break;
		case 9:
			userMenu();
			break;
		case 0:
			quit();
		default:
			printf("Invalid Choice!\n");
			editUserMenu(g);
		}
	} while (ch <= 100);
}

void removeUserMenu(Graph *g) {
	system("clear");

	int ch;
	do {
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
		printf("\n");

		printf("Enter your choice: ");
		scanf("%d", &ch);

		switch (ch) {
		case 1:
			removeUserUID(g, h);
			break;
		case 2:
			removeUserName(g, h);
			break;
		case 9:
			userMenu();
			break;
		case 0:
			quit();
		default:
			printf("Invalid Choice!\n");
			searchUserMenu(g);
		}
	} while (ch <= 100);
}

void friendMenu() {
	system("clear");

	int ch;
	do {
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
		printf("  **                                  **  \n");
		printf("  **     9. Back to the Main Menu     **  \n");
		printf("  **          0. Exit Amigos          **  \n");
		printf("  **                                  **  \n");
		printf("  **************************************  \n");
		printf("  **************************************  \n");
		printf("\n");

		printf("Enter your choice: ");
		scanf("%d", &ch);

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

void addFriendMenu() {
	system("clear");

	int ch;
	do {
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
		printf("\n");

		printf("Enter your choice: ");
		scanf("%d", &ch);

		switch (ch) {
		case 1:
			addFriendshipUID(g);
			break;
		case 2:
			addFriendshipName(g);
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

void recommendFriendsMenu() {
	system("clear");

	int ch;
	do {
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
		printf("  **      2. To an Existing User	    **  \n");
		printf("  **                                  **  \n");
		printf("  **    9. Back to the Friend Menu    **  \n");
		printf("  **          0. Exit Amigos          **  \n");
		printf("  **                                  **  \n");
		printf("  **************************************  \n");
		printf("  **************************************  \n");
		printf("\n");

		printf("Enter your choice: ");
		scanf("%d", &ch);

		switch (ch) {
		case 1:
			recommendFriendsNewUser(g);
			break;
		case 2:
			recommendFriendsExistingUser(g);
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

void checkFriendMenu() {
	system("clear");

	int ch;
	do {
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
		printf("\n");

		printf("Enter your choice: ");
		scanf("%d", &ch);

		switch (ch) {
		case 1:
			checkFriendshipUID(g);
			break;
		case 2:
			checkFriendshipName(g);
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

void displayFriendsMenu() {
	system("clear");

	int ch;
	do {
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
		printf("\n");

		printf("Enter your choice: ");
		scanf("%d", &ch);

		switch (ch) {
		case 1:
			displayFriendsAdjacencyList(g);
			break;
		case 2:
			ViewFriendshipNetwork(g);
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

void quit() {
	system("clear");
	printf("Thank You for visiting us at https://amigos.com/\n");
	exit(0);
}
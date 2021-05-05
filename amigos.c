#include "amigos.h"

int minUID = 1;

Graph *g;
Heap *h;
int V = 1000;

// Adds Password Checker
void authorization() {
	string pass;
	gets(pass);
	if (strcmp(pass, "team13")) {
		system("clear");
		printf("403 ACCESS DENIED!\n");
		exit(0);
	}
}

// Initializes the Necessary Functions and Data Structures
void initialize() {
	srand(time(0));

	g = createGraph(V);
	h = createHeap(V);

	importData(g);
}

// Finds the minimum UID for a new user
int findUID(Heap *h) {
	if (h->count == 0 || minUID <= h->arr[0])
		return minUID++;
	else
		return PopMin(h);
}

// Creates the Friendship Network
Graph *createGraph(int V) {
	Graph *g = malloc(sizeof(Graph));
	g->V = V;

	g->adjList = malloc(V * sizeof(User *));
	g->visited = malloc(V * sizeof(bool));

	for (int i = 0; i < V; i++) {
		g->adjList[i] = NULL;
		g->visited[i] = 0;
	}

	return g;
}

// Creates a new User Node
User *createUser(User u) {
	User *newUser = malloc(sizeof(User));

	newUser->uid = u.uid;
	strcpy(newUser->name, u.name);
	strcpy(newUser->age, u.age);
	strcpy(newUser->gender, u.gender);
	strcpy(newUser->email, u.email);
	strcpy(newUser->ip, u.ip);
	strcpy(newUser->job_title, u.job_title);
	strcpy(newUser->location, u.location);
	newUser->next = NULL;

	return newUser;
}

// Adds a new User to the Friendship Network
void addUser(Graph *g, Heap *h) {
	User u;
	u.uid = findUID(h);
	printf("Enter the details of User [%03d]\n", u.uid);
	printf("Name: ");
	gets(u.name);
	printf("Age: ");
	gets(u.age);
	printf("Gender: ");
	gets(u.gender);
	printf("Email: ");
	gets(u.email);
	printf("IP Address: ");
	gets(u.ip);
	printf("Job Title: ");
	gets(u.job_title);
	printf("Location: ");
	gets(u.location);

	g->adjList[u.uid] = createUser(u);
	printUser(*(g->adjList[u.uid]));
}

// Imports a User Database from UserDatabase.csv
void importData(Graph *g) {
	system("clear");

	int entries = 50;  // max 1000
	char buffer;

	if (access("data/UserDatabase.csv", F_OK)) {
		system("make import");
	}

	FILE *f = fopen("data/UserDatabase.csv", "r");

	string header;
	fscanf(f, "%[^\n]s", header);

	for (int i = 1; i <= entries; ++i) {
		User u;

		fscanf(f, "%d", &u.uid);
		fscanf(f, "%c", &buffer);
		fscanf(f, "%[^,]s", u.name);
		fscanf(f, "%c", &buffer);
		fscanf(f, "%[^,]s", u.gender);
		fscanf(f, "%c", &buffer);
		fscanf(f, "%[^,]s", u.age);
		fscanf(f, "%c", &buffer);
		fscanf(f, "%[^,]s", u.email);
		fscanf(f, "%c", &buffer);
		fscanf(f, "%[^,]s", u.ip);
		fscanf(f, "%c", &buffer);
		fscanf(f, "%[^,]s", u.job_title);
		fscanf(f, "%c", &buffer);
		fscanf(f, "%[^\n]s", u.location);

		g->adjList[minUID++] = createUser(u);
	}

	for (int i = 1; i <= entries * 2; ++i) {
		int u = (rand() % entries) + 1;
		int v = (rand() % entries) + 1;

		if (u != v)
			addFriendship(g, *g->adjList[u], *g->adjList[v]);
	}

	fclose(f);
}

// Prints User Information
void printUser(User u) {
	printf("[%03d] %20s | %3s | %1s | %30s | %15s | %30s | %s\n",
		   u.uid, u.name, u.age, u.gender, u.email, u.ip, u.job_title, u.location);
}

// Searches a User by UID
void searchUserUID(Graph *g) {
	system("clear");

	int uid;
	printf("Enter the UID: ");
	scanf("%d", &uid);

	if (g->adjList[uid])
		printUser(*(g->adjList[uid]));
	else
		printf("EROR 404: USER ID #%d NOT FOUND!\n", uid);

	printf("\n");
}

// Searches a User by Name
void searchUserName(Graph *g) {
	system("clear");

	bool found = 0;

	string name;
	printf("Enter the Name: ");
	gets(name);

	for (int i = 0; i < g->V; ++i)
		if (g->adjList[i] && !strcmp(g->adjList[i]->name, name)) {
			printUser(*(g->adjList[i]));
			found = 1;
			break;
		}

	if (!found)
		printf("ERROR 404: USER \"%s\" NOT FOUND.", name);

	printf("\n");
}

// Edits User by UID
void editUserUID(Graph *g) {
	system("clear");

	int uid;
	printf("Enter the UID: ");
	scanf("%d", &uid);

	if (g->adjList[uid]) {
		printUser(*(g->adjList[uid]));
		printf("\n");

		printf("Enter the new details\n");
		printf("Name: ");
		gets(g->adjList[uid]->name);
		printf("Age: ");
		gets(g->adjList[uid]->age);
		printf("Gender: ");
		gets(g->adjList[uid]->gender);
		printf("Email: ");
		gets(g->adjList[uid]->email);
		printf("IP Address: ");
		gets(g->adjList[uid]->ip);
		printf("Job Title: ");
		gets(g->adjList[uid]->job_title);
		printf("Location: ");
		gets(g->adjList[uid]->location);

		printf("Edited.\n");
		printUser(*(g->adjList[uid]));
	} else
		printf("EROR 404: USER ID #%d NOT FOUND!\n", uid);

	printf("\n");
}

// Edits User by Name
void editUserName(Graph *g) {
	system("clear");

	bool found = 0;

	string name;
	printf("Enter the Name: ");
	gets(name);

	for (int i = 0; i < g->V; ++i)
		if (g->adjList[i] && !strcmp(g->adjList[i]->name, name)) {
			printUser(*(g->adjList[i]));
			printf("\n");

			printf("Enter the new details\n");
			printf("Name: ");
			gets(g->adjList[i]->name);
			printf("Age: ");
			gets(g->adjList[i]->age);
			printf("Gender: ");
			gets(g->adjList[i]->gender);
			printf("Email: ");
			gets(g->adjList[i]->email);
			printf("IP Address: ");
			gets(g->adjList[i]->ip);
			printf("Job Title: ");
			gets(g->adjList[i]->job_title);
			printf("Location: ");
			gets(g->adjList[i]->location);

			printf("Edited.\n");
			printUser(*(g->adjList[i]));
			found = 1;
			break;
		}

	if (!found)
		printf("ERROR 404: USER \"%s\" NOT FOUND.", name);

	printf("\n");
}

// Displays the User Database
void displayUserDatabase(Graph *g) {
	system("clear");

	bool found = 0;
	printf("-------------------------------------------------------");
	printf("-------------------------------------------------------");
	printf("-------------------------------------------------------\n");
	for (int i = 1; i <= g->V; ++i)
		if (g->adjList[i]) {
			if (!found)
				found = 1;
			printUser(*(g->adjList[i]));
		}

	if (!found)
		printf("User Database is Empty!\n");

	printf("-------------------------------------------------------");
	printf("-------------------------------------------------------");
	printf("-------------------------------------------------------\n");

	printf("\n");
	getchar();
	getchar();
}

// Removes User by UID
void removeUserUID(Graph *g, Heap *h) {
	system("clear");

	int uid;
	printf("Enter the UID: ");
	scanf("%d", &uid);

	if (g->adjList[uid]) {
		printUser(*(g->adjList[uid]));
		printf("Confirm Delete (y/n)? ");
		char c, buff;
		scanf("%c%c", &buff, &c);
		if (c != 'n') {
			printf("Deleted!\n");
			insertHeap(h, uid);
			g->adjList[uid]->uid = 0;
			strcpy(g->adjList[uid]->name, "");
			strcpy(g->adjList[uid]->age, "");
			strcpy(g->adjList[uid]->gender, "");
			strcpy(g->adjList[uid]->location, "");
			g->adjList[uid] = NULL;
		} else {
			printf("Skipped!\n");
		}
	} else
		printf("EROR 404: USER ID #%d NOT FOUND!\n", uid);

	printf("\n");
}

// Removes User by Name
void removeUserName(Graph *g, Heap *h) {
	system("clear");

	bool found = 0;

	string name;
	printf("Enter the Name: ");
	gets(name);

	for (int i = 0; i < g->V; ++i)
		if (g->adjList[i] && !strcmp(g->adjList[i]->name, name)) {
			printUser(*(g->adjList[i]));
			printf("Confirm Delete (y/n)? ");
			char c, buff;
			scanf("%c%c", &buff, &c);

			if (c != 'n') {
				printf("Deleted!\n");
				insertHeap(h, i);
				strcpy(g->adjList[i]->age, "");
				g->adjList[i]->uid = INT_MAX;
				strcpy(g->adjList[i]->name, "");
				strcpy(g->adjList[i]->location, "");
				g->adjList[i] = NULL;
				found = 1;
			} else {
				printf("Skipped!\n");
			}
			break;
		}

	if (!found)
		printf("ERROR 404: USER \"%s\" NOT FOUND.", name);

	printf("\n");
}

// Adds a Frienship to the Network
void addFriendship(Graph *g, User u, User v) {
	User *newUser = createUser(v);
	newUser->next = g->adjList[u.uid]->next;
	g->adjList[u.uid]->next = newUser;
}

void addFriendshipUID(Graph *g) {}
void addFriendshipName(Graph *g) {}

void recommendFriendsNewUser(Graph *g) {}
void recommendFriendsExistingUser(Graph *g) {}

void checkFriendshipUID(Graph *g) {
	system("clear");

	int uid1, uid2;
	printf("Enter the 2 UIDs\n");
	scanf("%d %d", &uid1, &uid2);

	if (g->adjList[uid1] == NULL || g->adjList[uid2] == NULL) {
		printf("ERROR 404: USER(S) NOT FOUND!\n");
		return;
	}

	bool friend12 = 0;
	User *temp = g->adjList[uid1]->next;
	while (temp)
		if (!strcmp(temp->name, g->adjList[uid2]->name)) {
			friend12 = 1;
			break;
		} else {
			temp = temp->next;
		}

	bool friend21 = 0;
	temp = g->adjList[uid2]->next;
	while (temp)
		if (!strcmp(temp->name, g->adjList[uid1]->name)) {
			friend21 = 1;
			break;
		} else {
			temp = temp->next;
		}

	if (friend12 && friend21)
		printf("%s and %s are Mutual Friends.\n", g->adjList[uid1]->name, g->adjList[uid2]->name);
	else if (friend12)
		printf("%s considers %s to be a friend.\n", g->adjList[uid1]->name, g->adjList[uid2]->name);
	else if (friend21)
		printf("%s considers %s to be a friend.\n", g->adjList[uid2]->name, g->adjList[uid1]->name);
	else
		printf("%s and %s are not Friends.\n", g->adjList[uid1]->name, g->adjList[uid2]->name);

	printf("\n");
}

void checkFriendshipName(Graph *g) {
	system("clear");

	string name1, name2;
	printf("Enter the 2 Names\n");
	gets(name1);
	gets(name2);

	int uid1 = 0;
	int uid2 = 0;

	for (int i = 0; i < g->V; ++i)
		if (uid1 && uid2)
			break;
		else if (g->adjList[i] && !strcmp(g->adjList[i]->name, name1))
			uid1 = i;
		else if (g->adjList[i] && !strcmp(g->adjList[i]->name, name2))
			uid2 = i;

	if (g->adjList[uid1] == NULL || g->adjList[uid2] == NULL) {
		printf("ERROR 404: USER(S) NOT FOUND!\n");
		return;
	}

	bool friend12 = 0;
	User *temp = g->adjList[uid1]->next;
	while (temp)
		if (!strcmp(temp->name, g->adjList[uid2]->name)) {
			friend12 = 1;
			break;
		} else {
			temp = temp->next;
		}

	bool friend21 = 0;
	temp = g->adjList[uid2]->next;
	while (temp)
		if (!strcmp(temp->name, g->adjList[uid1]->name)) {
			friend21 = 1;
			break;
		} else {
			temp = temp->next;
		}

	if (friend12 && friend21)
		printf("%s and %s are Mutual Friends.\n", g->adjList[uid1]->name, g->adjList[uid2]->name);
	else if (friend12)
		printf("%s considers %s to be a friend.\n", g->adjList[uid1]->name, g->adjList[uid2]->name);
	else if (friend21)
		printf("%s considers %s to be a friend.\n", g->adjList[uid2]->name, g->adjList[uid1]->name);
	else
		printf("%s and %s are not Friends.\n", g->adjList[uid1]->name, g->adjList[uid2]->name);

	printf("\n");
}

// Displays the Frienship Network
void displayFriendsAdjacencyList(Graph *g) {
	system("clear");

	bool found = 0;

	printf("-------------------------------------------------------");
	printf("-------------------------------------------------------");
	printf("-------------------------------------------------------\n");

	for (int i = 0; i < g->V; ++i) {
		if (g->adjList[i]) {
			if (!found)
				found = 1;
			User *temp = g->adjList[i];
			printf("Friends of [%03d] %25s: ", temp->uid, temp->name);
			temp = temp->next;
			while (temp) {
				printf("[%03d]%s", temp->uid, temp->name);
				temp = temp->next;
				if (temp)
					printf(", ");
			}
			printf("\n");
		}
	}

	if (!found)
		printf("User Database is Empty!\n");

	printf("-------------------------------------------------------");
	printf("-------------------------------------------------------");
	printf("-------------------------------------------------------\n");

	printf("\n");
}

//  Writes the Adjacency List for Network Visualization in DOT
void writeFriendshipNetwork(Graph *g) {
	system("clear");
	FILE *f = fopen("data/graphviz.dot", "w");

	fprintf(f, "digraph AmigosFriendNetwork {\n");
	fprintf(f, "\tnode [fontname=\"Consolas\", shape=oval, style=filled, color=\".7 .3 1.0\"];\n");

	for (int i = 1; i <= g->V; ++i) {
		if (g->adjList[i]) {
			User *temp = g->adjList[i];
			fprintf(f, "\t\"%s\" -> ", temp->name);
			temp = temp->next;
			while (temp) {
				fprintf(f, "\"%s\"", temp->name);
				temp = temp->next;
				if (temp)
					fprintf(f, " -> ");
			}
			fprintf(f, "\n");
		}
	}
	fprintf(f, "}");
	fclose(f);
}

void ViewFriendshipNetwork(Graph *g) {
	writeFriendshipNetwork(g);
	system("dot -Tpng data/graphviz.dot -o data/friendship-network.png && xdg-open data/friendship-network.png");
}
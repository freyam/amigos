#include "friendsbook.h"

Graph *g;
Heap *h;

int main() {
    banner();

    // string pass;
    // scanf("%s", pass);
    // if (strcmp(pass, "frey")) {
    //     clrscr;
    //     printf("403 ACCESS DENIED!\n");
    //     exit(0);
    // }

    g = createGraph(100);
    h = createHeap(100);

    mainmenu();
}
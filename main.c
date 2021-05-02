#include "amigos.h"

Graph *g;
Heap *h;

int main() {
    banner();

    // string pass;
    // scanf("%s", pass);
    // if (strcmp(pass, "team13")) {
    //     clrscr;
    //     printf("403 ACCESS DENIED!\n");
    //     exit(0);
    // }

    g = createGraph(100);
    h = createHeap(100);

    system("sleep 1");

    mainmenu();
}
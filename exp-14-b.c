//FILE ORGANIZATION TECHNIQUE - TWO LEVEL DIRECTORY
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

#define MAX_LINKS 5

struct TreeElement {
    char name[20];
    int x, y, ftype, leftX, rightX, numChildren, level;
    struct TreeElement *links[MAX_LINKS];
};

typedef struct TreeElement Node;

void create(Node **root, int level, char *directoryName, int leftX, int rightX, int x);
void display(Node *root);

int main() {
    int graphicsDriver = DETECT, graphicsMode;
    Node *root = NULL;

    // Clear the screen and create the tree
    create(&root, 0, "null", 0, 639, 320);

    // Initialize graphics mode
    initgraph(&graphicsDriver, &graphicsMode, "C:\\tc\\bgi");

    // Display the tree
    display(root);

    getch();
    closegraph();

    return 0;
}

void create(Node **root, int level, char *directoryName, int leftX, int rightX, int x) {
    int i, gap;

    if (*root == NULL) {
        *root = (Node*)malloc(sizeof(Node));

        printf("Enter the name of directory/file (parent: %s): ", directoryName);
        fflush(stdin);
        gets((*root)->name);

        (*root)->ftype = (level == 0 || level == 1) ? 1 : 2;
        (*root)->level = level;
        (*root)->y = 50 + level * 50;
        (*root)->x = x;
        (*root)->leftX = leftX;
        (*root)->rightX = rightX;

        for (i = 0; i < MAX_LINKS; i++) {
            (*root)->links[i] = NULL;
        }

        if ((*root)->ftype == 1) {
            if (level == 0) {
                printf("How many users: ");
            } else {
                printf("How many files (for %s): ", (*root)->name);
            }
            scanf("%d", &(*root)->numChildren);
        } else {
            (*root)->numChildren = 0;
        }

        if ((*root)->numChildren == 0) {
            gap = rightX - leftX;
        } else {
            gap = (rightX - leftX) / (*root)->numChildren;
        }

        for (i = 0; i < (*root)->numChildren; i++) {
            create(&((*root)->links[i]), level + 1, (*root)->name, leftX + gap * i, leftX + gap * (i + 1), leftX + gap * i + gap / 2);
        }
    }
}

void display(Node *root) {
    int i;

    settextstyle(2, 0, 4);
    settextjustify(1, 1);
    setfillstyle(1, BLUE);
    setcolor(14);

    if (root != NULL) {
        for (i = 0; i < root->numChildren; i++) {
            line(root->x, root->y, root->links[i]->x, root->links[i]->y);
        }

        if (root->ftype == 1) {
            bar3d(root->x - 20, root->y - 10, root->x + 20, root->y + 10, 0, 0);
        } else {
            fillellipse(root->x, root->y, 20, 20);
        }

        outtextxy(root->x, root->y, root->name);

        for (i = 0; i < root->numChildren; i++) {
            display(root->links[i]);
        }
    }
}

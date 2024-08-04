//FILE ORGANIZATION TECHNIQUE - //SINGLE LEVEL DIRECTORY
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

int main() {
    int graphicsDriver = DETECT, graphicsMode;
    int numFiles, fileIndex, lineIndex, midPoint, circleX;
    char fileNames[10][20];

    // Initialize the graphics mode
    initgraph(&graphicsDriver, &graphicsMode, "");

    // Clear the screen and set the background color
    cleardevice();
    setbkcolor(GREEN);

    // Prompt user for the number of files
    printf("Enter number of files: ");
    scanf("%d", &numFiles);

    // Loop through and get file names
    for (fileIndex = 0; fileIndex < numFiles; fileIndex++) {
        cleardevice();
        setbkcolor(GREEN);

        // Prompt for file name
        printf("Enter file name %d: ", fileIndex + 1);
        scanf("%s", fileNames[fileIndex]);

        // Draw root directory bar
        setfillstyle(1, MAGENTA);
        bar3d(270, 100, 370, 150, 0, 0);

        // Set text style and print "root directory"
        settextstyle(2, 0, 4);
        settextjustify(1, 1);
        outtextxy(320, 125, "root directory");

        // Calculate mid position and draw lines and circles
        midPoint = 640 / numFiles;
        circleX = midPoint / 3;

        for (lineIndex = 0; lineIndex <= fileIndex; lineIndex++, circleX += midPoint) {
            line(320, 150, circleX, 250);
            fillellipse(circleX, 250, 30, 30);
            outtextxy(circleX, 250, fileNames[lineIndex]);
        }
    }

    getch();
    closegraph();
    return 0;
}

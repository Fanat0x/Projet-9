#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define gridMaxX 10
#define gridMaxY 10

typedef struct tile {
    char* status;
    int danger;
    int proximity;
    int flag;
}tile;

void displayGrid(tile tableau[10][10]);
void randomGrid(tile tableau[10][10], int bombe);
int proximity(tile tableau[10][10], int x, int y);
void initTile(tile tableau[10][10]);

int main(int argc, char** argv)
{
    srand(time(NULL));
    tile tableau[10][10];
    initTile(tableau);


    displayGrid(tableau);

    int bombe = 10;
    randomGrid(tableau, bombe);
    displayGrid(tableau);

    return 0;
}



int proximity(tile tableau[10][10], int x, int y)
{   
    int proxy = 0;

        if (tableau[x - 1] <= gridMaxX && tableau[y - 1] <= gridMaxY)
        {
            if (tableau[x][y].danger == 1)
            proxy++;
        }
        else if (tableau[x - 1] <= gridMaxX && tableau[y] <= gridMaxY)
        {
            if (tableau[x][y].danger == 1)
            proxy++;
        }
        else if (tableau[x - 1] <= gridMaxX && tableau[y + 1] <= gridMaxY)
        {
            if (tableau[x][y].danger == 1)
            proxy++;
        }
        else if (tableau[x] <= gridMaxX && tableau[y - 1] <= gridMaxY)
        {
            if (tableau[x][y].danger == 1)
            proxy++;
        }
        else if (tableau[x] <= gridMaxX && tableau[y + 1] <= gridMaxY)
        {
            if (tableau[x][y].danger == 1)
            proxy++;
        }
        else if (tableau[x + 1] <= gridMaxX && tableau[y - 1] <= gridMaxY)
        {
            if (tableau[x][y].danger == 1)
            proxy++;
        }
        else if (tableau[x + 1] <= gridMaxX && tableau[y] <= gridMaxY)
        {
            if (tableau[x][y].danger == 1)
            proxy++;
        }
        else if (tableau[x + 1] <= gridMaxX && tableau[y + 1] <= gridMaxY)
        {
            if (tableau[x][y].danger == 1)
            proxy++;
        }
        return proxy;

}

void initTile(tile tableau[10][10])
{   
    for (int x = 0; x < 10; x++) 
    {
        for (int y = 0; y < 10; y++) 
        {
            tableau[x][y].status = "hidden";
            tableau[x][y].danger = 0;
            tableau[x][y].flag = 0;
            tableau[x][y].proximity = proximity(tableau, x, y);
        }
    }
}

//a refaire avec la struct
void displayGrid( tile tableau[10][10])
{
    int i = 0;
    int y = 0;
    printf("\n-----------------------------------------\n");
    for (i = 0; i < 10; i++) {
        printf("|");
        for (y = 0; y < 10; y++) {
            if (tableau[i][y].status == "hidden" && tableau[i][y].flag == 1)
                printf(" P |");
            else if (tableau[i][y].status == "hidden")
                printf(" - |");
            else if (tableau[i][y].status == "revealed" && tableau[i][y].danger == 1)
                printf(" * |");
            else if (tableau[i][y].status == "revealed")
                printf("   |");



        }
        printf("\n-----------------------------------------\n");
    }
}

void randomGrid( tile tableau[10][10], int bombe)
{
    
    for (int i = 0; i < 10; i++) {
        int x = rand() % 10;
        int y = rand() % 10;
        if (tableau[x][y].danger == 1)
        {
            i--;
            continue;
        }
        else
        {
            printf("bombe = %d  %d \n", x+1, y+1);
            tableau[x][y].danger = 1;
        }
    }
}
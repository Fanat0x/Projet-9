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

void displayGrid(tile tableau[gridMaxX][gridMaxY]);
void randomGrid(tile tableau[gridMaxX][gridMaxY], int bombe);
int proximity(tile tableau[gridMaxX][gridMaxY]);
void initTile(tile tableau[gridMaxX][gridMaxY]);
void turn(tile tableau[gridMaxX][gridMaxY]);
void displayGridEnd(tile tableau[gridMaxX][gridMaxY]);
void reveal(tile tableau[gridMaxX][gridMaxY], int x, int y);
void displayGridProxy(tile tableau[gridMaxX][gridMaxY]);
int inTable(int x, int y, int MaxX, int MaxY);
int win(tile tableau[gridMaxX][gridMaxY]);


int main(int argc, char** argv)
{
    srand(time(NULL));
    tile tableau[gridMaxX][gridMaxY];
    initTile(tableau);
    int bombe = 10;
    randomGrid(tableau, bombe);
    proximity(tableau);
    displayGridProxy(tableau);
    displayGrid(tableau);

    turn(tableau);

    return 0;
}



int proximity(tile tableau[gridMaxX][gridMaxY])
{
    for (int x = 0; x < gridMaxX; x++)
    {
        for (int y = 0; y < gridMaxY; y++)
        {
            int proxy = 0;

            if (inTable(x - 1, y - 1,gridMaxX, gridMaxY ) == 1)
            {
                if (tableau[x - 1][y - 1].danger == 1)
                {
                    proxy++;
                } 
            }
            if (inTable(x - 1, y, gridMaxX, gridMaxY) == 1)
            {
                if (tableau[x - 1][y].danger == 1)
                {
                    proxy++;
                }
            }
            if (inTable(x - 1, y + 1, gridMaxX, gridMaxY) == 1)
            {
                if (tableau[x - 1][y + 1].danger == 1)
                {
                    proxy++;
                }
            }
            if (inTable(x, y - 1, gridMaxX, gridMaxY) == 1)
            {
                if (tableau[x][y - 1].danger == 1)
                {
                    proxy++;
                }
            }
            if (inTable(x, y + 1, gridMaxX, gridMaxY) == 1)
            {
                if (tableau[x][y + 1].danger == 1)
                {
                    proxy++;
                }
            }
            if (inTable(x + 1, y - 1, gridMaxX, gridMaxY) == 1)
            {
                if (tableau[x + 1][y - 1].danger == 1)
                {
                    proxy++;
                }
            }
            if (inTable(x + 1, y, gridMaxX, gridMaxY) == 1)
            {
                if (tableau[x + 1][y].danger == 1)
                {
                    proxy++;
                }
            }
            if (inTable(x + 1, y + 1, gridMaxX, gridMaxY) == 1)
            {
                if (tableau[x + 1 ][y + 1].danger == 1)
                {
                    proxy++;
                }
            }
            tableau[x][y].proximity = proxy;
        }
            
    }
    
}


int inTable(int x,int  y, int MaxX, int MaxY)
{
    if ( x >= 0 && x < MaxX && y >= 0 && y <  MaxY )
    {
        return 1;
    }
    
    return 0;
}

void initTile(tile tableau[gridMaxX][gridMaxY])
{   
    for (int x = 0; x < 10; x++) 
    {
        for (int y = 0; y < 10; y++) 
        {
            tableau[x][y].status = "hidden";
            tableau[x][y].danger = 0;
            tableau[x][y].flag = 0;
        }
    }
}

//a refaire avec la struct
void displayGrid( tile tableau[gridMaxX][gridMaxY])
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
            else if (tableau[i][y].status == "revealed" && tableau[i][y].proximity == 0)
                printf("   |");
            else if (tableau[i][y].status == "revealed" && tableau[i][y].proximity > 0)
                printf(" %d |", tableau[i][y].proximity);
        }
        printf("\n-----------------------------------------\n");
    }
}

void randomGrid( tile tableau[gridMaxX][gridMaxY], int bombe)
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

void turn(tile tableau[gridMaxX][gridMaxY])
{
    
    int grandX = 0;
    printf("Indiquez une coordonnee X (1 a 10) : ");
    scanf_s("%d", &grandX);
    int grandY = 0;
    printf("Indiquez une coordonnee Y (1 a 10) : ");
    scanf_s("%d", &grandY);



    printf("[%d,", grandX);
    printf("%d]\n", grandY);

    int x = grandX - 1;
    int y = grandY - 1;


    if (inTable(x, y, gridMaxX, gridMaxY) == 1 && x===1 && y===1)
    {
        if (tableau[x][y].status == "revealed")
        {
            printf("Cette case à deja ete revelee\n");
            turn(tableau);
        }
        else if (tableau[x][y].danger == 1)
        {
            displayGridEnd(tableau);
            printf("Vous avez clique sur une mine, perdu !\n");
        }
        else
        {
            reveal(tableau, x, y);
            if (win(tableau) == 1)
            {
                printf("Bravo, vous avez gagne\n");
            }
            else
            {
                displayGrid(tableau);
                turn(tableau);
            }
        }
    }
    else
    {
        printf("Ces coordonees n'existent pas \n");
        turn(tableau);
    }
}

void displayGridEnd(tile tableau[gridMaxX][gridMaxY])
{
    printf("\n-----------------------------------------\n");
    for (int i = 0; i < 10; i++) {
        printf("|");
        for (int y = 0; y < 10; y++) {
            if (tableau[i][y].danger == 0 && tableau[i][y].flag == 1)
                printf(" X |");
            else if (tableau[i][y].danger == 1 && tableau[i][y].flag == 1)
                printf(" P |");
            else if (tableau[i][y].danger == 1)
                printf(" * |");
            else if (tableau[i][y].status == "hidden")
                printf(" - |");
            else if (tableau[i][y].status == "revealed")
                printf("   |");
        }
        printf("\n-----------------------------------------\n");
    }
}

int win(tile tableau[gridMaxX][gridMaxY])
{
    int count = 0;
    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            if (tableau[x][y].status == "revealed" && tableau[x][y].danger == 0)
            {
                count++;
            }
        }
    }
    if (count == 90)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void reveal(tile tableau[gridMaxX][gridMaxY], int x, int y)
{
    if (inTable(x, y, gridMaxX, gridMaxY) == 0 )
        return;

    if (tableau[x][y].status == "revealed")
        return;

    tableau[x][y].status = "revealed";

    if (tableau[x][y].proximity != 0)
        return;

    reveal(tableau, x - 1, y - 1);
    reveal(tableau, x - 1, y);
    reveal(tableau, x - 1, y + 1);

    reveal(tableau, x, y - 1);
    reveal(tableau, x, y + 1);

    reveal(tableau, x + 1, y - 1);
    reveal(tableau, x + 1, y);
    reveal(tableau, x + 1, y + 1);


}

void displayGridProxy(tile tableau[gridMaxX][gridMaxY])
{
    int i = 0;
    int y = 0;
    printf("\n-----------------------------------------\n");
    for (i = 0; i < 10; i++) {
        printf("|");
        for (y = 0; y < 10; y++) {
            if (tableau[i][y].danger == 1)
                printf(" * |");
            else
                printf(" %d |", tableau[i][y].proximity);
        }
        printf("\n-----------------------------------------\n");
    }
}
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
void turn(tile tableau[10][10]);
void displayGridEnd(tile tableau[10][10]);
void reveal(tile tableau[10][10], int x, int y);


int main(int argc, char** argv)
{
    srand(time(NULL));
    tile tableau[10][10];
    initTile(tableau);


    displayGrid(tableau);

    int bombe = 10;
    randomGrid(tableau, bombe);
    displayGrid(tableau);

    turn(tableau);

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
            else if (tableau[i][y].status == "revealed" && tableau[i][y].proximity == 0)
                printf("   |");
            else if (tableau[i][y].status == "revealed" && tableau[i][y].proximity > 0)
                printf(" %d |", tableau[i][y].proximity);
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

void turn(tile tableau[10][10])
{
    
    int grandX = 0;
    printf("Indiquez une coordonnée X (1 à 10)");
    scanf_s("%d", grandX);
    int grandY = 0;
    printf("Indiquez une coordonnée Y (1 à 10)");
    scanf_s("%d", grandY);
    int coordonnée[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    if (grandX == coordonnée && grandY == coordonnée)
    {
        if (tableau[grandX][grandY].status == "revealed")
        {
            printf("Cette case à déjà été révelée");
            turn(tableau);
        }
        else if (tableau[grandX][grandY].danger == 1)
        {
            displayGridEnd(tableau);
            printf("Vous avez cliqué sur une mine, perdu !");
        }
        else
        {
            tableau[grandX][grandY].status = "revealed";
            if (win(tableau) == 1)
            {
                printf("Bravo, vous avez gagné");
            }
            else
            {
                reveal(tableau, grandX, grandY);
                turn(tableau);
            }
        }
    }
    else
    {
        printf("Ces coordonées n'existent pas");
        turn(tableau);
    }
}

void displayGridEnd(tile tableau[10][10])
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

int win(tile tableau[10][10])
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

void reveal(tile tableau[10][10], int x, int y)
{
    if (tableau[x - 1] <= gridMaxX && tableau[y - 1] <= gridMaxY)
    {
        if (tableau[x - 1][y - 1].proximity == 0)
        {
            tableau[x - 1][y - 1].status = "revealed";
            reveal(tableau, x - 1, y - 1);
        }
        else
        {
            tableau[x - 1][y - 1].status = "revealed";
        }
    }

    if (tableau[x - 1] <= gridMaxX && tableau[y] <= gridMaxY)
    {
        if (tableau[x - 1][y].proximity == 0)
        {
            tableau[x - 1][y].status = "revealed";
            reveal(tableau, x - 1, y);
        }
        else
        {
            tableau[x - 1][y].status = "revealed";
        }
    }

    if (tableau[x - 1] <= gridMaxX && tableau[y + 1] <= gridMaxY)
    {
        if (tableau[x - 1][y + 1].proximity == 0)
        {
            tableau[x - 1][y + 1].status = "revealed";
            reveal(tableau, x - 1, y + 1);
        }
        else
        {
            tableau[x - 1][y + 1].status = "revealed";
        }
    }

    if (tableau[x] <= gridMaxX && tableau[y - 1] <= gridMaxY)
    {
        if (tableau[x][y - 1].proximity == 0)
        {
            tableau[x][y - 1].status = "revealed";
            reveal(tableau, x, y - 1);
        }
        else
        {
            tableau[x][y - 1].status = "revealed";
        }
    }

    if (tableau[x] <= gridMaxX && tableau[y + 1] <= gridMaxY)
    {
        if (tableau[x][y + 1].proximity == 0)
        {
            tableau[x][y + 1].status = "revealed";
            reveal(tableau, x, y + 1);
        }
        else
        {
            tableau[x][y + 1].status = "revealed";
        }
    }

    if (tableau[x + 1] <= gridMaxX && tableau[y - 1] <= gridMaxY)
    {
        if (tableau[x + 1][y - 1].proximity == 0)
        {
            tableau[x + 1][y - 1].status = "revealed";
            reveal(tableau, x + 1, y - 1);
        }
        else
        {
            tableau[x + 1][y - 1].status = "revealed";
        }
    }

    if (tableau[x + 1] <= gridMaxX && tableau[y] <= gridMaxY)
    {
        if (tableau[x + 1][y].proximity == 0)
        {
            tableau[x + 1][y].status = "revealed";
            reveal(tableau, x + 1, y);
        }
        else
        {
            tableau[x + 1][y].status = "revealed";
        }
    }

    if (tableau[x + 1] <= gridMaxX && tableau[y + 1] <= gridMaxY)
    {
        if (tableau[x + 1][y + 1].proximity == 0)
        {
            tableau[x + 1][y + 1].status = "revealed";
            reveal(tableau, x + 1, y + 1);
        }
        else
        {
            tableau[x + 1][y + 1].status = "revealed";
        }
    }


}
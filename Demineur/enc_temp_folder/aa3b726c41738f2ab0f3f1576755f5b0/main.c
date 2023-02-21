#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void displayGrid(unsigned char tableau[10][10]);
void randomGrid(unsigned char tableau[10][10], int bombe);

int main(int argc, char** argv)
{
    srand(time(NULL));
    unsigned char tableau[10][10] = { 0 };

    displayGrid(tableau);

    int bombe = 10;
    randomGrid(tableau, bombe);
    displayGrid(tableau);

    return 0;
}
struct tile {
    const int x ; 
};

void displayGrid(unsigned char tableau[10][10])
{
    int i = 0;
    int y = 0;
    printf("\n-----------------------------------------\n");
    for (i = 0; i < 10; i++) {
        printf("|");
        for (y = 0; y < 10; y++) {
            if (tableau[i][y] == "")
                printf(" %d |", tableau[i][y]);
        }
        printf("\n-----------------------------------------\n");//a
    }
}

void randomGrid(unsigned char tableau[10][10], int bombe)
{
    
    for (int i = 0; i < 10; i++) {
        int x = rand() % 10;
        int y = rand() % 10;
        if (tableau[x][y] == 1)
        {
            i--;
            continue;
        }
        else
        {
            printf("bombe = %d  %d \n", x+1, y+1);
            tableau[x][y] = 9;
        }
    }
}
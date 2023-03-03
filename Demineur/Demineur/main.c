//Import des différentes librairies C nécessaires

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Définition de la taille maximale du tableau

#define gridMaxX 10
#define gridMaxY 10
#define bombe 10

//Définition des paramètres des cases en structure

typedef struct tile {
    char* status;
    int danger;
    int proximity;
    int flag;
    int start;
}tile;

//Initialisation de différentes fontions

void displayGrid(tile tableau[gridMaxX][gridMaxY]);
void randomGrid(tile tableau[gridMaxX][gridMaxY], int x, int y);
void proximity(tile tableau[gridMaxX][gridMaxY]);
void initTile(tile tableau[gridMaxX][gridMaxY]);
void turn(tile tableau[gridMaxX][gridMaxY]);
void displayGridEnd(tile tableau[gridMaxX][gridMaxY]);
void reveal(tile tableau[gridMaxX][gridMaxY], int x, int y);
//void displayGridProxy(tile tableau[gridMaxX][gridMaxY]);
int inTable(int x, int y, int MaxX, int MaxY);
int win(tile tableau[gridMaxX][gridMaxY]);
void action(tile tableau[gridMaxX][gridMaxY], int x, int y, int action_type);
void firstTurn(tile tableau[gridMaxX][gridMaxY]);
int safeZone(tile tableau[gridMaxX][gridMaxY], int x, int y);
void displayGridLose(tile tableau[gridMaxX][gridMaxY]);

//Fonction main éxécutant le jeu

int main(int argc, char** argv)
{
    srand(time(NULL));
    tile tableau[gridMaxX][gridMaxY];
    firstTurn(tableau, bombe);
    //displayGridProxy(tableau);
    displayGrid(tableau);
    turn(tableau);

    return 0;
}

//Fonction firstTurn permettant de placer les bombes après le premier coup joué

void firstTurn(tile tableau[gridMaxX][gridMaxY])
{
    initTile(tableau);
    displayGrid(tableau);
    int grandX = 0;
    printf("Indiquez une coordonnee X (1 a 10) : ");

    if (scanf_s("%d", &grandX) == 0)
    {
        printf("Coordonnees incorrectes\n");
        firstTurn(tableau, bombe);
    }
    while (getchar() != '\n');
    grandX--;

    int grandY = 0;
    printf("Indiquez une coordonnee Y (1 a 10) : ");

    if (scanf_s("%d", &grandY) == 0)
    {
        printf("Coordonnees incorrectes\n");
        firstTurn(tableau, bombe);
    }
    while (getchar() != '\n');
    grandY--;

    randomGrid(tableau, grandX, grandY);
    proximity(tableau);
    reveal(tableau, grandX, grandY);
}

//Fonction proximity affichant le nombre de bombes autour de chaque case

void proximity(tile tableau[gridMaxX][gridMaxY])
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

//Fonction inTable vérifiant si chaque coup joué est présent dans le tableau

int inTable(int x,int  y, int MaxX, int MaxY)
{
    if ( x >= 0 && x < MaxX && y >= 0 && y <  MaxY )
    {
        return 1;
    }
    else 
    {
        return 0;
    }
    
}

//Fonction initTile cachant le statut de toutes les cases

void initTile(tile tableau[gridMaxX][gridMaxY])
{   
    for (int x = 0; x < 10; x++) 
    {
        for (int y = 0; y < 10; y++) 
        {
            tableau[x][y].status = "hidden";
            tableau[x][y].danger = 0;
            tableau[x][y].flag = 0;
            tableau[x][y].start = 0;
        }
    }
}

//Fonction displayGrid affichant le tableau avec les différentes propriétés de chaque case

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

//Fonction displayGridLose affichant le tableau après la défaite du joueur

void displayGridLose(tile tableau[gridMaxX][gridMaxY])
{
    int i = 0;
    int y = 0;
    printf("\n-----------------------------------------\n");
    for (i = 0; i < 10; i++) {
        printf("|");
        for (y = 0; y < 10; y++) {
            if (tableau[i][y].status == "hidden" && tableau[i][y].flag == 1)
                printf(" P |");
            else if (tableau[i][y].danger == 1)
                printf(" * |");
            else if (tableau[i][y].status == "hidden")
                printf(" - |");
            else if (tableau[i][y].status == "revealed" && tableau[i][y].proximity == 0)
                printf("   |");
            else if (tableau[i][y].status == "revealed" && tableau[i][y].proximity > 0)
                printf(" %d |", tableau[i][y].proximity);
        }
        printf("\n-----------------------------------------\n");
    }
}

//Fonction randomGrid plaçant 10 bombes aléatoirement dans le tableau

void randomGrid( tile tableau[gridMaxX][gridMaxY], int x,int y)
{   
    int bombeOn = 0;
    int safeCases = safeZone(tableau, x, y);
    int matrix = gridMaxX * gridMaxY - safeCases;
    while (bombeOn < 10)
    {
        matrix = matrix - bombeOn;
        bombeOn++;
        int placeBombe = rand() % matrix;
        for (int i = 0; i < 10; i++)
        {
            if (placeBombe < 0)
            {
                break;
            }
            else
            {
                for (int y = 0; y < 10; y++)
                {
                    if (tableau[i][y].danger == 0 && tableau[i][y].start == 0)
                    {

                        if (placeBombe == 0)
                        {
                            tableau[i][y].danger = 1;
                            placeBombe--;
                            break;
                        }
                        else
                        {
                            placeBombe--;
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
            } 
        }
    }  
}

//Fonction safeZone permettant de ne pas avoir de bombes autour de la case jouée au premier tour

int safeZone(tile tableau[gridMaxX][gridMaxY],int x, int y)
{   
    tableau[x][y].start = 1;
    int caseCount = 1;
    if (inTable(x - 1, y - 1, gridMaxX, gridMaxY) == 1)
    {
        tableau[x - 1][y - 1].start = 1;
        caseCount++;
    }
    if (inTable(x - 1, y, gridMaxX, gridMaxY) == 1)
    {
        tableau[x - 1][y].start = 1;
        caseCount++;
    }
    if (inTable(x - 1, y + 1, gridMaxX, gridMaxY) == 1)
    {
        tableau[x - 1][y + 1].start = 1;
        caseCount++;
    }
    if (inTable(x, y - 1, gridMaxX, gridMaxY) == 1)
    {
        tableau[x][y - 1].start = 1;
        caseCount++;
    }
    if (inTable(x, y + 1, gridMaxX, gridMaxY) == 1)
    {
        tableau[x][y + 1].start = 1;
        caseCount++;
        printf("%d", tableau[x][y + 1].start);
    }
    if (inTable(x + 1, y - 1, gridMaxX, gridMaxY) == 1)
    {
        tableau[x + 1][y - 1].start = 1;
        caseCount++;
    }
    if (inTable(x + 1, y, gridMaxX, gridMaxY) == 1)
    {
        tableau[x + 1][y].start = 1;
        caseCount++;
    }
    if (inTable(x + 1, y + 1, gridMaxX, gridMaxY) == 1)
    {
        tableau[x + 1][y + 1].start = 1;
        caseCount++;
    }
    return caseCount;
}

//Fonction turn permettant de jouer chaque tour de jeu

void turn(tile tableau[gridMaxX][gridMaxY])
{
    int action_type;
    printf("Entrez 1 si vous souhaitez reveler une case ou entrez 2 si vous souhaitez placer un drapeau: ");
    if (scanf_s("%d", &action_type) == 0 || action_type != 1 && action_type != 2)
    {
        printf("Action incorrecte\n");
        turn(tableau);
    }
    while (getchar() != '\n');

    int grandX = 0;
    printf("Indiquez une coordonnee X (1 a 10) : ");
    
    if (scanf_s("%d", &grandX) == 0)
    {
        printf("Coordonnees incorrectes\n");
        turn(tableau);
    }
    while (getchar() != '\n');

    int grandY = 0;
    printf("Indiquez une coordonnee Y (1 a 10) : ");

    if (scanf_s("%d", &grandY) == 0)
    {
        printf("Coordonnees incorrectes\n");
        turn(tableau);
    }
    while (getchar() != '\n');

    int x = grandX - 1;
    int y = grandY - 1;

    action(tableau, x, y, action_type);
}

//Fonction action annonçant si la case peut être joué

void action(tile tableau[gridMaxX][gridMaxY], int x, int y, int action_type)
{
    if (inTable(x, y, gridMaxX, gridMaxY) == 1 && action_type == 1)
    {
        if (tableau[x][y].status == "revealed")
        {
            printf("Cette case à deja ete revelee\n");
            turn(tableau);
        }
        else if (tableau[x][y].danger == 1)
        {
            displayGridLose(tableau);
            printf("Vous avez clique sur une mine, perdu !\n");
        }
        else
        {
            reveal(tableau, x, y);
            if (win(tableau) == 1)
            {
                displayGridEnd(tableau);
                printf("Bravo, vous avez gagne\n");
            }
            else
            {
                displayGrid(tableau);
                turn(tableau);
            }
        }
    }
    else if (inTable(x, y, gridMaxX, gridMaxY) == 1 && action_type == 2)
    {
        if (tableau[x][y].status == "revealed")
        {
            printf("Cette case à deja ete revelee\n");
            turn(tableau);
        }
        else
        {
            tableau[x][y].flag = 1;
            displayGrid(tableau);
            turn(tableau);
        }
    }
    else
    {
        printf("Ces coordonees n'existent pas \n");
        turn(tableau);
    }
}

//Fonction displayGridEnd affichant le tableau après la fin de la partie

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

//Fonction win calculant si le joueur a gagné la partie

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
    if (count == gridMaxX * gridMaxY - bombe)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Fonction reveal créant les cases vides entre les bombes et les proximity

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

//void displayGridProxy(tile tableau[gridMaxX][gridMaxY])
//{
//    int i = 0;
//    int y = 0;
//    printf("\n-----------------------------------------\n");
//    for (i = 0; i < 10; i++) {
//        printf("|");
//        for (y = 0; y < 10; y++) {
//            
//            
//            if (tableau[i][y].danger == 1)
//            {
//                printf(" * |");
//            }
//
//            else if (tableau[i][y].status == "revealed" && tableau[i][y].proximity == 0)
//            {
//                printf("   |");
//            }
//            else
//            {
//                printf(" %d |", tableau[i][y].proximity);
//            }
//        }
//        printf("\n-----------------------------------------\n");
//    }
//}
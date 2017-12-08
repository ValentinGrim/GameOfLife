//
//  main.c
//  GameOfLife By Conway.
//  Ce jeu c'est la vie
//  Created by Valentin Monnot on 22/11/2017.
//  ESIEA Laval TD Info.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>

int height, width, iter, patern, voisin;
char **grid, **tmpgrid;


int Menu(void)
{
 
    printf("Hauteur de la grille = ");
    scanf("%d", &height);
    
    printf("Largeur = ");
    scanf("%d", &width);
    
    printf("Choix du patern de début (4 pour menu aléatoire) :\n\n 1    2    3\n     █ █  ███\n███  █ █    █\n     ███   █\n\n: ");
    scanf("%d", &patern);
    
    if(patern == 4)
       {
           
           printf("Choix du patern aléatoire :\n\n5 - Aléatoire complet\n6 - Aléatoire avec symétrie vertical\n7 - Aléatoire avec symétrie horizontal\n\n: ");
           scanf("%d", &patern);
           
       }
    
    return 0;
    
}

int AllocFamilliale(void)
{
    
    grid = (char**) calloc(height, sizeof(char*));
    for (int i=0; i<height; i++)
    {
        grid[i] = (char*)calloc(width, sizeof(char));
        
    }
    
    tmpgrid = (char**) calloc(height, sizeof(char*));
    for (int i=0; i<height; i++)
    {
        tmpgrid[i] = (char*)calloc(width, sizeof(char));
        
    }
    
    int AllHeight = height / 2;
    int AllWidth = width / 2;
    
    switch(patern)
    {
            
        case 1:
            for(int a = 0; a < height; a++)
            {
             
                for(int b = 0; b < width; b++)
                {
                 
                    grid[a][b] = ' ';
                    
                }
            }
            
            grid[AllHeight][AllWidth] = '#';
            grid[AllHeight][AllWidth-1] = '#';
            grid[AllHeight][AllWidth+1] = '#';
            break;
        
        case 2:
            for(int a = 0; a < height; a++)
            {
                
                for(int b = 0; b < width; b++)
                {
                    
                    grid[a][b] = ' ';
                    
                }
            }
            
            grid[AllHeight-1][AllWidth-1] = '#';
            grid[AllHeight-1][AllWidth+1] = '#';
            grid[AllHeight][AllWidth-1] = '#';
            grid[AllHeight][AllWidth+1] = '#';
            grid[AllHeight+1][AllWidth-1] = '#';
            grid[AllHeight+1][AllWidth] = '#';
            grid[AllHeight+1][AllWidth+1] = '#';
            break;
            
        case 3:
            for(int a = 0; a < height; a++)
            {
                
                for(int b = 0; b < width; b++)
                {
                    
                    grid[a][b] = ' ';
                    
                }
            }
            
            grid[AllHeight-1][AllWidth-1] = '#';
            grid[AllHeight-1][AllWidth] = '#';
            grid[AllHeight-1][AllWidth+1] = '#';
            grid[AllHeight][AllWidth+1] = '#';
            grid[AllHeight+1][AllWidth] = '#';
            break;
            
        case 5:
            for(int a = 0; a < height; a++)
            {
                
                for(int b = 0; b < width; b++)
                {
                    
                    int alea = (rand() % (3 - 1 + 1)) + 1;
                    
                    switch(alea)
                    {
                        
                        case 1:
                            grid[a][b] = ' ';
                            break;
                            
                        case 2:
                            grid[a][b] = '#';
                            break;
                        
                        case 3:
                            grid[a][b] = ' ';
                            break;
                        
                    }
                }
            }
            break;
            
        case 6:
            for(int a = 0; a < height ; a++)
            {
                
                for(int b = 0; b < width / 2; b++)
                {
                    
                    int alea = (rand() % (3 - 1 +1)) +1;
                    
                    switch(alea)
                    {
                            
                        case 1:
                            grid[a][b] = ' ';
                            break;
                            
                        case 2:
                            grid[a][b] = '#';
                            break;
                            
                        case 3:
                            grid[a][b] = ' ';
                            break;
                            
                    }
                }
            }

            
            for(int a = 0; a < height ; a++)
            {
                
                int c  = width / 2;
                
                for (int b = width / 2 ; b < width ; b++)
                {
                    
                    c--;
                    grid[a][b] = grid[a][c];
                    
                }
            }
            break;
            
            case 7:
            for(int a = 0; a <= height / 2 ; a++)
            {
                
                for(int b = 0; b < width ; b++)
                {
                    
                    int alea = (rand() % (3 - 1 +1)) +1;
                    
                    switch(alea)
                    {
                            
                        case 1:
                            grid[a][b] = ' ';
                            break;
                            
                        case 2:
                            grid[a][b] = '#';
                            break;
                            
                        case 3:
                            grid[a][b] = ' ';
                            break;
                            
                    }
                }
            }
            
            for(int a = 0; a < width ; a++)
            {
                
                int c  = height / 2;
                
                for (int b = height / 2 ; b < height ; b++)
                {
                    
                    c--;
                    grid[b][a] = grid[c][a];
                    
                }
            }
            

            break;
            
    }

    return 0;
}

int TesDedansOuPo(int x, int y)
{
    
    int YorN = 1;
    
    if(x <= 0 || x >= height)
    {
        
        YorN = 0;
        
    }
    
    if (y <= 0 || y >= width)
    {
        
        YorN = 0;
        
    }
    
    return YorN;
    
}

int QuiEstLa(int x, int y)
{

    int YorN, YenACcombien = 0;
    
    for(int a = x-1; a <= x+1; a++)
    {
        
        for(int b = y-1; b <= y+1; b++)
        {
            
            if(a == x && b == y)
            {
                
            }
            
            else
            {
                
                YorN = TesDedansOuPo(a, b);
                
                if(YorN == 1)
                {
                    
                    if(grid[a][b] == '#')
                    {
                        
                        YenACcombien++;
                        
                    }
                }
            }
        }
    }
 
    return YenACcombien;
    
}

int DrawMyLife(void)
{
    
    system("clear");
    
    for(int i = 0; i < width + 2; i++)
    {
        
        printf("_");
        
    }
    
    printf("\n");
    
    for(int a = 0; a < height; a++)
    {
        
        printf("|");
        
        for(int b = 0; b < width; b++)
        {
            
            if( grid[a][b] == '#')
            {
                
                printf("█");

            }
            
            else
            {
                
                printf(" ");
                
            }
            
        }
        
        printf("|");
        printf("\n");
    }
    
    
    int AH = 2;
    
    if (width > 20)
    {
        AH = width/10;
        
    }
    
    for(int i = 0; i < width + 2 ; i++)
    {
        
        printf("‾");
        
    }
    
    printf("\n");
    
    return 0;
    
}

void ReDrawMyLife (void)
{
    
    for(int a = 0; a < height; a++)
    {
        
        for(int b = 0; b < width; b++)
        {
            
            if(grid[a][b] == '#')
            {
                
                voisin = QuiEstLa(a, b);
                
                switch(voisin)
                {
                        
                    case 2:
                        tmpgrid[a][b] = '#';
                        break;
                        
                    case 3:
                        tmpgrid[a][b] = '#';
                        break;
                        
                    default:
                        tmpgrid[a][b] = ' ';
                        break;
                        
                }
            }
            
            if(grid[a][b] == ' ')
            {
             
                voisin = QuiEstLa(a, b);
                
                switch(voisin)
                {
                        
                    case 3:
                        tmpgrid[a][b] = '#';
                        break;
                        
                    default:
                        tmpgrid[a][b] = ' ';
                        break;
                }
            }
        }
    }
    
    for(int a = 0; a < height; a++)
    {
        
        for(int b = 0; b < width; b++)
        {
            
            grid[a][b] = tmpgrid[a][b];
            
        }
    }
}



int main()
{
    srand((int)time(NULL));
    
    Menu();
    AllocFamilliale();

    int i = 1;
    
    while(i == 1)
    {

        char detect = '&';
        scanf("%c", &detect);
    
        switch(detect)
        {
          
            case '&':
                break;
    
    
            case 's':
                i = 0;
                break;
            
            default:
                DrawMyLife();
                ReDrawMyLife();
            
        }

    }
    
}

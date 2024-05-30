//
//  main.c
//  GameOfLife By Conway.
//  Created by Valentin Monnot on 22/11/2017.
//  ESIEA Laval TD Info.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>

int height, width, iter, patern, neighbour;
char **grid, **tmpgrid;

int main_menu(void)
{
    printf("Grid height = ");
    scanf("%d", &height);

    printf("Grid width = ");
    scanf("%d", &width);

    printf("Choose your pattern (choose 4 for random menu) :\n\n 1    2    3\n");
    printf("     █ █  ███\n███  █ █    █\n     ███   █\n\n: ");
    scanf("%d", &patern);

    if (patern == 4) {
        printf("Choose your random pattern :\n\n5 - Full random\n6 - Random with vertical symmetry\n");
        printf("7 - Random with horizontal symmetry\n\n: ");
        scanf("%d", &patern);
    }
    return 0;
}

int mem_alloc(void)
{
    grid = (char **)calloc(height, sizeof(char *));
    for (int i = 0; i < height; i++) {
        grid[i] = (char *)calloc(width, sizeof(char));
    }

    tmpgrid = (char **)calloc(height, sizeof(char *));
    for (int i = 0; i < height; i++) {
        tmpgrid[i] = (char *)calloc(width, sizeof(char));
    }

    int AllHeight = height / 2;
    int AllWidth = width / 2;

    switch (patern) {
        case 1:
            for (int a = 0; a < height; a++) {
                for (int b = 0; b < width; b++) {
                    grid[a][b] = ' ';
                }
            }
            grid[AllHeight][AllWidth] = '#';
            grid[AllHeight][AllWidth - 1] = '#';
            grid[AllHeight][AllWidth + 1] = '#';
            break;

        case 2:
            for (int a = 0; a < height; a++) {
                for (int b = 0; b < width; b++) {
                    grid[a][b] = ' ';
                }
            }

            grid[AllHeight - 1][AllWidth - 1] = '#';
            grid[AllHeight - 1][AllWidth + 1] = '#';
            grid[AllHeight][AllWidth - 1] = '#';
            grid[AllHeight][AllWidth + 1] = '#';
            grid[AllHeight + 1][AllWidth - 1] = '#';
            grid[AllHeight + 1][AllWidth] = '#';
            grid[AllHeight + 1][AllWidth + 1] = '#';
            break;

        case 3:
            for (int a = 0; a < height; a++) {
                for (int b = 0; b < width; b++) {
                    grid[a][b] = ' ';
                }
            }

            grid[AllHeight - 1][AllWidth - 1] = '#';
            grid[AllHeight - 1][AllWidth] = '#';
            grid[AllHeight - 1][AllWidth + 1] = '#';
            grid[AllHeight][AllWidth + 1] = '#';
            grid[AllHeight + 1][AllWidth] = '#';
            break;

        case 5:
            for (int a = 0; a < height; a++) {
                for (int b = 0; b < width; b++) {
                    int random = (rand() % (3 - 1 + 1)) + 1;
                    switch (random) {
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
            for (int a = 0; a < height; a++) {
                for (int b = 0; b < width / 2; b++) {
                    int random = (rand() % (3 - 1 + 1)) + 1;
                    switch (random) {
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

            for (int a = 0; a < height; a++) {
                int c = width / 2;
                for (int b = width / 2; b < width; b++) {
                    c--;
                    grid[a][b] = grid[a][c];
                }
            }
            break;

        case 7:
            for (int a = 0; a <= height / 2; a++) {
                for (int b = 0; b < width; b++) {
                    int random = (rand() % (3 - 1 + 1)) + 1;
                    switch (random) {
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

            for (int a = 0; a < width; a++) {
                int c = height / 2;
                for (int b = height / 2; b < height; b++) {
                    c--;
                    grid[b][a] = grid[c][a];
                }
            }
            break;
    }
    return 0;
}

int is_in(int x, int y)
{
    int fake_bool = 1;

    if (x <= 0 || x >= height) {
        fake_bool = 0;
    }

    if (y <= 0 || y >= width) {
        fake_bool = 0;
    }

    return fake_bool;
}

int whos_there(int x, int y)
{
    int fake_bool, how_many = 0;

    for (int a = x - 1; a <= x + 1; a++) {
        for (int b = y - 1; b <= y + 1; b++) {
            if (a == x && b == y) {
            } else {
                fake_bool = is_in(a, b);
                if (fake_bool == 1) {
                    if (grid[a][b] == '#') {
                        how_many++;
                    }
                }
            }
        }
    }

    return how_many;
}

int draw(void)
{
    system("clear");

    for (int i = 0; i < width + 2; i++) {
        printf("_");
    }
    printf("\n");

    for (int a = 0; a < height; a++) {
        printf("|");
        for (int b = 0; b < width; b++) {
            if (grid[a][b] == '#') {
                printf("█");
            } else {
                printf(" ");
            }
        }

        printf("|");
        printf("\n");
    }

    int AH = 2;

    if (width > 20) {
        AH = width / 10;
    }

    for (int i = 0; i < width + 2; i++) {
        printf("‾");
    }
    printf("\n");

    return 0;
}

void re_draw(void)
{

    for (int a = 0; a < height; a++) {
        for (int b = 0; b < width; b++) {
            if (grid[a][b] == '#') {
                neighbour = whos_there(a, b);
                switch (neighbour) {
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

            if (grid[a][b] == ' ') {
                neighbour = whos_there(a, b);
                switch (neighbour) {
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

    for (int a = 0; a < height; a++) {
        for (int b = 0; b < width; b++) {
            grid[a][b] = tmpgrid[a][b];
        }
    }
}

int main()
{
    srand((int)time(NULL));

    main_menu();
    mem_alloc();

    int i = 1;
    while (i == 1) {
        char detect = '&';
        scanf("%c", &detect);
        switch (detect) {
            case '&':
                break;
            case 's':
                i = 0;
                break;
            default:
                draw();
                re_draw();
        }
    }
}

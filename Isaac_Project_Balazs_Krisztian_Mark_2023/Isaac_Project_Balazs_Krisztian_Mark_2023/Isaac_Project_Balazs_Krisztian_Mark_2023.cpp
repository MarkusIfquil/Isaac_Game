#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool game_running = 1;
int isaac_x = 9;
int isaac_y = 4;
int tear_x = 0;
int tear_y = 0;
int tear_direction = 0;
char floor_tile = '.';
char isaac = 1;

void shoot_input()
{
    #define SHOOT_UP 'i'
    #define SHOOT_DOWN 'k'
    #define SHOOT_LEFT 'j'
    #define SHOOT_RIGHT 'l'


    int c = 0;
    switch ((c = _getch())) {
    case SHOOT_UP:
        tear_x = isaac_x;
        tear_y = isaac_y;
        tear_direction = 1;
        break;
    case SHOOT_DOWN:
        tear_x = isaac_x;
        tear_y = isaac_y;
        tear_direction = 2;
        break;
    case SHOOT_LEFT:
        tear_x = isaac_x;
        tear_y = isaac_y;
        tear_direction = 3;
        break;
    case SHOOT_RIGHT:
        tear_x = isaac_x;
        tear_y = isaac_y;
        tear_direction = 4;
        break;
    case 'w':
        if(isaac_y > 1)
            isaac_y -= 1;
        break;
    case 'a':
        if(isaac_x > 1)
            isaac_x -= 1;
        break;
    case 's':
        if (isaac_y < 7)
            isaac_y += 1;
        break;
    case 'd':
        if(isaac_x < 17)
            isaac_x += 1;
        break;
    case 27:
        game_running = 0;
        break;
    default:
        break;
    }
}

void check_if_issac_there_x(int j,int i, int isaac_x, int isaac_y, char floor_tile, int tear_x, int tear_y)
{
    if (isaac_x == i && isaac_y == j)
    {
        printf("%c", isaac);
    }
    else if (tear_x == i && tear_y == j)
    {
        printf("O");
    }
    else
    {
        printf(".");
    }
}

void arena_render()
{
    printf("Izsak kotese\n");
    printf("isaac_x = %d\n", isaac_x);
    printf("isaac_y = %d\n", isaac_y);
    printf("tear_x = %d\n", tear_x);
    printf("tear_y = %d\n", tear_y);
    if (_kbhit()) //input
    {
        shoot_input();
        while (_kbhit())
            int trash_input = _getch();
    }

    switch (tear_direction)
    {
    case 1:
        tear_y--;
        break;
    case 2:
        tear_y++;
        break;
    case 3:
        tear_x--;
        break;
    case 4:
        tear_x++;
        break;
    default:
        break;
    }

    if (tear_y == 8 || tear_y == 0 || tear_x == 18 || tear_x == 0)
    {
        tear_y = 0;
        tear_x = 0;
        tear_direction = 0;
    }

    //rendering
    for (int j = 0; j < 9; j++) {
        switch (j) {
        case 0:
        {
            for (int i = 0; i < 17; i++)
            {
                if (i == 8)
                    printf("|O|");
                else
                    printf("_");
            }
            break;
        }
        case 3:
        case 5:
            for (int i = 0; i < 19; i++)
            {
                switch (i)
                {
                case 0:
                case 18:
                    printf("-");
                    break;
                default:
                    check_if_issac_there_x(j, i, isaac_x, isaac_y, floor_tile, tear_x,tear_y);
                    break;
                }
            }
            break;
        case 4:
            for (int i = 0; i < 19; i++)
            {
                switch (i)
                {
                case 0:
                    printf("(");
                    break;
                case 18:
                    printf(")");
                    break;
                default:
                    check_if_issac_there_x(j, i, isaac_x, isaac_y, floor_tile, tear_x, tear_y);
                    break;
                }
            }
            break;
        case 1:
        case 2:
        case 6:
        case 7:
        {
            for (int i = 0; i < 19; i++)
            {
                switch (i)
                {
                case 0:
                    printf("|");
                    break;
                case 18:
                    printf("|");
                    break;
                default:
                    check_if_issac_there_x(j, i, isaac_x, isaac_y, floor_tile, tear_x, tear_y);
                    break;
                }
            }
            break;
        }
        case 8:
        {
            for (int i = 0; i < 17; i++)
            {
                if (i == 8)
                    printf("|O|");
                else
                    printf("-");
            }
            break;
        }
        }
        printf("\n");
    }
}


// izsak kotese
int main()
{


    while (game_running)
    {
        arena_render();
        Sleep(500); //frame rate (1 fps)
        system("cls");
    }
}
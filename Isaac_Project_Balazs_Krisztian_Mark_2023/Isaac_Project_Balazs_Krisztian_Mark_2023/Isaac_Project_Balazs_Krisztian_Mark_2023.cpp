#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

#define SHOOT_UP 'i'
#define SHOOT_DOWN 'k'
#define SHOOT_LEFT 'j'
#define SHOOT_RIGHT 'l'


bool game_running = 1;
int isaac_x = 9;
int isaac_y = 4;
char isaac = 1;

struct projectile {
    int tear_x;
    int tear_y;
    int tear_direction;
    char symbol;
};

vector<projectile> projectiles;

void projectilespawner(int c)
{
    projectile new_projectile;
    new_projectile.tear_x = isaac_x;
    new_projectile.tear_y = isaac_y;
    switch (c = _getch())
    {
    case SHOOT_UP:
        new_projectile.tear_direction = 1;
        break;
    case SHOOT_DOWN:
        new_projectile.tear_direction = 2;
        break;
    case SHOOT_LEFT:
        new_projectile.tear_direction = 3;
        break;
    case SHOOT_RIGHT:
        new_projectile.tear_direction = 4;
        break;
    default:
        new_projectile.tear_direction = 1;
        break;

    }
    projectiles.push_back(new_projectile);
    
}

void shoot_input()
{
    int c = 0;
    switch ((c = _getch())) {
    case SHOOT_UP:
        projectilespawner(c);
        break;
    case SHOOT_DOWN:
        projectilespawner(c);
        break;
    case SHOOT_LEFT:
        projectilespawner(c);
        break;
    case SHOOT_RIGHT:
        projectilespawner(c);
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

void projectile_mover()
{
    for (int i = 0; i < projectiles.size(); i++)
    {

        switch (projectiles[i].tear_direction)
        {
        case 1:
            projectiles[i].tear_y--;
            break;
        case 2:
            projectiles[i].tear_y++;
            break;
        case 3:
            projectiles[i].tear_x--;
            break;
        case 4:
            projectiles[i].tear_x++;
            break;
        default:
            break;

        }
        if (projectiles[i].tear_y == 8 || projectiles[i].tear_y == 0 || projectiles[i].tear_x == 18 || projectiles[i].tear_x == 0)
        {
            projectiles.erase(projectiles.begin() + i);
        }

    }
}

void check_if_issac_there_x(int j, int i, int isaac_x, int isaac_y)
{
    bool projectile_on_screen = 0;

    if (isaac_x == i && isaac_y == j)
    {
        printf("%c", isaac);
    }
    else if (projectiles.size() > 0) {
        for (int w = 0; w < projectiles.size(); w++)
        {
            if (projectiles[w].tear_x == i && projectiles[w].tear_y == j)
            {
                printf("O");
                projectile_on_screen = 1;
                break;
            }
        }
        if (!projectile_on_screen)
        {
            printf(".");
        }
    }
    else
    {
        printf(".");
    }
}


void arena_render()
{
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
                    check_if_issac_there_x(j, i, isaac_x, isaac_y);
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
                    check_if_issac_there_x(j, i, isaac_x, isaac_y);
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
                    check_if_issac_there_x(j, i, isaac_x, isaac_y);
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
        if (_kbhit()) //input
        {
            shoot_input();
            while (_kbhit())
                int trash_input = _getch();
        }
        projectile_mover();
        arena_render();
        printf("\nIzsak kotese\n");
        printf("isaac_x = %d\n", isaac_x);
        printf("isaac_y = %d\n", isaac_y);
        printf("vector size: %d\n", projectiles.size());
        if (projectiles.size() > 0)
        {
            for (int i = 0; i < projectiles.size(); i++)
            {
                printf("tear%d tear_x:%d\n", i, projectiles[i].tear_x);
                printf("tear%d tear_y:%d\n", i, projectiles[i].tear_y);
                printf("tear%d tear_direction:%d\n", i, projectiles[i].tear_direction);

            }
        }
        Sleep(500); //frame rate (1 fps)
        system("clrs");
    }
}

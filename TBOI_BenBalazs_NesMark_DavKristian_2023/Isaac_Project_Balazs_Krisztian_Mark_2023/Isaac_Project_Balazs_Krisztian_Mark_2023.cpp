#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <random>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

struct enemy
{
    int enemy_x = rand() % (17)+1;
    int enemy_y = rand() % (7)+1;
    int enemy_hp = 6;
    int enemy_direction;
};

vector<enemy> enemies;
vector<enemy> moving_enemy;

int score = 0;
int isaac_move_cache;
#define SHOOT_UP 'i'
#define SHOOT_DOWN 'k'
#define SHOOT_LEFT 'j'
#define SHOOT_RIGHT 'l'

int isaac_health = 6;
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
    switch (c)
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
        //printf("up\n");
        break;
    case SHOOT_DOWN:
        projectilespawner(c);
        //printf("down\n");
        break;
    case SHOOT_LEFT:
        projectilespawner(c);
        //printf("left\n");
        break;
    case SHOOT_RIGHT:
        projectilespawner(c);
        //printf("right\n");
        break;
    case 'w':
        if (isaac_y > 1) {
            isaac_move_cache = c;
            isaac_y -= 1;
        }
        break;
    case 'a':
        if (isaac_x > 1) {
            isaac_x -= 1;
            isaac_move_cache = c;
        }
        break;
    case 's':
        if (isaac_y < 7) {
            isaac_y += 1;
            isaac_move_cache = c;
        }
        break;
    case 'd':
        if (isaac_x < 17) {
            isaac_x += 1;
            isaac_move_cache = c;
        }
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

void collision_check()
{
    for (int t = 0; t < enemies.size(); t++)
    {
        if (isaac_x == enemies[t].enemy_x && isaac_y == enemies[t].enemy_y)
        {
            isaac_health--;
            if (isaac_health == 0)
            {
                system("cls");
                printf("GAME OVER. A pontjaid: %d. Restart? Y/N", score);
                ofstream my_file("scores.txt");
                time_t now = time(0);
                my_file << "Score: " << score << "\n";
                switch (int u = _getch())
                {
                case 'y':
                case 'Y':
                    isaac_health = 6;
                    isaac_x = 9;
                    isaac_y = 4;
                    break;
                case 'n':
                case 'N':
                    game_running = 0;
                    break;
                default:
                    game_running = 0;
                    break;
                }
            }
            switch (isaac_move_cache)
            {
            case 119:
                isaac_y++;
                break;
            case 115:
                isaac_y--;
                break;
            case 97:
                isaac_x++;
                break;
            case 100:
                isaac_x--;
                break;
            default:
                break;
            }
        }
    }
}

void check_if_issac_there_x(int j, int i, int isaac_x, int isaac_y)
{
    bool projectile_on_screen = false;
    bool already_done = false;
    bool isaac_rendered = false;
    for (int w = 0; w < projectiles.size(); w++)
    {
        for (int q = 0; q < enemies.size(); q++)
        {
            if (projectiles[w].tear_x == enemies[q].enemy_x && projectiles[w].tear_y == enemies[q].enemy_y)
            {
                projectiles.erase(projectiles.begin() + w);
                enemies[q].enemy_hp--;
                if (enemies[q].enemy_hp == 0)
                {
                    score++;
                    enemies.erase(enemies.begin() + q);
                    enemy new_enemy;
                    enemies.push_back(new_enemy);
                }
                break;
            }
        }
    }
    
    if (isaac_x == i && isaac_y == j)
    {
        printf("%c", isaac);
        isaac_rendered = true;
    }
    else if (projectiles.size() > 0)
    {
        for (int w = 0; w < projectiles.size(); w++)
        {
            if (projectiles[w].tear_x == i && projectiles[w].tear_y == j)
            {
                printf("o");
                projectile_on_screen = true;
                break;
            }
        }
    }

    if (enemies.size() > 0) 
    {
        for (int q = 0; q < enemies.size(); q++)
        {
            if (enemies[q].enemy_x == i && enemies[q].enemy_y == j)
            {
                printf("E");
                already_done = true;
                break;
            }
        }
    }
    if (!already_done && !projectile_on_screen && !isaac_rendered)
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
    enemy new_enemy;
    enemies.push_back(new_enemy);

    while (game_running)
    {
        if (_kbhit()) //input
        {
            shoot_input();
            while (_kbhit())
                int trash_input = _getch();
        }
        collision_check();
        projectile_mover();
        printf("The Binding of Isaac: Dos Version\n\nIzsak elet:%d\nScore:%d\n", isaac_health,score);

        arena_render();
        /*
        printf("\nIzsak kotese\n");
        printf("isaac_x = %d\n", isaac_x);
        printf("isaac_y = %d\n", isaac_y);
        printf("vector size: %d\n", projectiles.size());
        printf("enemies vector size: %d\n", enemies.size());
        printf("isaac move cache: %d\n", isaac_move_cache);
        printf("enemy_x:%d\n", enemies[0].enemy_x);
        printf("enemy_y:%d\n", enemies[0].enemy_y);
        */
        Sleep(200); //frame rate (1 fps)
        system("cls");
    }
}
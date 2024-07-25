#ifndef GAME_H
#define GAME_H

#include <sys/time.h>
#include <cstdlib>
#include <iostream>
#include <GLFW/glfw3.h>

#include <chrono>
#include <thread>


#include "snake.h"

#define MOVE_TIME 1000
#define PAUSE_MINUS_TIME (int(MOVE_TIME*0.9))

#define WINDOWS_WIDTH 800
#define WINDOWS_HEIGHT 800

#define WINDOWS_TITLE "Snake game"

class Snake_game
{
    public:
        int move;
        struct timeval tp;
        long int start_time;

        GLFWwindow* window;
        const GLFWvidmode* mode;

        Snake local_snake;

        Snake_game();

        void start_game();

        void check_key();

        bool try_move();

        bool check_escape();

        void draw_game();

        void draw_snake();

        void draw_block(int l_x,int l_y,int object);

        void draw_pause();
};

#endif
#ifndef SNAKE_H
#define SNAKE_H

#include <cstdlib>
#include <iostream>

#define GRID_SIZE 10

#define APPLE 2
#define SANKE_BODY 1
#define EMPTY 0

#define SNAKE_START_X int(GRID_SIZE/3)
#define SNAKE_START_Y int(GRID_SIZE/3)

class Snake_body
{
    public:
        int x_body;
        int y_body;
        Snake_body* tail;

        Snake_body(int l_x,int l_y,Snake_body* l_tail):x_body(l_x),y_body(l_y),tail(l_tail) {};
        ~Snake_body();

        void moveSnakeTo(int l_x,int l_y);
};


class Snake
{
    public:
        int grid[GRID_SIZE][GRID_SIZE];
        int x_apple;
        int y_apple;
        Snake_body* head;
        bool isLose_V;
        int score;

        inline int getGridSize() { return GRID_SIZE; };

        Snake();
        void displayOnTerminal();
        void createNewApple();
        void refereshGrid();

        bool isSnakeBody(int l_x,int l_y);
        bool isSnakeBodyWithoutTail(int l_x,int l_y);
        bool isApple(int l_x,int l_y);

        void makeMoveTo(int l_x,int l_y);

        void growTo(int l_x,int l_y);
        void die();

        void moveRight();
        void moveLeft();
        void moveUp();
        void moveDown();

        bool isWin();
        bool isLose();

        inline int getViewForPostition(int l_x,int l_y) { return this->grid[l_x][l_y]; };
        
};



#endif
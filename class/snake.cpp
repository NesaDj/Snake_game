#include "snake.h"

Snake_body::~Snake_body()
{
    if(this->tail != NULL)
    {
        delete tail;
    }
};


Snake::Snake()
{
    srand((unsigned int)time(NULL));

    for(int i=0;i<GRID_SIZE;i++)
    {
        for(int j=0;j<GRID_SIZE;j++)
        {
            this->grid[i][j]=EMPTY;
        }
    }

    this->head = new Snake_body(SNAKE_START_X,SNAKE_START_Y,NULL);
    this->isLose_V = false;

    this->createNewApple();
    this->score = 1;
};


void Snake::displayOnTerminal()
{
    
    for(int i=0;i<GRID_SIZE;i++)
    {
        for(int j=0;j<GRID_SIZE;j++)
        {
            if(this->grid[i][j]==EMPTY)
            {
                std::cout << " - ";
            }else if(this->grid[i][j]==SANKE_BODY)
            {
                std::cout << " X ";
            }else if(this->grid[i][j]==APPLE)
            {
                std::cout << " O ";
            }
        }
        std::cout << std::endl;
    }
};

void Snake::createNewApple()
{
    int l_x,l_y;

    do
    {
        l_x = rand() % GRID_SIZE;
        l_y = rand() % GRID_SIZE;
    }while(this->isSnakeBody(l_x,l_y));

    this->x_apple = l_x;
    this->y_apple = l_y;
}

void Snake::refereshGrid()
{
    for(int i=0;i<GRID_SIZE;i++)
    {
        for(int j=0;j<GRID_SIZE;j++)
        {
            this->grid[i][j]=EMPTY;
        }
    }

    this->grid[this->x_apple][this->y_apple] = APPLE;

    Snake_body* temp = this->head;

    while(true)
    {
        this->grid[temp->x_body][temp->y_body] = SANKE_BODY;

        if(temp->tail!=NULL)
        {
            temp = temp->tail;
        }else
        {
            break;
        }
    }
}


bool Snake::isSnakeBody(int l_x,int l_y)
{
    Snake_body* temp = this->head;

    while(true)
    {
        if(temp == NULL) break;

        if(temp->x_body == l_x && temp->y_body == l_y)
        {
            return true;
        }

        temp = temp->tail;
    }

    return false;
}

bool Snake::isSnakeBodyWithoutTail(int l_x,int l_y)
{
    Snake_body* temp = this->head;

    while(true)
    {
        if(temp == NULL) break;

        if(temp->x_body == l_x && temp->y_body == l_y && temp->tail!=NULL)
        {
            return true;
        }

        temp = temp->tail;
    }

    return false;
}


bool Snake::isApple(int l_x,int l_y)
{
    if(this->x_apple == l_x && this->y_apple == l_y)
    {
        return true;
    }else
    {
        return false;
    }
}

void Snake::makeMoveTo(int l_x,int l_y)
{
    if(l_x<0 || l_x>GRID_SIZE-1 || l_y<0 || l_y>GRID_SIZE-1)
    {
        this->die();
    }else if(this->isSnakeBodyWithoutTail(l_x,l_y))
    {
        this->die();
    }else if(this->isApple(l_x,l_y))
    {
        this->growTo(l_x,l_y);
    }else
    {
        this->head->moveSnakeTo(l_x,l_y);
    }
}

void Snake::die()
{
    this->isLose_V=1;
}

void Snake::growTo(int l_x,int l_y)
{
    Snake_body* grow = new Snake_body(l_x,l_y,this->head);
    this->head = grow;

    this->score++;

    if(!this->isWin() && !this->isLose())
    {
        this->createNewApple();
    }
}

void Snake_body::moveSnakeTo(int l_x,int l_y)
{
    if(this->tail==NULL)
    {
        this->x_body = l_x;
        this->y_body = l_y;
    }else
    {
        this->tail->moveSnakeTo(this->x_body,this->y_body);
        this->x_body = l_x;
        this->y_body = l_y;
    }
}

void Snake::moveUp()
{
    int l_x,l_y;

    l_x = this->head->x_body-1;
    l_y = this->head->y_body;

    this->makeMoveTo(l_x,l_y);
}

void Snake::moveDown()
{
    int l_x,l_y;

    l_x = this->head->x_body+1;
    l_y = this->head->y_body;

    this->makeMoveTo(l_x,l_y);
}

void Snake::moveRight()
{
    int l_x,l_y;

    l_x = this->head->x_body;
    l_y = this->head->y_body+1;

    this->makeMoveTo(l_x,l_y);
}

void Snake::moveLeft()
{
    int l_x,l_y;

    l_x = this->head->x_body;
    l_y = this->head->y_body-1;

    this->makeMoveTo(l_x,l_y);
}

bool Snake::isWin()
{
    if(this->score>=(GRID_SIZE*GRID_SIZE))
    {
        return true;
    }else
    {
        return false;
    }
}

bool Snake::isLose()
{
    return this->isLose_V;
};



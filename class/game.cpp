#include "game.h"
#include <GLFW/glfw3.h>

Snake_game::Snake_game()
{
    this->move = 0;

    gettimeofday(&this->tp, NULL);

    this->start_time = tp.tv_sec * MOVE_TIME + tp.tv_usec / MOVE_TIME;

    glfwInit();

    this->window = glfwCreateWindow(WINDOWS_WIDTH, WINDOWS_HEIGHT, WINDOWS_TITLE, NULL, NULL);
    this->mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(this->window, (mode->width - WINDOWS_WIDTH) / 2, (mode->height - WINDOWS_HEIGHT) / 2);

    glfwMakeContextCurrent(this->window);
};

void Snake_game::start_game()
{
    this->draw_game();

    while(!glfwWindowShouldClose(this->window))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        this->check_key();

        if(this->move!=0 && this->try_move())
        {
            switch(this->move)
            {
                case 2:
                    this->local_snake.moveRight();
                    break;
                case 4:
                    this->local_snake.moveUp();
                    break;
                case 8:
                    this->local_snake.moveLeft();
                    break;
                case 6:
                    this->local_snake.moveDown();
                    break;
            }

            this->draw_game();
        }

        if(this->move==0)
        {
            this->draw_game();

            gettimeofday(&this->tp, NULL);  
  
            start_time=(tp.tv_sec * MOVE_TIME + tp.tv_usec / MOVE_TIME)-PAUSE_MINUS_TIME;        
        }

        if(this->local_snake.isLose())
        {
            std::cout << "You lose... " << std::endl << "Your score is : " << this->local_snake.score << std::endl;
            break; 
        }

        if(this->local_snake.isWin())
        {
            std::cout << "You win... " << std::endl << "Your score is : " << this->local_snake.score << std::endl;
            break; 
        }

        if(this->check_escape()) break;
   
        glfwPollEvents();
    }

    glfwTerminate();
};


bool Snake_game::try_move()
{
    gettimeofday(&this->tp, NULL);
    long int time = tp.tv_sec * MOVE_TIME + tp.tv_usec / MOVE_TIME;

    if(this->start_time+MOVE_TIME<time)
    {
        start_time+=MOVE_TIME;
        return true;
    };
    return false;
};

bool Snake_game::check_escape()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        return true;
    }

    return false;
}


void Snake_game::check_key()
{
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        this->move = 0;
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        this->move = 2;
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        this->move = 4;
    }

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        this->move = 8;
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        this->move = 6;
    }
}

void Snake_game::draw_game()
{
    glClear(GL_COLOR_BUFFER_BIT);

    this->draw_block(this->local_snake.x_apple,this->local_snake.y_apple,APPLE);
    
    this->draw_snake();
    

    glfwSwapBuffers(this->window);
}

void Snake_game::draw_snake()
{
    Snake_body *temp_body;

    temp_body = this->local_snake.head;

    do{
        this->draw_block(temp_body->x_body,temp_body->y_body,SANKE_BODY);
        temp_body = temp_body->tail;
    }while(temp_body!=NULL);

    if(this->move==0)
    {
        this->draw_pause();
    }

}

void Snake_game::draw_pause()
{
    glColor3f(0.6f, 0.6f, 0.6f);

    glBegin(GL_QUADS);
    glVertex2f(-0.3f, 0.5f);   
    glVertex2f(-0.5f, 0.5f);    
    glVertex2f(-0.5f, -0.5f);     
    glVertex2f(-0.3f, -0.5f);    
    glEnd();


    glBegin(GL_QUADS);
    glVertex2f(0.3f, 0.5f);   
    glVertex2f(0.5f, 0.5f);    
    glVertex2f(0.5f, -0.5f);     
    glVertex2f(0.3f, -0.5f);    
    glEnd();

}

void Snake_game::draw_block(int l_x,int l_y,int object)
{
    if(object==EMPTY)
    {
        return;
    }

    l_y = l_y - (GRID_SIZE/2-1);
    l_x = l_x - (GRID_SIZE/2);

    l_y = -l_y;

    float size_of_block = 1.0f/(float(GRID_SIZE/2));
    float x = size_of_block * l_x;
    float y = size_of_block * l_y;

    if(object==APPLE)
    {
        glColor3f(1.0f, 0.0f, 0.0f);
    }else if(object==SANKE_BODY)
    {
        glColor3f(0.0f, 1.0f, 0.0f);
    }

    glBegin(GL_QUADS);
    glVertex2f(x, y);   
    glVertex2f(x+size_of_block, y);    
    glVertex2f(x+size_of_block, y+size_of_block);     
    glVertex2f(x, y+size_of_block);    
    glEnd();
};
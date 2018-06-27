#ifndef HEROES_H
#define HEROES_H

#include "../OakEngine/OakEngine.h"
#include "../acorn.h"
#include "config.h"


/*========================================================================================
 *
 *                              Welcome to the Heroes Header file
 *
 *
 *
 *  created by Nikita Dubovik
 /========================================================================================*/



enum BALL_STATE
{
    HIT = 0,
    CALM,
    BALL_STATE_DEFAULT
};


struct Ball : public oak::GameObject
{

    uint32_t counter_ = 0;

    BALL_STATE ball_state_ = HIT;

    sf::CircleShape ball_{};

    Ball();

    virtual void collide_response(oak::GameObject* someone) override ;

    virtual void draw() override ;

    virtual void come_back() override ;
};


struct Wall : public oak::GameObject
{

    sf::RectangleShape line_{};

    Wall();

    virtual void collide_response(oak::GameObject* someone) override ;

    virtual void draw() override ;

    void set_wall(oak::COLLIDER_TYPE type, int position);

    void set_line(int x_pos, int y_pos, int wide, int height);
};


struct Box
{
    Wall left_{};
    Wall right_{};
    Wall top_{};
    Wall bottom_{};

    Box();
};



const int DOTS_AMOUNT = oak_config::BALL_SPEED * 2;

struct Graph
{
    sf::RectangleShape x_axis_{};
    sf::RectangleShape y_axis_{};

    float* dots_ = nullptr;

    Graph();

    ~Graph();

    void draw_axis();

    void null_dots();

    void normilize_dots();

    void print_dots();
};

struct Experiment
{
    Ball* gas_ = nullptr;

    Box box_{};

    Graph graph_{};

    Experiment();

    ~Experiment();

    double measure_energy();

    void display_distribution();

    void make_tex_file();

};

#include "Heroes.hpp"
#endif //HEROES_H

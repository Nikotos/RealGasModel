#ifndef HEROES_HPP
#define HEROES_HPP
#include "Heroes.h"
#include "../window.h"

/*========================================================================================
 *
 *
 *      struct Ball
 *      Implementation
 *
 *
 *
 /========================================================================================*/

Ball::Ball():
    GameObject(oak::BALL)
{
    physeg_.collider_.set(oak::SPHERE, oak_config::BALL_RADIUS);


    /*
    physeg_.speed_ = {rand() % (2 * oak_config::BALL_SPEED) - oak_config::BALL_SPEED,
                      rand() % (2 * oak_config::BALL_SPEED) - oak_config::BALL_SPEED};
    */



    physeg_.speed_ = {rand() % (oak_config::BALL_SPEED / 3) - oak_config::BALL_SPEED / 2,
                      rand() % (oak_config::BALL_SPEED / 3) - oak_config::BALL_SPEED / 2};




    physeg_.coord_ = {(rand() % 1100 + 50), (rand() % 800 + 50)};

    ball_.setRadius(oak_config::BALL_RADIUS);
    ball_.setPosition(physeg_.coord_);
    ball_.setFillColor(sf::Color::Green);
}


// проверка векторами
void Ball::collide_response(oak::GameObject *someone)
{

        switch (ball_state_)
        {
            case CALM :
            {
                ball_state_ = HIT;

                counter_ = oak::SAMPLE;

                if (someone->type_ == oak::SPHERE)
                {
                    double a = physeg_.coord_.y - someone->physeg_.coord_.y;
                    double b = physeg_.coord_.x - someone->physeg_.coord_.x;

                    double c = sqrt(a * a + b * b);

                    double sin_a = a / c;
                    double cos_a = b / c;

                    double u_save_1 = physeg_.speed_.x * sin_a + physeg_.speed_.y * cos_a;
                    double u_save_2 = someone->physeg_.speed_.x * sin_a + someone->physeg_.speed_.y * cos_a;

                    double u_ref_1 = someone->physeg_.speed_.x * cos_a - someone->physeg_.speed_.y * sin_a;
                    double u_ref_2 = physeg_.speed_.x * cos_a - physeg_.speed_.y * sin_a;



                    /*  just test
                    physeg_.speed_.x = -physeg_.speed_.x;
                    physeg_.speed_.y = -physeg_.speed_.y;

                    someone->physeg_.speed_.x = -someone->physeg_.speed_.x;
                    someone->physeg_.speed_.y = -someone->physeg_.speed_.y;
                    */


                    physeg_.speed_.x = u_ref_1 * cos_a + u_save_1 * sin_a;
                    physeg_.speed_.y = u_save_1 * cos_a - u_ref_1 * sin_a;

                    someone->physeg_.speed_.x = u_ref_2 * cos_a + u_save_2 * sin_a;
                    someone->physeg_.speed_.y = u_save_2 * cos_a - u_ref_2 * sin_a;
                }

                if (someone->type_ == oak::WALL)
                {
                    if (someone->physeg_.collider_.type_ == oak::HORIZONTAL_LINE)
                    {
                        physeg_.speed_.y = (-1) * physeg_.speed_.y;
                    }
                    else if (someone->physeg_.collider_.type_ == oak::VERTICAL_LINE)
                    {
                        physeg_.speed_.x = (-1) * physeg_.speed_.x;
                    }
                }


            }
                break;

            case HIT :
            {
                if (oak::SAMPLE - counter_ >=  oak_config::HIT_SAMPLE_DELAY)
                {
                    ball_state_ = CALM;
                }
            }
                break;
        }

}


void Ball::draw()
{
    ball_.setPosition(physeg_.coord_);
    window.draw(ball_);
}

void Ball::come_back()
{
    physeg_.coord_ = {(rand() % 1100 + 50), (rand() % 800 + 50)};
}

/*========================================================================================
 *
 *
 *      struct Wall
 *      Implementation
 *
 *
 *
 /========================================================================================*/

Wall::Wall():
    GameObject(oak::WALL)
{}


void Wall::collide_response(oak::GameObject *someone)
{

    if (someone->type_ == oak::BALL)
    {
        switch (((Ball *)someone)->ball_state_)
        {
            case CALM :
            {
                ((Ball *)someone)->ball_state_ = HIT;

                ((Ball *)someone)->counter_ = oak::SAMPLE;


                if (physeg_.collider_.type_ == oak::HORIZONTAL_LINE)
                {
                    someone->physeg_.speed_.y = (-1) * someone->physeg_.speed_.y;
                }
                else if (physeg_.collider_.type_ == oak::VERTICAL_LINE)
                {
                    someone->physeg_.speed_.x = (-1) * someone->physeg_.speed_.x;
                }

            }
                break;

            case HIT :
            {
                if (oak::SAMPLE - ((Ball *)someone)->counter_ >= oak_config::HIT_SAMPLE_DELAY)
                {
                    ((Ball *)someone)->ball_state_ = CALM;
                }
            }
                break;
        }

    }
}


void Wall::set_wall(oak::COLLIDER_TYPE type, int position)
{
    physeg_.collider_.set(type, position);
}


void Wall::set_line(int x_pos, int y_pos, int wide, int height)
{
    line_.setSize({wide, height});
    line_.setPosition(x_pos, y_pos);

    line_.setFillColor(sf::Color::Green);
}

void Wall::draw()
{
    window.draw(line_);
}

/*========================================================================================
 *
 *
 *      struct Box
 *      Implementation
 *
 *
 *
 /========================================================================================*/

Box::Box()
{
    left_.set_wall(oak::VERTICAL_LINE, oak_config::LEFT_WALL_X);
    right_.set_wall(oak::VERTICAL_LINE, oak_config::RIGHT_WALL_X);
    top_.set_wall(oak::HORIZONTAL_LINE, oak_config::TOP_WALL_Y);
    bottom_.set_wall(oak::HORIZONTAL_LINE, oak_config::BOTTOM_WALL_Y);


    /*
    left_.set_line(oak_config::LEFT_WALL_X, oak_config::TOP_WALL_Y, 3,
                   oak_config::BOTTOM_WALL_Y - oak_config::TOP_WALL_Y);

    right_.set_line(oak_config::RIGHT_WALL_X, oak_config::TOP_WALL_Y, 3,
            oak_config::BOTTOM_WALL_Y - oak_config::TOP_WALL_Y);

    top_.set_line(oak_config::LEFT_WALL_X, oak_config::TOP_WALL_Y,
                  oak_config::BOTTOM_WALL_Y - oak_config::TOP_WALL_Y, 3);


    bottom_.set_line(oak_config::LEFT_WALL_X,oak_config::BOTTOM_WALL_Y,
                     oak_config::BOTTOM_WALL_Y - oak_config::TOP_WALL_Y, 3);

                     */


    left_.set_line(0,0,3,900);
    right_.set_line(1197,0,3,900);
    top_.set_line(0,0,1200,3);
    bottom_.set_line(0,897,1200,3);
}



/*========================================================================================
 *
 *
 *      struct Graph
 *      Implementation
 *
 *
 *
 /========================================================================================*/


Graph::Graph()
{
    x_axis_.setSize({500, 3});
    y_axis_.setSize({3, 500});

    x_axis_.setPosition({50, 550});
    y_axis_.setPosition({47, 50});

    x_axis_.setFillColor(sf::Color::Green);
    y_axis_.setFillColor(sf::Color::Green);

    dots_ = new float [DOTS_AMOUNT];

    for (int i = 0 ; i < DOTS_AMOUNT; i++)
    {
        dots_[i] = 0;
    }
}


Graph::~Graph()
{
    delete [] dots_;
}


void Graph::draw_axis()
{
    info_window.draw(x_axis_);
    info_window.draw(y_axis_);
}

void Graph::null_dots()
{
    for (int i = 0; i < DOTS_AMOUNT; i++)
    {
        dots_[i] = 0;
    }
}


void Graph::normilize_dots()
{
    float max = 0;

    for (int i = 0; i < DOTS_AMOUNT; i++)
    {
        if (dots_[i] > max)
        {
            max = dots_[i];
        }
    }

    for (int i = 0; i < DOTS_AMOUNT; i++)
    {
        dots_[i] = (dots_[i] * 500)/max;
    }
}



void Graph::print_dots()
{
    sf::RectangleShape line{};
    line.setFillColor(sf::Color::Green);

    for (int i = 0; i < DOTS_AMOUNT; i++)
    {
        if (dots_[i] != 0)
        {
            line.setPosition({50 + (i * 500 * 1.5) / DOTS_AMOUNT, 550 - dots_[i]});
            line.setSize({3,3});
            info_window.draw(line);
        }

    }
}
/*========================================================================================
 *
 *
 *      struct Experiment
 *      Implementation
 *
 *
 *
 /========================================================================================*/

Experiment::Experiment()
{
    gas_ = new Ball [oak_config::BALLS_AMOUNT]{};
}


Experiment::~Experiment()
{
    delete [] gas_;
    gas_ = nullptr;
}

#define SQUARE(o) ((o)*(o))

double Experiment::measure_energy()
{
    double energy = 0;

    for (int i = 0; i < oak_config::BALLS_AMOUNT; i++)
    {
        energy += (SQUARE(gas_[i].physeg_.speed_.x) + (SQUARE(gas_[i].physeg_.speed_.y)));
    }
}



void Experiment::display_distribution()
{
    graph_.draw_axis();

    graph_.null_dots();

    int speed = 0;

    for (int i = 0; i < oak_config::BALLS_AMOUNT; i++)
    {
        speed = roundf(sqrtf(SQUARE(gas_[i].physeg_.speed_.x ) + SQUARE(gas_[i].physeg_.speed_.y)));

        if ((speed / oak_config::SPEED_SAMPLE < oak_config::BALL_SPEED) && speed > 0)
        {
            graph_.dots_[speed / oak_config::SPEED_SAMPLE] += 1;
        }
    }

    graph_.normilize_dots();

    graph_.print_dots();
}



#define MAKE_HEADER                                                                 \
    fprintf(output,"\\documentclass[a4paper,12pt]{article}\n"                       \
                    "\\usepackage{float}\n"                                         \
                    "\\usepackage{pgfplots}\n"                                      \
                    "% Preamble: \\pgfplotsset{width=1cm,compat=newest}\n"          \
                    "\\begin{document}\n");

#define MAKE_END                                                                    \
     fprintf(output,"\\end{document}\n");


#define MAKE_GRAPH(LEGEND)                                                          \
                                                                                    \
    fprintf(output, "\\begin{tikzpicture}\n"                                        \
                    "\\begin{axis}[height=15cm,width=15cm,grid=major]\n"            \
                    "\\addlegendentry{"                                             \
                    LEGEND                                                          \
                    "}\n"                                                           \
                    "\\addplot[color = blue, mark = * ] coordinates {\n");          \
                                                                                    \
    for (int i = 0; i <  DOTS_AMOUNT; i++)                                          \
    {                                                                               \
        fprintf(output,"(%d,%d)\n", i, dots[i]);                                    \
    }                                                                               \
    fprintf(output, "};\n\n"                                                        \
                    "\\end{axis}\n"                                                 \
                    "\\end{tikzpicture}\n");


#define NUL_DOTS \
    for (int i = 0; i < DOTS_AMOUNT; i++) dots[i] = 0;



void Experiment::make_tex_file()
{
    static int counter = 0;

    auto filename = new char [20];
    for (int i = 0; i < 20; i++) filename[i] = 0;

    sprintf(filename, "data%d.tex", counter);

    counter++;

    FILE* output = fopen(filename, "w");

    auto dots = new int [DOTS_AMOUNT];


    MAKE_HEADER

    NUL_DOTS

    int speed = 0;

    for (int i = 0; i < oak_config::BALLS_AMOUNT; i++)
    {
        speed = roundf(sqrtf(SQUARE(gas_[i].physeg_.speed_.x ) + SQUARE(gas_[i].physeg_.speed_.y)));

        if ((speed < DOTS_AMOUNT) && (speed > 0))
        {
            dots[speed]++;
        }

    }

    MAKE_GRAPH("Absolute speed distribution")

    NUL_DOTS

    for (int i = 0; i < oak_config::BALLS_AMOUNT; i++)
    {
        speed = roundf(gas_[i].physeg_.speed_.x);

        if ((speed < DOTS_AMOUNT) && (speed > 0))
        {
            dots[speed]++;
        }

    }

    MAKE_GRAPH("Ux distribution, Ux above 0")

    NUL_DOTS

    for (int i = 0; i < oak_config::BALLS_AMOUNT; i++)
    {
        speed = roundf(gas_[i].physeg_.speed_.x);

        if ((abs(speed) < DOTS_AMOUNT) && (speed < 0))
        {
            dots[abs(speed)]++;
        }

    }

    MAKE_GRAPH("Ux distribution, Ux under 0")

    NUL_DOTS

    for (int i = 0; i < oak_config::BALLS_AMOUNT; i++)
    {
        speed = roundf(gas_[i].physeg_.speed_.y);

        if ((speed < DOTS_AMOUNT) && (speed > 0))
        {
            dots[speed]++;
        }

    }

    MAKE_GRAPH("Uy distribution, Uy above 0")

    NUL_DOTS

    for (int i = 0; i < oak_config::BALLS_AMOUNT; i++)
    {
        speed = roundf(gas_[i].physeg_.speed_.y);

        if ((abs(speed) < DOTS_AMOUNT) && (speed < 0))
        {
            dots[abs(speed)]++;
        }

    }

    MAKE_GRAPH("Uy distribution, Uy under 0")

    MAKE_END


    fclose(output);

    delete [] dots;
    dots = nullptr;


    auto command = new char [100];
    for (int i = 0; i < 100; i++) command[i] = 0;

    sprintf(command, "pdflatex %s\n rm data%d.aux data%d.log data%d.tex",
            filename, counter - 1, counter - 1, counter - 1);

    system(command);

}
#endif //HEROES_HPP

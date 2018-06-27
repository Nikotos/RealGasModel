#ifndef OAKENGINE_HPP
#define OAKENGINE_HPP

#include "OakEngine.h"

#include <SFML/Graphics.hpp>


/*========================================================================================
 *
 *          struct Collider, Implementation
 *
 *
 *
 /========================================================================================*/

void oak::Collider::set(COLLIDER_TYPE type, float data)
{
    type_ = type;
    data_ = data;
}

/*========================================================================================
 *
 *          struct Physical Object, Implementation
 *
 *
 *
 /========================================================================================*/


oak::PhysObject::PhysObject():
        coord_({-1,-1}),
        speed_({0,0}),
        acc_({0,0})
{}


oak::PhysObject::~PhysObject()
{
    boss_ptr_ = nullptr;
}


void oak::PhysObject::move()
{
    coord_.x += speed_.x * oak::TIME_SAMPLE;
    coord_.y += speed_.y * oak::TIME_SAMPLE;

    //speed_.y += 98 * oak::TIME_SAMPLE;
}



void oak::PhysObject::set_boss(oak::GameObject* boss)
{
    boss_ptr_ = boss;
}



bool oak::PhysObject::check_collision(PhysObject *someone)
{
    if ((collider_.type_ == SPHERE) && (someone->collider_.type_ == SPHERE))
    {
        float a = coord_.x - someone->coord_.x;
        float b = coord_.y - someone->coord_.y;
        float r1 = collider_.data_;
        float r2 = someone->collider_.data_;

        if (a * a + b * b <= (r1 + r2) * (r1 + r2))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    else if ((collider_.type_ == SPHERE) && (someone->collider_.type_ == SPHERE))
    {

        float a = (coord_.x + FUTURE_COLLISION_K * speed_.x * TIME_SAMPLE) -
                (someone->coord_.x + FUTURE_COLLISION_K * someone->speed_.x * TIME_SAMPLE);

        float b = (coord_.y + FUTURE_COLLISION_K * speed_.y * TIME_SAMPLE) -
                (someone->coord_.y + FUTURE_COLLISION_K * speed_.y * TIME_SAMPLE);

        float r1 = collider_.data_;
        float r2 = someone->collider_.data_;

        if (a * a + b * b <= (r1 + r2) * (r1 + r2))
        {
            coord_.x += FUTURE_COLLISION_K * speed_.x * TIME_SAMPLE;
            coord_.y += FUTURE_COLLISION_K * speed_.y * TIME_SAMPLE;

            someone->coord_.x += FUTURE_COLLISION_K * someone->speed_.x * TIME_SAMPLE;
            someone->coord_.y += FUTURE_COLLISION_K * someone->speed_.y * TIME_SAMPLE;
            return true;
        }
        else
        {
            return false;
        }
    }


    else if ((collider_.type_ == SPHERE) && (someone->collider_.type_ == HORIZONTAL_LINE))
    {
        if (abs(coord_.y - someone->collider_.data_) <= collider_.data_)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    else if ((collider_.type_ == SPHERE) && (someone->collider_.type_ == VERTICAL_LINE))
    {
        if (abs(coord_.x - someone->collider_.data_) <= collider_.data_)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    else if ((collider_.type_ == HORIZONTAL_LINE) && (someone->collider_.type_ == SPHERE))
    {
        if (abs(someone->coord_.y - collider_.data_) <= someone->collider_.data_)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    else if ((collider_.type_ == VERTICAL_LINE) && (someone->collider_.type_ == SPHERE))
    {
        if (abs(someone->coord_.x - collider_.data_) <= someone->collider_.data_)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}


bool oak::PhysObject::check_position()
{
    if ((coord_.x < 1205) && (coord_.x > -5) && (coord_.y < 905) && (coord_.y > -5))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*========================================================================================
 *
 *          struct Graphical Object, Implementation
 *
 *
 *
 /========================================================================================*/

void oak::GraphObject::set_boss(oak::GameObject* boss)
{
    boss_ptr_ = boss;
}


void oak::GraphObject::set_texture(const char *filename)
{
    sf::Texture texture;

    if(!texture.loadFromFile(filename))
    {
        FTHROW(MEMORY_ACCES_ERROR, "can't open file!");
    }

    sprite_.setTexture(texture);
}

#define COORDS\
     boss_ptr_->physeg_.coord_

void oak::GraphObject::draw()
{
    sprite_.setPosition(COORDS.x, COORDS.y);
    window.draw(sprite_);
}

#undef COORDS


oak::GraphObject::~GraphObject()
{
    boss_ptr_ = nullptr;
}

/*========================================================================================
 *
 *          struct Game Object, Implementation
 *
 *
 *
 /========================================================================================*/

oak::GameObject::GameObject(OBJECT_TYPES type)
{
    type_ = type;
    set_dependences();
}


oak::GameObject::~GameObject()
{
    is_alive_ = false;
}

void oak::GameObject::set_dependences()
{
    physeg_.set_boss(this);
    grapheg_.set_boss(this);
}


void oak::GameObject::draw()
{
    grapheg_.draw();
}


void oak::GameObject::move()
{
    physeg_.move();
}

/*=========================================================================================
 *
 *          struct OakEngine, Implementation
 *
 *
 *
 /========================================================================================*/

oak::OakEngine::OakEngine()
{
    run_list_ = new GameObject* [oak::RUN_LIST_SIZE];
}



oak::OakEngine::~OakEngine()
{
    delete [] run_list_;
    run_list_ = nullptr;
}


void oak::OakEngine::add(GameObject *obj)
{
    run_list_[obj_amount_] = obj;
    obj_amount_++;
}


void oak::OakEngine::handle_event(sf::Event event)
{
    current_event_ = event;

    for(int i = 0; i < obj_amount_; i++)
    {
        run_list_[i]->move();
        run_list_[i]->draw();
    }

    collide_all();
}


void oak::OakEngine::tick()
{
    for(int i = 0; i < obj_amount_; i++)
    {
        run_list_[i]->move();
        run_list_[i]->draw();

        if ((!run_list_[i]->physeg_.check_position()) && (run_list_[i]->type_ == BALL))
        {
            run_list_[i]->come_back();
        }
    }

    collide_all();

    SAMPLE++;
}



//TODO to been upgraded later
void oak::OakEngine::collide_all()
{
    for (int i = 0; i < obj_amount_; i++)
    {
        for(int j = i + 1; j < obj_amount_; j++)
        {
            if(run_list_[i]->physeg_.check_collision(&run_list_[j]->physeg_))
            {
                run_list_[i]->collide_response(run_list_[j]);
            }
        }
    }
}

#endif //OAKENGINE_HPP

#ifndef OAKENGINE_H
#define OAKENGINE_H

#include <SFML/Graphics.hpp>
#include "../acorn.h"

/*=====================================================================================
 *
 *                              Welcome to the OakEngine!
 *
 *                              Like CryEngine, but OakEngine
 *
 *
 *  created by Nikita Dubovik
 /========================================================================================*/

namespace oak
{
    struct GameObject;

    /*Frames per second, exactly*/
    const float TIME_SAMPLE = 0.02;

    const float FUTURE_COLLISION_K = 0.5;

    const int RUN_LIST_SIZE = 10000;

    const float DEFAULT_SPEED = 10;

    uint32_t SAMPLE = 0;

    enum OBJECT_TYPES
    {
        BALL = 0,
        WALL,
        OBJECT_TYPES_DEFAULT
    };

    enum COLLIDER_TYPE
    {
        SPHERE = 0,
        VERTICAL_LINE,
        HORIZONTAL_LINE,
        COLLIDER_TYPE_DEFAULT
    };

    struct Collider
    {
        COLLIDER_TYPE type_ = COLLIDER_TYPE_DEFAULT;

        float data_ = -1;

        Collider() = default;

        ~Collider() = default;

        void set(COLLIDER_TYPE type, float data);
    };

    struct PhysObject
    {
        GameObject* boss_ptr_ = nullptr;

        sf::Vector2f coord_;
        sf::Vector2f speed_;
        sf::Vector2f acc_;

        Collider collider_{};

        PhysObject();

        ~PhysObject();

        void set_boss(GameObject* boss);

        void move();

        bool check_collision(PhysObject* someone);

        bool check_position();

    };


    struct GraphObject
    {
        GameObject* boss_ptr_ = nullptr;

        sf::Sprite sprite_{};

        GraphObject(){};

        ~GraphObject();

        void set_boss(oak::GameObject* boss);

        void set_texture(const char* filename);

        void draw();
    };


    struct GameObject
    {
        OBJECT_TYPES type_ = OBJECT_TYPES_DEFAULT;

        PhysObject physeg_{};
        GraphObject grapheg_{};

        bool is_alive_ = true;

        GameObject()  = delete;

        GameObject(OBJECT_TYPES type);

        ~GameObject();

        void set_dependences();

        virtual void collide_response(GameObject* someone) = 0;

        virtual void draw();

        void move();

        virtual void come_back(){};
    };



    struct OakEngine
    {
        GameObject** run_list_ = nullptr;

        size_t obj_amount_ = 0;

        sf::Event current_event_{};


        OakEngine();

        ~OakEngine();

        void add(GameObject* obj);

        void handle_event(sf::Event event);

        void tick();

        void collide_all();

    };



}

#include "OakEngine.hpp"
#endif //OAKENGINE_H

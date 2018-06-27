#ifndef COLLECTOR_H
#define COLLECTOR_H

/*=====================================================================================
 *
 *                              Welcome to the Game Collector
 *
 *
 *
 *  created by Nikita Dubovik
 /========================================================================================*/
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "acorn.h"
#include "OakEngine/OakEngine.h"
#include "objects/Heroes.h"

namespace oak
{
    struct Game
    {
        void run();

        void measure(Experiment* experiment);
    };
}



#include "Collector.hpp"


#endif //COLLECTOR_H

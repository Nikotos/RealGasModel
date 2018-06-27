#include <iostream>
#include <SFML/Graphics.hpp>


//TODO upgrade to singleton (it isn't simple)
#include "Collector/window.h"

#include "Collector/Collector.h"


int main()
{
try{

    srand(time(NULL));

    oak::Game gama;

    gama.run();
    }
   catch (Acorn* acorn)
   {
       acorn->tell_user();
   }

    return 0;

}
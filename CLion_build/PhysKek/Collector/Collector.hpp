#ifndef COLLECTOR_HPP
#define COLLECTOR_HPP


#include "Collector.h"
#include "objects/Heroes.h"



void oak::Game::run()
{
    window.setFramerateLimit(50);

    Experiment experiment{};
    OakEngine engine{};

    for (int i = 0 ; i < oak_config::BALLS_AMOUNT; i++)
    {
        engine.add(&experiment.gas_[i]);
    }

    engine.add(&experiment.box_.left_);
    engine.add(&experiment.box_.right_);
    engine.add(&experiment.box_.top_);
    engine.add(&experiment.box_.bottom_);


    while ((window.isOpen() && info_window.isOpen()))
    {
        sf::Event event1;
        sf::Event event2;

        while ((window.pollEvent(event1)) || info_window.pollEvent(event2))
        {
            if (event1.type == sf::Event::Closed)
            {
                window.close();
            }

            else if (event2.type == sf::Event::Closed)
            {
                info_window.close();
            }

        }

        if (oak::SAMPLE % 300 == 0)
        {
            measure(&experiment);
            printf("%f\n",experiment.measure_energy());
        }

        if (oak::SAMPLE % 900 == 0)
        {
            experiment.make_tex_file();

        }

        window.clear();
        engine.tick();
        window.display();


    }

}


void oak::Game::measure(Experiment* experiment)
{
    info_window.clear();
    experiment->display_distribution();
    info_window.display();

}



#endif //COLLECTOR_HPP

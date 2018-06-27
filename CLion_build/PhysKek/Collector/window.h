#ifndef WINDOW_H
#define WINDOW_H

#define WINDOW_WIDE 1200
#define WINDOW_HEIGHT 900


#define INFO_WINDOW_WIDE 600
#define INFO_WINDOW_HEIGHT 900



sf::RenderWindow window (sf::VideoMode(WINDOW_WIDE, WINDOW_HEIGHT), "test");
sf::RenderWindow info_window (sf::VideoMode(INFO_WINDOW_WIDE, INFO_WINDOW_HEIGHT), "test");


#endif // WINDOW_H
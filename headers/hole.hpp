#ifndef NIBBLES_HOLE_HPP
#define NIBBLES_HOLE_HPP

#include <SFML/Graphics.hpp>


class Hole{

private:
    sf::RectangleShape holeShape;

public:
    Hole(sf::Vector2f position, sf::Vector2f size);

    sf::RectangleShape getShape();

};



#endif 

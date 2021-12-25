#ifndef NIBBLES_APPLE_HPP
#define NIBBLES_APPLE_HPP

#include <SFML/Graphics.hpp>


class Apple{
private:
    sf::CircleShape sprite;
    

public:
    Apple();
    
    void setPosition(sf::Vector2f newPosition);

    sf::CircleShape getSprite();

};

#endif






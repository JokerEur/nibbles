#include "apple.hpp"

Apple::Apple(){
    sf::Vector2f startingPosition(400, 400);
    sprite.setRadius(10);
    sprite.setFillColor(sf::Color::Red);
    sprite.setPosition(startingPosition);
}

void Apple::setPosition(sf::Vector2f newPosition){
    sprite.setPosition(newPosition);
}

sf::CircleShape Apple::getSprite(){
    return sprite;
}
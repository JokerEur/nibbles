#include "hole.hpp"

Hole::Hole(sf::Vector2f position, sf::Vector2f size){
    holeShape.setSize(size);
    holeShape.setFillColor(sf::Color(128,128,128));
    holeShape.setPosition(position);
}

sf::RectangleShape Hole::getShape(){
    return holeShape;
}
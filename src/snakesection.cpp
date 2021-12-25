#include "snakesection.hpp"

SnakeSection::SnakeSection(sf::Vector2f startPosition) {
  section.setSize(sf::Vector2f(20, 20));
  section.setFillColor(sf::Color::Green);
  section.setPosition(startPosition);
  position = startPosition;
}

sf::Vector2f SnakeSection::getPosition() {
  return position;
}

void SnakeSection::setPosition(sf::Vector2f newPosition) {
  position = newPosition;
}

sf::RectangleShape SnakeSection::getShape() {
  return section;
}

void SnakeSection::update() {
  section.setPosition(position);
}
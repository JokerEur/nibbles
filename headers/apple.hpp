#ifndef NIBBLES_APPLE_HPP
#define NIBBLES_APPLE_HPP

#include <SFML/Graphics.hpp>


class Apple{
private:
    sf::CircleShape sprite;
    

public:
    Apple();
    /**
     * @brief Устанавливает ноую позицию для объекта
     * 
     * @param newPosition Новая позиция
     */
    void setPosition(sf::Vector2f newPosition);

    /**
     * @brief Позволяет получить спрайт объекта
     * 
     * @return sf::CircleShape sprite
     */
    sf::CircleShape getSprite();

};

#endif






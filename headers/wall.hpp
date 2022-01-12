#ifndef NIBBLES_WALL_HPP
#define NIBBLES_WALL_HPP

#include <SFML/Graphics.hpp>


class Wall{

private:
    sf::RectangleShape wallShape;

public:

    /**
     * @brief Конструктор для нового объекта Wall
     * 
     * @param position Позиция
     * @param size Размер
     */
    Wall(sf::Vector2f position, sf::Vector2f size);

    /**
     * @brief Получить форму объекта Wall
     * 
     * @return sf::RectangleShape wallShape
     */
    sf::RectangleShape getShape();


};



#endif 

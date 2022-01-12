#ifndef NIBBLES_HOLE_HPP
#define NIBBLES_HOLE_HPP

#include <SFML/Graphics.hpp>


class Hole{

private:
    sf::RectangleShape holeShape;

public:
    /**
     * @brief Конструктор для нового объекта Hole
     * 
     * @param position Позиция
     * @param size Размер
     */
    Hole(sf::Vector2f position, sf::Vector2f size);


    /**
     * @brief Получить форму объекта Hole
     * 
     * @return sf::RectangleShape holeSahep
     */
    sf::RectangleShape getShape();

};



#endif 

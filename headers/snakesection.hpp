#ifndef NIBBLES_SNAKESECTION_HPP
#define NIBBLES_SNAKESECTION_HPP

#include <SFML/Graphics.hpp>

class SnakeSection
{
private:
    sf::Vector2f position;
    sf::RectangleShape section;

public:

    /**
     * @brief Конструктор для нового объекта sakeSection
     * 
     * @param startPosition  Стартовая позиция для секции
     */
    explicit SnakeSection(sf::Vector2f startPosition);

    /**
     * @brief Получить позицию объекта
     * 
     * @return sf::Vector2f posiotion
     */
    sf::Vector2f getPosition();
    
    /**
     * @brief Установить новую позицию
     * 
     * @param newPosition 
     */
    void setPosition(sf::Vector2f newPosition);

    /**
     * @brief Получть форму объекта SnakeSection
     * 
     * @return sf::RectangleShape section
     */
    sf::RectangleShape getShape();

    /**
     * @brief Обновляет позицию секции
     * 
     */
    void update();
};

#endif
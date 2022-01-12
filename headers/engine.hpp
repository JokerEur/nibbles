#ifndef NIBBLES_ENGINE_HPP
#define NIBBLES_ENGINE_HPP

#include "snakesection.hpp"
#include "apple.hpp"
#include "wall.hpp"
#include "hole.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <deque>
#include <utility> 
#include <fstream>

class Engine
{
private:
    // Window
    sf::Vector2f resolution;
    sf::RenderWindow window;
    const unsigned int FPS = 60;
    static const sf::Time TimePerFrame;

    

    std::vector<SnakeSection> snake;

    int snakeDirection;
    std::deque<int> directionQueue;
    int snakeSpeed;
    int sectionToAdd;
    int applesEatenOnThisLevel;
    int applesEatenTotal;
    unsigned long long int score;

    Apple apple;

    std::vector<Wall> wallSections;
    std::vector<std::pair<Hole,Hole>> holeSections;
    int currentLevel;
    int maxLevels;
    std::vector<std::string> levels;

    sf::Font mainFont;

    sf::Text titleText;
    sf::Text applesEatenText;
    sf::Text currentLevelText;
    sf::Text scoreText;

    sf::Text pauseText;
    sf::Text gameoverText;
    sf::Text pressEnterText;

    sf::Time timeSinceLastMove;

    int currentGameState;
    int lastGameState;

public:
    Engine();

    /**
     * @brief Перечесление для направления змейхи 
     * 
     */
    enum Direction
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    /**
     * @brief Перечесление для состояния игры 
     * 
     */
    enum GameState
    {
        RUNNING,
        PAUSED,
        GAMEOVER
    };

    
    /**
     * @brief Позволяет взаимодействовать со змейкой
     * 
     * 
     */
    void input();

    /**
     * @brief Позваляет добавлять новое направление в очеред направления
     * 
     * @param newDirection Новое направление змейки
     */
    void addDirection(int newDirection);

    void update();

    /**
     * @brief Позволяет отрисовать объекты на экране 
     * 
     */
    void draw();

    /**
     * @brief Создаёт новую змейку на экране
     * 
     */
    void newSnake();

    /**
     * @brief Добавляет новую секию к змейке
     * 
     */
    void addSnakeSection();
    
    /**
     * @brief Размещает яблоко на карте
     * 
     */
    void moveApple();

    /**
     * @brief Начинает новый уровень
     * 
     */
    void beginNextLevel();

    /**
     * @brief Устанавливает паузу
     * 
     * 
     * 
     */
    void Pause();

    /**
     * @brief 
     * 
     */
    void StartGame();

    /**
     * @brief Позволяет редактировать текст, который будет выведен на экран
     * 
     * @param txtItem Объект класса sf::Text
     * @param font Шрифт
     * @param value Значение строки
     * @param size Размер отображаемого текста
     * @param color Цвет
     */
    static void manageText(sf::Text *txtItem, const sf::Font &font, const std::string &value, int size, sf::Color color);

    /**
    * @brief Проверяет файл levels.txt на наличие уровней
    *
    */
    void checkLevelFiles();

    /**
     * @brief Загружает уровень
     * 
     * @param levelsNumber Индекс уровня
     */
    void loadLevel(int levelsNumber);

    /**
     * @brief Основной цикл игры
     * 
     */
    void run();
};

#endif
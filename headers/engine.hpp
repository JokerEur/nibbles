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

    enum Direction
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };
    enum GameState
    {
        RUNNING,
        PAUSED,
        GAMEOVER
    };

    void input();
    void addDirection(int newDirection);
    void update();

    void draw();

    void newSnake();
    void addSnakeSection();

    void moveApple();

    void beginNextLevel();
    void Pause();
    void StartGame();
    static void manageText(sf::Text *txtItem, const sf::Font &font, const std::string &value, int size, sf::Color color);

    void checkLevelFiles();
    void loadLevel(int levelsNumber);

    // The main loop will be in the run function
    void run();
};

#endif
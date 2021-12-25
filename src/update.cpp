#include "engine.hpp"

void Engine::update()
{

    if (timeSinceLastMove.asSeconds() >= sf::seconds(1.f / static_cast<float>(snakeSpeed)).asSeconds())
    {
        sf::Vector2f thisSectionPosition = snake[0].getPosition();
        sf::Vector2f lastSectionPosition = thisSectionPosition;

        if (!directionQueue.empty())
        {
            switch (snakeDirection)
            {
            case Direction::UP:
                if (directionQueue.front() != Direction::DOWN)
                {
                    snakeDirection = directionQueue.front();
                }
                break;
            case Direction::DOWN:
                if (directionQueue.front() != Direction::UP)
                {
                    snakeDirection = directionQueue.front();
                }
                break;
            case Direction::RIGHT:
                if(directionQueue.front() != Direction::LEFT){
                        snakeDirection = directionQueue.front();
                }
                break;
            case Direction::LEFT:
                if(directionQueue.front() != Direction::RIGHT){
                    snakeDirection = directionQueue.front();
                }
                break;
            }
            directionQueue.pop_front();
        }


        score += snake.size() + (applesEatenTotal + 1);
        scoreText.setString("score  " + std::to_string(score));
        sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
        scoreText.setPosition(sf::Vector2f(resolution.x - scoreTextBounds.width - 20 , - 5));
         
        if(sectionToAdd){
            addSnakeSection();
            --sectionToAdd;
        }


        switch(snakeDirection){
            case Direction::RIGHT:
                snake[0].setPosition(sf::Vector2f(thisSectionPosition.x + 20,thisSectionPosition.y));
                break;
            case Direction::LEFT:
                snake[0].setPosition(sf::Vector2f(thisSectionPosition.x-20, thisSectionPosition.y));
                break;
            case Direction::UP:
                snake[0].setPosition(sf::Vector2f(thisSectionPosition.x,thisSectionPosition.y - 20)); 
                break;
            case Direction::DOWN:
                snake[0].setPosition(sf::Vector2f(thisSectionPosition.x,thisSectionPosition.y+20));
                break;
        }


        for(int s = 1; s < snake.size(); ++s){
            thisSectionPosition = snake[s].getPosition();
            snake[s].setPosition(lastSectionPosition);
            lastSectionPosition = thisSectionPosition;
        }
        

        for(auto & s : snake){
            s.update();
        }

        if(snake[0].getShape().getGlobalBounds().intersects(apple.getSprite().getGlobalBounds())){

            applesEatenOnThisLevel += 1;
            applesEatenTotal += 1;
            applesEatenText.setString("apples  " + std::to_string(applesEatenTotal));
            sf::FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
            applesEatenText.setPosition(sf::Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width+30,-5));

            bool beginNewLevel = false;

            if(applesEatenOnThisLevel >= 5){
                if (currentLevel < maxLevels){
                    beginNewLevel = true;
                    beginNextLevel();
                }
            }

            if(!beginNewLevel){

                sectionToAdd += 4;
                ++snakeSpeed;
                moveApple();
            }
        }


        for(int s = 1; s < snake.size(); ++s){
            if(snake[0].getShape().getGlobalBounds().intersects(snake[s].getShape().getGlobalBounds())){
                currentGameState = GameState::GAMEOVER;
            }
        }


        for(auto &w : wallSections){
            if(snake[0].getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds())){
                currentGameState = GameState::GAMEOVER;
            }
        }













        timeSinceLastMove = sf::Time::Zero;
    } //!END//
}
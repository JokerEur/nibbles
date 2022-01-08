#include "engine.hpp"

void Engine::draw() {
  window.clear(sf::Color::Black);


  for(auto &w : wallSections){
    window.draw(w.getShape());
  }



  window.draw(apple.getSprite()); 

  // Draw snake sections
  for (auto & s : snake) {
    window.draw(s.getShape());
  }
  
  for(auto &h :holeSections){
    window.draw(h.first.getShape());
    window.draw(h.second.getShape());
  }

  window.draw(titleText);
  window.draw(currentLevelText);
  window.draw(applesEatenText);
  window.draw(scoreText);

  if(currentGameState == GameState::GAMEOVER){
    window.clear();
    window.draw(gameoverText);
    window.draw(pressEnterText);
  }

  if(currentGameState == GameState::PAUSED){
    window.draw(pauseText);
  }


  window.display();
}
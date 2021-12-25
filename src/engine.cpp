#include "engine.hpp"

const sf::Time Engine::TimePerFrame = sf::seconds(1.f / 60.f);

Engine::Engine()
{
  resolution = sf::Vector2f(800, 600);
  window.create(sf::VideoMode(resolution.x, resolution.y), "Nibbles", sf::Style::Default);
  window.setFramerateLimit(FPS);
  maxLevels = 0;
// 
  checkLevelFiles();

  StartGame();


  mainFont.loadFromFile("assets/fonts/ka1.ttf");
  manageText(&titleText,mainFont,"Nibbles",23, sf::Color::Red);
  sf::FloatRect titleTextBounds = titleText.getLocalBounds();
  titleText.setPosition(sf::Vector2f(resolution.x/2 - titleTextBounds.width / 2,-7));

  manageText(&currentLevelText,mainFont,"level 1" , 20 , sf::Color::Blue);
  currentLevelText.setPosition(sf::Vector2f(20,-5));
  sf::FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();

  manageText(&applesEatenText,mainFont, "apples  0",20,sf::Color::Blue);
  applesEatenText.setPosition(sf::Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 30, -5));

  manageText(&scoreText, mainFont,"score  " + std::to_string(score), 20 , sf::Color::Blue);
  sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
  scoreText.setPosition(sf::Vector2f(resolution.x - scoreTextBounds.width - 20 , -5));

  manageText(&gameoverText,mainFont,"GAME OVER", 75 , sf::Color::White);
  sf::FloatRect gameoverTextBounds = gameoverText.getLocalBounds();
  gameoverText.setPosition(sf::Vector2f(resolution.x / 2 - gameoverTextBounds.width/2,200));
  gameoverText.setOutlineColor(sf::Color::Black);
  gameoverText.setOutlineThickness(2);

  manageText(&pressEnterText, mainFont, "Press ENTER to try again", 38, sf::Color::Green);
  sf::FloatRect pressEnterTextBounds = pressEnterText.getLocalBounds();
  pressEnterText.setPosition(sf::Vector2f(resolution.x /2 - pressEnterTextBounds.width /2,300));
  pressEnterText.setOutlineColor(sf::Color::Black);
  pressEnterText.setOutlineThickness(2);

  manageText(&pauseText,mainFont,"PAUSED",75,sf::Color::White);
  sf::FloatRect pauseTextBounds = pauseText.getLocalBounds();
  pauseText.setPosition(sf::Vector2f(resolution.x / 2 - pauseTextBounds.width/2,200));
  pauseText.setOutlineColor(sf::Color::Black);
  pauseText.setOutlineThickness(2);
  
  
}

void Engine::checkLevelFiles()
{
  std::ifstream levelsManifest("assets/levels/levels.txt");
  std::ifstream testFile;
  for (std::string manifestLine; getline(levelsManifest, manifestLine);)
  {
    testFile.open("assets/levels/" + manifestLine);
    if (testFile.is_open())
    {
      levels.emplace_back("assets/levels/" + manifestLine);
      testFile.close();
      ++maxLevels;
    }
  }
}


void Engine::manageText(sf::Text *textItem , const sf::Font &font, const std::string &value, int size , sf::Color color){
  textItem->setFont(font);
  textItem->setString(value);
  textItem->setCharacterSize(size);
  textItem->setFillColor(color);
}


void Engine::StartGame()
{
  score = 0;
  snakeSpeed = 2;
  snakeDirection = Direction::RIGHT;
  timeSinceLastMove = sf::Time::Zero;
  sectionToAdd = 0;
  directionQueue.clear();
  wallSections.clear();
  applesEatenOnThisLevel = 0;
  applesEatenTotal = 0;

  currentLevel = 1;

  loadLevel(currentLevel);
  newSnake();
  moveApple();
  currentGameState = GameState::RUNNING;
  lastGameState = currentGameState;
  currentLevelText.setString("level  " + std::to_string(currentLevel)); 
  applesEatenText.setString("apples  " + std::to_string(applesEatenTotal));
  sf::FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
  applesEatenText.setPosition(sf::Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width+30,-5));
  scoreText.setString("score  " + std::to_string(score));
  sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
  scoreText.setPosition(sf::Vector2f(resolution.x - scoreTextBounds.width - 20 , - 5));
}

void Engine::loadLevel(int levelsNumber)
{
  std::string levelFile = levels[levelsNumber - 1];
  std::ifstream level(levelFile);
  std::string line;
  if (level.is_open())
  {
    for (int y = 0; y < 30; ++y)
    {
      getline(level, line);
      for (int x = 0; x < 40; ++x)
      {
        if (line[x] == 'x')
        {
          wallSections.emplace_back(Wall(sf::Vector2f(x * 20, y * 20), sf::Vector2f(20, 20)));
        }
      }
    }
  }
  level.close();
}

void Engine::beginNextLevel(){
  currentLevel+= 1;
  wallSections.clear();
  directionQueue.clear();

  snakeSpeed = 2 + currentLevel;
  snakeDirection = Direction::RIGHT;
  sectionToAdd = 0;
  applesEatenOnThisLevel = 0;

  loadLevel(currentLevel);
  newSnake();
  moveApple();

  currentLevelText.setString("level  " + std::to_string(currentLevel)); 
  sf::FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
  applesEatenText.setPosition(sf::Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width+30,-5));

}

void Engine::newSnake()
{
  snake.clear();
  snake.emplace_back(sf::Vector2f(100, 100));
  snake.emplace_back(sf::Vector2f(80, 100));
  snake.emplace_back(sf::Vector2f(60, 100));
}

void Engine::addSnakeSection()
{
  sf::Vector2f newSectionPosition = snake[snake.size() - 1].getPosition();
  snake.emplace_back(newSectionPosition);
}

void Engine::moveApple()
{

  sf::Vector2f appleResolution = sf::Vector2f(resolution.x / 20 - 2, resolution.y / 20 - 2);
  sf::Vector2f newAppleLocation;
  bool badLocation = false;
  srand(time(nullptr));
  do
  {
    badLocation = false;
    newAppleLocation.x = static_cast<float>(1 + rand() / ((RAND_MAX + 1u) / static_cast<int>(appleResolution.x))) * 20;
    newAppleLocation.y = static_cast<float>(1 + rand() / ((RAND_MAX + 1u) / static_cast<int>(appleResolution.y))) * 20;

    for (auto &s : snake)
    {
      if (s.getShape().getGlobalBounds().intersects(sf::Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20)))
      {
        badLocation = true;
        break;
      }
    }

    for(auto &w : wallSections){
      if(w.getShape().getGlobalBounds().intersects(sf::Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20))){
        badLocation = true;
        break;
      }
    }



  } while (badLocation);
  apple.setPosition(newAppleLocation);
}

void Engine::Pause()
{
  if (currentGameState == GameState::RUNNING)
  {
    lastGameState = currentGameState;
    currentGameState = GameState::PAUSED;
  }
  else if (currentGameState == GameState::PAUSED)
  {
    currentGameState = lastGameState;
  }
}

void Engine::run()
{

  sf::Clock clock;

  while (window.isOpen())
  {
    sf::Time DT = clock.restart();

    if (currentGameState == GameState::PAUSED || currentGameState == GameState::GAMEOVER)
    {

      input();

      if (currentGameState == GameState::GAMEOVER)
      {

        draw();
      }

      sf::sleep(sf::milliseconds(3));
      continue;
    }

    timeSinceLastMove += DT;

    input();
    update();
    draw();
  }
}
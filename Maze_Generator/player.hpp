//
//  Player.hpp
//  SFML1
//
//  Created by GO AWAY SCOTT on 11/16/18.
//  Copyright © 2018 et. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "maze.hpp"
#include <SFML/Graphics.hpp>

class Player : public sf::Sprite {
    
protected:
  int x;
  int y;

  sf::Texture playerTexture;
  sf::Texture ladderTexture;;
  
  int targetX;
  int targetY;

  Maze& maze;

  bool atTarget() const;

  sf::Sprite ladder;
  
public:

  bool InputTest(sf::RenderWindow * window);
  
  Player(int x, int y, int targetX, int targetY, Maze& maze);
  
  bool move(Direction dir, sf::RenderWindow * window);

  void draw(sf::RenderWindow* window);

  void randomizeTarget();
  
};

#endif /* maze_hpp */

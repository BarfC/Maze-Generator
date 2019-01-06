//
//  Player.cpp
//  Maze_Generator
//
//  Created by GO AWAY SCOTT on 12/4/18.
//  Copyright © 2018 et. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

#include <iostream>

#include "player.hpp"

Player::Player (int posX, int posY, int targetX, int targetY, Maze& maze)
  : x(posX), y(posY), targetX(targetX), targetY(targetY), maze(maze)
{
  
  playerTexture.loadFromFile( "res/player.png");
  setTexture(playerTexture);
  
  ladderTexture.loadFromFile("res/ladder.png");
  ladder.setTexture(ladderTexture);
  
  int size = maze.scale/ 2;
  setScale(size, size);
  
  ladder.setScale(size, size);
}

bool Player::atTarget() const
{
  return (x == targetX && y == targetY);
}

//returns true if player has located end
bool Player::move(Direction dir, sf::RenderWindow * window){
  cell& current = maze.at(x, y);
  if(current.noWall(dir)){
    current.drawCell(window, maze.scale);
    
    //std::cout << "x,y before " << dir << " delta:" << x << ", " << y << std::endl;
    
    maze.delta(x, y, dir);
    //std::cout << "x,y after delta:" << x << ", " << y << std::endl;
    
    draw(window);
    window->display();
    return atTarget();
  }
  return false;
}


void Player::draw(sf::RenderWindow* window){
  //std::cout << "drawing player and ladder" << std::endl;
  maze.at(targetX, targetY).drawCell(window, maze.scale);
  ladder.setPosition(targetX * maze.scale * 6, targetY * maze.scale * 6);
  window->draw(ladder);  //std::cout << "setting sprite pos to " << x * maze.scale * 6 << ", " << y * maze.scale * 6 << std::endl;
  setPosition(x * maze.scale * 6, y * maze.scale * 6);
  window->draw(*this);  
}


bool Player::InputTest(sf::RenderWindow* window)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      
      //std::cout << "FOUND LEFT ARROW" << std::endl;
      return move(West, window);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      //std::cout << "FOUND RIGHT ARROW" << std::endl;
      return move(East, window);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      //std::cout << "FOUND UP ARROW" << std::endl;
      return move(North, window);
    }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      //std::cout << "FOUND DOWN ARROW" << std::endl;
      return move(South, window);
    }
}

void Player::randomizeTarget()
{
  do
    {
  targetX = rand() % maze.getSize();
  targetY = rand() % maze.getSize();
    } while(atTarget());
}


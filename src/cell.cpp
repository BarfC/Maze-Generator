//
//  maze.cpp
//  Maze_Generator
//
//  Created by GO AWAY SCOTT on 12/4/18.
//  Copyright © 2018 et. All rights reserved.
//


#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

#include <iostream>
#include "cell.hpp"

const char* DIR[] = {"West", "East", "South", "North"};

Direction opposite(Direction dir) {
  switch (dir) {
  case North:
    return South;
  case South:
    return North;
  case West:
    return East;
  case East:
    return West;
  }
}


std::vector<sf::Texture> cell::tileTextures;

cell::cell (int posX, int posY)
  : x(posX), y(posY), used{0}
{
    
    //load texture array
    if ( tileTextures.empty()){
        //names of images
      std::string directions[] = { "closed",
				   "n",
				   "s",
				   "ns",
				   "e",
				   "ne",
				   "se",
				   "nse",
				   "w",
				   "nw",
				   "sw",
				   "nsw",
				   "ew",
				   "new",
				   "sew",
				   "nsew"
      };
        for(int i = 0; i < 16; i++) {
            sf::Texture t;
            t.loadFromFile(resourcePath() + directions[i] + ".png");
            tileTextures.push_back(t);
        }
    }
    
    
}

bool cell::use(Direction dir)
{
  used[dir] = true;
}

bool cell::isOpen() const
{
  return !(used[North] || used[South] || used[East] || used[West]);
}

void cell::position(int& px, int& py) const
{
  px = x;
  py = y;
}

void cell::drawCell(sf::RenderWindow * window, int scale){
    spriteNum = spriteIndex();
    setTexture(tileTextures[spriteNum]);
    setPosition(x * imageSize * scale, y * imageSize * scale);
    setScale(scale, scale);
    window->draw(*this);
    //std::cout << "drew texture with index " << spriteNum << " at "  << x << ", " << y << std::endl;
    
}

int cell::spriteIndex() const {
  //std::cout << "north:" << north << " south:" << south << " east:" << east << " west:" << west << " total: " << (north << 3) + (south << 2) + (east << 1) + west << std::endl;

  return (used[North] << 0) + (used[South] << 1) + (used[East] << 2) + (used[West] << 3);
}


//
//  cell.hpp
//  SFML1
//
//  Created by GO AWAY SCOTT on 11/16/18.
//  Copyright © 2018 et. All rights reserved.
//

#ifndef cell_hpp
#define cell_hpp

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

extern const char* DIR[];

enum Direction { North, South, East, West };
Direction opposite(Direction dir);

class cell : public sf::Sprite {

public:
    static const int imageSize = 6;

protected:
    
  bool used[4];

public:


  // Position.
  const int x;
  const int y;

 
  // True if the given wall is removed.
  static std::vector<sf::Texture> tileTextures;
    
  cell( int x, int y );
    
  int spriteNum;
  
  int spriteIndex() const;
  
  bool isOpen() const;

  void position(int& x, int& y) const;

  bool use(Direction dir);

  void drawCell(sf::RenderWindow *, int scale);

  bool noWall(Direction dir) const
  {
    return used[dir];
  }
};

#endif /* cell_hpp */

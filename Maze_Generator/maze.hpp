//
//  vector.hpp
//  SFML1
//
//  Created by GO AWAY SCOTT on 11/16/18.
//  Copyright © 2018 et. All rights reserved.
//

#ifndef maze_hpp
#define maze_hpp


#include "cell.hpp"
#include <SFML/Graphics.hpp>

class Maze {
protected:
  
  friend class Player;
  
  const int sizeX;
  const int sizeY;
  // current generation location
  int mazeX, mazeY;
  
  std::vector<cell*> trace;
  std::vector<cell> mazeData;
  
  cell& at(int x, int y) { return mazeData[y * sizeX + x]; }
  const cell& at(int x, int y) const { return mazeData[y * sizeX + x]; }

  bool isOpen(int x, int y, Direction dir) const;
  bool isOpen(int x, int y) const;
  std::vector<Direction> available(int x, int y) const;  

  bool findNew();
  
public:
  Maze(int sizeX = 1, int sizeY = 1, int scale = 1);

  void SetupArray(int, int);//MazeSize

  static void delta(int& x, int& y, Direction dir); 
  void draw(sf::RenderWindow * ); //int = scale
    
  void generate();

  bool canMove (int x, int y, Direction dir) const;
  
  bool step();
    
  void openCell();

  const int scale;

  int getSize()
  {
    return sizeX;
  }

  void resetData();
  
};

#endif /* maze_hpp */

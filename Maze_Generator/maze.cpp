//
//  maze.cpp
//  Maze_Generator
//
//  Created by GO AWAY SCOTT on 12/4/18.
//  Copyright © 2018 et. All rights reserved.
//

#include "maze.hpp"
#include "cell.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void Maze::draw(sf::RenderWindow* w)
{
    //std::cout << "test" << std::endl;
    for(int i =0; i < mazeData.size(); i++){
        mazeData[i].drawCell(w, scale);
    }
}

Maze::Maze( int x, int y, int scale)
  : sizeX(x), sizeY(y), scale(scale)
{
  for (int y = 0; y < sizeY; y++)
  {
    for (int x = 0; x < sizeX; x++)
    {
      cell c(x, y);
      mazeData.push_back( c );
    }
  }
}

void Maze::generate()
{
    mazeX = 0;
    mazeY = 0;
    while(true){
      while (step()) {
      }
      if ( !findNew())
      {
	break;
      }
    }
}

/**
 * Return true if cell is in grid and is closed
 */
bool Maze::isOpen(int x, int y) const
{
  if ( x < 0 || x >= sizeX) return false;
  if ( y < 0 || y >= sizeY) return false;
  return at(x, y).isOpen();
}

/**
 * Return true if cell is in grid and is closed
 */
void Maze::delta(int& x, int& y, Direction dir)
{
  switch (dir){
  case North:
    y--;
    break;
  case South:
    y++;
    break;
  case West:
    x--;
    break;
  case East:
    x++;
    break;
  }
}  

/**
 * Return true if cell is in grid and is closed
 */
bool Maze::isOpen(int x, int y, Direction dir) const
{
  delta(x, y, dir);
  return isOpen(x,y);
}


std::vector<Direction> Maze::available(int x, int y) const
{
  //store absolute coordinates and then relative coordinates
    std::vector<Direction> open;
    if (isOpen(mazeX, mazeY, West))
      // can go West
      open.push_back(West);
    
    if (isOpen(mazeX, mazeY, East))
      // can go East
      open.push_back(East);
    
    if (isOpen(mazeX, mazeY, North))
      // can go North
      open.push_back(North);
    
    if (isOpen(mazeX, mazeY, South))
      // can go South
      open.push_back(South);

    return open;
}
bool Maze::step(){
  std::vector<Direction> open = available(mazeX,mazeY);

  if (open.size() == 0 ) {
    return false;
  }
     
  int selected = rand() % open.size();
  Direction dir = open[selected];
  
  std::cout << "From " << mazeX << ", " << mazeY << " by " <<
    DIR[dir] << " to #" << selected << " < " << open.size() << std::endl;

  trace.push_back(&at(mazeX,mazeY));
  
  at(mazeX, mazeY).use(dir);
  delta(mazeX, mazeY, dir);
  at(mazeX, mazeY).use(opposite(dir));

  return true;
}

bool Maze::canMove (int x, int y, Direction dir) const
{
  return at(x, y).noWall(dir);
}

bool Maze::findNew()
{
  while(!trace.empty()){
    cell& last = *trace.back();
    trace.pop_back();
    last.position(mazeX, mazeY); 
    if ( available(mazeX, mazeY).empty())
    {
      std::cout << "No neighbors: " << mazeX << ", " << mazeY << std::endl;
    }
    else {
      std::cout << "Restart: " << mazeX << ", " << mazeY << std::endl;
      return true;
    }
  }

  return false;
}

void Maze::resetData()
{
  mazeData.clear();
 for (int y = 0; y < sizeY; y++)
  {
    for (int x = 0; x < sizeX; x++)
    {
      cell c(x, y);
      mazeData.push_back( c );
    }
  }
}

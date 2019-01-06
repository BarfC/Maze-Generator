
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include <unistd.h>

#include "maze.hpp"
#include "player.hpp"


#include "ResourcePath.hpp"

std::vector<int> currentPos (0,0);
#define cellSize 10
#define gridSize 10

int main()
{
    sf::Color background(100,100,100);
    int scale = 30;
    
    
    std::cout << "TEST" << std::endl;
    Maze maze(gridSize, gridSize, cellSize);

    Player player(0, 0, rand() % maze.getSize(), rand() % maze.getSize(), maze);
    player.randomizeTarget();
		  
    // Create the main window
    sf::RenderWindow window(sf::VideoMode( gridSize * cellSize * 6, gridSize * cellSize * 6),
                            "Maze Runner");
    window.setFramerateLimit(10);
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }

    
    maze.generate();
     // Clear screen
        window.clear(background);
        // Draw the sprite
        
        maze.draw(&window);
	player.draw(&window);
        // Update the window
        window.display();
    // Start the game loop
    while (window.isOpen())
    {
      
      if(player.InputTest(&window))
	{
	  //generate new level
	  std::cout << "LEVEL ENDED" << std::endl;
	  maze.resetData();
	  maze.generate();
	  player.randomizeTarget();

	  maze.draw(&window);
	  player.draw(&window);
        // Update the window
	  window.display();
	}
      
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();

	    }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
	usleep(100000);//0.1s
    }

    return EXIT_SUCCESS;
}


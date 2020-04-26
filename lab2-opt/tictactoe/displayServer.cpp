//
//  displayServer.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Copyright © 2019 Tarek Abdelrahman. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;

#include "tictactoe.h"
#include "gameState.h"

// Function prototype for playMove
void playMove(gameState&);

// The display server function
int displayServer() {

    /************************************************************************************************************/
    /* Insert code that loads the various images used by the game and creates the sprites                       */
    /* ECE244 Student: The loading of the X image is shown. Repeat for the rest of the images                  */
    /************************************************************************************************************/

    // Get the X image
    sf::Texture X_texture;
    if (!X_texture.loadFromFile("/share/copy/ece244f/lab2/data/X.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite X_sprite(X_texture);
    
    // Get the O image
    sf::Texture O_texture;
    if (!O_texture.loadFromFile("/share/copy/ece244f/lab2/data/O.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite O_sprite(O_texture);
    
    // Get the blank image
    sf::Texture Blank_texture;
    if (!Blank_texture.loadFromFile("/share/copy/ece244f/lab2/data/B.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite Blank_sprite(Blank_texture);
    
    // First, we find the sizes of the images so we can determine the size of the window we must create
    // The images (X, O and Black) are assumed to be square are are all of the same size
    // Thus, we just find the size of one of them
    
    // The tile size is the size of the images
    const int tileSize = O_texture.getSize().x;
    
    // The cell borders (thick lines) are rectangles
    // The size of these rectangles is 1/20th of the size of the tile by 3 
    const int barWidth = tileSize/20;
    const int barHeight = boardSize*tileSize + (boardSize-1)*barWidth;
    
    // The size of the window in pixels can now be calculated
    const int windowSize = boardSize*tileSize + (boardSize-1)*barWidth;
    
    // Create the main window: it has a title bar and a close button, but is not resizable
    // ECE244 Student: you should replace ECE244 in the title of the window by your login ID
    sf::RenderWindow window(
    sf::VideoMode(windowSize, windowSize),
            "Tic-Tac_Toe (brooks56 Display Server)", 
            sf::Style::Titlebar | sf::Style::Close
    );
    // Set the Icon that appears in the task bar when the window is minimized
    // ECE244 Student: add your code here
    sf::Image RenderWindowIcon;
    if (!RenderWindowIcon.loadFromFile("/share/copy/ece244f/lab2/data/icon.jpg")) {
        return EXIT_FAILURE;
    }
    window.setIcon(RenderWindowIcon.getSize().x,
    RenderWindowIcon.getSize().y,
    RenderWindowIcon.getPixelsPtr());	 
    // Create the horizonal (vertical) borders as rectangles of sizes barWidth and barHeight (barHeight and barWidth)
    // ECE244 Student: insert your code here
    sf::RectangleShape winBar(sf::Vector2f(barWidth, 3*barHeight));
    
    
    /************************************************************************************************************/
    /* Create and initialize the game state object                                                              */
    /************************************************************************************************************/
    gameState game_state;

    game_state.set_clickedRow(0);
    game_state.set_clickedColumn(0);
    game_state.set_moveValid(true); // This must start out as true
    game_state.set_gameOver(false);
    game_state.set_winCode(0);
    game_state.set_turn(true);  // X always plays first
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            game_state.set_gameBoard(i,j,Empty);
        }
    }
    
    /************************************************************************************************************/
    /* This is the main event loop of the code                                                                  */
    /************************************************************************************************************/
    
    // Start the game loop that runs as long as the window is open
    while (window.isOpen()) {
        // The event
        sf::Event event;
        
        // Process the events
        while (window.pollEvent(event)) {
            
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            // Left mouse button pressed: get the click position and update the game
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !game_state.get_gameOver()) {
                // left mouse button is pressed: get the coordinates in pixels
                // ECE244 Student: Insert your code to get the coordinates here                
                
                sf::Vector2i mousePosition = Mouse::getPosition(window);
                
                // Convert the pixel coordinates into game board rows and columns
                // Just divide by tileSize
                // Observe that the x axis is the rows and the y axis is the columns
                // Also make sure that row and column values are valid
                // ECE244 Student: Insert your code below
                
                int row = (mousePosition.y)/tileSize;
                int col = (mousePosition.x)/tileSize;
                
                // Update the game state object with the coordinates
                // ECE244 Student: insert code to update the object game_state here
                                
                game_state.set_clickedColumn(col);
                game_state.set_clickedRow(row);
                
                // Update the game with the new move
                // ECE244 Student: invoke the playMove function here
                
                playMove(game_state);
            }
        }

        // If the move is invalid, go to next event
        if (!game_state.get_moveValid()) continue;
                
        // Insert code to draw the tiles using the sprites created earlier
        // You must determine the position of each cell on the grid, taking into account the width of
        // the border and then position the sprite there and draw it.
        // Draw the entire board, cell borders included,
        // reflecting any move that has just happened (check the gameBoard array)
        // Further, if the game is over and one player wins, you must create and draw a rectangle of
        // windowSize width and 10 pixels height to indicate the winning marks
        // The fill of this rectangle should be white

        // ECE244 Student: insert your code here
        
        
        if (game_state.get_moveValid())
        {
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                   if (game_state.get_gameBoard(i, j) == 0)
                   {
                       Blank_sprite.setPosition(j*(tileSize+barWidth), i*(tileSize+barWidth));
                       window.draw(Blank_sprite);
                   } else if (game_state.get_gameBoard(i, j) == 1)
                   {
                        X_sprite.setPosition(j*(tileSize+barWidth), i*(tileSize+barWidth));
                        window.draw(X_sprite);
                   } else if (game_state.get_gameBoard(i, j) == -1)
                   {
                        O_sprite.setPosition(j*(tileSize+barWidth), i*(tileSize+barWidth));
                        window.draw(O_sprite);
                   }
                }
            }
        }
                
        if (game_state.get_winCode() == 1)
        {
            winBar.setPosition(0, 0.5*(tileSize+barWidth));
            winBar.setRotation(-90);
            window.draw(winBar);
        } else if (game_state.get_winCode() == 2)
        {
            winBar.setPosition(0, 1.5*(tileSize+barWidth));
            winBar.setRotation(-90);
            window.draw(winBar);
        } else if (game_state.get_winCode() == 3)
        {
            winBar.setPosition(0, 2.5*(tileSize+barWidth));
            winBar.setRotation(-90);
            window.draw(winBar);
        } else if (game_state.get_winCode() == 4)
        {
            winBar.setPosition(0.5*(tileSize+barWidth), 0);
            window.draw(winBar);
        } else if (game_state.get_winCode() == 5)
        {
            winBar.setPosition(1.5*(tileSize+barWidth), 0);
            window.draw(winBar);
        } else if (game_state.get_winCode() == 6)
        {
            winBar.setPosition(2.5*(tileSize+barWidth) - barWidth, 0);
            window.draw(winBar);
        } else if (game_state.get_winCode() == 7)
        {
            winBar.setPosition(0, 0);
            winBar.setRotation(-45);
            window.draw(winBar);
        } else if (game_state.get_winCode() == 8)
        {
            winBar.setPosition(3*(tileSize+barWidth), 0);
            winBar.setRotation(45);
            window.draw(winBar);
        }

 
       // Display to the window
       window.display();
    }
    
    return EXIT_SUCCESS;
}


/******************************************************************************
* Copyright 2024 John Brann
*
* Chess Coordinate Practice Game
* main.cpp
*
* This program implements a simple chess coordinate practice game using SFML.
* A random chess coordinate is displayed and the user must click the correct
* square on the board before the 30 second timer runs out. Helps improve chess 
* players' visual recognition and response time for square coordinates by 
* displaying random locations.
*
* Main components:
*
* - Chess object: Handles game board, pieces, gameplay
* - SFML: Graphics, Window, user mouse input
* - GameState: Manages game state transitions (PREGAME, INGAME, POSTGAME)
*
*******************************************************************************/


#include <iostream>
#include <SFML/Graphics.hpp>
#include "chess.hpp"
#include <cstdlib>
#include <ctime>

int main() {

    // font 
    sf::Font font;
    font.loadFromFile("C:\\Users\\johnb\\SFMLFonts\\Mosk-Bold-700.ttf");

    // creates game object
    Chess game(font);

    // variables for timer/clock 
    sf::Clock timer;
    float time;
    // changes time limit
    float timeLimit = 30.f;

    sf::RenderWindow window(sf::VideoMode(game.getWindowWidth(), game.getWindowHeight()), "Chess Coordinate Practice");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
               window.close();
            }
            // PREGAME gamestate
            if (game.getCurrentGameState() == game.PREGAME) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (game.withinStartBox(event.mouseButton.x, event.mouseButton.y)) {
                            game.setNewGameState(game.INGAME);
                            // starts timer
                            timer.restart();
                        }
                    }
                }
            } // INGAME gamestate
            else if (game.getCurrentGameState() == game.INGAME) {
                time = timer.getElapsedTime().asSeconds();
                game.setTimerText(time);
                if (time >= timeLimit) {
                    game.setNewGameState(game.POSTGAME);
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        game.click(event.mouseButton.x, event.mouseButton.y);
                    }
                }
            } // POSTGAME gamestate
            else if (game.getCurrentGameState() == game.POSTGAME) {
                game.resetScore();
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (game.withinReStartBox(event.mouseButton.x, event.mouseButton.y)) {
                            game.setNewGameState(game.PREGAME);
                        }
                    }
                }
            }
            window.clear();
            window.draw(game);
            window.display();
        }
    }
    return 0;
}
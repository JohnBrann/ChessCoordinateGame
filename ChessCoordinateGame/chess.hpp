/******************************************************************************
* Copyright 2024 John Brann
*
* Chess Coordinate Training Game
* chess.hpp
* 
* Chess class is sf::Drawable to allow for a virtual void draw function makeing 
* drawing differnt game states easier
*
*******************************************************************************/

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <time.h>

class Chess : public sf::Drawable {
public:
	// Constructor. Initializes game objects, fonts, sizes, etc...
	Chess(sf::Font& font);

	// enumeration for different states of the game
	enum GameState { PREGAME, INGAME, POSTGAME };

	// window and square dimensions "getters"
	size_t getSquareSize()const;
	size_t getWindowHeight()const;
	size_t getWindowWidth()const;

	// "getter" for scoreString
	std::string getScoreString()const;

	// highlights clicked square in green (for correct guesses)
	void correctHighlight(int mouseX, int mouseY);

	// highlights clicked square in red (for incorrect guesses) 
	void incorrectHighlight(int mouseX, int mouseY);

	// checks if mouseclick is within board, returns true if inside, false if outside
	bool isSquarePressed(int mouseX, int mouseY);

	// generates random square (a-h, 1-8)
	std::string generateRandomSquare();

	// checks if mouseclick is correct square, returns true if yes, false if not
	bool checkSquare(std::string displayedSquare, int x, int y);

	// gets square in (a-h, 1-8) terms from mouseclick, returns square as string
	std::string getSquare(int x, int y);

	// handles INGAME game mechanics
	void click(int mousex, int mousey);

	// centers score on side panel
	void centerScore();

	// updates score
	void updateScore(bool& isCorrect);

	// "getter" for currentGameState
	GameState getCurrentGameState();

	// changes currentGameState "setter"
	void setNewGameState(GameState newState);

	// check if click is within startBox
	bool withinStartBox(int mousex, int mousey);

	// check if click is within startBox
	bool withinReStartBox(int mousex, int mousey);

	// "getter" for timerText
	sf::Text getTimerText();

	// sets timerText
	void setTimerText(int time);

	// resets score after game 
	void resetScore();

private:
	// virtual void draw function to display objects to screen depending on currentGameState
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

	// window size and square size variables
	size_t _SquareSize = 100;
	size_t _WindowWidth = _SquareSize * 11;
	size_t _WindowHeight = _SquareSize * 8;

	// _board vector that holds squares
	std::vector<sf::RectangleShape> _Board;

	// rectangle shapes
	sf::RectangleShape _LightSquare;
	sf::RectangleShape _DarkSquare;
	sf::RectangleShape _Highlight;
	sf::RectangleShape _cover;
	sf::RectangleShape _StartBox;
	sf::RectangleShape _RestartBox;

	// variables for score
	bool isCorrect = false; 
	int totalCorrect = 0;
	int totalGuessed = 0;

	// helper strings for on-screen text
	std::string displayedSquare;
	std::string scoreString;
	std::string finalScore;

	// on-screen text
	sf::Text coordText;
	sf::Text scoreText;
	sf::Text timerText;
	sf::Text presstostartText;
	sf::Text presstoRestartText;
	sf::Text finalScoreText;

	// enum variable to hold current game state
	GameState currentGameState;
};
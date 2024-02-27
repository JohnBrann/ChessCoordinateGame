/******************************************************************************
* Copyright 2024 John Brann
* 
* Chess Coordinate Training Game
* chess.cpp
* 
* The Chess class represents the core game logic and SFML handles graphics.
* The game has three states: pregame, in-game, and postgame.
*
* Key Components:
*
* - Chess: Board, pieces, game logic, scoring
* - Board: 2D vector of square sprites
* - Score: Tracks correct and total guesses
*
*******************************************************************************/

#include "chess.hpp"

// Constructor. Initializes game objects, fonts, sizes, etc...
Chess::Chess(sf::Font& font) {
    // light squares
    _LightSquare.setSize(sf::Vector2f(_SquareSize, _SquareSize));
    _LightSquare.setFillColor(sf::Color::White);

    // dark squares 
    _DarkSquare.setSize(sf::Vector2f(_SquareSize, _SquareSize));
    _DarkSquare.setFillColor(sf::Color{ 20, 100, 140, 255 });

    // highlight
    _Highlight.setSize(sf::Vector2f(_SquareSize, _SquareSize));
    _Highlight.setFillColor(sf::Color{ 20, 255, 20, 255 });
    _Highlight.setPosition(_WindowHeight,_WindowHeight);

    // pregame cover
    _cover.setSize(sf::Vector2f(_WindowWidth, _WindowHeight));
    _cover.setFillColor({ 20,20,20,220 });
    _cover.setPosition(0, 0);
    
    // press to start button
    _StartBox.setSize(sf::Vector2f(530, 150));
    _StartBox.setFillColor({ 30, 255, 80, 255 });
    _StartBox.setPosition(200, 200);

    // press to restart button
    _RestartBox.setSize(sf::Vector2f(570, 150));
    _RestartBox.setFillColor({ 255, 20, 80, 255 });
    _RestartBox.setPosition(200, 500);

    //Fills _Board vector 
    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                _LightSquare.setPosition(i * _SquareSize, j * _SquareSize);
                _Board.push_back(_LightSquare);
            }
            else {
                _DarkSquare.setPosition(i * _SquareSize, j * _SquareSize);
                _Board.push_back(_DarkSquare);
            }
        }
    }

    // coordinate text
    coordText.setFont(font);
    coordText.setPosition(880, 50);
    coordText.setCharacterSize(120);

    // score text
    scoreText.setFont(font);
    scoreText.setPosition(870, 275);
    scoreText.setCharacterSize(90);

    // timer text
    timerText.setFont(font);
    timerText.setPosition(860, 500);
    timerText.setCharacterSize(75);

    // press to start text
    presstostartText.setString("Press To Start");
    presstostartText.setFont(font);
    presstostartText.setFillColor(sf::Color::Black);
    presstostartText.setPosition(230, 220);
    presstostartText.setCharacterSize(75);

    // press to restart text
    presstoRestartText.setString("Press To Restart");
    presstoRestartText.setFont(font);
    presstoRestartText.setFillColor(sf::Color::Black);
    presstoRestartText.setPosition(220, 520);
    presstoRestartText.setCharacterSize(75);

    //final score text
    finalScoreText.setFont(font);
    finalScoreText.setPosition(195, 200);
    finalScoreText.setCharacterSize(90);

    // timer text
    timerText.setFont(font);
    timerText.setPosition(910, 560);
    timerText.setCharacterSize(130);
    
    // initializes starting random square
    displayedSquare = generateRandomSquare();
    coordText.setString(displayedSquare);

    // sets currentState (starting state) to PREGAME 
    currentGameState = PREGAME;
}

// window and square dimensions "getters"
size_t Chess::getSquareSize()const {
    return _SquareSize;
}
size_t Chess::getWindowHeight()const {
    return _WindowHeight;
}
size_t Chess::getWindowWidth()const {
    return _WindowWidth;
}

// "getter" for scoreString
std::string Chess::getScoreString()const {
    return scoreString;
}


// highlights clicked square in green (for correct guesses)
void Chess::correctHighlight(int mouseX, int mouseY) {
    size_t index;
    for (size_t i = 0; i < _Board.size(); i++) {
        if ((mouseX / _SquareSize) == (_Board.at(i).getPosition().x / _SquareSize)
            && (mouseY / _SquareSize) == (_Board.at(i).getPosition().y / _SquareSize)) {
            _Highlight.setFillColor(sf::Color{ 20, 255, 20, 255 });
            _Highlight.setPosition(_Board.at(i).getPosition());
        }
    }
}

// highlights clicked square in red (for incorrect guesses) 
void Chess:: incorrectHighlight(int mouseX, int mouseY) {
    size_t index;
    for (size_t i = 0; i < _Board.size(); i++) {
        if ((mouseX / _SquareSize) == (_Board.at(i).getPosition().x / _SquareSize)
            && (mouseY / _SquareSize) == (_Board.at(i).getPosition().y / _SquareSize)) {
            _Highlight.setFillColor(sf::Color::Red);
            _Highlight.setPosition(_Board.at(i).getPosition());
        }
    }
}

// checks if mouseclick is within board, returns true if inside, false if outside
bool Chess::isSquarePressed(int mouseX, int mouseY) {
    bool _cond = false;
    if ((mouseX >= 0 && mouseX <= _WindowHeight) && (mouseY >= 0 && mouseY <= _WindowWidth)) {
        return true;
    }
    return false;
}

// generates random square (a-h, 1-8)
std::string Chess::generateRandomSquare() {
    std::srand(std::time(nullptr));

    // generates random a-h
    char col = 'a' + std::rand() % 8;
    // generates random 1-8  
    int row = 1 + std::rand() % 8;

    std::string square = "";
    square += col;
    square += std::to_string(row);

    return square;
}

// gets square in (a-h, 1-8) terms from mouseclick, returns square as string
std::string Chess::getSquare(int x, int y) {

    int col = x / getSquareSize();
    int row = 7 - (y / getSquareSize());

    char letter = 'a' + col;
    int number = row + 1;

    std::string square = "";
    square += letter;
    square += std::to_string(number);

    return square;
}

// checks if mouseclick is correct square, returns true if yes, false if not
bool Chess::checkSquare(std::string displayedSquare, int x, int y) {
    std::string clickedSquare = getSquare(x, y);

    if (clickedSquare == displayedSquare) {
        return true;
    }
    else {
        return false;
    }
}

// handles INGAME game mechanics
void Chess::click(int mousex, int mousey) {
    std::string guessedSquare = getSquare(mousex, mousey);
    scoreText.setString(scoreString);

    if (isSquarePressed(mousex, mousey)) {
        if (checkSquare(displayedSquare, mousex, mousey)) {
            // correct 
            correctHighlight(mousex, mousey);
            // update score
            isCorrect = true;
            updateScore(isCorrect);
            centerScore();

            // scoreText
            scoreString = std::to_string(totalCorrect) + "/" + std::to_string(totalGuessed);
            scoreText.setString(scoreString);
        } else {
            // incorrect
            incorrectHighlight(mousex, mousey);
            // update score
            isCorrect = false;
            updateScore(isCorrect);
            centerScore();

            // scoreText
            scoreString = std::to_string(totalCorrect) + "/" + std::to_string(totalGuessed);
            scoreText.setString(scoreString);
        }
        // generates new square after click
        displayedSquare.clear();
        displayedSquare = generateRandomSquare();
        coordText.setString(displayedSquare);
    }
}

// centers score on side panel
void Chess::centerScore() {
    // centering score
    if (totalGuessed >= 10 || totalCorrect >= 10) {
        if (totalCorrect >= 10) {
            scoreText.setPosition(835, 275);
        }
        else {
            scoreText.setPosition(860, 275);
        }
    }
}

// updates score
void Chess::updateScore(bool& isCorrect) {
    if (isCorrect)
        totalCorrect++;

    totalGuessed++;
    scoreString = std::to_string(totalCorrect) + "/" + std::to_string(totalGuessed);
    finalScoreText.setString("Final Score: " + scoreString);
}

// "getter" for currentGameState
Chess::GameState Chess::getCurrentGameState() {
    return currentGameState;
}

// changes currentGameState "setter"
void Chess::setNewGameState(GameState newState) {
    currentGameState = newState;
}

// check if click is within startBox
bool Chess::withinStartBox(int mousex, int mousey) {
    if (_StartBox.getGlobalBounds().contains(mousex, mousey))
        return true;
    return false;
}

// check if click is within RestartBox
bool Chess::withinReStartBox(int mousex, int mousey) {
    if (_RestartBox.getGlobalBounds().contains(mousex, mousey))
        return true;
    return false;
}

// "getter" for timerText
sf::Text Chess::getTimerText() {
    return timerText;
}

// sets timerText
void Chess::setTimerText(int time) {
    timerText.setString(std::to_string(time));
}

// resets score after game 
void Chess::resetScore() {
    totalCorrect = 0;
    totalGuessed = 0;
}

// virtual void draw function to display objects to screen depending on currentGameState
void Chess::draw(sf::RenderTarget& target, sf::RenderStates states)const {
    //draws board
    for (int i = 0; i < _Board.size(); i++) {
        target.draw(_Board.at(i));
    }
    // draws PREGAME state
    if (currentGameState == PREGAME) {
        target.draw(_cover, states);
        target.draw(_StartBox, states);
        target.draw(presstostartText, states);
    } // draws INGAME state
    else if (currentGameState == INGAME) {
        target.draw(_Highlight, states);
        target.draw(scoreText, states);
        target.draw(coordText, states);
        target.draw(timerText, states);
    } // draws POSTGAME state
    else if (currentGameState == POSTGAME) {
        target.draw(_cover, states);
        target.draw(_RestartBox, states);
        target.draw(presstoRestartText, states);
        target.draw(finalScoreText, states);
    }
}

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iomanip>
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include "Welcome.h"
using namespace std;

string Window::playerName;

Window::Window(bool welcomeWindowOpen, bool gameWindowOpen, bool leaderboardWindowOpen, bool gamePaused, bool leftclick, bool rightclick,
    int screenwidth, int screenheight, int columns, int rows, bool flagTile, int mine_count, int minesAdjacent, int minesFound,
    int minesPlaced, int xcoord, int ycoord, vector<string> playerNames, vector<string> playerTimes, string winnerCompleteTime,
    string winnerTimeSeconds, int winnerMinutes, int winnerSeconds, int minutes, int seconds, int tempSeconds)
{
    this->welcomeWindowOpen = welcomeWindowOpen;
    this->gameWindowOpen = gameWindowOpen;
    this->leaderboardWindowOpen = leaderboardWindowOpen;
    this->gamePaused = gamePaused;
    this->leftclick = leftclick;
    this->rightclick = rightclick;
    this->screenwidth = screenwidth;
    this->screenheight = screenheight;
    this->columns = columns;
    this->rows = rows;
    this->flagTile = flagTile;
    // might not need flag count 


    // mine generation section
    this->maxMines = maxMines;
    this->minesAdjacent = minesAdjacent;
    this->minesFound = minesFound;
    this->minesPlaced = minesPlaced;
    this->xcoord = xcoord;
    this->ycoord = ycoord;

    this->debugmode = debugmode;
    this->beginClock = beginClock;

    // for playernames
    this->playerNames = playerNames;
    this->playerTimes = playerTimes;
    this->winnerTimeSeconds = winnerTimeSeconds;
    this->winnerSeconds = winnerSeconds;
    this->winnerMinutes = winnerMinutes;
    this->winnerCompleteTime = winnerCompleteTime;
    //string Window::playerName;

    //time 
    this->minutes = minutes;
    this->seconds = seconds;
    this->tempSeconds = tempSeconds;

    // for rf
    /*this->mineTile = mineTile;
    this->flagOnTile = flagOnTile;
    this->hiddenTile = hiddenTile;
    this->numBombsNearby = numBombsNearby;
    this->mineSprites = mineSprites;
    this->flagsprites = flagsprites;
    this->revealedSprites = revealedSprites;
    this->nearbyBombs = nearbyBombs;*/


    // hidden tiles, x and y clicked on, revealed tiles array
}

bool Window::welcomeWindow(sf::RenderWindow& welcomewindow)
{
    int screenwidth = 800;
    int screenheight = 600;
    //sf::RenderWindow welcomewindowdimensions(sf::VideoMode(800, 600), "Welcome Window");
    //welcomewindow.clear(sf::Color::Blue);

    // loading the font file 
    sf::Font font;
    font.loadFromFile("./files/font.ttf");

    // Create the text
    sf::Text text("", font, 20);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Underlined | sf::Text::Bold);
    text.setString("WELCOME TO MINESWEEPER");

    sf::FloatRect textCenter = text.getLocalBounds();
    text.setOrigin(textCenter.width / 2.0f, textCenter.height / 2.0f);
    text.setPosition(sf::Vector2f(screenwidth / 2.0f, (screenheight / 2.0f) - 150));

    sf::Text nameinput("", font, 20);
    nameinput.setFillColor(sf::Color::White);
    nameinput.setStyle(sf::Text::Bold);
    nameinput.setString("Enter your name:");

    sf::FloatRect nameCenter = nameinput.getLocalBounds();
    nameinput.setOrigin(nameCenter.width / 2.0f, nameCenter.height / 2.0f);
    nameinput.setPosition(sf::Vector2f(screenwidth / 2.0f, (screenheight / 2.0f) - 75));

    sf::Text actualname("", font, 18);
    actualname.setFillColor(sf::Color::Yellow);
    actualname.setStyle(sf::Text::Bold);
    actualname.setString("|");

    sf::FloatRect username = actualname.getLocalBounds();
    actualname.setOrigin(username.width / 2.0f, username.height / 2.0f);
    actualname.setPosition(sf::Vector2f(screenwidth / 2.0f, (screenheight / 2.0f) - 45));
    // FloatRect refer to stackoverflow link in questions, just setting origin

    // String to store the name input 
    string name;

    // bool closedwelcome = false;

    // Run the event loop
    while (welcomewindow.isOpen())
    {
        // create Event object sfml article (read)
        sf::Event event;
        while (welcomewindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                welcomewindow.close();
            }
            else if (event.type == sf::Event::TextEntered)
            {

                if (event.text.unicode < 128 && event.text.unicode != 8)
                {
                    char enteredCharacter = static_cast<char>(event.text.unicode);
                    // Append the character to the input string
                    if (enteredCharacter == ' ' && name.size() < 10)
                    {
                        name += " ";
                        actualname.setString(name + "|");
                    }

                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && name.size() > 0)
                    {
                        this->playerName = name;
                        //playerNames.push_back(name);
                        cout << "temp name variable is: " << name << endl;
                        cout << "playername is: " << playerName << endl;

                        // stores the playername for the leaderboard later on
                        welcomewindow.close();
                        return true;
                    }

                    if (std::isalpha(enteredCharacter))
                    {

                        if (name.size() < 10)
                        {
                            name += std::tolower(enteredCharacter);
                            name[0] = std::toupper(name[0]);

                            for (int i = 0; i < name.size(); i++)
                            {
                                name[i + 1] = std::tolower(name[i + 1]);
                            }
                            actualname.setString(name + "|");

                        }
                        else
                            break;
                    }
                    else
                    {
                        continue;
                    }

                }

                else if (sf::Keyboard::BackSpace && name.size() > 0)
                    // else if (sf::Keyboard::BackSpace && name.length() > 0)
                {
                    // Handle backspace key
                    name.pop_back();

                    // Update the text object
                    actualname.setString(name + "|");
                }

                // enter key closes window after name size is greater than 0

            }

        }

        // sets the window to blue
        // can be top or bottom 
        welcomewindow.clear(sf::Color::Blue);

        // draws the text onto the screen
        welcomewindow.draw(text);
        welcomewindow.draw(nameinput);
        welcomewindow.draw(actualname);

        // Display the welcome window
        welcomewindow.display();

        // Update the | character and its position
        sf::FloatRect username = actualname.getLocalBounds();
        actualname.setOrigin(username.width / 2.0f, username.height / 2.0f);
        actualname.setPosition(sf::Vector2f(screenwidth / 2.0f, (screenheight / 2.0f) - 45));
    }
    return false;
}

void Window::gameWindow(int columns, int rows, int numMines, string currPlayer)
{
    sf::RenderWindow gameWindow(sf::VideoMode(screenwidth = columns * 32, screenheight = (rows * 32) + 100), "MINESWEEPERRRR WOOOOOOOO");

    currPlayer = Window::playerName;
    cout << "gamewindow name: " << currPlayer << endl << endl;

    int maxTiles = columns * rows;
    cout << "maxTiles Value: " << maxTiles << endl;

    //cout << "the playername is " << this->playername << endl;

    int revealedTiles = 0;
    this->columns = columns;
    this->rows = rows;
    this->maxMines = numMines;
    this->mineCounter = numMines;


    cout << "Number of Mines: " << maxMines << endl;

    sf::Texture happyface;
    sf::Sprite happyfacesprite;
    happyface.loadFromFile("./files/images/face_happy.png");
    happyfacesprite.setTexture(happyface);
    //happyfacesprite.setOrigin(screenwidth / 2.0f, screenheight / 2.0f);
    // don't need to set origin for buttons
    happyfacesprite.setPosition(((columns / 2.0) * 32) - 32, 32 * (rows + 0.5f));

    sf::Texture sadface;
    sf::Sprite sadfacesprite;
    sadface.loadFromFile("./files/images/face_lose.png");
    sadfacesprite.setTexture(sadface);
    sadfacesprite.setPosition(((columns / 2.0) * 32) - 32, 32 * (rows + 0.5f));

    sf::Texture coolface;
    sf::Sprite coolfacesprite;
    coolface.loadFromFile("./files/images/face_win.png");
    coolfacesprite.setTexture(coolface);
    coolfacesprite.setPosition(((columns / 2.0) * 32) - 32, 32 * (rows + 0.5f));

    sf::Texture timer;
    sf::Sprite timerpic;
    timer.loadFromFile("./files/images/digits.png");
    timerpic.setTexture(timer);
    timerpic.setPosition(((columns / 2.0) * 32) - 32, 32 * (rows + 0.5f));
    // temporary position, however timer consists of two positions, the minutes
    // and the seconds
    // will most likely be separate from this function is order to draw it out, might do in int main()


    sf::Texture debug;
    sf::Sprite debugsprite;
    debug.loadFromFile("./files/images/debug.png");
    debugsprite.setTexture(debug);
    debugsprite.setPosition(((columns) * 32) - 304, 32 * ((rows)+0.5f));


    sf::Texture play;
    sf::Sprite playsprite;
    play.loadFromFile("./files/images/play.png");
    playsprite.setTexture(play);
    playsprite.setPosition(((columns) * 32) - 240, 32 * ((rows)+0.5f));


    sf::Texture pause;
    sf::Sprite pausesprite;
    pause.loadFromFile("./files/images/pause.png");
    pausesprite.setTexture(pause);
    pausesprite.setPosition(((columns) * 32) - 240, 32 * ((rows)+0.5f));


    sf::Texture leaderboard;
    sf::Sprite leaderboardsprite;
    leaderboard.loadFromFile("./files/images/leaderboard.png");
    leaderboardsprite.setTexture(leaderboard);
    leaderboardsprite.setPosition(((columns) * 32) - 176, 32 * ((rows)+0.5f));

    sf::Texture flag;
    sf::Sprite flagsprite;
    flag.loadFromFile("./files/images/flag.png");
    flagsprite.setTexture(flag);

    sf::Texture hidden;
    sf::Sprite hiddenSprite;
    hidden.loadFromFile("./files/images/tile_hidden.png");
    hiddenSprite.setTexture(hidden);

    sf::Texture revealed;
    sf::Sprite revealedSprite;
    revealed.loadFromFile("./files/images/tile_revealed.png");
    revealedSprite.setTexture(revealed);

    sf::Texture mine;
    sf::Sprite mineSprite;
    mine.loadFromFile("./files/images/mine.png");
    mineSprite.setTexture(mine);

    // this is for the flag/mine counter system
    sf::Texture counter;
    sf::Sprite counterSprite;
    counter.loadFromFile("./files/images/digits.png");
    counterSprite.setTexture(counter);

    sf::Vector2f counterPosition(33, 32 * (rows + 0.5f) + 16);
    sf::IntRect counterTextureRect(0, 0, 21, 32);
    counterSprite.setTextureRect(counterTextureRect);
    counterSprite.setPosition(counterPosition);
    // everything above this too

    // timer function for minutes
    sf::Texture timerMinute;
    sf::Sprite minuteSprite;
    timerMinute.loadFromFile("./files/images/digits.png");
    minuteSprite.setTexture(timerMinute);

    sf::Vector2f minutePosition((columns * 32) - 97, 32 * (rows + 0.5f) + 16);
    sf::IntRect minuteTextureRect(0, 0, 21, 32);
    minuteSprite.setTextureRect(minuteTextureRect);
    minuteSprite.setPosition(minutePosition);
    // everything above is minutes

    // timer function for seconds 
    sf::Texture timerSecond;
    sf::Sprite secondSprite;
    timerSecond.loadFromFile("./files/images/digits.png");
    secondSprite.setTexture(timerSecond);

    sf::Vector2f secondPosition((columns * 32) - 54, 32 * (rows + 0.5f) + 16);
    sf::IntRect secondTextureRect(0, 0, 21, 32);
    secondSprite.setTextureRect(secondTextureRect);
    secondSprite.setPosition(secondPosition);
    // everything above is seconds

    sf::Clock currentClock;
    int tempMinute = this->minutes;
    int tempSecond = this->seconds;
    int tempTimerCountMinute = 0;
    int tempTimerCountSecond = 0;
    int tempNum = 0;

    auto start = chrono::steady_clock::now();
    auto pauseTime = chrono::steady_clock::now();
    // start time and pause time declarations
    // everything above is timer function

    // everything below is for digits
    sf::Texture digitOne;
    sf::Sprite digitOneSprite;
    digitOne.loadFromFile("./files/images/number_1.png");
    digitOneSprite.setTexture(digitOne);

    sf::Texture digitTwo;
    sf::Sprite digitTwoSprite;
    digitTwo.loadFromFile("./files/images/number_2.png");
    digitTwoSprite.setTexture(digitTwo);

    sf::Texture digitThree;
    sf::Sprite digitThreeSprite;
    digitThree.loadFromFile("./files/images/number_3.png");
    digitThreeSprite.setTexture(digitThree);

    sf::Texture digitFour;
    sf::Sprite digitFourSprite;
    digitFour.loadFromFile("./files/images/number_4.png");
    digitFourSprite.setTexture(digitFour);

    sf::Texture digitFive;
    sf::Sprite digitFiveSprite;
    digitFive.loadFromFile("./files/images/number_5.png");
    digitFiveSprite.setTexture(digitFive);

    sf::Texture digitSix;
    sf::Sprite digitSixSprite;
    digitSix.loadFromFile("./files/images/number_6.png");
    digitSixSprite.setTexture(digitSix);

    sf::Texture digitSeven;
    sf::Sprite digitSevenSprite;
    digitSeven.loadFromFile("./files/images/number_7.png");
    digitSevenSprite.setTexture(digitSeven);

    sf::Texture digitEight;
    sf::Sprite digitEightSprite;
    digitEight.loadFromFile("./files/images/number_8.png");
    digitEightSprite.setTexture(digitEight);

    // digits for recursive checking

    vector<vector<bool>> mineTile(this->columns, vector<bool>(this->rows, false));
    vector<vector<bool>> flagOnTile(this->columns, vector<bool>(this->rows, false));
    vector<vector<bool>> hiddenTile(this->columns, vector<bool>(this->rows, true));
    vector<vector<int>> numBombsNearby(this->columns, vector<int>(this->rows, 0));

    // nullptr is out of bounds 
    // temp for flag placement, later implement in the tiles class
    // check geeksforgeeks for implementation vector info
    vector<sf::Sprite> mineSprites;
    vector<sf::Sprite> flagsprites;
    vector<sf::Sprite> revealedSprites;
    vector<sf::Sprite> nearbyBombs;

    bool tempWinner = false;

    // going to tell you how many nearby bombs there are to that square
    // sf::Vector2f numSprites; 



    srand(time(NULL));

    /*sf::Texture mine;
    sf::Sprite mineSprite;
    mine.loadFromFile("./files/images/mine.png");
    mineSprite.setTexture(mine);*/

    while (minesPlaced < maxMines)
    {
        int x = rand() % columns;
        int y = rand() % rows;
        //cout << "x value is: " << x << ", " << y << endl;

        if (!mineTile[x][y])
        {
            mineTile[x][y] = true;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    int tempx = x + i;
                    int tempy = y + j;
                    if ((tempx >= 0 && tempy >= 0 && tempx < columns && tempy < rows) || (i == 0 && j == 0))
                    {
                        numBombsNearby[tempx][tempy]++;

                        // neighbors of the bombs 
                    }

                }

            }
            minesPlaced++;
            sf::Sprite tempMineSprite = mineSprite;
            tempMineSprite.setPosition(x * 32, y * 32);
            mineSprites.push_back(tempMineSprite);
        }
        else
        {
            cout << "testing, a mine already exists there" << endl;
        }

    }

    for (int a = 0; a < columns; a++)
    {

        for (int b = 0; b < rows; b++)
        {
            if (numBombsNearby[a][b] > 0 && mineTile[a][b] == false)
            {
                sf::Sprite tempNumSprite;
                if (numBombsNearby[a][b] == 1)
                {

                    digitOneSprite.setTexture(digitOne);
                    tempNumSprite = digitOneSprite;

                }
                else if (numBombsNearby[a][b] == 2)
                {
                    digitTwoSprite.setTexture(digitTwo);
                    tempNumSprite = digitTwoSprite;

                }
                else if (numBombsNearby[a][b] == 3)
                {
                    digitThreeSprite.setTexture(digitThree);
                    tempNumSprite = digitThreeSprite;

                }
                else if (numBombsNearby[a][b] == 4)
                {
                    digitFourSprite.setTexture(digitFour);
                    tempNumSprite = digitFourSprite;

                }
                else if (numBombsNearby[a][b] == 5)
                {
                    digitFiveSprite.setTexture(digitFive);
                    tempNumSprite = digitFiveSprite;

                }
                else if (numBombsNearby[a][b] == 6)
                {
                    digitSixSprite.setTexture(digitSix);
                    tempNumSprite = digitSixSprite;

                }
                else if (numBombsNearby[a][b] == 7)
                {
                    digitSevenSprite.setTexture(digitSeven);
                    tempNumSprite = digitSevenSprite;

                }
                else if (numBombsNearby[a][b] == 8)
                {
                    digitEightSprite.setTexture(digitEight);
                    tempNumSprite = digitEightSprite;

                }
                tempNumSprite.setPosition(a * 32, b * 32);
                nearbyBombs.push_back(tempNumSprite);
            }

        }
    }

    //cout << "made it past checkpoint " << endl;
    while (gameWindow.isOpen())
    {

        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                gameWindow.close();
                exit(0);
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    leftclick = true;

                    sf::Vector2i mousePosition = sf::Mouse::getPosition(gameWindow);
                    //sf::FloatRect playbutton = playsprite.getGlobalBounds();
                    //sf::FloatRect debugbutton = debugsprite.getGlobalBounds();
                    //sf::FloatRect leaderboardbutton = leaderboardsprite.getGlobalBounds();

                    if (playsprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && gamelose == false && gamewin == false)
                    {

                        if (gamePaused)
                        {
                            gamePaused = false;
                            gameBegan = true;
                            playsprite.setTexture(pause);

                            auto pause = chrono::steady_clock::now();
                            std::cout << "the game has resumed" << endl;

                            if (!beginClock)
                            {
                                beginClock = true;
                                // begin clock 


                                start = chrono::steady_clock::now();
                                // auto currTime = start - pauseTime;
                                seconds += tempSeconds;
                                // timer starts here
                                auto end = chrono::steady_clock::now();
                                chrono::duration<double> elapsed_seconds = end - start;
                                seconds = (int)elapsed_seconds.count();

                                cout << "time: " << seconds << "s\n";

                            }

                        }

                        else
                        {
                            gamePaused = true;

                            playsprite.setTexture(play);
                            std::cout << "the game has been paused within the playsprite" << endl;
                            if (beginClock)
                            {
                                auto pause = chrono::steady_clock::now();
                                tempSeconds += chrono::duration_cast<chrono::seconds>(pause - start).count();
                                cout << "tempsecond value:" << tempSeconds << endl;
                                beginClock = false;
                                // this statement adds the seconds when you pause the game, however
                                // we need it to be added once we resume the game 
                            }

                        }

                    }

                    // realistically only for debugging purposes, not graded
                    else if (debugsprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && gamelose == false && gamePaused == false && gamewin == false)
                    {
                        cout << "clicked debug" << endl;
                        //playsprite.setTexture(pause);
                        debugmode = !debugmode;

                    }

                    else if (leaderboardsprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        cout << "leaderboard button has been pressed " << endl;
                        gamePaused = true;
                        playsprite.setTexture(play);
                        std::cout << "the game has been paused within leaderboard" << endl;

                        if (beginClock)
                        {
                            auto pause = chrono::steady_clock::now();
                            tempSeconds += chrono::duration_cast<chrono::seconds>(pause - start).count();
                            cout << "tempsecond value:" << tempSeconds << endl;
                            beginClock = false;
                            // this statement adds the seconds when you pause the game, however
                            // we need it to be added once we resume the game 
                        }
                        leaderboardWindowOpen = true;
                        leaderboardWindow(columns, rows);

                        //}
                        //// either way if it it pressed it sets the game to paused, and stops the clock
                        //cout << "the leaderboard button was pressed" << endl;
                        //gamePaused = false;
                        //beginClock = false;
                        //cout << "we have entered the leaderboard statement " << endl;


                    }
                    // end of the leaderboard sprite 


                    // restart the board
                    else if (happyfacesprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || sadfacesprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        for (int i = 0; i < columns; i++)
                        {
                            for (int j = 0; j < rows; j++)
                            {
                                mineTile[i][j] = false;
                                flagOnTile[i][j] = false;
                                hiddenTile[i][j] = true;
                                numBombsNearby[i][j] = 0;

                            }
                        }

                        // nullptr is out of bounds 
                        // temp for flag placement, later implement in the tiles class
                        // check geeksforgeeks for implementation vector info
                        mineSprites.clear();
                        flagsprites.clear();
                        revealedSprites.clear();
                        nearbyBombs.clear();
                        mineCounter = numMines;
                        minesPlaced = 0;
                        gamePaused = true;
                        gamelose = false;
                        gamewin = false;
                        gameBegan = false;
                        beginClock = false;
                        debugmode = false;
                        seconds = 0;
                        playsprite.setTexture(play);
                        // this->gameWindow(columns, rows); LOL 


                        while (minesPlaced < maxMines)
                        {

                            int x = rand() % columns;
                            int y = rand() % rows;
                            //cout << "x value is: " << x << ", " << y << endl;

                            if (!mineTile[x][y])
                            {
                                cout << "entered minefield" << "\t x value: " << x << "\t y value: " << y << endl;
                                mineTile[x][y] = true;
                                for (int i = -1; i < 2; i++)
                                {
                                    for (int j = -1; j < 2; j++)
                                    {
                                        int tempx = x + i;
                                        int tempy = y + j;
                                        if ((tempx >= 0 && tempy >= 0 && tempx < columns && tempy < rows) || (i == 0 && j == 0))
                                        {
                                            numBombsNearby[tempx][tempy]++;

                                            // neighbors of the bombs 
                                        }

                                    }

                                }
                                minesPlaced++;
                                sf::Sprite tempMineSprite = mineSprite;
                                tempMineSprite.setPosition(x * 32, y * 32);
                                mineSprites.push_back(tempMineSprite);
                            }
                            else
                            {
                                cout << "testing, a mine already exists there" << endl;
                            }

                        }
                        cout << "mines sprite size" << mineSprites.size() << endl;

                        for (int a = 0; a < columns; a++)
                        {

                            for (int b = 0; b < rows; b++)
                            {
                                if (numBombsNearby[a][b] > 0 && mineTile[a][b] == false)
                                {
                                    sf::Sprite tempNumSprite;
                                    if (numBombsNearby[a][b] == 1)
                                    {

                                        digitOneSprite.setTexture(digitOne);
                                        tempNumSprite = digitOneSprite;

                                    }
                                    else if (numBombsNearby[a][b] == 2)
                                    {
                                        digitTwoSprite.setTexture(digitTwo);
                                        tempNumSprite = digitTwoSprite;

                                    }
                                    else if (numBombsNearby[a][b] == 3)
                                    {
                                        digitThreeSprite.setTexture(digitThree);
                                        tempNumSprite = digitThreeSprite;

                                    }
                                    else if (numBombsNearby[a][b] == 4)
                                    {
                                        digitFourSprite.setTexture(digitFour);
                                        tempNumSprite = digitFourSprite;

                                    }
                                    else if (numBombsNearby[a][b] == 5)
                                    {
                                        digitFiveSprite.setTexture(digitFive);
                                        tempNumSprite = digitFiveSprite;

                                    }
                                    else if (numBombsNearby[a][b] == 6)
                                    {
                                        digitSixSprite.setTexture(digitSix);
                                        tempNumSprite = digitSixSprite;

                                    }
                                    else if (numBombsNearby[a][b] == 7)
                                    {
                                        digitSevenSprite.setTexture(digitSeven);
                                        tempNumSprite = digitSevenSprite;

                                    }
                                    else if (numBombsNearby[a][b] == 8)
                                    {
                                        digitEightSprite.setTexture(digitEight);
                                        tempNumSprite = digitEightSprite;

                                    }
                                    tempNumSprite.setPosition(a * 32, b * 32);
                                    nearbyBombs.push_back(tempNumSprite);
                                }

                            }
                        }
                    }

                    else if (!gamePaused)
                    {
                        int xtile = mousePosition.x / 32;
                        int ytile = mousePosition.y / 32;
                        sf::Vector2f tilePosition(xtile * 32, ytile * 32);
                        //std::cout << "checkpoint for entering if statement hiddensprite" << endl;
                        /*cout << "xtile value is: " << xtile << endl;
                        cout << "ytile value is: " << ytile << endl;
                        cout << "mouse x values: " << mousePosition.x << endl;
                        cout << "mouse y values: " << mousePosition.y << endl << endl;*/
                        if (!gamePaused && (xtile >= 0 && ytile >= 0 && xtile < columns && ytile < rows))
                        {
                            // if flag on tile, cannot reveal tile (update hidden sprite)
                            if (!flagOnTile[xtile][ytile])
                            {
                                leftclick = false;
                                //revealedTiles++;
                                rf(xtile, ytile, revealedSprite, hiddenTile, revealedSprites, flagOnTile, numBombsNearby);
                                //hiddenTile[xtile][ytile] = false;
                                //cout << "revealed tile testing draw" << endl;
                                //sf::Sprite tempRevealedSprite = revealedSprite;
                                //cout << "xtile pos: " << xtile << "\tytile pos: " << ytile << endl;
                                //tempRevealedSprite.setPosition(tilePosition.x, tilePosition.y);
                                //revealedSprites.push_back(tempRevealedSprite);
                            }
                            if (mineTile[xtile][ytile])
                            {
                                gamelose = true;
                                beginClock = false;
                                gamePaused = true;


                                cout << "there is a mine at this tile" << endl;
                                /*sf::Sprite tempMineSprite = mineSprite;
                                tempMineSprite.setPosition(tilePosition.x, tilePosition.y);
                                mineSprites.push_back(tempMineSprite);*/
                                leftclick = false;
                            }

                        }

                    }

                }

                if (event.mouseButton.button == sf::Mouse::Right) {
                    rightclick = true;

                    sf::Vector2i mousePosition = sf::Mouse::getPosition(gameWindow);

                    int xtile = mousePosition.x / 32;
                    int ytile = mousePosition.y / 32;
                    sf::Vector2f tilePosition(xtile * 32, ytile * 32);
                    /*cout << "xtile value is: " << xtile << endl;
                    cout << "ytile value is: " << ytile << endl;
                    cout << "mouse x values: " << mousePosition.x << endl;
                    cout << "mouse y values: " << mousePosition.y << endl << endl;*/
                    if (!gamePaused && (xtile >= 0 && ytile >= 0 && xtile < columns && ytile < rows))
                    {
                        if (flagOnTile.at(xtile).at(ytile))
                        {
                            flagOnTile[xtile][ytile] = false;
                            for (int i = 0; i < flagsprites.size(); i++)
                            {
                                // for removing the flagsprites if needed
                                sf::Vector2f temp = flagsprites[i].getPosition();
                                if ((temp.x / 32) == xtile && (temp.y / 32) == ytile)
                                {
                                    mineCounter++;
                                    flagsprites.erase(flagsprites.begin() + i);
                                    break;
                                }

                            }

                            cout << mineCounter << endl;
                            cout << "flag was removed" << endl;
                            rightclick = false;
                        }
                        else
                        {
                            bool tempHidden = hiddenTile.at(xtile).at(ytile);
                            if (tempHidden)
                            {
                                cout << "flag was drawn" << endl;
                                flagOnTile[xtile][ytile] = true;
                                sf::Sprite tempflagSprite = flagsprite;
                                tempflagSprite.setPosition(tilePosition.x, tilePosition.y);
                                flagsprites.push_back(tempflagSprite);
                                mineCounter--;
                                cout << mineCounter << endl;
                                rightclick = false;
                            }
                            else
                            {
                                cout << "no hidden tile here" << endl;
                            }


                        }
                        cout << "checkpoint 1" << endl;
                    }

                }

            }

        }
        if (leaderboardWindowOpen)
        {
            cout << "we have reached checkpoint" << endl;
            leaderboardWindow(columns, rows);
            std::cout << "the game has been paused" << endl;
        }

        // the win condition
        if (revealedSprites.size() == (maxTiles - maxMines))
        {
            debugmode = true;
            gamewin = true;
            gamePaused = true;
            beginClock = false;
            mineCounter = 0;
            cout << "winner winner chicken dinner" << endl;
            playerNames.push_back(currPlayer);
            cout << "current seconds: " << seconds << endl;
            winnerTimeSeconds += tempWinner ? "" : to_string(seconds);
            winnerMinutes = stoi(winnerTimeSeconds) / 60;
            winnerSeconds = stoi(winnerTimeSeconds) % 60;

            winnerCompleteTime += tempWinner ? "" : to_string(winnerSeconds);
            winnerCompleteTime += tempWinner ? "" : to_string(winnerMinutes);

            tempWinner = true;




            cout << "Total Winner Minutes: " << winnerMinutes << endl;
            cout << "Total Winner Seconds: " << winnerSeconds << endl;
            cout << "winnetCompleteTime currently is: " << winnerCompleteTime << endl;

            cout << "Total Seconds Elapsed: " << winnerTimeSeconds << endl;

            for (int i = 0; i < columns; i++)
            {
                for (int j = 0; j < rows; j++)
                {
                    flagOnTile[i][j] = true;
                    sf::Sprite tempflagSprite = flagsprite;
                    tempflagSprite.setPosition(i * 32, j * 32);
                    flagsprites.push_back(tempflagSprite);
                }
            }

        }

        // renders the hidden sprites
        gameWindow.clear(sf::Color::White);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                hiddenSprite.setPosition(j * 32, i * 32);
                gameWindow.draw(hiddenSprite);
            }
        }

        // renders the flagsprites vector
        for (int i = 0; i < flagsprites.size(); i++)
        {
            sf::Vector2f tempFlagSprites = flagsprites[i].getPosition();
            gameWindow.draw(flagsprites[i]);
        }

        // renders the revealed sprites vector
        for (int i = 0; i < revealedSprites.size(); i++)
        {
            gameWindow.draw(revealedSprites[i]);
        }

        // renders the mine sprites vector
        for (int i = 0; i < mineSprites.size(); i++)
        {

            sf::Vector2f tempMineSprites = mineSprites[i].getPosition();
            if (hiddenTile[tempMineSprites.x / 32][tempMineSprites.y / 32] == false || debugmode == true || gamelose == true)
            {
                gameWindow.draw(mineSprites[i]);
            }
        }

        // displays the nums or "bombs" nearby
        for (int i = 0; i < nearbyBombs.size(); i++)
        {

            sf::Vector2f tempTile = nearbyBombs[i].getPosition();
            if (hiddenTile[tempTile.x / 32][tempTile.y / 32] == false)
            {
                gameWindow.draw(nearbyBombs[i]);
            }
        }

        // FOR THE MINECOUNTER NOT THE TIMER
        // for the counter for mines;
        tempNum = mineCounter;
        int tempDigitCount = 0;

        if (tempNum < 0) {
            // draws the '-' symbol at (12, 32 * (rows + 0.5f) + 16)
            sf::IntRect textureRect(10 * 21, 0, 21, 32);
            cout << "we are in the negative block" << endl;
            counterSprite.setTextureRect(textureRect);
            counterSprite.setPosition(12, 32 * (rows + 0.5f) + 16);
            gameWindow.draw(counterSprite);

            // change tempNum to positive for digit drawing
            tempNum = -tempNum;
            // tempDigitCount = 0;
        }

        while (tempDigitCount < 2)
        {
            int tempDigit = tempNum % 10;
            tempNum /= 10;

            sf::IntRect counterTextureRect(tempDigit * 21, 0, 21, 32);
            counterSprite.setTextureRect(counterTextureRect);
            counterSprite.setPosition(counterPosition.x + (1 - tempDigitCount) * 21, counterPosition.y);
            gameWindow.draw(counterSprite);
            tempDigitCount++;
        }

        // game loss condition

        if (gamelose == true)
        {
            gameWindow.draw(sadfacesprite);
            playsprite.setTexture(play);
        }
        else if (gamewin == true)
        {
            gameWindow.draw(coolfacesprite);
            playsprite.setTexture(play);
        }
        else
        {
            gameWindow.draw(happyfacesprite);
        }

        gameWindow.draw(debugsprite);
        if (gameBegan == true)
        {
            gameWindow.draw(pausesprite);
        }
        else if (gameBegan == false)
        {
            gameWindow.draw(playsprite);
        }
        gameWindow.draw(playsprite);
        gameWindow.draw(leaderboardsprite);

        // TIMER, DO NOT MESS WITH ANYMORE DO NOT MOVE 
        int numDigits = 2;
        tempNum = seconds % 60;
        //cout << "seconds: " << seconds << endl;
        tempTimerCountSecond = 0;
        while (tempTimerCountSecond < numDigits)
        {

            //cout << "second NUM IS: " << tempNum << endl;
            int tempDigit = tempNum % 10;
            tempNum /= 10;
            sf::IntRect secondTextureRect(tempDigit * 21, 0, 21, 32);
            secondSprite.setTextureRect(secondTextureRect);
            secondSprite.setPosition(secondPosition.x + (1 - tempTimerCountSecond) * 21, secondPosition.y);
            gameWindow.draw(secondSprite);
            tempTimerCountSecond++;
        }


        tempNum = seconds / 60;
        tempTimerCountMinute = 0;
        while (tempTimerCountMinute < numDigits)
        {
            //cout << "minute Num is: " << tempNum << endl;
            int tempDigit = tempNum % 10;
            tempNum /= 10;
            sf::IntRect minuteTextureRect(tempDigit * 21, 0, 21, 32);
            minuteSprite.setTextureRect(minuteTextureRect);
            minuteSprite.setPosition(minutePosition.x + (1 - tempTimerCountMinute) * 21, minutePosition.y);
            gameWindow.draw(minuteSprite);
            tempTimerCountMinute++;
        }

        // restarts the clock
        if (beginClock == true)
        {
            auto end = chrono::steady_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            seconds = (int)elapsed_seconds.count() + tempSeconds;
        }



        gameWindow.display();
    }

};


void Window::rf(int x, int y, sf::Sprite& revealedSprite, vector<vector<bool>>& hiddenTile, vector<sf::Sprite>& revealedSprites,
    vector<vector<bool>>& flagOnTile, vector<vector<int>>& numBombsNearby)
{
    cout << "x value: " << x << "\ty value: " << y << endl;
    if ((x < 0 || y < 0 || x >= columns || y >= rows) || hiddenTile[x][y] == false || flagOnTile[x][y] == true)
    {
        cout << "returned early " << endl;
        return;
    }
    hiddenTile[x][y] = false;
    sf::Sprite tempRevealedSprite = revealedSprite;

    tempRevealedSprite.setPosition(x * 32, y * 32);

    revealedSprites.push_back(tempRevealedSprite);

    if (numBombsNearby[x][y] > 0)
    {
        return;
    }

    rf(x - 1, y, revealedSprite, hiddenTile, revealedSprites, flagOnTile, numBombsNearby);
    rf(x + 1, y, revealedSprite, hiddenTile, revealedSprites, flagOnTile, numBombsNearby);
    rf(x, y - 1, revealedSprite, hiddenTile, revealedSprites, flagOnTile, numBombsNearby);
    rf(x, y + 1, revealedSprite, hiddenTile, revealedSprites, flagOnTile, numBombsNearby);

}

bool Window::leaderboardWindow(int columns, int rows)
{
    sf::RenderWindow leaderWindow(sf::VideoMode(screenwidth = columns * 16, screenheight = (rows * 16) + 50), "Leaderboard");

    sf::Font font;
    font.loadFromFile("./files/font.ttf");

    // Create the text

    sf::Text playerText("", font, 18);
    playerText.setFillColor(sf::Color::White);
    playerText.setStyle(sf::Text::Bold);

    sf::FloatRect playerCenter = playerText.getLocalBounds();
    playerText.setOrigin(playerCenter.width / 2.0f, playerCenter.height / 2.0f);
    playerText.setPosition(sf::Vector2f((columns / 2.0f) + 50, (rows / 2.0f) + 50));

    auto start = chrono::steady_clock::now();

    int numLines = 0;
    string line;
    string playerTime;
    string playerNameinList;
    leaderboardWindowOpen = true;
    fstream leaderFile;
    leaderFile.open("./files/leaderboard.txt", ios_base::in || ios_base::out);
    if (leaderFile.is_open())
    {
        while (getline(leaderFile, line))
        {
            stringstream currLine(line);
            getline(currLine, playerTime, ':');
            int minutes = stoi(playerTime);
            getline(currLine, playerTime, ',');
            int seconds = stoi(playerTime);
            getline(currLine, playerNameinList);
            numLines += 1;

            std::ostringstream timeStream;
            timeStream << std::setfill('0') << std::setw(2) << minutes << ":"
                << std::setfill('0') << std::setw(2) << seconds;

            playerText.setString(playerText.getString() + "\n" + to_string(numLines) + ".\t " + timeStream.str() + "\t" + playerNameinList + "\n");


        }

    }
    sf::Text leaderboardText("", font, 20);
    leaderboardText.setFillColor(sf::Color::White);
    leaderboardText.setStyle(sf::Text::Underlined | sf::Text::Bold);
    leaderboardText.setString("LEADERBOARD");

    sf::FloatRect textCenter = leaderboardText.getLocalBounds();
    leaderboardText.setOrigin(textCenter.width / 2.0f, textCenter.height / 2.0f);
    leaderboardText.setPosition(sf::Vector2f(screenwidth / 2.0f, (screenheight / 2.0f) - 120));
    while (leaderWindow.isOpen())
    {
        // create Event object sfml article (read)
        sf::Event event;
        while (leaderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                if (!gamePaused)
                {
                    beginClock = true;
                }


                beginClock = false;
                leaderboardWindowOpen = false;

                std::cout << "the game has been paused" << endl;


                leaderWindow.close();
            }
            leaderWindow.clear(sf::Color::Blue);
            leaderWindow.draw(leaderboardText);
            leaderWindow.draw(playerText);
            leaderWindow.display();


        }


    }
    return true;
}
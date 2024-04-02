#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "Welcome.h"
using namespace std;

int main()
{
    Window beginWelcome;
    Window beginBoard;
    Window leaderBoard;
    //Window debugmode;
    string filename;
    int columns = 0;
    int rows = 0;
    int numMines = 0;
    string currPlayer = "";
    ifstream file("./files/board_config.cfg");
    string line;

    if (file.is_open())
    {
        getline(file, line);
        columns = stoi(line);

        getline(file, line);
        rows = stoi(line);

        getline(file, line);
        numMines = stoi(line);
    }
    

    sf::RenderWindow welcomewindow(sf::VideoMode(800, 600), "Welcome Window");
    bool welcome = beginWelcome.welcomeWindow(welcomewindow);

    if (welcome)
    {
        beginBoard.gameWindow(columns, rows, numMines, currPlayer);
        bool leader = leaderBoard.leaderboardWindow(columns, rows);
        //if (leader)
        //{
        //    // sf::RenderWindow leaderboardwindow(sf::VideoMode(columns * 16, (rows * 16) + 50));
        //    leaderBoard.leaderboardWindow(columns, rows);
        //}
        
    }
};
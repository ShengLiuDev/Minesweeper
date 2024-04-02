#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iomanip>
#include <iostream>
using namespace std;

class Window
{
public:
	bool welcomeWindowOpen;
	bool gameWindowOpen;
	bool leaderboardWindowOpen = false;
	bool gamePaused = true;
	bool gameBegan = false;
	bool leftclick = false;
	bool rightclick = false;
	int screenwidth;
	int screenheight;
	int columns;
	int rows;
	bool flagTile = false;
	

	// for mines
	
	int minesAdjacent;
	int minesFound = 0;
	int minesPlaced = 0;
	int xcoord;
	int ycoord;

	// for the game conditions
	bool gamewin = false;
	bool gamelose = false;
	bool beginClock = false;
	bool debugmode = false;

	// for the counter
	int maxMines;
	int mineCounter;

	// for names and leaderboard stuff
	vector<string> playerNames;
	vector<string> playerTimes;
	static string playerName;
	string winnerCompleteTime = "";
	string winnerTimeSeconds = "";
	int winnerMinutes = 0;
	int winnerSeconds = 0;

	int minutes = 0;
	int seconds = 0;
	int tempSeconds = 0;


	// for the rf
	//vector<vector<bool>> mineTile;
	//vector<vector<bool>> flagOnTile;
	//vector<vector<bool>> hiddenTile;
	//vector<vector<int>> numBombsNearby;

	//// nullptr is out of bounds 
	//// temp for flag placement, later implement in the tiles class
	//// check geeksforgeeks for implementation vector info
	//vector<sf::Sprite> mineSprites;
	//vector<sf::Sprite> flagsprites;
	//vector<sf::Sprite> revealedSprites;
	//vector<sf::Sprite> nearbyBombs;
	Window()
	{

	}

	Window(bool welcomeWindowOpen, bool gameWindowOpen, bool leaderboardWindowOpen, bool gamePaused, bool leftclick, bool rightclick,
		int screenwidth, int screenheight, int columns, int rows, bool flagTile, int mine_count, int minesAdjacent, int minesFound,
		int minesPlaced, int xcoord, int ycoord, vector<string> playerNames, vector<string> playerTimes, string winnerCompleteTime,
		string winnerTimeSeconds, int winnerMinutes, int winnerSeconds, int minutes, int seconds, int tempSeconds);

	bool welcomeWindow(sf::RenderWindow& welcomewindow);

	void gameWindow(int columns, int rows, int numMines, string currPlayer);

	void rf(int x, int y, sf::Sprite& revealedSprite, vector<vector<bool>>& hiddenTile, vector<sf::Sprite>& revealedSprites,
		vector<vector<bool>>& flagOnTile, vector<vector<int>>& numBombsNearby);

		/*void randomXY(int columns, int rows);

		bool mineExists(int xcoord, int ycoord);*/

		/*bool numMinesAdjacent();*/
	bool leaderboardWindow(int columns, int rows);

	sf::Sprite getRevealedSprite(int x, int y);
};

//class Mines
//{
//public:
//	int mine_count = 50;
//	int minesAdjacent;
//	int minesFound = 0;
//	int minesPlaced = 0;
//	int xcoord;
//	int ycoord;
//
//	Mines()
//	{
//
//	}
//
//	Mines(int mine_count, int minesAdjacent, int minesFound, int minesPlaced, int columns, int rows, int xcoord, int ycoord, vector<vector<bool>> mineTile);
//
//	
//
//private:
//	// placeholder for now, maybe will need for bool values of mines 
//
//
//};
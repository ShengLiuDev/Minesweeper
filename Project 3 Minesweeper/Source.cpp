#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iomanip>
#include <iostream>
using namespace sf;

bool Welcomewindow()
{
    int screenwidth = 0;
    int screenheight = 0;
    int columns = 22;
    int rows = 16;
    int mine_count = 50;
    // mine count is provided in the board_config.cfg file
    // temporary place holder revise later

    sf::RenderWindow welcomewindow(sf::VideoMode(screenwidth = 800, screenheight = 600), "Welcome Window");
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
    std::string name;
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

        // draws the texts onto the screen
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

void gameWindow()
{
    int screenwidth = 0;
    int screenheight = 0;
    int columns = 22;
    int rows = 16;
    int mine_count = 50;
    int tilecount = columns * rows;

    sf::RenderWindow gameWindow(sf::VideoMode(screenwidth = columns * 32, screenheight = (rows * 32) + 100), "MINESWEEPERRRR WOOOOOOOO");
    //gameWindow.clear(sf::Color::Blue); testing

    sf::Texture happyface;
    sf::Sprite happyfacesprite;
    happyface.loadFromFile("./files/images/face_happy.png");
    happyfacesprite.setTexture(happyface);
    happyfacesprite.setOrigin(screenwidth / 2.0f, screenheight / 2.0f);
    happyfacesprite.setPosition(((screenwidth / 2.0) * 32) - 32, 32 * (screenheight + 0.5f));
    

    while (gameWindow.isOpen())
    {

        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                gameWindow.close();
            }
            else
            {
                gameWindow.clear(sf::Color::White);
                sf::Sprite sprite;
                for (int i = 0; i < rows; i++)
                {
                    sf::Texture gametiletexture;
                    sf::Sprite gametile;
                    sf::Texture happyface;
                    sf::Sprite happyfacesprite;
                    for (int j = 0; j < columns; j++)
                    {
                        gametiletexture.loadFromFile("./files/images/tile_hidden.png");
                        gametile.setTexture(gametiletexture);
                        gametile.setPosition(j * 32, i * 32);
                        // spaces them apart by 32 bits, refer to stackoverflow on setPosition func
                        // gametile.setOrigin(screenwidth / 2.0f, screenheight / 2.0f);
                        gameWindow.draw(gametile);

                        //gameWindow.draw(texture);
                        // texture.update(gamewindow) is used to update the textures of the game window
                    }
                }
                gameWindow.draw(happyfacesprite);
                gameWindow.display();

            }

        }
        
    }
}


int main()
{
    if (Welcomewindow() == true)
    {
        std::cout << "successfully opened game window" << std::endl;
        gameWindow();
    }
    else
    {
        std::cout << "gameWindow could not be opened" << std::endl;
    }
    


    /*if (closedwelcome)
    {
        

    return 0;*/

    /*sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;*/
}
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>

#include "vector.h" // own new lib with vectors and operations on them
#include "GraphicsManeger.h"

const int SCREEN_Y = 600;
const int SCREEN_X = 900;
const float DT = 0.05;
const float RESISTANCE_COEF = 0.025;

class gameObject: public DrawableObject
{
    public:
        
        sf::RectangleShape shape;

        sf::Texture texture;

        vector2f Q; //здесь мои вектора собственные. Координаты и скорость
        vector2f V;

        int xSize;
        int ySize;

        bool isStrickingWithBorders = true;

        void setSize(int length, int width)
        {
            xSize = length;
            ySize = width;
            shape.setSize(sf::Vector2f(xSize, ySize));
        }

        void setTexture(sf::Texture* newTexture)
        {
            shape.setTexture(newTexture);
        }

        void setPosition(int x, int y)
        {
            Q.x = x;
            Q.y = y;
            shape.setPosition(Q.x, Q.y);
        }

        void draw(sf::RenderWindow* window)
        {
             window->draw(shape);
        }

        void move(float DT, int SCREEN_Y, int SCREEN_X)
        {
            if(isStrickingWithBorders)
            {
                if(Q.x <= 0 or Q.x >= SCREEN_X - xSize) //bounce from screen borders
                    V.x = -V.x;
                if(Q.y <= 0 or Q.y >= SCREEN_Y - ySize)
                    V.y = -V.y; 
            }

            if(Q.x < 0)                         // dividing stucked object in border
                Q.x += abs(Q.x) + 1;
            if(Q.x > SCREEN_X - xSize)
                Q.x -= Q.x + xSize - SCREEN_X + 1;
            if(Q.y < 0)
                Q.y += abs(Q.y) + 1;
            if(Q.y > SCREEN_Y - ySize)
                Q.y -= Q.y + ySize - SCREEN_Y + 1;

            this->Q.x += this->V.x * DT;
            this->Q.y += this->V.y * DT;
            shape.setPosition(Q.x, Q.y);
        }

        void addResistance(float resistanceCoef)
        {
            this->V.x = this->V.x - resistanceCoef * this->V.x;
            this->V.y = this->V.y - resistanceCoef * this->V.y;
        }

        void addSpeed(int horisontalSpeed, int vertivalSpeed)
        {
            V.x += horisontalSpeed;
            V.y += vertivalSpeed;
        }
    
} ;



main()
{
    //CONTEXT:
    sf::Event event;

    sf::RenderWindow menuWindow(sf::VideoMode(1200, 800), "menu");
    sf::Texture menuTexture;

    if (!menuTexture.loadFromFile("menu.png"))
    {
        std::cout << "Loading texture erorr" << "\n";
    }

    gameObject menu;
    menu.setSize(1200, 800);
    menu.setTexture(&menuTexture);
    menu.setPosition(0,0);
    menu.draw(&menuWindow);

    while (menuWindow.isOpen())
    {
        while (menuWindow.pollEvent(event))
		{
		    if (event.type == sf::Event::Closed) 
                    menuWindow.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space) // exit by escape
                    menuWindow.close();
            }
            menuWindow.display();
        }
    }

    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "game");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("texture.png"))
    {
        std::cout << "Loading texture erorr" << "\n";
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.jpg"))
    {
        std::cout << "Loading texture erorr" << "\n";
    }

    playerTexture.setSmooth(true);
    backgroundTexture.setSmooth(true);

    gameObject player;
    gameObject background;

    player.setSize(50, 50);
    player.setTexture(&playerTexture);
    player.setPosition(300,400);

    background.setSize(900, 600);
    background.setTexture(&backgroundTexture);
    background.setPosition(0, 0);


    while (window.isOpen())
    {
        //PHISICS: 

        player.move(DT, SCREEN_Y, SCREEN_X);
        player.addResistance(RESISTANCE_COEF);

        //EVEN HANDLER
        while (window.pollEvent(event))
		{
		    if (event.type == sf::Event::Closed) 
                  window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) // exit by escape
                    window.close();
                if (event.key.code == sf::Keyboard::Up)
                    player.addSpeed(0, -3);
                if (event.key.code == sf::Keyboard::Down)
                    player.addSpeed(0, 3);
                if (event.key.code == sf::Keyboard::Left)
                    player.addSpeed(-3, 0);
                if (event.key.code == sf::Keyboard::Right)
                    player.addSpeed(3, 0);
			}
		}
        //LOGICS:

        //GRAPHICS:
        //manager.drawAll(&window);
        window.clear();
        background.draw(&window);
        player.draw(&window);
        window.display();
    }
}

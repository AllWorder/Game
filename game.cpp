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

        int xSize; // длина
        int ySize; // ширина

        bool isStrickingWithBorders = true; // видимо я предусмотрел что-то

        void setSize(int length, int width)
        {
            xSize = length;
            ySize = width;
            shape.setSize(sf::Vector2f(xSize, ySize)); // ВАЖНО! Здесь приходится использовать СФМЛьные вектора, принимает только их. просто форма записи.
        }

        void setTexture(sf::Texture* newTexture) // достаточно при создании объекта кинуть в него текстуру
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

        void addSpeed(int horisontalSpeed, int vertivalSpeed) // для прибаления скорости при нажатии, можно и при отталкивании по х отрицательную добавлять
        {
            V.x += horisontalSpeed;
            V.y += vertivalSpeed;
        }
	
	// надо гравитацию
	// надо столкновения
    
} ;



main()
{
    //CONTEXT:
    sf::Event event;
// здесь идёт меню, чтобы одно окно только грузилось (вот и проблема для функции, что просто новое окно окно появляется и стопориться старое. Лучше сделать, чтобы просто в нашем игровом окне риосались другие объекты, по выходу снова рисовались старые) Вывод: два окна - не очень идея.
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
// конец менюшки 
	
    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "game");
    window.setVerticalSyncEnabled(true); // вот синхра и фпс
    window.setFramerateLimit(60);

    
    sf::Texture playerTexture; // процедура загрузки нужных текстур, возможно стоит сделать массив указателей на них?
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

    player.setSize(50, 50); // можно фабрику запилить
    player.setTexture(&playerTexture);
    player.setPosition(300,400);

    background.setSize(900, 600);
    background.setTexture(&backgroundTexture);
    background.setPosition(0, 0);


    while (window.isOpen())
    {
        //PHISICS: 

        player.move(DT, SCREEN_Y, SCREEN_X); // опять удобнее массив из платформ сделать и потом по ним бегать
        player.addResistance(RESISTANCE_COEF);

        //EVEN HANDLER
        while (window.pollEvent(event)) // у тебя это лучше сделано
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
        player.draw(&window); // ну тут пока без менеджера
        window.display();
    }
}

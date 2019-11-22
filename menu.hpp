class Menu
{
    public:
        
        int screen_x = 1280;
        int screen_y = 960;

        gameObject menuBackground;
        gameObject buttonContinue;
        gameObject buttonRules;
        gameObject buttonExit;
        gameObject logo;

        void load()
        {
            menuBackground.setSize(1920, 720);
            menuBackground.setPosition(-320, 0);
            menuBackground.addSpeed(1.5, 0);

            buttonContinue.setSize(560, 70);
            buttonContinue.setPosition(360, 320);

            buttonRules.setSize(560,70);
            buttonRules.setPosition(360, 410);

            buttonExit.setSize(560, 70);
            buttonExit.setPosition(360, 500);

            logo.setSize(600, 150);
            logo.setPosition(340, 75);

        }

        void moveBackground()
        {
            if(menuBackground.Q.x <= -640 or menuBackground.Q.x >= 0) //bounce from screen borders
                menuBackground.V.x = -menuBackground.V.x; 
            menuBackground.Q.x += menuBackground.V.x;
            menuBackground.setPosition(menuBackground.Q.x, menuBackground.Q.y);
        }

        void setTextures(sf::Texture* menuBackTexture, sf::Texture* button1Texture, sf::Texture* button2Texture, sf::Texture* button3Texture, sf::Texture* logoTexture)
        {
            menuBackground.setTexture(menuBackTexture);
            buttonContinue.setTexture(button1Texture);
            buttonRules.setTexture(button2Texture);
            buttonExit.setTexture(button3Texture);
            logo.setTexture(logoTexture);

        }

        void drawAll(sf::RenderWindow* window)
        {
            window->clear();
            
            menuBackground.draw(window);
            buttonContinue.draw(window);
            buttonRules.draw(window);
            buttonExit.draw(window);
            logo.draw(window);
            
            window->display();
        }

        void run(sf::RenderWindow* window)
        {
            bool isMenuOpen = true;
            int mouseOnButton = 0;

            this->load();

            while(isMenuOpen)
            {
                this->moveBackground();
                
                if (sf::IntRect(360, 320, 560, 70).contains(sf::Mouse::getPosition(*window)))
                    mouseOnButton = 1;
                if (sf::IntRect(360, 410, 560, 70).contains(sf::Mouse::getPosition(*window)))
                    mouseOnButton = 2;
                if (sf::IntRect(360, 500, 560, 70).contains(sf::Mouse::getPosition(*window)))
                    mouseOnButton = 3;
                
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (mouseOnButton == 1)
                        isMenuOpen = false;     //exit from menu
                    if (mouseOnButton == 3)
                    { 
                        window->close();
                        isMenuOpen = false;
                    }

                }

                mouseOnButton = 0;
                this->drawAll(window);
            }
        }
};
// PLACE IN CONTEXT
/*
 Menu menu;

    sf::Texture menuBackTexture;
    sf::Texture button1Texture;
    sf::Texture button2Texture;
    sf::Texture button3Texture;
    sf::Texture logoTexture;
    menuBackTexture.loadFromFile("menuBackground.png");
    button1Texture.loadFromFile("button1.png");
    button2Texture.loadFromFile("button2.png");
    button3Texture.loadFromFile("button3.png");
    logoTexture.loadFromFile("logo.png");

    menu.setTextures(&menuBackTexture, &button1Texture, &button2Texture, &button3Texture, &logoTexture);
*/

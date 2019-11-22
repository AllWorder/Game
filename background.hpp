class Background
{
    public:

        gameObject background;

        void setTexture(sf::Texture* backgroundTexture)
        {
            background.setTexture(backgroundTexture);
        }

        void load()
        {
            background.setSize(5120, 720);
            background.setPosition(0, 0);
            background.V.x = -3;
        }

        void move()
        {
            if(background.Q.x <= -3840)
                background.Q.x = 0; 
            background.Q.x += background.V.x;
            background.setPosition(background.Q.x, background.Q.y);
        }

        void draw(sf::RenderWindow* window)
        {
            background.draw(window);
        }


};

// PLACE IN CONTEXT
/*
    Background background;

        sf::Texture backgroundTexture;
        backgroundTexture.loadFromFile("background.png");
        backgroundTexture.setSmooth(true);

        background.load();
        background.setTexture(&backgroundTexture);
*/


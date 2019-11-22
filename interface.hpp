class Text: public DrawableObject
{
    public:
        sf::Text text;

        void draw(sf::RenderWindow* window)
        {
            window->draw(text);
        }

        void build(sf::Font* font, int fontSize, int x, int y, sf::Color color = sf::Color::Green)
        {
            text.setFont(*font);
            text.setCharacterSize(fontSize); // in pixeles
            text.setFillColor(sf::Color(color));
            text.setPosition(x, y);
        }

        void setString(char* VisibleText)
        {
            text.setString(VisibleText);
        }
};

class HUD
{
    public:
        gameObject interface;
        Text brsText;
        Text peresdText;
        char brsChar;
        char peresdChar;

        void setBRS(int score)
        {
            std::sprintf(&brsChar, "%d", score);
            brsText.setString(&brsChar);
        }

        void setPeresd(int score)
        {
            std::sprintf(&peresdChar, "%d", score);
            peresdText.setString(&peresdChar);
        }

        void load(sf::Font* font)
        {
            brsText.build(font, 55, 150, 0, sf::Color::White);
            peresdText.build(font, 45, 1200, 8, sf::Color::White);
            interface.setSize(1280, 720);
            interface.setPosition(0, 0);
        }

        void setTextures(sf::Texture* HUDTexture)
        {
            interface.setTexture(HUDTexture);
        }

        void draw(sf::RenderWindow* window)
        {
            brsText.draw(window);
            peresdText.draw(window);
            interface.draw(window);
        }

};

// PLACE IN CONTEXT
/*
    HUD hud;

    sf::Texture hudTexture;
    hudTexture.loadFromFile("hud.png");

    sf::Font font; 
    font.loadFromFile("arial.ttf");

    hud.load(&font);

    int BRS = 0;
    int PERESD = 3;

    hud.setBRS(BRS);
    hud.setPeresd(PERESD);
    hud.setTextures(&hudTexture);
*/
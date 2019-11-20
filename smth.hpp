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

// Я соврал, сам шрифт не хранится, но его достаточно один раз определить.
// Нет сетПоситион, но есть фабрика. Учитывая статичность текста должно хватить.

Circle* Balls = new Circle[partNumber];             //generating balls with random speed and position
    spawnBalls( Balls, partNumber, SCREEN_X, SCREEN_Y);

    
    GraphicsManager manager;

    for(int i = 0; i < partNumber; i++)
        manager.registrate(&Balls[i]);

// Вообще я делал массив классов, чтобы перебирать их для регистрации, столкновений и т.д., здесь такой для платформ можно замутить.

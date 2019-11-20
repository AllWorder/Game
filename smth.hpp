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

// Ya vrunishka. U menya zdes' ssilka na shrift, sam shrift ne hranitsa. I ne hvataet funczii setPosition(int x, int y).
// No est' fabrika, v kotoroi mojno ukazat' pozotsiyu (vrode text po hodu progi ne dvigaetsa)

Circle* Balls = new Circle[partNumber];             //generating balls with random speed and position
    spawnBalls( Balls, partNumber, SCREEN_X, SCREEN_Y);

    
    GraphicsManager manager;

    for(int i = 0; i < partNumber; i++)
        manager.registrate(&Balls[i]);

// Voobshe ya delal eshe massiv otdel'niy s classami, mojet bit' horoshei ideey takoi dlya platform sdelat', ctoby proshe stolknovenia perebirat'
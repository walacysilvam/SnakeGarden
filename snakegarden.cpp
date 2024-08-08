/*
*******************************************************************************************************************
 ******************************************************************************************************************
 
          ██████  ███▄    █  ▄▄▄       ██ ▄█▀▓█████      ▄████  ▄▄▄       ██▀███  ▓█████▄ ▓█████  ███▄    █
        ▒██    ▒  ██ ▀█   █ ▒████▄     ██▄█▒ ▓█   ▀     ██▒ ▀█▒▒████▄    ▓██ ▒ ██▒▒██▀ ██▌▓█   ▀  ██ ▀█   █
        ░ ▓██▄   ▓██  ▀█ ██▒▒██  ▀█▄  ▓███▄░ ▒███      ▒██░▄▄▄░▒██  ▀█▄  ▓██ ░▄█ ▒░██   █▌▒███   ▓██  ▀█ ██▒
          ▒   ██▒▓██▒  ▐▌██▒░██▄▄▄▄██ ▓██ █▄ ▒▓█  ▄    ░▓█  ██▓░██▄▄▄▄██ ▒██▀▀█▄  ░▓█▄   ▌▒▓█  ▄ ▓██▒  ▐▌██▒
        ▒██████▒▒▒██░   ▓██░ ▓█   ▓██▒▒██▒ █▄░▒████▒   ░▒▓███▀▒ ▓█   ▓██▒░██▓ ▒██▒░▒████▓ ░▒████▒▒██░   ▓██░
        ▒ ▒▓▒ ▒ ░░ ▒░   ▒ ▒  ▒▒   ▓▒█░▒ ▒▒ ▓▒░░ ▒░ ░    ░▒   ▒  ▒▒   ▓▒█░░ ▒▓ ░▒▓░ ▒▒▓  ▒ ░░ ▒░ ░░ ▒░   ▒ ▒
        ░ ░▒  ░ ░░ ░░   ░ ▒░  ▒   ▒▒ ░░ ░▒ ▒░ ░ ░  ░     ░   ░   ▒   ▒▒ ░  ░▒ ░ ▒░ ░ ▒  ▒  ░ ░  ░░ ░░   ░ ▒░
        ░  ░  ░     ░   ░ ░   ░   ▒   ░ ░░ ░    ░      ░ ░   ░   ░   ▒     ░░   ░  ░ ░  ░    ░      ░   ░ ░
              ░           ░       ░  ░░  ░      ░  ░         ░       ░  ░   ░        ░       ░  ░         ░
                                                                                   ░
                                                    BY WALACYSILVA
 ******************************************************************************************************************
 ******************************************************************************************************************
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

/******************************************************************************************

     .|'''.|                   '||                   ..|'''.| '||
     ||..  '  .. ...    ....    ||  ..    ....     .|'     '   ||   ....    ....   ....
      ''|||.   ||  ||  '' .||   || .'   .|...||    ||          ||  '' .||  ||. '  ||. '
    .     '||  ||  ||  .|' ||   ||'|.   ||         '|.      .  ||  .|' ||  . '|.. . '|..
    |'....|'  .||. ||. '|..'|' .||. ||.  '|...'     ''|....'  .||. '|..'|' |'..|' |'..|'

******************************************************************************************/

class Snake
{
private:
    std::vector<sf::RectangleShape> snake;
    const float blocoSize;
    sf::Vector2f direcao;

public:
    Snake() : blocoSize(20.f), direcao(blocoSize, 0.f) {
        //  TAMANHO INICIAL DE 3 SEGMENTOS
        for (int i = 0; i < 3; ++i) {
            sf::RectangleShape bloco(sf::Vector2f(blocoSize, blocoSize));
            bloco.setPosition(100.f + i * blocoSize, 100.f);
            bloco.setFillColor(sf::Color::Green);
            snake.push_back(bloco);
        }
    }

    void move() {
        // MOVE CADA SEGMENTO
        for (int i = snake.size() - 1; i > 0; --i) {
            snake[i].setPosition(snake[i - 1].getPosition());
        }
        snake[0].move(direcao);
    }

    void grow() {
        // ADD 1 BLOCO
        sf::RectangleShape bloco(sf::Vector2f(blocoSize, blocoSize));
        bloco.setFillColor(sf::Color::Green);
        bloco.setPosition(snake.back().getPosition());
        snake.push_back(bloco);
    }

    void setDirection(sf::Keyboard::Key key) {
        // CONTROLE DE DIRECAO
        if (key == sf::Keyboard::Up && direcao.y == 0.f) direcao = sf::Vector2f(0.f, -blocoSize);
        if (key == sf::Keyboard::Down && direcao.y == 0.f) direcao = sf::Vector2f(0.f, blocoSize);
        if (key == sf::Keyboard::Left && direcao.x == 0.f) direcao = sf::Vector2f(-blocoSize, 0.f);
        if (key == sf::Keyboard::Right && direcao.x == 0.f) direcao = sf::Vector2f(blocoSize, 0.f);
    }

    void draw(sf::RenderWindow& window) {
        // DESENHA A SNAKE NA JANELA
        for (const auto& bloco : snake) {
            window.draw(bloco);
        }
    }

    // CHECA A COLISÃO DA SNAKE COM OUTROS OBJETOS(RATO)
    bool checkCollision(const sf::RectangleShape& other) const {
        return snake[0].getGlobalBounds().intersects(other.getGlobalBounds());
    }
};

/******************************************************************************************

        '||''|.             .        ..|'''.| '||
         ||   ||   ....   .||.     .|'     '   ||   ....    ....   ....
         ||''|'   '' .||   ||      ||          ||  '' .||  ||. '  ||. '
         ||   |.  .|' ||   ||      '|.      .  ||  .|' ||  . '|.. . '|..
        .||.  '|' '|..'|'  '|.'     ''|....'  .||. '|..'|' |'..|' |'..|'

******************************************************************************************/

class Rat {
private:
    sf::RectangleShape bloco;
    const float blocoSize;

public:
    Rat(float blocoSize) : blocoSize(blocoSize) {
        bloco.setSize(sf::Vector2f(blocoSize, blocoSize));
        bloco.setFillColor(sf::Color::White);
        move();
    }

    void move() {
        bloco.setPosition(static_cast<float>(rand() % 40) * blocoSize, static_cast<float>(rand() % 30) * blocoSize);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(bloco);
    }

    const sf::RectangleShape& getShape() const {
        return bloco;
    }
};

/******************************************************************************************
 
         ..|'''.|                                  ..|'''.| '||
        .|'     '   ....   .. .. ..     ....     .|'     '   ||   ....    ....   ....
        ||    .... '' .||   || || ||  .|...||    ||          ||  '' .||  ||. '  ||. '
        '|.    ||  .|' ||   || || ||  ||         '|.      .  ||  .|' ||  . '|.. . '|..
         ''|...'|  '|..'|' .|| || ||.  '|...'     ''|....'  .||. '|..'|' |'..|' |'..|'

******************************************************************************************/

class Game
{
private:
    sf::RenderWindow janela;
    Snake snake;
    Rat rat;
    sf::Clock clock;
    const float updateTime;
    float elapsedTime;


    // ENTRADA DO USUARIO
    void handleEvents() {
        sf::Event event;
        while (janela.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                janela.close();

            // DIRECAO
            if (event.type == sf::Event::KeyPressed) {
                snake.setDirection(event.key.code);
            }
        }
    }

    void update() {
        elapsedTime += clock.restart().asSeconds();
        if (elapsedTime >= updateTime) {
            elapsedTime -= updateTime;
            snake.move();

            // COLISAO COM O RATO
            if (snake.checkCollision(rat.getShape())) {
                snake.grow();
                rat.move();
            }
        }
    }

    void render() {
        janela.clear();
        snake.draw(janela);
        rat.draw(janela);
        janela.display();
    }

public:
    Game() : janela(sf::VideoMode(800, 600), "Snake Garden -< Sketch >- "), updateTime(0.2f), elapsedTime(0.f), rat(20.f) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    void run() {
        // MAIN LOOP
        while (janela.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }
};

/******************************************************************************************
 
                    '||    ||'          ||              / \
                     |||  |||   ....   ...  .. ...    //   \\
                     |'|..'||  '' .||   ||   ||  ||   ||   ||
                     | '|' ||  .|' ||   ||   ||  ||   ||   ||
                    .|. | .||. '|..'|' .||. .||. ||.  ||   ||
                                                      \\   //
                                                        \ /
******************************************************************************************/

int main()
{   
    Game game;
    game.run();
    
    return EXIT_SUCCESS;
}

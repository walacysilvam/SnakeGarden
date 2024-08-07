/*
 ******************************************************************************************************************
 
                  ██████ ▄▄▄      ███▄    █▓█████ ██ ▄█▀     ▄████ ▄▄▄      ██▀███ ▓█████▄▓█████ ███▄    █
                ▒██    ▒▒████▄    ██ ▀█   █▓█   ▀ ██▄█▒     ██▒ ▀█▒████▄   ▓██ ▒ ██▒██▀ ██▓█   ▀ ██ ▀█   █
                ░ ▓██▄  ▒██  ▀█▄ ▓██  ▀█ ██▒███  ▓███▄░    ▒██░▄▄▄▒██  ▀█▄ ▓██ ░▄█ ░██   █▒███  ▓██  ▀█ ██▒
                  ▒   ██░██▄▄▄▄██▓██▒  ▐▌██▒▓█  ▄▓██ █▄    ░▓█  ██░██▄▄▄▄██▒██▀▀█▄ ░▓█▄   ▒▓█  ▄▓██▒  ▐▌██▒
                ▒██████▒▒▓█   ▓██▒██░   ▓██░▒████▒██▒ █▄   ░▒▓███▀▒▓█   ▓██░██▓ ▒██░▒████▓░▒████▒██░   ▓██░
                ▒ ▒▓▒ ▒ ░▒▒   ▓▒█░ ▒░   ▒ ▒░░ ▒░ ▒ ▒▒ ▓▒    ░▒   ▒ ▒▒   ▓▒█░ ▒▓ ░▒▓░▒▒▓  ▒░░ ▒░ ░ ▒░   ▒ ▒
                ░ ░▒  ░ ░ ▒   ▒▒ ░ ░░   ░ ▒░░ ░  ░ ░▒ ▒░     ░   ░  ▒   ▒▒ ░ ░▒ ░ ▒░░ ▒  ▒ ░ ░  ░ ░░   ░ ▒░
                ░  ░  ░   ░   ▒     ░   ░ ░   ░  ░ ░░ ░    ░ ░   ░  ░   ▒    ░░   ░ ░ ░  ░   ░     ░   ░ ░
                      ░       ░  ░        ░   ░  ░  ░            ░      ░  ░  ░       ░      ░  ░        ░
                                                                    ░
                                                    BY WALACYSILVA
 ******************************************************************************************************************
*/

#include <iostream>
#include <SFML/Graphics.hpp>


int main()
{   
    sf::RenderWindow janela(sf::VideoMode(800, 600), "Snake Garden -< Sketch >- ");
 
    const float blocoSize = 20.f;
    std::vector<sf::RectangleShape> snake;
    
    for (int i = 0; i < 3; ++i)
    {
        sf::RectangleShape bloco(sf::Vector2f(blocoSize, blocoSize));
        bloco.setPosition(100.f + i* blocoSize, 100.f);
        bloco.setFillColor(sf::Color::Green);
        snake.push_back(bloco);
    }

    sf::Vector2f direcao(blocoSize, 0.f);

    // VARIAVEIS PARA CONTROLE DE TEMPO
    sf::Clock clock;                // 
    const float updateTime = 0.2f;  // TEMPO ENTRE AS ATUALIZACOES
    float elapsedTime = 0.f;        //

    // LOOP PRINCIPAL
    while (janela.isOpen())
    {
        sf::Event event;
        while (janela.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                janela.close();

            // CONTROLE DE DIRECAO
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up && direcao.y == 0.f) direcao = sf::Vector2f(0.f, -blocoSize);
                if (event.key.code == sf::Keyboard::Down && direcao.y == 0.f) direcao = sf::Vector2f(0.f, blocoSize);
                if (event.key.code == sf::Keyboard::Left && direcao.x == 0.f) direcao = sf::Vector2f(-blocoSize, 0.f);
                if (event.key.code == sf::Keyboard::Right && direcao.x == 0.f) direcao = sf::Vector2f(blocoSize, 0.f);
            }
        }

        // ATUALIZA CADA POSICAO DOS SEGMENTOS
        elapsedTime += clock.restart().asSeconds();
        if (elapsedTime >= updateTime) {
            elapsedTime -= updateTime;

            for (int i = snake.size() - 1; i > 0; --i) {
                snake[i].setPosition(snake[i - 1].getPosition());
            }
            snake[0].move(direcao);
        }

        //snake[0].move(direcao);

        janela.clear();

        // desenhando a cobrinha
        for (const auto& bloco : snake) {
            janela.draw(bloco);
        }

        janela.display();
    }
    
    return EXIT_SUCCESS;
}

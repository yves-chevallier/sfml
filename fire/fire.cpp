#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    const float winW = 1000;
    const float winH = 1000;
    const float scale = 0.7;
    sf::RenderWindow window(sf::VideoMode(winW, winH), "SFML Shader Example");
    window.setMouseCursorVisible(false);

    sf::Texture tex;
    tex.create(winW, winH);
    sf::Sprite spr(tex);

    sf::Shader shader;
    shader.loadFromFile("fire.glsl", sf::Shader::Fragment);

    if (!shader.isAvailable()) std::cout << "The shader is not available\n";

    shader.setUniform("resolution", sf::Vector2f(winW * scale, winH * scale));

    sf::Clock clk;
    clk.restart();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        shader.setUniform("time", clk.getElapsedTime().asSeconds());

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        shader.setUniform("mouse", sf::Vector2f(mousePos.x, mousePos.y));

        window.clear();
        window.draw(spr, &shader);
        window.display();
    }
}

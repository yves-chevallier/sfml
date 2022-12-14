#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    const float winSize = 800;
    const float scale = 0.2;
    sf::RenderWindow window(sf::VideoMode(winSize, winSize), "SFML Shader Example");

    sf::Texture tex;
    tex.create(winSize, winSize);
    sf::Sprite spr(tex);

    sf::Shader shader;
    shader.loadFromFile("glow.glsl", sf::Shader::Fragment);

    if (!shader.isAvailable()) std::cout << "The shader is not available\n";

    shader.setUniform("resolution", sf::Vector2f(winSize * scale, winSize * scale));
    shader.setUniform("size", sf::Vector2f(winSize/2, winSize/2));
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }


        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        // spr.setPosition(mousePos.x - winSize / 2, mousePos.y - winSize / 2);

        window.clear();
        window.draw(spr, &shader);
        window.display();
    }
}

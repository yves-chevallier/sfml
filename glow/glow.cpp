#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    const float winSize = 800;
    const float scale = 50;
    sf::RenderWindow window(sf::VideoMode(winSize, winSize), "SFML Shader Example");

    sf::Texture tex;
    tex.create(winSize, winSize);
    sf::Sprite spr(tex);

    sf::Shader shader;
    shader.loadFromFile("glow.glsl", sf::Shader::Fragment);

    if (!shader.isAvailable()) std::cout << "The shader is not available\n";

    shader.setUniform("resolution", sf::Vector2f(scale, scale));
    shader.setUniform("size", sf::Vector2f(winSize/2, winSize/2));

    sf::Vector2f v[4] = {
        sf::Vector2f(100, 100 - 2* winSize / 2),
        sf::Vector2f(200, 200 - 2* winSize / 2),
        sf::Vector2f(300, 300 - 2* winSize / 2),
        sf::Vector2f(400, 400 - 2* winSize / 2)};
    shader.setUniformArray("tail", v, 4);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        mousePos.y -= 2* winSize / 2 ;
        shader.setUniform("mouse", sf::Vector2f(mousePos.x , mousePos.y ));
        //std::cout << mousePos.x << " " << mousePos.y << std::endl;

        window.clear();
        window.draw(spr, &shader);
        window.display();
    }
}

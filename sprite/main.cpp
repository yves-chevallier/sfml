#include <SFML/Graphics.hpp>
#include <iostream>
#define WIDTH 800
int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, WIDTH), "Test");

    sf::Shader shader, buffer;
    shader.loadFromFile("shader.frag", sf::Shader::Fragment);
    buffer.loadFromFile("buffer.frag", sf::Shader::Fragment);

    sf::Texture texture;
    if (!texture.loadFromFile("guy.png"))
    {
        std::cerr << "Error while loading texture" << std::endl;
        return -1;
    }
    std::cout << texture.getSize().x << " " << texture.getSize().y << std::endl;

    sf::Sprite sprite(texture);

    shader.setUniform("iResolution", sf::Glsl::Vec2(WIDTH, WIDTH));
    while(window.isOpen()) {
        sf::Event currEvent;
        while(window.pollEvent(currEvent)) {
            switch(currEvent.type) {
                case(sf::Event::Closed): window.close(); break;
            }
        }

        window.clear();
        window.draw(sprite, &shader);
        window.display();
    }
}

#include <SFML/Graphics.hpp>
#include <iostream>
#define WIDTH 800
int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, WIDTH), "Test");

    sf::Shader shader, buffer;
    shader.loadFromFile("shader.frag", sf::Shader::Fragment);
    buffer.loadFromFile("buffer.frag", sf::Shader::Fragment);

    sf::Shader *shaders[] = {&shader, &buffer};
    sf::Texture texture;
    texture.create(WIDTH, WIDTH);
    sf::Sprite sprite(texture);

    sf::RenderTexture renderTexture;
    renderTexture.create(WIDTH, WIDTH);

    sf::Vector2f mousePos = sf::Vector2f(-1.f, -1.f);
    for(auto &shader : shaders) {
        shader->setUniform("iChannel0", texture);
        shader->setUniform("iResolution", sf::Glsl::Vec2(WIDTH, WIDTH));
    }
    auto time = sf::Clock();

    while(window.isOpen()) {
        sf::Event currEvent;
        while(window.pollEvent(currEvent)) {
            switch(currEvent.type) {
                case(sf::Event::Closed): window.close(); break;
                case(sf::Event::MouseMoved):
                    mousePos = sf::Vector2f(
                        currEvent.mouseMove.x, currEvent.mouseMove.y);
                    break;
            }
        }

        buffer.setUniform("iTime", (float)time.getElapsedTime().asSeconds());
        buffer.setUniform("iMouse", sf::Glsl::Vec2(mousePos.x, WIDTH-mousePos.y));

        renderTexture.clear();
        renderTexture.draw(sprite, &buffer);
        renderTexture.display();
        texture.update(renderTexture.getTexture());

        window.clear();
        window.draw(sprite, &shader);
        window.display();
    }
}

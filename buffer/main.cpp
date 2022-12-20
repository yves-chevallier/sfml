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
    texture.update(window);
    sf::Sprite sprite(texture);

    sf::RenderTexture renderTexture;

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

        buffer.setUniform("iTime", time.getElapsedTime().asSeconds());
        // buffer.setUniform("iMouse", sf::Glsl::Vec2(
        //     mousePos.x / WIDTH, 1.0 - mousePos.y / WIDTH));

        sf::RenderStates states;
        states.blendMode = sf::BlendAdd;
        states.shader = &buffer;

        renderTexture.clear(sf::Color::Transparent);
        renderTexture.draw(sprite, states);
        renderTexture.display();
        sprite.setTexture(renderTexture.getTexture());
        texture.update(renderTexture.getTexture());
        buffer.setUniform("iChannel0", texture);
        shader.setUniform("iChannel0", texture);

        window.clear(sf::Color::Transparent);
        window.draw(sprite, &shader);
        window.display();
        //texture.update(window);
    }
}

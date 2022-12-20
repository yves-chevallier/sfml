//main.cpp
#include <iostream>
#include <SFML/Graphics.hpp>

#include <GL/glew.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Test");

    sf::Shader shader;
    shader.loadFromFile("shader.frag", sf::Shader::Fragment);

    sf::Texture texture;
    sf::RenderTexture renderTexture;
    while(window.isOpen())
    {
        sf::Event currEvent;
        sf::Vector2f mousePos;
        while(window.pollEvent(currEvent))
        {
            switch(currEvent.type)
            {
                case(sf::Event::Closed):
                    window.close();
                    break;
                case(sf::Event::MouseMoved):
                    shader.setUniform("mouse", sf::Vector2f(currEvent.mouseMove.x, currEvent.mouseMove.y));
                    break;
                default:
                    break;
            }
        }

        window.clear(sf::Color::Black);


        window.display();
    }
}

//main.cpp
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Test");

    sf::Shader shader;
    shader.loadFromFile("shader.vert", "shader.frag");
    //shader.loadFromFile("shader.frag", sf::Shader::Fragment);
    sf::Transform matrix = sf::Transform::Identity;
    matrix.scale(1/800.f, 1/800.f);

    sf::CircleShape triangle(100.f, 3);
    triangle.setFillColor(sf::Color::Red);
    triangle.setPosition(400.f, 400.f);

    sf::Glsl::Mat4 projectionViewMatrix = matrix;

    shader.setUniform("projectionViewMatrix", projectionViewMatrix);

    while(window.isOpen())
    {
        sf::Event currEvent;
        while(window.pollEvent(currEvent))
        {
            switch(currEvent.type)
            {
                case(sf::Event::Closed):
                    window.close();
                    break;
                default:
                    break;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(triangle, &shader);
        window.display();
    }
}

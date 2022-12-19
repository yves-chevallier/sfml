#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    const float winSize = 800;
    const float scale = 0.2;
    sf::RenderWindow window(sf::VideoMode(winSize, winSize), "SFML Shader Example");

    sf::Shader shader;
    shader.loadFromFile("vertex.vert", "fragment.frag");
    if (!shader.isAvailable()) std::cout << "The shader is not available\n";

    if (!shader.isGeometryAvailable()) std::cout << "The geometry shader is not available\n";

    const float radius = winSize / 10;
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(0,0);

    shader.setUniform("resolution", sf::Vector2f(winSize * scale, winSize * scale));

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        shape.setOrigin(radius, radius);
        shape.setPosition(mousePos.x, mousePos.y);

        window.clear();

        // Apply the shader to the shape
        // sf::RenderStates states;
        // states.shader = &shader;

        // states.transform = shape.getTransform();
        // //states.transform.rotate(45);

        window.draw(shape, &shader);
        window.display();
    }
}

#include <SFML/Graphics.hpp>
#include <boost/circular_buffer.hpp>
#include <iostream>
int main()
{
    const float winW = 1000;
    const float winH = 1000;
    const int tail_length = 100;
    sf::RenderWindow window(sf::VideoMode(winW, winH), "SFML");

    sf::VertexArray lines(sf::LinesStrip, tail_length);
    boost::circular_buffer<sf::Vector2i> tail(tail_length);

    sf::Clock clk;
    clk.restart();

    sf::Vector2i old_mouse_pos = sf::Vector2i(0, 0);

    // std::fill(tail.begin(), tail.end(), sf::Mouse::getPosition(window));
    sf::Texture tex;
    tex.create(winW, winH);
    sf::Sprite spr(tex);
    sf::Shader shader;
    shader.loadFromFile("main.glsl", sf::Shader::Fragment);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        shader.setUniform("resolution", sf::Vector2f(40, 40));
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (old_mouse_pos != mousePos)
            tail.push_back(mousePos);

        old_mouse_pos = sf::Vector2i(mousePos.x, mousePos.y);

        sf::Vector2f v[100];
        for (int i = 0; i < tail.size(); i++)
        {
            v[i] = sf::Vector2f(tail[i].x, tail[i].y- 2* winH / 2);
            lines[i].position = sf::Vector2f(tail[i].x, tail[i].y);
            lines[i].color = sf::Color(255, 0, 0, i * 255 / tail_length);
        }
        shader.setUniformArray("tail", v, tail.size());
        window.clear();
        window.draw(spr, &shader);
        window.draw(lines);
        window.display();
    }
}

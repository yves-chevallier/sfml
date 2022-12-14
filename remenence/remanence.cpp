#include <SFML/Graphics.hpp>
#include <boost/circular_buffer.hpp>

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

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (old_mouse_pos != mousePos)
            tail.push_back(mousePos);

        old_mouse_pos = sf::Vector2i(mousePos.x, mousePos.y);

        for (int i = 0; i < tail.size(); i++)
        {
            lines[i].position = sf::Vector2f(tail[i].x, tail[i].y);
            lines[i].color = sf::Color(255, 0, 0, i * 255 / tail_length);
        }

        window.clear();
        window.draw(lines);
        window.display();
    }
}

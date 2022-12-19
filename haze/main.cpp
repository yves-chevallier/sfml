#include <SFML/Graphics.hpp>



int main()
{
    //createDistortionMap();

    sf::RenderWindow window(sf::VideoMode(600, 600), "Heat");

    sf::Texture objectTexture;

    if (!objectTexture.loadFromFile("asset.jpg"))
    {
        sf::err() << "Failed to load object texture, exiting..." << std::endl;
        return -1;
    }

    sf::Sprite object;
    object.setTexture(objectTexture);
    object.setScale(.5f, .5f);

    sf::Texture distortionMap;

    // It is important to set repeated to true to enable scrolling upwards
    distortionMap.setRepeated(true);

    // Setting smooth to true lets us use small maps even on larger images
    distortionMap.setSmooth(true);

    if (!distortionMap.loadFromFile("distortion_map.png"))
    {
        sf::err() << "Failed to load distortion map, exiting..." << std::endl;
        return -1;
    }

    sf::RenderTexture renderTexture;
    renderTexture.create(400, 300);

    sf::Sprite sprite;
    sprite.setTexture(renderTexture.getTexture());
    sprite.setPosition(100, 150);

    sf::Shader shader;

    if (!shader.loadFromFile("heat_shader.vs", "heat_shader.fs"))
    {
        sf::err() << "Failed to load shader, exiting..." << std::endl;
        return -1;
    }

    shader.setParameter("currentTexture", sf::Shader::CurrentTexture);
    shader.setParameter("distortionMapTexture", distortionMap);

    float distortionFactor = .05f;
    float riseFactor = .2f;

    sf::Clock clock;

    while (true)
    {
        sf::Event event;
        if (window.pollEvent(event)) {
            switch (event.type)
            {
                case sf::Event::Closed: return 0;
                case sf::Event::KeyPressed:
                {
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape: return 0;
                        case sf::Keyboard::Add: distortionFactor *= 2.f; break;
                        case sf::Keyboard::Subtract: distortionFactor /= 2.f; break;
                        case sf::Keyboard::Multiply: riseFactor *= 2.f; break;
                        case sf::Keyboard::Divide: riseFactor /= 2.f; break;
                        default: break;
                    }
                    break;
                }
                default: break;
            }
        }

        shader.setParameter("time", clock.getElapsedTime().asSeconds());
        shader.setParameter("distortionFactor", distortionFactor);
        shader.setParameter("riseFactor", riseFactor);

        renderTexture.clear();
        renderTexture.draw(object);
        renderTexture.display();

        window.clear();
        window.draw(sprite, &shader);
        window.display();
    }
}

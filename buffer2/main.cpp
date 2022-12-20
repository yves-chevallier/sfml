#include <SFML/Graphics.hpp>
#include <GL/glew.h>

#define WIDTH 100
int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, WIDTH), "Test");
    sf::Shader shader;
    shader.loadFromMemory(
        "#version 140\n"
        "void main() {\n"
        "gl_PointSize = 10; // Not working\n"
        "gl_Position =  gl_Vertex;\n"
        "}\n",
        "#version 140\n"
        "out vec4 out_Colour;\n"
        "void main(void) {\n"
        "out_Colour = vec4(vec3(1.0), 1.0);\n"
        "}\n"
    );

    sf::VertexArray points(sf::Points, 3);

    points[0].position = sf::Vector2f(0, 0);
    points[1].position = sf::Vector2f(-.1, -.1);
    points[2].position = sf::Vector2f(.1, .1);

    while(window.isOpen()) {
        sf::Event currEvent;
        while(window.pollEvent(currEvent)) {
            switch(currEvent.type) {
                case(sf::Event::Closed): window.close(); break;
            }
        }
        //glEnable(GL_PROGRAM_POINT_SIZE);

        sf::RectangleShape rect(sf::Vector2f(0.3, 0.3));



        window.clear();
        window.draw(rect, &shader);
        window.display();
    }
}

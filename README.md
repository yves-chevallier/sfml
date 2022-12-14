# SFML Playground with examples

This is a playground for SFML. It contains examples of how to use SFML.


## Shaders

There are different types of shaders:

* Vertex Shader: This shader is executed for each vertex of a mesh. It can be used to transform the vertex position, or to pass additional data to the fragment shader.
* Fragment Shader: This shader is executed for each pixel of a mesh. It can be used to color the pixel, or to perform additional calculations.

Uniforms are variables that can be set from the C++ code and used in the shader. They are declared in the shader code with the `uniform` keyword.

## Anti-Aliasing

```cpp
sf::ContextSettings settings;
settings.antialiasingLevel = 8;

sf::RenderWindow window(sf::VideoMode(800, 600), "SFML shapes", sf::Style::Default, settings);
```

## Threads

```cpp
void renderingThread(sf::Window* window)
{
    // activate the window's context
    window->setActive(true);

    // the rendering loop
    while (window->isOpen())
    {
        // draw...

        // end the current frame -- this is a rendering function (it requires the context to be active)
        window->display();
    }
}

int main()
{
    // create the window (remember: it's safer to create it in the main thread due to OS limitations)
    sf::Window window(sf::VideoMode(800, 600), "OpenGL");

    // deactivate its OpenGL context
    window.setActive(false);

    // launch the rendering thread
    sf::Thread thread(&renderingThread, &window);
    thread.launch();

    // the event/logic/whatever loop
    while (window.isOpen())
    {
        ...
    }

    return 0;
}
```

## Vertex Array

```cpp
sf::VertexArray vertices(sf::Triangles, 3);
sf::VertexArray lines(sf::LineStrip, 30);

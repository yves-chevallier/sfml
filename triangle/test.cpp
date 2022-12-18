#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL2/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>

static const GLuint WIDTH = 512;
static const GLuint HEIGHT = 512;

static GLfloat vertices[] = {
     0.0,  0.8,
    -0.8, -0.8,
     0.8, -0.8,
};

GLuint load_shader(GLenum type, std::string const &source) {
    std::ifstream is(source);
    std::stringstream buffer;
    buffer << is.rdbuf();
    const char *source_code = buffer.str().c_str();
    printf("%s", source_code);

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source_code, NULL);
    glCompileShader(shader);

    GLint log_length, success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

    GLchar *log = (GLchar*)malloc(log_length);
    if (log_length > 0) {
        glGetShaderInfoLog(shader, log_length, NULL, log);
        printf("vertex shader log:\n\n%s\n", log);
    }
    if (!success) {
        printf("vertex shader compile error\n");
        exit(EXIT_FAILURE);
    }
    return shader;
}

GLuint common_get_shader_program( std::string vertex_filename, std::string fragment_filename) {
    GLchar *log = NULL;
    GLint log_length, success;

    GLuint vertex_shader = load_shader(GL_VERTEX_SHADER, vertex_filename);
    GLuint fragment_shader = load_shader(GL_FRAGMENT_SHADER, fragment_filename);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        log = (GLchar*)realloc(log, log_length);
        glGetProgramInfoLog(program, log_length, NULL, log);
        printf("shader link log:\n\n%s\n", log);
    }
    if (!success) {
        printf("shader link error");
        exit(EXIT_FAILURE);
    }

    free(log);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;
}

int main(void) {
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    auto window = SDL_CreateWindow("TITLE", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    auto gl_context = SDL_GL_CreateContext(window);
    glewInit();

    GLuint program = common_get_shader_program("v.vert", "v.frag");
    GLint attribute_coord2d = glGetAttribLocation(program, "coord2d");

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUseProgram(program);
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    SDL_Event event;
    while (1) {
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(attribute_coord2d);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(attribute_coord2d);
        SDL_GL_SwapWindow(window);
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }

    glDeleteBuffers(1, &vbo);
    glDeleteProgram(program);
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

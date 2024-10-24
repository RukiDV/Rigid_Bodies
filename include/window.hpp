#pragma once

#include <GL/glew.h> 
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <glm/vec2.hpp>

constexpr glm::uvec2 WINDOW_SIZE{1200, 1200};

class Window
{
public:
    Window(int width, int height, const char* title);
    void swapBuffers();
    bool pollEvents(SDL_Event& event);
    void clear();

private:
    SDL_Window* window;
    SDL_GLContext context;
    int width;
    int height;
};

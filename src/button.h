#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

enum ButtonState
{
    NORMAL = 0,
    PRESSED = 1
};

struct ButtonDimensions
{
    int w;
    int h;
};

class Button
{
public:
    Button(std::vector<std::string> images);
    ~Button() {}

    void Render(SDL_Renderer *sdl_renderer);

    void ChangeState();

    void SetPosition(int x, int y);

    // delete copy constructor, copy assigment operator
    // move constractor and move assigment operator
    Button(const Button &) = delete;
    Button &operator=(const Button &) = delete;
    Button(Button &&) = delete;
    Button &operator=(Button &&) = delete;

private:
    // Load images for play/pause (normal/pressed) state of button
    void LoadImageFromFile(std::string paths_to_image, SDL_Surface *&loaded_surface);

    // Top left position
    SDL_Point position_;

    ButtonDimensions button_dimensions;

    // Surfaces to create textures for play/pause button
    SDL_Surface *surface_normal_;
    SDL_Surface *surface_pressed_;

    ButtonState button_state_ = NORMAL;
};

#endif
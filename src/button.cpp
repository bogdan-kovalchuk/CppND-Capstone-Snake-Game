#include <iostream>

#include "button.h"

void Button::Render(SDL_Renderer *sdl_renderer)
{
    SDL_Rect clip;
    clip.x = 0;
    clip.y = 0;
    clip.w = 200;
    clip.h = 200;

    // Set rendering space
    SDL_Rect render_quad = {position_.x, position_.y, 200, 200};

    if (button_state_ == NORMAL)
    {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, surface_normal_);
        SDL_RenderCopy(sdl_renderer, texture, &clip, &render_quad);
    }
    else
    {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, surface_pressed_);
        SDL_RenderCopy(sdl_renderer, texture, &clip, &render_quad);
    }
}

void Button::ChangeState()
{
    if (button_state_ == NORMAL)
    {
        button_state_ = PRESSED;
    }
    else
    {
        button_state_ = NORMAL;
    }
}

void Button::SetPosition(int x, int y)
{
    position_.x = x;
    position_.y = y;
}

void Button::LoadImageFromFile(std::string paths_to_image, SDL_Surface *loaded_surface)
{
    // Load image at specified path
    loaded_surface = IMG_Load(paths_to_image.c_str());

    if (loaded_surface == nullptr)
    {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }
}

#include <iostream>
#include <filesystem>

#include "button.h"

Button::Button(std::vector<std::string> paths_to_images)
{
    LoadImageFromFile(paths_to_images[NORMAL], surface_normal_);
    LoadImageFromFile(paths_to_images[PRESSED], surface_pressed_);

    if (surface_normal_ == nullptr || surface_pressed_ == nullptr)
    {
        std::cerr << "Unable to create textures!\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
    else if (surface_normal_->w != surface_pressed_->w ||
             surface_normal_->h != surface_pressed_->h)
    {
    }
    else
    {
        // Get button dimensions
        button_dimensions.h = surface_normal_->w;
        button_dimensions.w = surface_normal_->h;
    }
}

void Button::Render(SDL_Renderer *sdl_renderer)
{
    // Rendering space for button
    SDL_Rect dstrect = {position_.x, position_.y, 64, 64};

    SDL_Texture *texture = nullptr;
    if (button_state_ == NORMAL)
    {
        texture = SDL_CreateTextureFromSurface(sdl_renderer, surface_normal_);
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(sdl_renderer, surface_pressed_);
    }

    SDL_RenderCopy(sdl_renderer, texture, nullptr, &dstrect);
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

void Button::LoadImageFromFile(std::string paths_to_image, SDL_Surface *&loaded_surface)
{
    // Load image at specified path
    auto tmp = IMG_Load(paths_to_image.c_str());
    loaded_surface = tmp;

    if (loaded_surface == nullptr)
    {
        std::cerr << "Error loading image.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

#include "button.h"

Button::Button()
{
    std::vector<std::string> paths_to_images = {"assets/buttons/play.png",
                                                "assets/buttons/pause.png"};

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
        std::cerr << "Dimensions of play and pause images are different!\n";
    }
    else
    {
        // Get button dimensions from image
        button_dimensions_.h = surface_normal_->w;
        button_dimensions_.w = surface_normal_->h;
    }
}

void Button::Render(SDL_Renderer *sdl_renderer)
{
    // Rendering space for button
    SDL_Rect dstrect = {position_.x, position_.y, button_dimensions_.h, button_dimensions_.w};

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

ButtonState Button::GetState() const
{
    return button_state_;
}

ButtonDimensions Button::GetButtonDimensions() const
{
    return button_dimensions_;
}

void Button::SetPosition(int x, int y)
{
    position_.x = x;
    position_.y = y;
}

SDL_Point Button::GetPosition() const
{
    return position_;
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

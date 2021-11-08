#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main()
{
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  std::vector<std::string> images = {"/home/s1000239/Documents/Study/Cpp/CppND/CppND-Capstone-Snake-Game/assets/buttons/play.png",
                                     "/home/s1000239/Documents/Study/Cpp/CppND/CppND-Capstone-Snake-Game/assets/buttons/pause.png"};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, images);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  return 0;
}
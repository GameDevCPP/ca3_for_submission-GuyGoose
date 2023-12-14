#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

void MenuScene::Load() {
  cout << "Menu Load \n";
  {
    auto txt = makeEntity();
    // Move text to the top of the screen (200px down)
    txt->setPosition(Vector2f(Engine::getWindowSize().x / 2 - 200,
                              Engine::getWindowSize().y / 2 - 300));
    auto t = txt->addComponent<TextComponent>(
        "        Bulb\nPress Space to Start\n\n\n\nControls:\n- A/D to move\n- Space to jump\n\n\n\nObjective:\n- Reach the Electrical\n  Socket\n- Don't stay out of the\n  light for too long");
    // Set to center of screen


  }
  cout << "Menu Load Done" << endl;
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
      auto lvlNum = 1;
      // Check if there is a number in level.txt
        ifstream myfile("res/level.txt");
        if (myfile.is_open())
        {
            myfile >> lvlNum;
            myfile.close();
        }
        else cout << "Unable to open file";

        // Set the current level to the level number in level.txt
      if (lvlNum == 1) {
          Engine::ChangeScene(&level1);
      } else if (lvlNum == 2) {
          Engine::ChangeScene(&level2);
      } else if (lvlNum == 3) {
          Engine::ChangeScene(&level3);
      } else {
          Engine::ChangeScene(&level1);
      }


  }

  Scene::Update(dt);
}

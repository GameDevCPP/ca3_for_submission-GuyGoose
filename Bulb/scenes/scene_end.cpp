#include "scene_end.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

void EndScene::Load() {
  cout << "end Load \n";

    // Write the level number to a file.
    auto levelNum = 1;
    ofstream myfile;
    myfile.open ("res/level.txt");
    myfile << levelNum;
    myfile.close();

  {
    auto txt = makeEntity();
    // Move text to the top of the screen (200px down)
    txt->setPosition(Vector2f(Engine::getWindowSize().x / 2 - 200,
                              Engine::getWindowSize().y / 2 - 300));
    auto t = txt->addComponent<TextComponent>(
        "        YOU WIN!\n   Thanks for Playing!\nPress Space to play again");


  }
  cout << "End Load Done" << endl;
  setLoaded(true);
}

void EndScene::Update(const double& dt) {

  if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
      Engine::ChangeScene(&menu);
  }

  Scene::Update(dt);
}

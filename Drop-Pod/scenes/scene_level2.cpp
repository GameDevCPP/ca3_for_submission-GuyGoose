#include "scene_level2.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include "../components/cmp_shotgun.h"
#include "../components/cmp_light.h"
#include "../components/cmp_text.h"
#include "../components/cmp_bullet.h"
#include "system_resources.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> shotgun;
static shared_ptr<Entity> light;
static shared_ptr<Entity> light2;
static shared_ptr<Entity> text;

// inDarkness is a boolean that is true when the player is in darkness and false when the player is in light.
static shared_ptr<bool> inDarkness;

void Level2Scene::Load() {
  cout << " Scene 2 Load" << endl;
  ls::loadLevelFile("res/level_2.txt", 40.0f);

  auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
  ls::setOffset(Vector2f(0, ho));

  inDarkness = make_shared<bool>(true);

  // Create player
  {
    player = makeEntity();
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    auto s = player->addComponent<ShapeComponent>();
    s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
    s->getShape().setFillColor(Color::Magenta);
    s->getShape().setOrigin(Vector2f(10.f, 15.f));
    //player->addComponent<LightComponent>(Vector2f(100.f, 100.f));
    //Tag as player
    player->addTag("player");

    player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
    //player->addComponent<LightComponent>(Vector2f (100.f, 100.f));
  }

  // Add shotgun attachment to player
    {
        shotgun = makeEntity();
        // Set to center of screen for now
        shotgun->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2.f, Engine::GetWindow().getSize().y / 2.f));
        // Create a sprite component, set origin to the player's center and the sprite be offset to the right
//        auto s = shotgun->addComponent<ShapeComponent>();
//        s->setShape<sf::RectangleShape>(Vector2f(20.f, 5.f));
//        s->getShape().setFillColor(Color::White);
//        s->getShape().setOrigin(Vector2f(-25, 2.5));
//        s->getShape().setPosition(Vector2f(100.f, 100.f));
        auto s = shotgun->addComponent<SpriteComponent>();
        s->setTexture(Resources::get<Texture>("Arrow.png"));
        s->getSprite().setOrigin(Vector2f(-25.f, 15.f));
        s->getSprite().setPosition(Vector2f(100.f, 100.f));

        // Create a shotgun component
        auto sc = shotgun->addComponent<ShotgunComponent>();
        auto sp = shotgun->addComponent<ShootingComponent>();
    }

    {
        light = makeEntity();
        auto s = light->addComponent<LightComponent>(Vector2f(100.f, 100.f), player, 1);
    }

    {
        light2 = makeEntity();
        light2->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2.f, Engine::GetWindow().getSize().y));
        auto s = light2->addComponent<LightComponent>(Vector2f(200.f, 200.f), player, 2);
    }

    // Add text to the top middle of the screen that displays In Darkness: true/false
    {
        text = makeEntity();
        text->setPosition(Vector2f(Engine::GetWindow().getSize().x / 3.f, 0.f));
        auto t = text->addComponent<TextComponent>();
    }


  // Add physics colliders to level tiles.
  {
    auto walls = ls::findTiles(ls::WALL);
    for (auto w : walls) {
      auto pos = ls::getTilePosition(w);
      pos += Vector2f(20.f, 20.f); //offset to center
      auto e = makeEntity();
      e->setPosition(pos);
      e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
    }

      auto floors = ls::findTiles(ls::FLOOR);
      for (auto w : floors) {
          auto pos = ls::getTilePosition(w);
          pos += Vector2f(20.f, 20.f); //offset to center
          auto e = makeEntity();
          e->setPosition(pos);
          e->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
      }
  }

  //Simulate long loading times
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  cout << " Scene 1 Load Done" << endl;

  setLoaded(true);
}

void Level2Scene::UnLoad() {
  cout << "Scene 1 Unload" << endl;
  player.reset();
  ls::unload();
  Scene::UnLoad();
}

void Level2Scene::Update(const double& dt) {

  if (ls::getTileAt(player->getPosition()) == ls::END) {
    Engine::ChangeScene((Scene*)&level1);
  }
  Scene::Update(dt);

  // Show the shotgun shape and entity rotation
    //cout << "Shotgun shape rotation: " << shotgun->getComponent<ShapeComponent>()->getShape().getRotation() << endl;
    //cout << "Shotgun entity rotation: " << shotgun->getRotation() << endl;

  // Set the shotguns entity rotation to the shotgun component rotation
    //shotgun->setRotation(shotgun->getComponent<ShotgunComponent>()->getRotation());

  // Shotgun attachment follows player (Players position + 10 pixels to the right)
    shotgun->setPosition(player->getPosition() + Vector2f(0.f, 0.f));

    // Light follows mouse
    light->setPosition(Vector2f(Mouse::getPosition(Engine::GetWindow()).x, Mouse::getPosition(Engine::GetWindow()).y));

    // If the player lightlist is empty, set set text to true.
    if (player->getComponent<PlayerPhysicsComponent>()->getLights().empty()) {
        text->getComponent<TextComponent>()->SetText("In Darkness: true");
    } else {
        text->getComponent<TextComponent>()->SetText("In Darkness: false");
    }
}

void Level2Scene::Render() {
  ls::render(Engine::GetWindow());
  Scene::Render();
}

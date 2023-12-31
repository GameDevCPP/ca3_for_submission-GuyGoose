#include "scene_level3.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include "../components/cmp_pointer.h"
#include "../components/cmp_light.h"
#include "../components/cmp_text.h"
#include "../components/cmp_bullet.h"
#include "../components/cmp_path_follow.h"
#include "system_resources.h"
#include "../components/cmp_player_anim.h"
#include <LevelSystem.h>
#include <iostream>
#include <thread>
#include <fstream>

using namespace std;
using namespace sf;


static shared_ptr<Entity> pointerArrow;
static shared_ptr<Entity> timerText;
static shared_ptr<Entity> player;
static shared_ptr<Entity> light;
static shared_ptr<Entity> lightpath;

// Time variables
static float baseTime = 5.f;
static float timeRemaining = 5.f;


void Level3Scene::Load() {
    cout << " Scene 3 Load" << endl;
    ls::loadLevelFile("res/level_3.txt", 40.0f);

    // Write the level number to a file.
    auto levelNum = 3;
    ofstream myfile;
    myfile.open ("res/level.txt");
    myfile << levelNum;
    myfile.close();

    cout << "Scene 3 Loaded" << endl;

    auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
    ls::setOffset(Vector2f(0, ho));

    timeRemaining = baseTime;

    // Create player
    {
        player = makeEntity();
        player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
        auto s = player->addComponent<ShapeComponent>();
        s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
        // Fully transparent
        s->getShape().setFillColor(Color(255, 255, 255, 0));
        s->getShape().setOrigin(Vector2f(10.f, 15.f));
        //player->addComponent<LightComponent>(Vector2f(100.f, 100.f));
        //Tag as player
        player->addTag("player");

        player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
        // Player animation stuff
        auto s2 = player->addComponent<SpriteComponent>();
        s2->getSprite().setOrigin(Vector2f(15.f, 15.f));
        auto anim = player->addComponent<AnimationComponent>();
        auto a = player->addComponent<PlayerAnimatorComponent>();
    }

    // Add pointerArrow attachment to player
    {
        pointerArrow = makeEntity();
        // Set to center of screen for now
        pointerArrow->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2.f, Engine::GetWindow().getSize().y / 2.f));
        // Create a sprite component, set origin to the player's center and the sprite be offset to the right
//        auto s = pointerArrow->addComponent<ShapeComponent>();
//        s->setShape<sf::RectangleShape>(Vector2f(20.f, 5.f));
//        s->getShape().setFillColor(Color::White);
//        s->getShape().setOrigin(Vector2f(-25, 2.5));
//        s->getShape().setPosition(Vector2f(100.f, 100.f));
        auto s = pointerArrow->addComponent<SpriteComponent>();
        s->setTexture(Resources::get<Texture>("Arrow.png"));
        s->getSprite().setOrigin(Vector2f(-25.f, 15.f));
        s->getSprite().setPosition(Vector2f(100.f, 100.f));

        // Create a pointerArrow component
        auto sc = pointerArrow->addComponent<PointerComponent>();
        auto sp = pointerArrow->addComponent<ShootingComponent>();
    }

    {
        light = makeEntity();
        auto s = light->addComponent<LightComponent>(Vector2f(100.f, 100.f), player, 100);
    }

    {
        lightpath = makeEntity();
        // Vector of points for the path to follow.
        vector<Vector2f> points;
        // Add points to the vector.
        points.push_back(Vector2f(50.f,650.f));
        points.push_back(Vector2f(350.f,650.f));
        points.push_back(Vector2f(500.f,450.f));
        points.push_back(Vector2f(700.f,450.f));
        points.push_back(Vector2f(1050.f,150.f));
        // Add a path follow component to the lightpath entity.
        auto pf = lightpath->addComponent<PathComponent>(points, 100.f, light);

    }

    {
//        light2 = makeEntity();
//        light2->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2.f, Engine::GetWindow().getSize().y));
//        auto s = light2->addComponent<LightComponent>(Vector2f(200.f, 200.f), player, 2);
    }

    // Add timer to the top left of the screen that displays the time left.
    {
        timerText = makeEntity();
        timerText->setPosition(Vector2f(0.f, 0.f));
        auto t = timerText->addComponent<TextComponent>();
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

    // Add all lights to the vector of lights.
    {
        auto lights = ls::findTiles(ls::LIGHT);
        int lightNum = 0;
        for (auto w : lights) {
            auto pos = ls::getTilePosition(w);
            // Center the light on the tile.
            pos += Vector2f(20.f, 20.f);
            auto e = makeEntity();
            e->setPosition(pos);
            e->addComponent<LightComponent>(Vector2f(100.f, 100.f), player, lightNum);
            lightNum++;
            // Add the new light to the vector of lights. (static vector<shared_ptr<Entity>> lights;)
            Level3Scene::lights.push_back(e);
        }
    }

    //Simulate long loading times
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    cout << " Scene 3 Load Done" << endl;

    setLoaded(true);
}

void Level3Scene::UnLoad() {
    cout << "Scene 3 Unload" << endl;
//    player.reset();
//    timerText.reset();
    Level3Scene::lights.clear();
    ls::unload();
    Scene::UnLoad();
}

void Level3Scene::Update(const double& dt) {

    if (ls::getTileAt(player->getPosition()) == ls::END) {
        Engine::ChangeScene(&end_game);
    }

    // Shotgun attachment follows player (Players position + 10 pixels to the right)
    pointerArrow->setPosition(player->getPosition() + Vector2f(0.f, 0.f));

    // Light follows mouse
    //light->setPosition(Vector2f(Mouse::getPosition(Engine::GetWindow()).x, Mouse::getPosition(Engine::GetWindow()).y));

    // Update the timer text to display the time remaining. format: "Time Remaining: 3
    timerText->getComponent<TextComponent>()->SetText( to_string(timeRemaining).substr(0, 3));

    // Display the time above the player.
    timerText->setPosition(player->getPosition() + Vector2f(-25.f, -50.f));

    // Timer of 3 seconds. If the player is in darkness for 3 seconds, go to the menu scene.
    if (player->getComponent<PlayerPhysicsComponent>()->getLights().empty()) {
        timeRemaining -= dt;
        if (timeRemaining <= 0) {
            Engine::ChangeScene((Scene*)&game_over);
        }
    } else {
        timeRemaining = baseTime;
    }

    // Debug : Print the mouse position
    cout << "Mouse Position: " << Mouse::getPosition(Engine::GetWindow()).x << ", " << Mouse::getPosition(Engine::GetWindow()).y << endl;

    Scene::Update(dt);
}

void Level3Scene::Render() {
    ls::render(Engine::GetWindow());
    Scene::Render();
}

#pragma once

#include "engine.h"

class GameOverScene : public Scene {
public:

    GameOverScene() = default;

  ~GameOverScene() override = default;

  void Load() override;

  void Update(const double& dt) override;
};

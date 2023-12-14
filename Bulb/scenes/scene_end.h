#pragma once

#include "engine.h"

class EndScene : public Scene {
public:

    EndScene() = default;

  ~EndScene() override = default;

  void Load() override;

  void Update(const double& dt) override;
};

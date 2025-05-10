#include <Vector3.h>
#include <Model.h>
#include "Sprite.h"


#pragma once
class Player
{
public:
    void Initialize();

    void Update();

    void Draw();

private:
    WorldTransform worldTransform_;
    ViewProjection* viewProjection_ = nullptr;
    Vector2 position_;
    Sprite* sprite_;
};


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
    // ワールドトランスフォーム
    WorldTransform worldTransform_;
    // ビュープロジェクション
    ViewProjection* viewProjection_ = nullptr;
    Vector3 position_;  // 敵の位置

    //スプライト
    Sprite* sprite_ = nullptr;
};


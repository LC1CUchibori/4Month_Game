#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"

class BONUS
{
public:
    void Initialize(Model* model, ViewProjection* viewProjection);

    void Update();

    void Draw();

    void StartBonus();

private:
    WorldTransform worldTransform_;
    Model* model_ = nullptr;
    ViewProjection* viewProjection_ = nullptr;

    enum class BonusState {
        None,
        Dropping,
        Waiting,
        Returning
    };

    BonusState bonusState_ = BonusState::None;
    int waitTimer_ = 0;
    Vector3 position_ = {0.0f, 2.0f, 0.0f}; // 初期位置（上）
};


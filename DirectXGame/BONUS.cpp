#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "BONUS.h"

void BONUS::Initialize(Model* model, ViewProjection* viewProjection)
{
    worldTransform_.Initialize();
    model_ = model;
    viewProjection_ = viewProjection;

    position_ = {0.0f, 5.0f, 0.0f}; // 上に配置
    worldTransform_.Initialize();
    worldTransform_.translation_ = position_;

    bonusState_ = BonusState::None;
}

void BONUS::Update()
{
    switch (bonusState_)
    {
    case BonusState::None:
        StartBonus();
        break;

    case BonusState::Dropping:
        position_.y -= 0.02f;
        if (position_.y <= 2.0f) {
            position_.y = 2.0f;
            bonusState_ = BonusState::Waiting;
            waitTimer_ = 0;
        }
        break;

    case BonusState::Waiting:
        waitTimer_++;
        if (waitTimer_ >= 120) {
            bonusState_ = BonusState::Returning;
        }
        break;

    case BonusState::Returning:
        position_.y += 0.02f;
        if (position_.y >= 5.0f) {
            position_.y = 5.0f;
            bonusState_ = BonusState::None;
        }
        break;
    }

    worldTransform_.translation_ = position_;
    worldTransform_.UpdateMatrix();
}

void BONUS::Draw()
{
    model_->Draw(worldTransform_, *viewProjection_);
}

void BONUS::StartBonus()
{
    if (bonusState_ == BonusState::None) {
        bonusState_ = BonusState::Dropping;
    }
}

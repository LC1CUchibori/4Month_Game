#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ヘッダーファイル/PushButton.h"

void PushButton::Initialize(Model* model, ViewProjection* viewProjection) {
    worldTransform_.Initialize();
    model_ = model;
    viewProjection_ = viewProjection;

    defaultY_ = worldTransform_.translation_.y; // 初期位置を保存
}

void PushButton::Update() {
    Input* input = Input::GetInstance();
    bool isCurrentlyPressed = input->PushKey(DIK_1); // 現在のキー状態

    // 現在のキー状態を保存
    wasPressed_ = isCurrentlyPressed;

    if (toggleState_) {
        worldTransform_.translation_.y = defaultY_ + pressHeight_; // 上がる
    } else {
        worldTransform_.translation_.y = defaultY_; // 下がる
    }

    // 1キーが押されたら toggleState_ を false にする（ボタンを下げる）
    if (isCurrentlyPressed) {
        toggleState_ = false;
    }

    worldTransform_.UpdateMatrix();
}

void PushButton::Draw() {
    model_->Draw(worldTransform_, *viewProjection_);
}

void PushButton::SetToggle(bool state)
{
    toggleState_ = state;
}


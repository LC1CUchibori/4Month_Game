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

    // キーが押された瞬間
    if (isCurrentlyPressed && !wasPressed_) {
        toggleState_ = !toggleState_;
    }

    // 現在の状態に応じてY座標を変更
    if (toggleState_) {
        worldTransform_.translation_.y = defaultY_ + pressHeight_; // 上がる
    } else {
        worldTransform_.translation_.y = defaultY_; // 下がる
    }

    worldTransform_.UpdateMatrix();

    // 現在のキー状態を保存
    wasPressed_ = isCurrentlyPressed;
}

void PushButton::Draw() {
    model_->Draw(worldTransform_, *viewProjection_);
}

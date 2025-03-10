#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"

class PushButton {
public:
    void Initialize(Model* model, ViewProjection* viewProjection);
    void Update();
    void Draw();

private:
    WorldTransform worldTransform_;
    Model* model_ = nullptr;
    ViewProjection* viewProjection_ = nullptr;

    bool toggleState_ = false; // true:上がる, false:下がる
    bool wasPressed_ = false;  // 前フレームのキー状態
    float pressHeight_ = 1.0f; // 上昇する高さ
    float defaultY_ = 0.0f;    // 初期のY座標
};

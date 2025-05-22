#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Model.h"
#include "Sprite.h"
#include "Input.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Title {
public:
    void Initialize(Model* model1, Model* model2, ViewProjection* viewProjection, Vector3 position);

    void Update();

    void Draw();

    void SpriteDraw();

    void Probability();

    void SetIsActive(bool active) { isActive_ = active; }

    //イーズアウトクアッド
    float EaseOutQuad(float x) {
        return 1 - (1 - x) * (1 - x);
    }

private:
    DirectXCommon* dxCommon_ = nullptr;
    Input* input_ = nullptr;
    Audio* audio_ = nullptr;

    // 3Dモデル
    Model* model1_ = nullptr;
    Model* model2_ = nullptr;
    Model* model3_ = nullptr;

    // テクスチャハンドル
    uint32_t textureHandle_[3];

    // スプライト
    Sprite* sprite_[3];

    // ワールドトランスフォーム
    WorldTransform worldTransform_;
    // ビュープロジェクション
    ViewProjection* viewProjection_ = nullptr;

    // サウンドデータ
    uint32_t Falling = 0;

    // 音声再生ハンドル
    uint32_t voiceHandle_ = 0u;

    // 速度
    float Speed = 0.08f;
    // タイマー
    float timer = 0.0f;
    // 元の位置を記録
    Vector3 originalPosition_;

    // 演出フラグ
    bool isActive_ = false;

    // モデル落下フラグ
    bool Fallingflag = true;

    // モデル切り替えフラグ
    bool Modelflag = false;

    // 役物落下フラグ
    bool Accessory = false;

    // スプライト切り替えフラグ
    bool Spriteflag1 = false;
    bool Spriteflag2 = false;
};


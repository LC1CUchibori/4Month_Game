#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Lever;

class Reel
{
public:
    void Initialize(Model* model, ViewProjection* viewProjection,Lever* lever);

    void Update();

    void Draw();

    void StartRotation();

    void StopRotation();

    bool IsRotating() const { return isRotating_; }

    int GetMedals() const { return medals_; }

    enum class Symbol {
        Cherry,
        RedSeven,
        blueSeven,
        Bar,
        Bell,
        Watermelon,
        RePlay,
    };

    Reel::Symbol GetResultSymbol();

    std::vector<Symbol> GetSymbols() const;

private:
    // 3Dモデル
    Model* model_ = nullptr;
    // ワールドトランスフォーム
    WorldTransform worldTransform_;
    // ビュープロジェクション
    ViewProjection* viewProjection_ = nullptr;

    Lever* lever_ = nullptr;

    // 回転してるかのフラグ
    bool isRotating_ = false;

    float symbolAngle = 360.0f / 10.0f; // 36度

    bool isStopping_ = false; // 滑らか停止中フラグ
    float stopTargetAngle_ = 0.0f; // 止めたい最終角度
    float rotationSpeed_ = 0.1f;   // 現在の回転速度

    std::vector<Symbol> symbols_; // リールに並ぶ役

    const float symbolAngleRad_ = 36.0f * (3.14159265f / 180.0f); // 一つのシンボル間の角度（10シンボルなら36度）

    int medals_ = 0; 
};


#pragma once
#include "ヘッダーファイル/Reel.h"
#include "ヘッダーファイル/Reel2.h"
#include "ヘッダーファイル/Reel3.h"

class Slot
{
public:
    void Initialize(Model* model, ViewProjection* viewProjection);

    void Update();

    void Draw();

    //Slot(Reel* reel1, Reel* reel2, Reel* reel3) {};

    // 横の判定
    bool CheckHorizontal();

    // 縦の判定
    bool CheckVertical();

private:
    // 3Dモデル
    Model* model_ = nullptr;
    // ワールドトランスフォーム
    WorldTransform worldTransform_;
    // ビュープロジェクション
    ViewProjection* viewProjection_ = nullptr;

    // レバーパーツのモデル
    Model* modelLeverParts_ = nullptr;

    // メダルカウントボタンのモデル
    Model* modelMedalCountButton_ = nullptr;

    // 投入機のモデル
    Model* modelMoneyBox_ = nullptr;

    Reel* reel1_;
    Reel* reel2_;
    Reel* reel3_;
};
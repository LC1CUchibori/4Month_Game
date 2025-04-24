#pragma once
#include "Input.h"
#include "Audio.h" 
#include <rand.h>

class GameScene;

class Lever
{
public:
    void Initialize(Model* model, ViewProjection* viewProjection,GameScene* pGameScene);

    void Update(int &medal, int&gameCont, bool&isFreePlay);

    void Draw();

    bool IsPulled() const
    {
        return downTimer_ > 0;
    }

    int GetStorenum(){return storenum;}

    // リール1の記憶フラグ
    void SetReel1(bool isRotating) { this->isRotating1_ = isRotating; }

    // リール2の記憶フラグ
    void SetReel2(bool isRotating) { this->isRotating2_ = isRotating; }

    // リール3の記憶フラグ
    void SetReel3(bool isRotating) { this->isRotating3_ = isRotating; }

private:
    Audio *audio_ = nullptr;

    // 3Dモデル
    Model* model_ = nullptr;
    // ワールドトランスフォーム
    WorldTransform worldTransform_;
    // ビュープロジェクション
    ViewProjection* viewProjection_ = nullptr;
    // インプット
    Input* input_ = nullptr;

    GameScene* mode_ = nullptr;

    const float DownOffsetY = -0.2f; // 下がる距離
    const int DownTime = 10;         // 下がっている時間
    int downTimer_ = 0;              // 下がり時間カウント

    //サウンドデータハンドル
    uint32_t LEVER = 0;

    //音声再生ハンドル
    uint32_t voiceHandle_ = 0;

    bool isPulled_ = false;

    Rand rng;


    int storenum = rng.GetRandamNumber(0,300);

    // リール1フラグ
    bool isRotating1_ = false;

    //　リール2フラグ
    bool isRotating2_ = false;

    // リール3フラグ
    bool isRotating3_ = false;
};





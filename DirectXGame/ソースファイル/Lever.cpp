#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ヘッダーファイル/Lever.h"
#include "GameScene.h"


void Lever::Initialize(Model *model, ViewProjection* viewProjection, GameScene* pGameScene)
{
    audio_ = Audio::GetInstance();
	input_ = Input::GetInstance();

    //BGM・SE読み込み
    LEVER = audio_->LoadWave("SE/Lever.wav");
    mode_ = pGameScene;
	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Lever::Update(int &medal,int&gameCount,bool&isFreePlay)
{
    // エンターキーが押されたらタイマー開始
    if (medal >= 3 && input_->TriggerKey(DIK_RETURN) &&
        isRotating1_ == false && isRotating2_ == false && isRotating3_ == false&&mode_->Getmode()==0) {
            voiceHandle_ = audio_->PlayWave(LEVER, false);
            downTimer_ = DownTime;
            storenum = rng.GetRandamNumber(1, 400);
           

            gameCount += 1;

            if (!isFreePlay) {
                medal -= 3;
            }
    }

    // エンターキーが押されたらタイマー開始
    if (medal >= 3 && input_->TriggerKey(DIK_RETURN) &&
        isRotating1_ == false && isRotating2_ == false && isRotating3_ == false&&mode_->Getmode()==1) {
        voiceHandle_ = audio_->PlayWave(LEVER, false);
        downTimer_ = DownTime;
        storenum = rng.GetRandamNumber(1, 200);


        gameCount += 1;

        if (!isFreePlay) {
            medal -= 3;
        }
    }

    //　リトライの時にメダルが2枚以下でも回るようにする処理
    if (medal <= 2 && isFreePlay && input_->TriggerKey(DIK_RETURN) &&
        isRotating1_ == false && isRotating2_ == false && isRotating3_ == false) {
        voiceHandle_ = audio_->PlayWave(LEVER, false);
        downTimer_ = DownTime;
        storenum = rng.GetRandamNumber(1, 300);

        gameCount += 1;
    }


    // タイマーが残っている間は下げる
    if (downTimer_ > 0) {
        worldTransform_.translation_.y = DownOffsetY;
        downTimer_--;
    } else{
        worldTransform_.translation_.y = 0.0f;
    }

    worldTransform_.UpdateMatrix();

    std::cout<<"ランダム"<<storenum<<std::endl;
}

void Lever::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}
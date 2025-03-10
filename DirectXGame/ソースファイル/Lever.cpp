#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "ヘッダーファイル/Lever.h"


void Lever::Initialize(Model *model, ViewProjection* viewProjection)
{
    audio_ = Audio::GetInstance();
	input_ = Input::GetInstance();

    //BGM・SE読み込み
    LEVER = audio_->LoadWave("SE/Lever.wav");

	worldTransform_.Initialize(); 
	model_ = model;
	viewProjection_ = viewProjection;
}

void Lever::Update(int &medal,int&gameCount)
{
    // エンターキーが押されたらタイマー開始
    if (medal >= 3 && input_->TriggerKey(DIK_RETURN)) {
        downTimer_ = DownTime;
        storenum = rng.GetRandamNumber(1,300);
        
        gameCount += 1;

        medal -= 3;
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
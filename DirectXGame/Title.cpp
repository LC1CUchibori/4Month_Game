#include "Title.h"

void Title::Initialize(Model* model1, Model* model2, ViewProjection* viewProjection, Vector3 position) {
    dxCommon_ = DirectXCommon::GetInstance();
    input_ = Input::GetInstance();
    audio_ = Audio::GetInstance();

    // 乱数の初期化
    srand((unsigned) time(NULL));

    //引数として受け取ったデータをメンバ変数に記録
    model1_ = model1;
    model2_ = model2;
    viewProjection_ = viewProjection;
    worldTransform_.translation_ = position;
    originalPosition_ = position;

    // BGM・SE読み込み
    Falling = audio_->LoadWave("SE/Falling.wav");

    ////ファイル名を指定してテクスチャを読み込む
    //textureHandle_[0] = TextureManager::Load("Haikei.png");
    //textureHandle_[1] = TextureManager::Load("Haikei1.png");
    //textureHandle_[2] = TextureManager::Load("Haikei2.png");

    //スプライトの生成
    sprite_[0] = Sprite::Create(textureHandle_[0], { 525, 160 });
    sprite_[1] = Sprite::Create(textureHandle_[1], { 525, 160 });
    sprite_[2] = Sprite::Create(textureHandle_[2], { 525, 160 });

    //ワールド変数の初期化
    worldTransform_.Initialize();
}

void Title::Update() {
    // 演出
    if (isActive_){
        if (Fallingflag) {
            // 落下処理
            worldTransform_.translation_.y -= Speed;

            // 落下が終わったら停止してタイマーをリセット
            if (worldTransform_.translation_.y < 4.5) {
                Probability();
                Fallingflag = false;
                timer = 0;
            }
        } else {
            // 停止後の待機時間をカウント
            timer += 0.1f;

            // 6秒経過したら上昇開始
            if (timer >= 60.0f) {
                worldTransform_.translation_.y += Speed;

                // 元の位置に戻ったか確認
                if (worldTransform_.translation_.y >= originalPosition_.y) {
                    isActive_ = false;
                    Fallingflag = true;
                    if (rand() % 100 < 100) {
                        Accessory = true;
                    }
                    worldTransform_.translation_.y = originalPosition_.y; // 正確な位置に戻す
                }
            }
        }
    }

    // 確率で役物落下
    if (Accessory) {
        voiceHandle_ = audio_->PlayWave(Falling, false);
        worldTransform_.translation_.y -= 3.0f;

        // 範囲制限
        if (worldTransform_.translation_.y < 4.5) {
            worldTransform_.translation_.y = 4.5;
            timer = 0;
            Modelflag = true;
            Accessory = false;
        }
    }

    if (Modelflag) {
        // 停止後の待機時間をカウント
        timer += 0.1f;

        // 2秒経過したら上昇開始
        if (timer >= 2.0f) {
            worldTransform_.translation_.y += 3.0f;

            // 元の位置に戻ったか確認
            if (worldTransform_.translation_.y >= originalPosition_.y) {
                worldTransform_.translation_.y = originalPosition_.y; // 正確な位置に戻す
            }
        }
    }

    // ワールドトランスフォームの更新
    worldTransform_.UpdateMatrix();
}

void Title::Draw() {
    if (!Modelflag) {
        model1_->Draw(worldTransform_, *viewProjection_);
    }
    else {
        model2_->Draw(worldTransform_, *viewProjection_);
    } 
}

void Title::SpriteDraw() {
    if (!Spriteflag1 && !Spriteflag2) {
        sprite_[0]->Draw();
    }
    else if (Spriteflag1 && !Spriteflag2) {
        sprite_[1]->Draw();
    }
    else if (!Spriteflag1 && Spriteflag2) {
        sprite_[2]->Draw();
    }
}

// 確率で判定
void Title::Probability() {
    int random = rand() % 100;

    if (random < 80) {
        Spriteflag1 = true;
        Spriteflag2 = false;
    }
    else if (random < 80 + 50) {
        Spriteflag1 = false;
        Spriteflag2 = true;
    }
    else {
        Spriteflag1 = false;
        Spriteflag2 = false;
    }
}



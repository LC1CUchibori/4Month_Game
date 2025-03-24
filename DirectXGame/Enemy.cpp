#include "Enemy.h"

// コンストラクタ
Enemy::Enemy() : isActive_(false) {}

// デストラクタ
Enemy::~Enemy() { 
    delete model_; 
}

void Enemy::Initialize()
{
    position_ = Vector3(0, 0, 0);  // 初期位置を設定
}

void Enemy::Update()
{
//if (isActive_) {
//    // 敵がアクティブなときの動作
//    // 例: 敵を動かす、攻撃するなどの処理を追加
//}
}

void Enemy::Draw()
{
    if (isActive_) {
        worldTransform_.translation_ = position_;
        model_->Draw(worldTransform_, *viewProjection_);
    }
}

#include "Player.h"

void Player::Initialize()
{
    position_ = Vector2(0, 0);  // 初期位置を設定
}

void Player::Update()
{
    static float speed = 2.0f;  // 移動速度
    static float maxX = 100.0f;  // 右端の位置
    static float minX = -100.0f; // 左端の位置

    // プレイヤーが右に進む
    position_.x += speed;

    // 右端を越えたら左に戻す
    if (position_.x > maxX) {
        position_.x = maxX;
        speed = -speed;  // 左に進むように速度を反転
    }

    // 左端を越えたら右に戻す
    if (position_.x < minX) {
        position_.x = minX;
        speed = -speed;  // 右に進むように速度を反転
    }
}

void Player::Draw()
{
    sprite_->Draw();  // sprite_ を描画
}

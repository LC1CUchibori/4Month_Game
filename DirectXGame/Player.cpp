#include "Player.h"

void Player::Initialize()
{
    position_ = Vector2(0, 0);  // 初期位置を設定
}

void Player::Update()
{
    walkAnimationTimer_++;
    const float amplitude = 5.0f;  // 揺れる幅（±5ピクセルくらい）
    const float speed = 0.1f;      // 揺れるスピード

    walkOffsetX_ = std::sin(walkAnimationTimer_ * speed) * amplitude;

}

void Player::Draw()
{
    if (sprite_) {
        Vector2 offsetPosition = { position_.x + walkOffsetX_, position_.y };
        sprite_->SetPosition(offsetPosition);
        sprite_->Draw();
    }
}

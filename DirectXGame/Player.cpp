#include "Player.h"

void Player::Initialize()
{
    position_ = Vector2(0, 0);  // 初期位置を設定
}

void Player::Update()
{
 
}

void Player::Draw()
{
    if (sprite_) {
        sprite_->Draw();
    }
}

#include "Player.h"

void Player::Initialize()
{
	position_ = Vector3(0, 0, 0);  // 初期位置を設定
}

void Player::Update()
{
}

void Player::Draw()
{
	sprite_->Draw();
}

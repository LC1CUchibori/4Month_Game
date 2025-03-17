#include "Puchun.h"

void Puchun::Initialize(const std::vector<uint32_t>& textureHandles) {
	sprites.clear();
	for (uint32_t handle : textureHandles) {
		sprites.push_back(Sprite::Create(handle, {0, 0}));
	}
	currentFrame = 0;
	time = 0.0f;
	isPlaying = false;
	isFinishing = false;
}

void Puchun::Update() {
	if (isPlaying) {
		// 時間を進める
		time += 0.016f; // 60FPSの場合
		if (time >= frameDuration) {
			// フレームを進める
			currentFrame++;
			if (static_cast<size_t>(currentFrame) >= sprites.size()) { // 最後のフレームに到達
				// 2 秒間最後のフレームを表示
				isPlaying = false;
				isFinishing = true;
				currentFrame = static_cast<int>(sprites.size()) - 1;
				time = 0.0f;
			} else {
				time = 0.0f;
			}
		}
	} else if (isFinishing) {
		// 最後のフレームを 2 秒間表示
		time += 0.016f;
		if (time >= lastFrameDuration) {
			isFinishing = false; // 完全に終了
		}
	}
}

void Puchun::Draw() {
	// アニメーション中または最後のフレームを表示中なら描画
	if (isPlaying || isFinishing) {
		if (currentFrame < sprites.size()) {
			sprites[currentFrame]->Draw();
		}
	}
}

void Puchun::Start() {
	currentFrame = 0;
	time = 0.0f;
	isPlaying = true;
	isFinishing = false;
}

bool Puchun::IsFinished() const { return !isPlaying && !isFinishing; }
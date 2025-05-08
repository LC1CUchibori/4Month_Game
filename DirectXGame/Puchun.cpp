#include "Puchun.h"

void Puchun::Initialize(const std::vector<uint32_t>& textureHandles, Audio* audio) {
	sprites.clear();
	for (uint32_t handle : textureHandles) {
		sprites.push_back(Sprite::Create(handle, {525, 160}));
	}

	audio_ = audio; // Audioインスタンスを保持
	if (audio_) {
		pichunSound_ = audio_->LoadWave("Pichun.wav");
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

	// アニメーション開始時（最初の画像が出たとき）に音を再生
	if (audio_) {
		audio_->PlayWave(pichunSound_);
	}
}

bool Puchun::IsFinished() const { return !isPlaying && !isFinishing; }

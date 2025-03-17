#pragma once
#include <Sprite.h>
#include <vector>

class Puchun {
public:
	/// <summary>
	/// 初期化（7枚のテクスチャを渡す）
	/// </summary>
	void Initialize(const std::vector<uint32_t>& textureHandles);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// アニメーションを開始
	/// </summary>
	void Start();

	/// <summary>
	/// アニメーションが終了したか判定
	/// </summary>
	bool IsFinished() const;

private:
	std::vector<Sprite*> sprites;
	int currentFrame = 0;
	float time = 0.0f;
	bool isPlaying = false;
	bool isFinishing = false; // 最後のフレームを表示するためのフラグ
	const float frameDuration = 0.0325f;
	const float lastFrameDuration = 0.5f; // 最後のフレームの表示時間
};

#pragma once
#include <Vector3.h>
#include <Model.h>
class Enemy
{
public:
    Enemy();

    ~Enemy();

    void Initialize();

    void Update();

    void Draw();

    void SetIsActive(bool active) {
        // 敵をアクティブにする処理
        isActive_ = active;
    }

    int GetIsActive() const { return isActive_; }

private:

    // ワールドトランスフォーム
    WorldTransform worldTransform_;
    // ビュープロジェクション
    ViewProjection* viewProjection_ = nullptr;
    Vector3 position_;  // 敵の位置
    Model* model_;      // 敵のモデル
    bool isActive_ = false;     // 敵がアクティブかどうか
};


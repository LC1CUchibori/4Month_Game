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
private:
    Vector3 position_;  // 敵の位置
    Model* model_;      // 敵のモデル
    bool isActive_;     // 敵がアクティブかどうか
};


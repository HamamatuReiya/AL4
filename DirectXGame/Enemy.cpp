#include "Enemy.h"

void Enemy::Initialize(const std::vector<Model*>& models) { 
	BaseCharacter::Initialize(models);

	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 5.0f};

	worldTransformBody_.Initialize();
	worldTransformBody_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformBody_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformBody_.translation_ = {0.0f, -0.5f, 0.0f};

	worldTransformL_arm_.Initialize();
	worldTransformL_arm_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformL_arm_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformL_arm_.translation_ = {-1.0f, 0.5f, 0.0f};

	worldTransformR_arm_.Initialize();
	worldTransformR_arm_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformR_arm_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_arm_.translation_ = {1.0f, 0.5f, 0.0f};
}

void Enemy::Update() {
	BaseCharacter::Update();

	Vector3 move = {0.0f, 0.0f, 1.5f};
	move = TransformNormal(move, worldTransform_.matWorld_);
	
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	worldTransform_.rotation_.y += 0.02f;

	worldTransformBody_.parent_ = &worldTransform_;
	worldTransformL_arm_.parent_ = &worldTransform_;
	worldTransformR_arm_.parent_ = &worldTransform_;

	

	// 行列の計算
	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	// 3Dモデル描画
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformL_arm_, viewProjection);
	models_[2]->Draw(worldTransformR_arm_, viewProjection);
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::RoopInitialize() {
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 5.0f};
}

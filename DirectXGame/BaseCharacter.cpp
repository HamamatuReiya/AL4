#include "BaseCharacter.h"

void BaseCharacter::Initialize(const std::vector<Model*>& models) { 
	models_ = models;
	worldTransform_.Initialize();

}

void BaseCharacter::Update() {
	// 行列の計算
	worldTransform_.UpdateMatrix();
}

void BaseCharacter::Draw(const ViewProjection& viewProjection) {
	// モデル描画
	for (Model* model : models_) {
		model->Draw(worldTransform_, viewProjection);
	}
}

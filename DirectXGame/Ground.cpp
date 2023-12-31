﻿#include "Ground.h"

void Ground::Initialize(Model* model) 
{
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void Ground::Update() {}

void Ground::Draw(ViewProjection& viewProjection) 
{
	// 3Dモデル描画
	model_->Draw(worldTransform_, viewProjection);
}

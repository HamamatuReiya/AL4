#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <Input.h>
#include "MatrixMath.h"
#define _USE_MATH_DEFINES
#include <math.h>


/// <summary>
/// 自キャラ
/// </summary>
class Player 
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション(参照渡し)</param>
	void Draw(ViewProjection& viewProjection);

	WorldTransform& GetWorldTransform() { return worldTransform_; };

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	//浮遊ギミック初期化
	void InitializeFloatGimmick();
	//浮遊ギミック更新
	void UpdateFloatingGimmick();

private:
	//ワールド座標データ
	WorldTransform worldTransform_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	//モデル
	Model* model_ = nullptr;
	//カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	//3Dモデル
	Model* modelFighterBody_;
	Model* modelFighterHead_;
	Model* modelFighterL_arm_;
	Model* modelFighterR_arm_;

	//浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;
};

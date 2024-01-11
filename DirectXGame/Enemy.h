#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "BaseCharacter.h"
#include "MatrixMath.h"

class Enemy : public BaseCharacter {
public:
	/// <summary>
	/// 初期化
	///  </summary>
	/// <param name="models_">モデルデータ配列</param>
	void Initialize(const std::vector<Model*>& models) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション(参照渡し)</param>
	void Draw(const ViewProjection& viewProjection) override;

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	void RoopInitialize();

private:
	// ワールド座標データ
	WorldTransform worldTransform_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	// モデル
	Model* model_ = nullptr;

	// 3Dモデル
	Model* modelFighterBody_;
	Model* modelFighterL_arm_;
	Model* modelFighterR_arm_;
};

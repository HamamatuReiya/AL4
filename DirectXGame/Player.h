#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <Input.h>
#include "MatrixMath.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "BaseCharacter.h"
#include <optional>

/// <summary>
/// 自キャラ
/// </summary>
class Player : public BaseCharacter
{
public:
	/// <summary>
	/// 初期化
	///  </summary>
	/// <param name="models_">モデルデータ配列</param>
	void Initialize(const std::vector<Model*>& models) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション(参照渡し)</param>
	void Draw(const ViewProjection& viewProjection) override;

	WorldTransform& GetWorldTransform() { return worldTransform_; };

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	//浮遊ギミック初期化
	void InitializeFloatGimmick();
	//浮遊ギミック更新
	void UpdateFloatingGimmick();

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	void RoopInitialize();

	
private:
	//ワールド座標データ
	WorldTransform worldTransform_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	WorldTransform worldTransformHammer_;
	//モデル
	Model* model_ = nullptr;
	//カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	//3Dモデル
	Model* modelFighterBody_;
	Model* modelFighterHead_;
	Model* modelFighterL_arm_;
	Model* modelFighterR_arm_;
	Model* modelFighterHammer_;

	//浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

	// 通常行動初期化
	void BehaviorRootInitialize();
	// 通常行動更新
	void BehaviorRootUpdate();

	// 攻撃行動初期化
	void BehaviorAttackInitialize();
	// 攻撃行動更新
	void BehaviorAttackUpdate();

	enum class Behavior {
		kRoot,   // 通常状態
		kAttack, // 攻撃中
	};

	// 振るまい
	Behavior behavior_ = Behavior::kRoot;

	// 次のふるまいのリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	//攻撃時間
	float attackTime;

	bool isHammerDraw_;
	bool isHammerSet_;
	float stanbyTime;
};

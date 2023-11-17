#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <Input.h>
#include "MatrixMath.h"


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
	void Initialize(Model* model);

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

private:
	//ワールド座標データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;
};

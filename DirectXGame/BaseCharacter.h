#pragma once
#include "Model.h"
#include "WorldTransform.h"

class BaseCharacter {

protected:
	// モデルデータ配列
	std::vector<Model*> models_;
	// ワールド座標データ
	WorldTransform worldTransform_;

public:
	/// <summary>
	/// 初期化
	///  </summary>
	/// <param name="models_">モデルデータ配列</param>
	virtual void Initialize(const std::vector<Model*>& models);

	/// <summary>
	/// 更新
	///  </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	///  </summary>
	/// <param name="viewProjection">ビュープロジェクション(参照渡し)</param>
	virtual void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// ワールド変換データを取得
	///  </summary>
	/// <returns>ワールド変換データ</returns>
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
};

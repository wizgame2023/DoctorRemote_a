/*!
@file EnemyMovieManager.h
@brief Enemyに出会ったときの演出
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"
#include"SelectSprite.h"

namespace basecross {
	class EnemyMovieManager :public GameObject
	{
	private:
		Vec3 m_Scale;
		Vec3 m_Position;
		Vec3 m_Rotate;
		shared_ptr<Transform> m_Trans;
		shared_ptr<Camera> m_MovieCamera;//ムービー用のカメラ
		weak_ptr<MainCamera> m_StageCamera;//ステージのカメラ(ゲームプレイ用)
		weak_ptr<ViewBase> m_StageView;//ステージのビュー(ゲームプレイ用)
		shared_ptr<Sprite> m_MovieBand;//ムービー用の帯

		int m_Count;//フラグ管理
		float m_Time;
	public:
		EnemyMovieManager(shared_ptr<Stage>& stage,Vec3 Pos, Vec3 scale);
		~EnemyMovieManager();

		void OnCreate()override;
		void OnUpdate()override;

		Vec3 MoveVec(float speed, Vec3 Pos, Vec3 tagetPos);//移動ベクトルを求める関数

		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;//コリジョンが入った時


	};
}
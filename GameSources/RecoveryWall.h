/*!
@file RecoveryWall.h
@brief 回復する壁
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RecoveryWall : public GameObject
	{
	private:
		Vec3 m_Scale;
		Vec3 m_Position;
		Vec3 m_Rotate;
		Vec3 m_StratPosition;
		int m_hp;
		weak_ptr<Bullet> m_bullet;
		shared_ptr<Transform> m_Transform;


	public:
		RecoveryWall(const shared_ptr<Stage>& StagePtr,
			Vec3 m_Position,
			Vec3 m_Scale,
			Vec3 m_Rotate
		);
		~RecoveryWall();
		void OnCreate()override;//初期化UnityでいうところのStart
		void OnUpdate()override;//アップデート
		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;//コリジョンが入った時

	};
}
//end namespace basecross


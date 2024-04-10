/*!
@file Bullet.h
@brief 弾
担当　三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Bullet : public GameObject
	{
	private:
		Vec3 m_Position;//場所
		Vec3 m_Scale;//サイズ
		float m_Speed;//速さ
		float m_angle;//角度
		int m_Attack;//攻撃力
	public:
		Bullet(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Position,
			const Vec3& Scale,
			float Speed,
			float angle,
			int Attack
		);
		~Bullet();
		void OnCreate()override;//初期化UnityでいうところのStart
		void OnUpdate()override;//アップデート
		void OnCollisionEnter(shared_ptr<GameObject>& Other) override;//コリジョンが入った時
		float GetSpeed();
		int GetAttack();

	};
}
//end namespace basecross
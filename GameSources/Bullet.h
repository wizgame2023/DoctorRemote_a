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
		Vec3 m_AllStartPosition;
		int m_Attack;//攻撃力
		int m_hit;//当たった相手によって数値が変わる
		bool statusFlag;

	public:
		static int STATUSBULLET;
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
		void SetStatusFlag(bool flag);

	};
}
//end namespace basecross
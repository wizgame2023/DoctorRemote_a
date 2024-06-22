/*!
@file Bullet.h
@brief 弾
担当　三瓶裕太
*/

#pragma once
#include "stdafx.h"
#include "EffectPiece.h"

namespace basecross {
	class Bullet : public GameObject
	{
	private:
		float m_speed;//速さ
		float m_angle;//角度
		int m_attack;//攻撃力
		int m_hit;//当たった相手によって数値が変わる
		int m_statusFlag;
		int m_bulletLevel;

		Vec3 m_Position;//場所
		Vec3 m_Scale;//サイズ
		Vec3 m_AllStartPosition;
		Vec3 m_velocity;
		Vec3 m_effectPos;

		float m_shotRange;

		wstring m_meshResName;
		weak_ptr<EffectPiece> m_effect;
		weak_ptr<EffectPiece> m_effect2;

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
		void ThisDestroy();
		float GetSpeed();
		int GetAttack();
		int GetBulletLevel();
		void SetBulletLevel(int level);

	};
}
//end namespace basecross
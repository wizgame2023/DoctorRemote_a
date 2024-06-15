/*!
@file EnemyPiece.h
@brief ìGÇÃåáï–
íSìñÅFàÌå©
*/

#pragma once
#include "stdafx.h"
#include "Bullet.h"

namespace basecross {
	class EnemyPiece :public GameObject {
	private:
		float m_pieceDeleteTime;
		float m_deg;
		int m_hp;
		int m_enemyDeletFlag;
		bool m_pieceDeleteFlag;
		bool m_ground;
		bool m_littlePieceFlag;
		Vec3 m_scale;
		Vec3 m_rotate;
		Vec3 m_position;
		Vec3 m_velocity;
		wstring m_meshResName;

		shared_ptr<Transform> m_trans;
		shared_ptr<GameObject> m_boss;
		shared_ptr<Bullet> m_bullet;

	public:
		EnemyPiece(const shared_ptr<Stage>& StagePtr,
			const Vec3& position,
			const Vec3& rotate,
			const Vec3& scale,
			const bool littlePiece = true
		);
		virtual ~EnemyPiece(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//è’ìÀÇµÇΩéû
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other);
		void Event(float deg);
		void UpdateEvent();
		Vec3 GetPos();
		Vec3 GetRot();

		int GetDeletFlag();
	};
}
//end namespace basecross

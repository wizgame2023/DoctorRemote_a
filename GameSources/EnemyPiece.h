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
		float m_breakCount;
		float m_chainTime;
		int m_hp;
		int m_pieceDeletFlag;
		bool m_ground;
		bool m_littlePieceFlag;
		bool m_otherPieceFlag;
		Vec3 m_scale;
		Vec3 m_rotate;
		Vec3 m_position;
		Vec3 m_velocity;
		wstring m_meshResName;

		shared_ptr<Transform> m_trans;
		shared_ptr<GameObject> m_boss;
		weak_ptr<Bullet> m_bullet;
		shared_ptr<EnemyPiece> m_otherPiece;

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
		void ScatterDestroy(int littleNum = 0,bool des = true);
		void ChainEffect(float radius);
		Vec3 GetPos();
		Vec3 GetRot();
		void DelDamage(int damage,float count, const shared_ptr<EnemyPiece>& origin);

		int GetDeletFlag();
	};
}



//end namespace basecross

/*!
@file BigPiece.cpp
@brief 大きい欠片の実装
担当：逸見
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BigPiece :public GameObject {
	private:
		bool m_ground;
		bool m_enemyDeletFlag;
		bool m_littlePieceFlag;
		int m_var;//ビックピースのどの形態にするかを決める
		int m_status;
		int m_hp;
		int m_littlePieceNum;
		float m_pieceDeleteTime;

		Vec3 m_scale;
		Vec3 m_rotate;
		Vec3 m_position;
		Vec3 m_velocity;
		wstring m_meshResName;
		wstring m_myMiniMapName;
		wstring m_effectName;;
		shared_ptr<Transform> m_trans;
		weak_ptr<Bullet> m_bullet;

	public:
		BigPiece(const shared_ptr<Stage>& stagePtr,
			const Vec3& position,
			const Vec3& rotate,
			const Vec3 scale,
			int var = 1
		);
		BigPiece(const shared_ptr<Stage>& stagePtr,
			const Vec3& position,
			const Vec3& rotate,
			const Vec3 scale,
			const bool littlePiece,
			const int var = 1
		);
		virtual ~BigPiece() {}

		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
		void MyMiniMapName(wstring Name);//自分の位置がミニマップに表示するオブジェクトの名前
		void Event(float deg, float power=6.0f);
		void UpdateEvent();
		void ScatterDestroy(int littleNum,bool des = true);

	};
}
//end namespace basecaross
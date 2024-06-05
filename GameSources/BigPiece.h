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
		Vec3 m_scale;
		Vec3 m_rotate;
		Vec3 m_position;
		Vec3 m_velocity;
		wstring m_meshResName;
		wstring m_myMiniMapName;
		int m_var;//ビックピースのどの形態にするかを決める

	public:
		BigPiece(const shared_ptr<Stage>& stagePtr,
			const Vec3& position,
			const Vec3& rotate,
			const Vec3 scale,
			int var = 1
		);
		virtual ~BigPiece() {}

		virtual void OnCreate() override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
		void MyMiniMapName(wstring Name);//自分の位置がミニマップに表示するオブジェクトの名前
		void Event(float deg);
		void UpdateEvent();

	};
}
//end namespace basecaross
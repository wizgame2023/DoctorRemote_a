/*!
@file PieceLittle.cpp
@brief 欠片を壊したらでてくるオブジェクトの実体
担当：逸見
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PieceLittle :public GameObject {
	private:
		Vec3 m_position;
		Vec3 m_rotete;
		Vec3 m_scale;
		Vec3 m_velocity;

		float m_deg;
		float m_collect;
		float m_count;
		bool m_ground;

		shared_ptr<GameObject> m_obj;
		shared_ptr<GameObject> m_target;
		wstring m_meshResName;
	public:
		PieceLittle(const shared_ptr<Stage>& stagePtr, const shared_ptr<GameObject>& obj,
			const shared_ptr<GameObject>& target, const float deg);
		virtual ~PieceLittle(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& other);
	};

}
//end namespace basecross
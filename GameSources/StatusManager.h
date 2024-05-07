/*!
@file SatusManager.cpp
@brief ステート全体の処理等
担当：
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class StatusManager :public GameObject {
	private:
		float m_maxX;
		float m_width;
		bool m_checkR;
		bool m_checkL;

		int m_status;

		shared_ptr<Transform> m_trans;
		//shared_ptr<Sprite> m_sprite;
		Col4 m_color;

	public:
		StatusManager(const shared_ptr<Stage>& stagePtr);
		virtual ~StatusManager() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};
}
//end namespace basecross

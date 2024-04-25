/*!
@file TimeManager.h
@brief ŠÔ‚Ì•\¦
’S“–FˆíŒ©
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TimeManager :public GameObject {
	private:
		float m_time;

	public:
		TimeManager(const shared_ptr<Stage>& stagePtr);
		virtual ~TimeManager(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end namespace basecross
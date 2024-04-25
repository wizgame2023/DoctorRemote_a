/*!
@file UITime.h
@brief ŠÔ
’S“–FˆíŒ©
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UITime :public GameObject {
	private:
		float m_time;

	public:
		UITime(const shared_ptr<Stage>& stagePtr,float time);
		virtual ~UITime(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end namespace basecross

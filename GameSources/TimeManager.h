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
		int m_minutes;
		int m_seconds;

		int m_first;
		int m_second;
		int m_third;
		int m_fourth;

		bool m_move;

		shared_ptr<UITime> m_firstNum;
		shared_ptr<UITime> m_secondNum;
		shared_ptr<UITime> m_thirdNum;
		shared_ptr<UITime> m_fourthNum;


	public:
		TimeManager(const shared_ptr<Stage>& stagePtr);
		TimeManager(const shared_ptr<Stage>& stagePtr,bool move);
		virtual ~TimeManager(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void UpdateNumber();
		int GetTime();
	};
}
//end namespace basecross
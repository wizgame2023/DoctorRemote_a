/*!
@file TimeManager.h
@brief 時間の表示
担当：逸見
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

		Vec3 m_pos;

		Col4 m_outCol;//暗転時に使用するカラーの色を保存する変数

		shared_ptr<Sprite> m_blackout;//暗転時に使用するスプライト

		shared_ptr<UITime> m_firstNum;
		shared_ptr<UITime> m_secondNum;
		shared_ptr<UITime> m_thirdNum;
		shared_ptr<UITime> m_fourthNum;
		shared_ptr<UITime> m_ten;


	public:
		TimeManager(const shared_ptr<Stage>& stagePtr);
		TimeManager(const shared_ptr<Stage>& stagePtr,int time,Vec3 pos);
		virtual ~TimeManager(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void UpdateNumber();
		void SetTimeFlag(bool timeFlag);
	};
}
//end namespace basecross
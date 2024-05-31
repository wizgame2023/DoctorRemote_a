/*!
@file StageManagar.h
@brief ステージ全体の処理等
担当：逸見
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "UITime.h"

namespace basecross {
	class StageManager :public GameObject {
	private:
		float m_currentHp;
		float m_maxHp;
		float m_hpSpeed;
		float m_count;
		float m_countStart;
		float m_comX;

		int m_ligthStatus;
		int m_stageFlag;//ステージ全体のフラグ
		bool m_start;

		bool m_countNumFlag;
		bool m_cfFlag;
		bool m_comFlag;
		bool m_countFlag;


		shared_ptr<Sprite> m_ligth;
		shared_ptr<Sprite> m_startSprite;
		shared_ptr<UITime> m_num;
		shared_ptr<Sprite> m_comFrame;
		shared_ptr<Transform> m_comTrans;

	public:
		StageManager(const shared_ptr<Stage>& stagePtr);
		virtual ~StageManager(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		float GetHp();
		float GetHpRatio();
		void SetHp(float hp);
		void SetCountFlag(bool OnOff);
		void SetStageFlag(int Flag);
		int GetStageFlag();
		bool GetStartFlag();
		void SetStartFlag(bool start);

	};
}
//end namespace basecross
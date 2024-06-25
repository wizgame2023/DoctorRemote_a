/*!
@file SatusManager.cpp
@brief ステート全体の処理等
担当：逸見
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "Player.h"
#include "CommentManager.h"
#include "StageSelectSprite.h"
#include "UITime.h"

namespace basecross {
	class StatusManager :public GameObject {
	private:
		float m_maxX;
		float m_width;
		bool m_checkR;
		bool m_checkL;
		bool m_colorCheck;
		bool m_moveCheck;
		bool m_comFlag;
		bool m_moveStick;
		float m_count;

		int m_decision;

		int m_status;
		int m_score;
		int m_control;
		shared_ptr<Transform> m_trans;
		shared_ptr<Player> m_player;
		shared_ptr<CommentManager> m_com[6];
		shared_ptr<StageSelectSprite> m_selectSprite;
		shared_ptr<UITime> m_pointNum[4];
		shared_ptr<Sprite> m_sprite;

		Col4 m_color;

	public:
		StatusManager(const shared_ptr<Stage>& stagePtr);
		virtual ~StatusManager() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void NumDisplay(int digit, int num,Vec3 pos);
		int GetStatus();
		int GetDecision();
	};
}
//end namespace basecross

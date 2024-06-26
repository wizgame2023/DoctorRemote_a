/*!
@file SelectSprite.h
@brief 動かすことができるスプライト
担当：逸見
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "StageSelectSprite.h"

namespace basecross {
	class SelectSprite :public GameObject {
	private:
		int m_stage;

		float m_width;
		float m_widthMax;
		float m_height;
		float m_heightMax;
		float m_heightMin;
		float m_spaces;
		float m_count;


		bool m_checkD;
		bool m_checkU;
		bool m_moveCheck;
		bool m_stageMove;
		bool m_stageStart;
		bool m_blinkCheck;
		bool m_selectStageFlag;
		bool m_exitFlag;

		shared_ptr<Transform> m_trans;
		shared_ptr<Sprite> m_sprite;
		shared_ptr<Sprite> m_stageFrame;
		shared_ptr<Sprite> m_RetrunCom;
		shared_ptr<Sprite> m_ExitTex;
		shared_ptr<StageSelectSprite> m_selectStage;
		Col4 m_color;

	public:
		SelectSprite(const shared_ptr<Stage>& stagePtr);
		virtual ~SelectSprite(){}

		virtual void OnCreate();
		virtual void OnUpdate();
		bool GetStageMove();
		void SetStageStart(bool start);
		void StageMove(wstring stage);

	};
}
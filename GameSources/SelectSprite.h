/*!
@file SelectSprite.h
@brief 動かすことができるスプライト
担当：逸見
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"

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
		bool m_blinkCheck;

		shared_ptr<Transform> m_trans;
		shared_ptr<Sprite> m_sprite;
		Col4 m_color;

	public:
		SelectSprite(const shared_ptr<Stage>& stagePtr);
		virtual ~SelectSprite(){}

		virtual void OnCreate();
		virtual void OnUpdate();
		bool GetMoveCheck();
	};
}
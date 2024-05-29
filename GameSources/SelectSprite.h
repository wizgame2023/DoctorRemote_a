/*!
@file SelectSprite.h
@brief 動かすことができるスプライト
担当：逸見
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SelectSprite :public GameObject {
	private:
		float m_width;
		float m_widthMax;
		float m_height;
		float m_heightMax;

		bool m_checkR;
		bool m_checkL;
		bool m_moveCheck;

		shared_ptr<Transform> m_trans;

	public:
		SelectSprite(const shared_ptr<Stage>& stagePtr);
		virtual ~SelectSprite(){}

		virtual void OnCreate();
		virtual void OnUpdate();
	};
}
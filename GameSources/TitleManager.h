/*!
@file TitleManager.h
@brief タイトルの選択
担当：逸見
*/

#pragma once
#include "stdafx.h"
#include"SelectSprite.h"

namespace basecross {
	class TitleManager :public GameObject {
	private:
		shared_ptr<Sprite> m_blackBoard;
		shared_ptr<SelectSprite>m_selectSprite;
		float m_anCollar;
	public:
		TitleManager(const shared_ptr<Stage>& stagePtr);
		virtual ~TitleManager(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}

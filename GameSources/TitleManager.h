/*!
@file TitleManager.h
@brief タイトルの選択
担当：逸見
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleManager :public GameObject {
	private:

	public:
		TitleManager(const shared_ptr<Stage>& stagePtr);
		virtual ~TitleManager(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}

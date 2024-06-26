/*!
@file ClearStage.h
@brief クリアステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ClearStage :public Stage {
		void CreateViewLight();

	public:
		ClearStage() :Stage() {}
		virtual ~ClearStage() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		shared_ptr<SoundItem> m_BGM;
		
		void BaseBGM();
		void OnDestroy();
		void StageChange();

	};
}
//end namespace basecross


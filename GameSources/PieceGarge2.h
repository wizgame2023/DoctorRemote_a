/*!
@file PlayerGarge.h
@brief プレイヤーの体力ゲージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PieceGarge2 :public GameObject {
	private:

		float m_ratio;

		bool m_gargeMaxFlag;
		shared_ptr<Garge> m_garge;
		shared_ptr<Transform> m_trans;
		wstring m_meshResName;

	public:
		PieceGarge2(const shared_ptr<Stage>& stagePtr);
		virtual ~PieceGarge2(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};
}
//end namesapce basecross

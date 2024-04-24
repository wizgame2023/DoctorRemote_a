/*!
@file Garge.cpp
@brief ƒQ[ƒW
’S“–FˆíŒ©
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	PieceGarge2::PieceGarge2(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr)
	{}

	void PieceGarge2::OnCreate() {
		auto stage = GetStage();

		m_trans = GetComponent<Transform>();
		Col4 color(1, 1, 1, 1);
		Col4 color(1, 0, 0, 1);

		float sw = App::GetApp()->GetGameWidth();
		float sh = App::GetApp()->GetGameHeight();


	}
}
//end namespace basecross
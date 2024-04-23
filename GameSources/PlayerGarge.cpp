/*!
@file PlayerGarge.cpp
@brief プレイヤー体力ゲージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	PlayerGarge::PlayerGarge(const shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr)
	{
	}

	void PlayerGarge::OnCreate() {
		auto stage = GetStage();

		auto pos = GetComponent<Transform>()->GetPosition();
		auto hp = m_currentHp / m_maxHp;

		auto garge = stage->AddGameObject<Garge>();
	}

	void PlayerGarge::OnUpdate() {

	}
}
//end namespace basecross
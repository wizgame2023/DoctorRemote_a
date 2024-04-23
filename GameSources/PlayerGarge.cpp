/*!
@file PlayerGarge.cpp
@brief プレイヤー体力ゲージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	PlayerGarge::PlayerGarge(const shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr),
		m_meshResName(L"BarSide"),
		m_currentHp(80.0f),
		m_maxHp(100.0f),
		m_screen(100,200,0)
	{
	}

	void PlayerGarge::OnCreate() {
		auto stage = GetStage();

		m_trans = GetComponent<Transform>();
		m_ratioHp = m_currentHp / m_maxHp;
		Col4 color(1, 1, 1, 1);
		Col4 color2(1, 0, 0, 1);

		float sw = App::GetApp()->GetGameWidth();
		float sh = App::GetApp()->GetGameHeight();
		Vec3 screen(-sw * 0.5, -sh * 0.5, 0);
		Vec3 zero(0, 0, 0);
		Vec3 dis(400, -0, 0);

		m_garge = stage->AddGameObject<Garge>(m_trans, 1024, 0,m_meshResName, m_ratioHp, 200, 200, color, color2, m_screen, zero);

	}

	void PlayerGarge::OnUpdate() {
		
		m_ratioHp = m_currentHp / m_maxHp;

		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");
		auto piece = player->GetPiece();
		m_garge->UpdateValue(piece);
		auto position = m_garge->GetComponent<Transform>()->GetPosition();

		//デバック用ストリーム
		wstringstream wss(L"");
		//デバック用
		auto scene = App::GetApp()->GetScene<Scene>();
		wss << L"transform :" <<
			position. y<<"\n" << position.x <<
			"\n" <<
			endl;
		auto dstr = scene->GetDebugString();
		scene->SetDebugString(dstr + wss.str());

	}
}
//end namespace basecross
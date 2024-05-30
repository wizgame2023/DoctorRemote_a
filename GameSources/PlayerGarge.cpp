/*!
@file PlayerGarge.cpp
@brief プレイヤー体力ゲージ実体
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	PlayerGarge::PlayerGarge(const shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr),
		m_meshResName(L"Hearts"),
		m_currentHp(80.0f),
		m_maxHp(100.0f)
	{
	}

	void PlayerGarge::OnCreate() {
		auto stage = GetStage();

		m_ratioHp = m_currentHp / m_maxHp;

		m_trans = GetComponent<Transform>();
		m_ratioHp = m_currentHp / m_maxHp;
		Col4 color(1, 1, 1, 1);
		Col4 color2(0, 1, 0, 1);

		float sw = App::GetApp()->GetGameWidth();
		float sh = App::GetApp()->GetGameHeight();
		Vec3 screen(-sw * 0.5, -sh * 0.5, 0);
		//Vec3 zero(0, 0, 0);
		Vec3 dis(320, 100, 0);

		m_garge = stage->AddGameObject<Garge>(m_trans, 220, 0,m_meshResName, m_ratioHp, 220, 40, color, color2, screen, dis);

		//auto frame = stage->AddGameObject<Sprite>(12, 203, L"BarFrame", Vec3(0, -335, 0.5),1);
		//auto frameTrans = frame->GetComponent<Transform>();
		//frameTrans->SetRotation(0, 0, 90 * XM_PI / 180);

	}

	void PlayerGarge::OnUpdate() {
		
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<StageManager>(L"StageManager");
		auto piece = player->GetHpRatio();
		m_garge->UpdateValue(piece);
		auto position = m_garge->GetComponent<Transform>()->GetPosition();

		////デバック用ストリーム
		//wstringstream wss(L"");
		////デバック用
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << L"transform :" <<
		//	position. y<<"\n" << position.x <<
		//	"\n" <<
		//	endl;
		//auto dstr = scene->GetDebugString();
		//scene->SetDebugString(dstr + wss.str());

	}

	float PlayerGarge::GetHp() {
		return m_currentHp;
	}
	void PlayerGarge::SetHp(float hp) {
		m_currentHp += hp;
	}
}
//end namespace basecross
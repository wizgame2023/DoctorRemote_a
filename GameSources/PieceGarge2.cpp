/*!
@file Garge.cpp
@brief ゲージ
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	PieceGarge2::PieceGarge2(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_meshResName(L"Bar"),
		m_ratio(0.5f)
	{}

	void PieceGarge2::OnCreate() {

		auto stage = GetStage();

		m_trans = GetComponent<Transform>();
		Col4 color(1, 1, 1, 1);
		Col4 color2(1, 0, 0, 1);

		float sw = App::GetApp()->GetGameWidth();
		float sh = App::GetApp()->GetGameHeight();

		Vec3 screen(-sw * 0.5f, -sh * 0.5f, 0);
		Vec3 dis(73, 300, 0);
		Vec3 zero(0, 0, 0);

		m_garge = stage->AddGameObject<Garge>(m_trans, 0, 1024, m_meshResName, m_ratio, 55, 240, color, color2, screen, dis);

		auto frame = stage->AddGameObject<Sprite>(57, 242, L"BarFrame",Vec3(-540, -220, 1.0f));
	}

	void PieceGarge2::OnUpdate() {
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");
		auto piece = player->GetPieceRatio();

		m_garge->UpdateValue(piece);

		auto position = m_garge->GetComponent<Transform>()->GetPosition();

		////デバック用ストリーム
		//wstringstream wss(L"");
		////デバック用
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << L"piece transform _x:" <<
		//	position.x << "\n" <<
		//	L"transform _y:" <<
		//	position.y <<
		//	"\n" <<
		//	piece<<
		//	"\n"<<
		//	endl;
		//auto dstr = scene->GetDebugString();
		//scene->SetDebugString(dstr + wss.str());

	}

}
//end namespace basecross
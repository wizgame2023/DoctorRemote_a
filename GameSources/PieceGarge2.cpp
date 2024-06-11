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
		m_meshResName(L"Garge"),
		m_ratio(1.0f),
		m_gargeMaxFlag(false)
	{}

	void PieceGarge2::OnCreate() {

		auto stage = GetStage();

		m_trans = GetComponent<Transform>();
		Col4 color(1, 1, 1, 1);
		Col4 color2(1, 1, 1, 1);

		float sw = App::GetApp()->GetGameWidth();
		float sh = App::GetApp()->GetGameHeight();

		Vec3 screen(-sw * 0.5f, -sh * 0.5f, 0);
		Vec3 dis(70, 300, 0);
		Vec3 zero(0, 0, 0);

		m_garge = stage->AddGameObject<Garge>(0, 92, m_meshResName, m_ratio, 32*2.5, 92*2.5, color, color2, screen, dis);

		auto frame = stage->AddGameObject<Sprite>(32*2.5, 128*2.5, L"GargeBar",Vec3(-530, -170, 1.0f),2);
	}

	void PieceGarge2::OnUpdate() {
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");
		auto piece = player->GetPieceRatio();
		auto trans = GetComponent<Transform>();

		float sw = App::GetApp()->GetGameWidth();
		float sh = App::GetApp()->GetGameHeight();

		Vec3 screen(-sw * 0.5f, -sh * 0.5f, 0);
		Vec3 dis(70, 300, 0);
		Vec3 zero(0, 0, 0);


		if (stage->GetSharedGameObject<Player>(L"GamePlayer")->GetRadarFlag()) {
			if (!m_gargeMaxFlag) {
				m_garge->SetColor(Col4(1.0f, 0.0f, 0.0f, 1.0f));
				auto gargeLight = stage->AddGameObject<Sprite>(32 * 2.5, 128 * 2.5, 
					L"GargeLight", Vec3(-530, -170.f, 1.0f), 2);
				gargeLight->SetColor(Col4(1.0f, 0.0, 0.0f, 1.0f));
				m_ratio = 1.0f;
				m_gargeMaxFlag=true;
				//m_garge->UpdateValue(piece);

			}
		}
		else {
			m_garge->UpdateValue(piece);
		}

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
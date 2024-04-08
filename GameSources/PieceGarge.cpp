/*!
@file PieceGarge.cpp
@brief 敵の欠片のゲージ
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	PieceGarge::PieceGarge(const shared_ptr<Stage>& StagePtr):
		GameObject(StagePtr),
		m_length(200.0f),
		m_maxLength(200.0f)
	{}

	void PieceGarge::OnCreate() {
		//ポリゴンの自作

		Col4 color(1, 1, 1, 1);
		const float w = m_length;
		const float h = 20.0f;

		//頂点データ
		vector<VertexPositionColor> vertices = {
			{Vec3(0,0,0),color}, //0
			{Vec3(w,0,0),color}, //1
			{Vec3(0,h,0),color}, //2
			{Vec3(w,h,0),color}	 //3
		};

		//頂点インディックス
		vector<uint16_t> indices = {
			0,1,2,
			2,1,3
		};

		auto drawComp = AddComponent<PCSpriteDraw>(vertices, indices);
		drawComp->SetSamplerState(SamplerState::LinearWrap);
		//色の設定
		drawComp->SetDiffuse(Col4(0, 1, 0, 0.5f));

		m_transform = AddComponent<Transform>();
		float sw = App::GetApp()->GetGameWidth();
		float sh = App::GetApp()->GetGameHeight();
		Vec3 screenOrigin(-sw * 0.5f, sh * 0.5f, 0);
		m_transform->SetPosition(screenOrigin + Vec3(200, -30, 0));

	}

	void PieceGarge::OnUpdate() {

		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"Player");

		m_length = player->GetHp() * 2.0f;
		m_transform->SetScale(m_length / m_maxLength, 1, 1);
	}

}
//end basecross

/*!
@file PieceGarge.cpp
@brief 敵の欠片のゲージ
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	PieceGarge::PieceGarge(const shared_ptr<Stage>& StagePtr,const shared_ptr<Player>& player):
		GameObject(StagePtr),
		m_player(player),
		m_length(100.0f),
		m_maxLength(200.0f),
		m_garge(0.0f)
	{}

	void PieceGarge::OnCreate() {
		//ポリゴンの自作

		Col4 color(1, 1, 1, 1);
		const float w = 200.0f;
		const float h = m_length;

		//頂点データ
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(0,0,0),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(w,0,0),color,Vec2(1.0f,0.0f)}, //1
			{Vec3(0,-h,0),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(w,-h,0),color,Vec2(1.0f,1.0f)}  //3
		};

		//頂点インディックス
		vector<uint16_t> indices = {
			0,1,2,
			2,1,3
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"Bar");
		drawComp->SetSamplerState(SamplerState::LinearWrap);
		//色の設定
		drawComp->SetDiffuse(Col4(0, 1, 0, 0.7));

		m_transform = AddComponent<Transform>();
		float sw = App::GetApp()->GetGameWidth();
		float sh = App::GetApp()->GetGameHeight();
		Vec3 screenOrigin(750 * 0.5f, -100 * 0.5f, 0);
		m_transform->SetPosition(screenOrigin + Vec3(10, -10, 0));
		SetAlphaActive(true);
	}

	void PieceGarge::OnUpdate() {

		m_length = m_player->GetHp() * 1.0f;

		m_garge = m_length / m_maxLength;
		//m_transform->SetScale(m_garge * 2.0f, 1, 1);
		m_transform->SetScale(1, 1, 1);
	}


	float PieceGarge::GetLength()
	{
		return m_length;
	}

	float PieceGarge::GetMaxLength()
	{
		return m_maxLength;
	}
	void PieceGarge::SetLength(float length)
	{
		m_length = length;
	}

}
//end basecross

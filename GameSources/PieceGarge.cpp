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
		m_height(240.0f),
		m_width(40.0f),
		m_length(0.0f),
		m_maxLength(100.0f),
		m_garge(0.0f)
	{}

	void PieceGarge::OnCreate() {

		m_piece = m_player->GetPiece();


		//ポリゴンの自作
		Col4 color(1, 1, 1, 1);
		//const float h = m_length;
		const float moveH = (1024 * m_piece)/1024;
		
		//頂点データ
		m_vertices = {
			{Vec3(0,0,0),color,Vec2(0.0f,(moveH))}, //0
			{Vec3(m_width,0,0),color,Vec2(1.0f,(moveH))}, //1
			{Vec3(0,-m_height,0),color,Vec2(0.0f,0.0f)}, //2
			{Vec3(m_width,-m_height,0),color,Vec2(1.0f,0.0f)}  //3
		};

		//頂点インディックス
		vector<uint16_t> indices = {
			0,1,2,
			2,1,3
		};

		m_drawComp = AddComponent<PCTSpriteDraw>(m_vertices, indices);
		m_drawComp->SetTextureResource(L"Bar");
		m_drawComp->SetSamplerState(SamplerState::LinearWrap);
		//色の設定
		m_drawComp->SetDiffuse(Col4(0, 1, 0, 0.7));

		m_transform = AddComponent<Transform>();
		float sw = App::GetApp()->GetGameWidth();
		float sh = App::GetApp()->GetGameHeight();
		//Vec3 screenOrigin(1000 * 0.5f, -500 * 0.5f, 0);
		Vec3 screenOrigin(sw * 0.5f, -sh * 0.5f, 0);
		m_transform->SetPosition(screenOrigin + Vec3(-120, 300, 0));
		SetAlphaActive(true);


	}

	void PieceGarge::OnUpdate() {
		//デバック用ストリーム
		wstringstream wss(L"");

		//m_garge = m_length / m_maxLength;
		//m_length = m_player->GetHp() * 1.0f;

		////m_transform->SetScale(1,-m_garge * 2.0f, 1);
		//m_transform->SetScale(1, 1, 1);

		//デバック用
		auto garge = m_player->GetPiece();
		auto scene = App::GetApp()->GetScene<Scene>();
		wss <<L"garge:"<<
			garge <<"\n"<<
			L"position.y:"<<
			m_vertices[0].position.y <<
			endl;
		auto dstr = scene->GetDebugString();
		scene->SetDebugString(dstr + wss.str());
	

	}

	void PieceGarge::UpdateValue(float value) {
		const float moveH = (1024 * value) / 1024;

		m_vertices[0].position.y = -m_height + (m_height * value);
		m_vertices[1].position.y = -m_height + (m_height * value);

		m_vertices[0].textureCoordinate.y = moveH;
		m_vertices[1].textureCoordinate.y = moveH;

		m_drawComp->UpdateVertices(m_vertices);
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

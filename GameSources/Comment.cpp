/*!
@file Comment.cpp
@brief ÉRÉÅÉìÉgé¿ëÃ
íSìñÅFàÌå©
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	Comment::Comment(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_mojinum(13),
		m_count(0.5f),
		m_meshResName(L"comment")
	{}

	void Comment::OnCreate() {
		m_width = 320.0f/13;
		m_heigth = 200.0f/6;
		m_uvWidth = (320.0f / 13) / 320.0f;
		m_uvHeigth = (200.0f / 6) / 200.0f;

		//int line = 13;
		//int column = 6;
		int moji = 0;
		int mojiLine = moji % 13;
		int mojiColumn = moji / 13;

		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);

		m_vertices = {
			{Vec3(0.0f,0.0f,0.0f),color,Vec2((m_uvWidth * moji),0.0f)},
			{Vec3(m_width,0.0f,0.0f),color,Vec2((m_uvWidth * (moji + 1)),0.0f)},
			{Vec3(0.0f,-m_heigth,0.0f),color,Vec2((m_uvWidth * moji),m_uvHeigth)},
			{Vec3(m_width,-m_heigth,0.0f),color,Vec2((m_uvWidth * (moji + 1)),m_uvHeigth)},
		};

		m_indices = {
			0,1,2,
			2,1,3
		};

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(m_meshResName);
		m_draw->SetSamplerState(SamplerState::LinearWrap);
		m_draw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		SetAlphaActive(true);
		SetDrawLayer(0);
		m_trans = GetComponent<Transform>();
		m_trans->SetPosition(Vec3());


	}
	void Comment::OnUpdate() {
		float elapase = App::GetApp()->GetElapsedTime();
		m_count -= elapase;
		if (1.0f > m_count) {
			m_moji++;
			if (m_moji < m_mojinum) {
				UpdateValue(m_moji);
			}
			m_count = 0.0f;
		}

		//UpdateValue(3);
	}
	void Comment::UpdateValue(int letter) {
		//int moji = letter;
		//m_vertices[0].textureCoordinate.x = m_uvWidth * letter;
		//m_vertices[2].textureCoordinate.x = m_uvWidth * letter;


		m_vertices[1].textureCoordinate.x = m_uvWidth * (letter + 1);
		m_vertices[3].textureCoordinate.x = m_uvWidth * (letter + 1);

		m_vertices[1].position.x = m_width * (letter+1);
		m_vertices[3].position.x = m_width * (letter+1);

		m_draw->UpdateVertices(m_vertices);
	}
}
//end namespace basecross

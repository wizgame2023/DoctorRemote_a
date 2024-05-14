/*!
@file UITime.cpp
@brief 数字の画像
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	UITime::UITime(const shared_ptr<Stage>& stagePtr,int number,Vec3 pos):
		GameObject(stagePtr),
		m_number(number),
		m_pos(pos),
		m_meshResName(L"NumbersWhite")
	{}

	void UITime::OnCreate() {

		m_width = 40.0f;
		m_heigth = 80.0f;
		m_moveW = (512.0f / 10) / 512.0f;
		m_moveH = 128.0f/128.0f;
		//m_moveW = 50.0f/512.0f;
		//m_moveH = 100.0f/128.0f;
		auto number = 9;

		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);

		m_vertices = {
			{Vec3(0.0f,0.0f,0.0f),color,Vec2((m_moveH * number),0.0f)},
			{Vec3(m_width,0.0f,0.0f),color,Vec2((m_moveH * (number + 1)),0.0f)},
			{Vec3(0.0f,-m_heigth,0.0f),color,Vec2((m_moveH * number),1.0f)},
			{Vec3(m_width,-m_heigth,0.0f),color,Vec2((m_moveH * (number + 1)),1.0f)},
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

		m_trans = GetComponent<Transform>();
		m_trans->SetPosition(m_pos);
	}
	void UITime::OnUpdate() {

		auto elapseTime = App::GetApp()->GetElapsedTime();
		m_time -= elapseTime;

		//UpdateValue(m_number);
	}

	void UITime::UpdateValue(int number) {
		m_vertices[0].textureCoordinate.x = m_moveW * number;
		m_vertices[1].textureCoordinate.x = m_moveW * (number + 1);
		m_vertices[2].textureCoordinate.x = m_moveW * number;
		m_vertices[3].textureCoordinate.x = m_moveW * (number + 1);

		m_draw->UpdateVertices(m_vertices);
	}


}
//end namespace basecross
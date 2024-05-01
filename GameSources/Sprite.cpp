/*!
@file Sprite.cpp
@brief スプライト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Sprite::Sprite(const shared_ptr<Stage>& stagePtr,float width, float heigth,
		wstring meshResName, Vec3 pos):
		GameObject(stagePtr),
		m_width(width),
		m_heigth(heigth),
		m_meshResName(meshResName),
		m_pos(pos)
	{}

	void Sprite::OnCreate() {

		auto color = Col4(1, 1, 1, 1);

		m_vertices = {
			{Vec3(-m_width * 0.5f,m_heigth * 0.5f,0),color,Vec2(0.0f,0.0f)},
			{Vec3(m_width * 0.5f,m_heigth * 0.5f,0),color,Vec2(1.0f,0.0f)},
			{Vec3(-m_width * 0.5f,-m_heigth * 0.5f,0),color,Vec2(0.0f,1.0f)},
			{Vec3(m_width * 0.5f,-m_heigth * 0.5f,0),color,Vec2(1.0f,1.0f)}
		};
		m_indices = {
			0,1,2,
			2,1,3
		};

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(m_meshResName);
		m_draw->SetSamplerState(SamplerState::LinearWrap);
		m_draw->SetDiffuse(Col4(1, 1, 1, 1.0f));

		SetAlphaActive(true);

		m_trans = GetComponent<Transform>();
		m_trans->SetPosition(m_pos);
	}
	void Sprite::OnUpdate() {

	}
}
//end namespace basecross
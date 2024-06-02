/*!
@file Sprite.cpp
@brief スプライト
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Sprite::Sprite(const shared_ptr<Stage>& stagePtr, float width, float heigth,
		wstring meshResName, Vec3 pos) :
		GameObject(stagePtr),
		m_width(width),
		m_heigth(heigth),
		m_meshResName(meshResName),
		m_pos(pos),
		m_rot(Vec3()),
		m_color(1, 1, 1, 1),
		m_layer(0)
	{}
	Sprite::Sprite(const shared_ptr<Stage>& stagePtr, float width, float heigth,
		wstring meshResName, Vec3 pos, int layer):
		GameObject(stagePtr),
			m_width(width),
			m_heigth(heigth),
			m_meshResName(meshResName),
			m_pos(pos),
			m_rot(Vec3()),
			m_color(1, 1, 1, 1),
			m_layer(layer)
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
		m_draw->SetDiffuse(Col4(m_color));

		SetAlphaActive(true);

		SetDrawLayer(m_layer);

		m_trans = GetComponent<Transform>();
		m_trans->SetPosition(m_pos);
		m_trans->SetRotation(m_rot);
	}
	void Sprite::OnUpdate() {

	}

	void Sprite::ThisDestory() {
		GetStage()->RemoveGameObject<Sprite>(GetThis<Sprite>());
	}

	void Sprite::SetColor(Col4 color) {
		m_draw->SetDiffuse(color);
	}
	Col4 Sprite::GetColor() {
		m_color = m_draw->GetDiffuse();
		return m_color;
	}

	void Sprite::Blinking(float count) {
	}

	void Sprite::UpdateRank(int value)
	{
		const float numberW =128.0f / 512.0f;
		m_vertices[0].textureCoordinate.x = numberW * value;
		m_vertices[1].textureCoordinate.x = numberW * (value + 1);
		m_vertices[2].textureCoordinate.x = numberW * value;
		m_vertices[3].textureCoordinate.x = numberW * (value + 1);

		m_draw->UpdateVertices(m_vertices);

	}
	void Sprite::UpdateIfClear(int value)
	{
		const float numberH = 100.0f /400.0f;
		m_vertices[0].textureCoordinate.y = numberH * value;
		m_vertices[1].textureCoordinate.y = numberH * value;
		m_vertices[2].textureCoordinate.y = numberH * (value + 1);
		m_vertices[3].textureCoordinate.y = numberH * (value + 1);

		m_draw->UpdateVertices(m_vertices);

	}

}
//end namespace basecross
/*!
@file Garge.cpp
@brief ゲージ
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	Garge::Garge(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_sizeX(),
		m_sizeY()
	{}

	void Garge::OnCreate() {
		m_moveW = (m_sizeX * m_ratio) / m_sizeX;
		m_moveH = (m_sizeY * m_ratio) / m_sizeY;

		if (m_moveW > 0) {
			m_vertices = {
				{Vec3(0,0,0),m_color,Vec2(m_moveW,0.0f)},
				{Vec3(m_width,0,0),m_color,Vec2(0.0f,0.0f)},
				{Vec3(0,-m_height,0),m_color,Vec2(m_moveW,1.0f)},
				{Vec3(m_width,-m_height,0),m_color,Vec2(0.0f,1.0f)}
			};
		}
		else if (m_moveH > 0) {
			m_vertices = {
				{Vec3(0,0,0),m_color,Vec2(0.0f,m_moveH)},
				{Vec3(m_width,0,0),m_color,Vec2(1.0f,m_moveH)},
				{Vec3(0,m_height,0),m_color,Vec2(0.0f,0.0f)},
				{Vec3(m_width,-m_height,0),m_color,Vec2(1.0f,0.0f)}
			};
		}

		m_indices = {
			0,1,2,
			2,1,3
		};

		//描画の表示
		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(m_meshResName);
		m_draw->SetSamplerState(SamplerState::LinearWrap);
		//色の設定
		m_draw->SetDiffuse(m_color2);
		//場所の設定
		m_trans->SetPosition(m_screen + m_distance);
		SetAlphaActive(true);
	}

	void Garge::OnUpdate() {

		UpdateValue();
	}


	void Garge::UpdateValue() {
		
		if (m_moveW > 0) {
			m_vertices[0].position.x = -m_width + (m_width * m_ratio);
			m_vertices[2].position.x = -m_width + (m_width * m_ratio);

			m_vertices[0].textureCoordinate.x = m_moveW;
			m_vertices[2].textureCoordinate.x = m_moveW;

			m_draw->UpdateVertices(m_vertices);
		}
		else if (m_moveH > 0) {

		}
	}



}
//end namespace basecross
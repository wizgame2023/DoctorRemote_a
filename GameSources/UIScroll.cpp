/*!
@file UIScroll.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	UIScroll::UIScroll(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0)
	{}

	UIScroll::~UIScroll() {}
	void UIScroll::OnCreate() {
		float helfSize = 1.0f;
		//頂点配列
		m_BackupVertices = {
			{ VertexPositionTexture(Vec3(-helfSize, helfSize, 0), Vec2(0.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(helfSize, helfSize, 0), Vec2(4.0f, 0.0f)) },
			{ VertexPositionTexture(Vec3(-helfSize, -helfSize, 0), Vec2(0.0f, 1.0f)) },
			{ VertexPositionTexture(Vec3(helfSize, -helfSize, 0), Vec2(4.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_TextureKey);
	}

	void UIScroll::OnUpdate() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime -= elapsedTime * 0.5f;
		if (m_TotalTime > 1.0f) {
			m_TotalTime = 0;
		}
		vector<VertexPositionTexture> newVertices;
		for (size_t i = 0; i < m_BackupVertices.size(); i++) {
			Vec2 uv = m_BackupVertices[i].textureCoordinate;
			if (uv.x == 0.0f) {
				uv.x = m_TotalTime;
			}
			else if (uv.x == 4.0f) {
				uv.x += m_TotalTime;
			}
			auto v = VertexPositionTexture(
				m_BackupVertices[i].position,
				uv
			);
			newVertices.push_back(v);
		}
		auto ptrDraw = GetComponent<PTSpriteDraw>();
		ptrDraw->UpdateVertices(newVertices);
	}
}
//end namespace basecross
/*!
@file UIScroll.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UIScroll : public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_TotalTime;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		UIScroll(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~UIScroll();
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};

}
//end namespace basecross

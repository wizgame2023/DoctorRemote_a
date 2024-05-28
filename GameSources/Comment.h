/*!
@file Comment.h
@brief ƒRƒƒ“ƒg
’S“–FˆíŒ©
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Comment :public GameObject {
	private:

		float m_width;
		float m_heigth;
		float m_uvWidth;
		float m_uvHeigth;

		float m_count;

		int m_mojinum;
		int m_moji;

		vector<VertexPositionColorTexture> m_vertices;
		shared_ptr<PCTSpriteDraw> m_draw;
		vector<uint16_t> m_indices;
		wstring m_meshResName;

		shared_ptr<Transform> m_trans;

	public:
		Comment(const shared_ptr<Stage>& stagePtr);
		virtual ~Comment() override{}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void UpdateValue(int letter);
		void UpdateValue2(int letter);
	};
}
//end namespace basecross
/*!
@file Sprite.h
@brief スプライト
担当：逸見
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprite :public GameObject {
	private:
		//画像の大きさ

		//画像の表示サイズ
		float m_width;
		float m_heigth;

		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;
		shared_ptr<PCTSpriteDraw> m_draw;
		wstring m_meshResName;

		shared_ptr<Transform> m_trans;

		Vec3 m_pos;
		Col4 m_color;

	public:
		Sprite(const shared_ptr<Stage>& stagePtr,float width, float heigth,
			wstring meshResName, Vec3 pos);
		virtual ~Sprite(){}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		
		shared_ptr<Transform> GetTrans();
		void SetColor(Col4 color);
	};

}
//end namespace basecross
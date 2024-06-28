/*!
@file UITime.h
@brief 数字の画像
担当：逸見
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UITime :public GameObject {
	private:

		//表示するサイズの情報
		float m_width;
		float m_heigth;
		float m_moveW;
		float m_moveH;
		int m_number;

		//頂点の情報
		vector<VertexPositionColorTexture> m_vertices;
		shared_ptr<PCTSpriteDraw> m_draw;
		vector<uint16_t> m_indices;
		wstring m_meshResName;

		//表示させる位置の情報
		shared_ptr<Transform> m_trans;
		Vec3 m_pos;
		Col4 m_color;

	public:
		UITime(const shared_ptr<Stage>& stagePtr, int number, Vec3 pos);
		UITime(const shared_ptr<Stage>& stagePtr, int number, Vec3 pos, float width, float heigth, Col4 color = Col4(0.1640f, 0.8632f, 0.2109f, 1.0f));
		UITime(const shared_ptr<Stage>& stagePtr, int number, Vec3 pos, float width, float heigth, 
			wstring meshResName,Col4 color= Col4(0.1640f, 0.8632f, 0.2109f, 1.0f));

		virtual ~UITime(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void OnClear(bool OnOff);

		void UpdateValue(int number);
		void ThisDestory();
		Col4 GetColor();
		void SetColor(Col4 color);
	};
}
//end namespace basecross

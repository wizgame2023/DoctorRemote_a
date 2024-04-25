/*!
@file UITime.h
@brief ŠÔ
’S“–FˆíŒ©
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UITime :public GameObject {
	private:
		//‰æ‘œ‚Ì‘å‚«‚³‚Ìî•ñ
		float m_width;
		float m_heigth;
		float m_moveW;
		float m_moveH;
		int m_number;

		//’¸“_‚Ìî•ñ
		vector<VertexPositionColorTexture> m_vertices;
		shared_ptr<PCTSpriteDraw> m_draw;
		vector<uint16_t> m_indices;
		wstring m_meshResName;

		//‰æ‘œ©‘Ì‚ÌˆÊ’u‚Ìî•ñ
		shared_ptr<Transform> m_trans;
		Vec3 m_pos;

		float m_time;

	public:
		UITime(const shared_ptr<Stage>& stagePtr, int number, Vec3 pos);
		virtual ~UITime(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void UpdateValue(int number);
	};
}
//end namespace basecross

/*!
@file Comment.h
@brief ÉRÉÅÉìÉg
íSìñÅFàÌå©
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

		int m_ver;
		int m_bes;
		float m_widthSize;
		float m_heigthSize;
		float m_sizeW;
		float m_sizeH;

		float m_count;
		float m_countTime;

		int m_line;
		int m_mojiNum;
		int m_moji;

		bool m_lineFlag;

		vector<VertexPositionColorTexture> m_vertices;
		shared_ptr<PCTSpriteDraw> m_draw;
		vector<uint16_t> m_indices;
		wstring m_meshResName;

		shared_ptr<Transform> m_trans;
		Vec3 m_pos;

	public:
		Comment(const shared_ptr<Stage>& stagePtr);
		Comment(const shared_ptr<Stage>& stagePtr,
			const int mojiNum,
			const int line
		);
		Comment(const shared_ptr<Stage>& stagePtr,
			const int mojiNum,
			const int line,
			const float countTime,
			const float widthSize,
			const float heigthSize,
			const float sizeW,
			const float sizeH,
			const int ber,
			const int ver,
			const Vec3 pos,
			const wstring mesh
		);

		virtual ~Comment() override{}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void UpdateValue(int letter);
		void UpdateLine(int letter,int line);

		void ThisDestroy();

	};
}
//end namespace basecross
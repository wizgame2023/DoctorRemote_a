/*!
@file Comment.h
@brief コメント
担当：逸見
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
		bool m_loopFlag;

		int m_numPtr;//何番目の配列にポインタを入れたかを表す変数

		vector<VertexPositionColorTexture> m_vertices;
		shared_ptr<PCTSpriteDraw> m_draw;
		vector<uint16_t> m_indices;
		wstring m_meshResName;
		Col4 m_color;

		shared_ptr<Transform> m_trans;
		Vec3 m_pos;

	public:
		Comment(const shared_ptr<Stage>& stagePtr);
		Comment(const shared_ptr<Stage>& stagePtr,
			const int mojiNum,
			const int line,
			const bool loopFlag = false
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
			const wstring mesh,
			const bool loopFlag = false
		);

		virtual ~Comment() override{}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void UpdateValue(int letter);
		void UpdateLine(int letter,int line);

		void OnClear(bool OnOff);//透明にする

		void ThisDestroy();

		int GetNumPtr();//自分の登録されている配列の番号を返す
		void SetNumPtr(int num);//自分の配列の番号を入れる

	};
}
//end namespace basecross
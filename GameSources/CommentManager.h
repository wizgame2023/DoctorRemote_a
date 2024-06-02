/*!
@file CommentManager.h
@brief コメントの表示
担当：逸見
*/

#pragma once
#include "stdafx.h"
#include "Comment.h"

namespace basecross {
	class CommentManager :public GameObject {
	private:
		float m_widthSize;
		float m_heigthSize;
		float m_sizeW;
		float m_sizeH;
		Vec3 m_pos;
		wstring m_meshResName;

		int m_moji[10];
		int m_mojiNum;
		int m_addLine;
		int m_mojiLine;
		int m_mojiColumn;

		int m_line;
		int m_column;
		int m_cnt;
		int m_lineNum;
		float m_count;
		float m_mtime;

		bool m_lineFlag;

		shared_ptr<Comment> m_com[10];
		shared_ptr<Transform> m_trans;
	public:
		CommentManager(const shared_ptr<Stage>& stagePtr,const int moji);
		CommentManager(const shared_ptr<Stage>& stagePtr, const int moji,const int line);
		CommentManager(const shared_ptr<Stage>& stagePtr, const int moji, const int line,Vec3 pos,const wstring mesh);
		CommentManager(const shared_ptr<Stage>& stagePtr,
			const int mojiNum,
			const int line,
			const float mtime,
			const float widthSize,
			const float heigthSize,
			const float sizeW,
			const float sizeH,
			const int ber,
			const int ver,
			const Vec3 pos,
			const wstring mesh
		);


		virtual ~CommentManager(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void ThisDestroy();
	};
}
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
		int m_moji[10];
		int m_mojiNum;
		int m_addLine;

		int m_mojiLine;
		int m_mojiColumn;

		int m_line;
		int m_column;

		float m_count;
		float m_mtime;
		int m_cnt;
		int m_lineNum;

		bool m_lineFlag;

		shared_ptr<Comment> m_com[10];
	public:
		CommentManager(const shared_ptr<Stage>& stagePtr,const int moji);
		CommentManager(const shared_ptr<Stage>& stagePtr, const int moji,const int line);

		virtual ~CommentManager(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
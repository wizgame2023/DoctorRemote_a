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
		int m_moji[5];
		int m_mojiNum;

		int m_mojiLine;
		int m_mojiColumn;

		int m_line;
		int m_column;

		shared_ptr<Comment> m_com[5];
	public:
		CommentManager(const shared_ptr<Stage>& stagePtr,const int moji);
		virtual ~CommentManager(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
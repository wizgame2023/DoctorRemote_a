/*!
@file CommentManager.cpp
@brief コメントの表示
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	CommentManager::CommentManager(const shared_ptr<Stage>& stagePtr,const int moji):
		GameObject(stagePtr),
		m_mojiNum(moji),
		m_line(8),
		m_column(13)
	{}

	void CommentManager::OnCreate() {
		m_mojiLine = m_mojiNum / m_column;
		m_mojiColumn = m_mojiNum % m_column;
		auto stage = GetStage();

	}

	void CommentManager::OnUpdate() {

	}
}
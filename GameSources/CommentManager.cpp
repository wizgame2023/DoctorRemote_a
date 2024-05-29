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
		m_addLine(0),
		m_line(8),
		m_column(13),
		m_mtime(0.2),
		m_count(m_mtime * 13),
		m_moji{13,13,13,13,13,13,13,13,13,13},
		m_cnt(0)
	{}
	CommentManager::CommentManager(const shared_ptr<Stage>& stagePtr, const int moji,const int line) :
		GameObject(stagePtr),
		m_mojiNum(moji),//文字数
		m_addLine(line),//何行目か
		m_line(8),      //何行
		m_column(13),   //何列
		m_mtime(0.2),   //文字と文字の間を何行と仮定するか
		m_count(m_mtime * 13),//次の行までの時間
		m_moji{ 13,13,13,13,13,13,13,13,13,13 },
		m_cnt(0)
	{}


	void CommentManager::OnCreate() {
		m_mojiLine = m_mojiNum / m_column;
		m_mojiColumn = m_mojiNum % m_column;

	}

	void CommentManager::OnUpdate() {
		float elapsed = App::GetApp()->GetElapsedTime();
		auto stage = GetStage();
		m_count -= elapsed;
		
		if (m_cnt <= m_mojiLine) {
			if (m_count < 0) {
				if (m_addLine > 0) {
					m_moji[m_mojiLine] = m_mojiNum % (m_column * (m_cnt + 1));
				}
				m_com[m_cnt] = stage->AddGameObject<Comment>(m_moji[m_cnt], m_cnt+m_addLine);

				m_count = m_mtime * m_column;
				m_cnt++;
				int a = 0;
			}
		}
	}
}
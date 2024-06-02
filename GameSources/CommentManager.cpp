/*!
@file CommentManager.cpp
@brief コメントの表示
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//文字数だけ
	CommentManager::CommentManager(const shared_ptr<Stage>& stagePtr,const int moji):
		GameObject(stagePtr),
		m_mojiNum(moji),//文字数
		m_addLine(0),//何行目から
		m_line(8),      //何行
		m_column(13),   //何列
		m_mtime(0.2f),   //文字と文字の間を秒数
		m_widthSize(256),//画像サイズ横
		m_heigthSize(256),//画像サイズ縦
		m_sizeW(350),//大きさ横
		m_sizeH(350),//大きさ縦
		m_count(m_mtime* m_column),//次の行までの時間
		m_moji{ 13,13,13,13,13,13,13,13,13,13 },
		m_cnt(0),
		m_pos(Vec3()),
		m_meshResName(L"comment")
	{}
	//
	CommentManager::CommentManager(const shared_ptr<Stage>& stagePtr, const int moji,const int line) :
		GameObject(stagePtr),
		m_mojiNum(moji),//文字数
		m_addLine(line),//何行目から
		m_line(8),      //何行
		m_column(13),   //何列
		m_mtime(0.2f),   //文字と文字の間を秒数
		m_widthSize(256),//画像サイズ横
		m_heigthSize(256),//画像サイズ縦
		m_sizeW(350),//大きさ横
		m_sizeH(350),//大きさ縦
		m_count(m_mtime* m_column),//次の行までの時間
		m_moji{ 13,13,13,13,13,13,13,13,13,13 },
		m_cnt(0),
		m_pos(Vec3()),
		m_meshResName(L"comment")

	{}
	CommentManager::CommentManager(const shared_ptr<Stage>& stagePtr, const int moji, const int line,Vec3 pos,const wstring mesh) :
		GameObject(stagePtr),
		m_mojiNum(moji),//文字数
		m_addLine(line),//何行目から
		m_line(8),      //何行
		m_column(13),   //何列
		m_mtime(0.1f),   //文字と文字の間を秒数
		m_widthSize(256),//画像サイズ横
		m_heigthSize(256),//画像サイズ縦
		m_sizeW(300),//大きさ横
		m_sizeH(300),//大きさ縦
		m_count(m_mtime* m_column),//次の行までの時間
		m_moji{ 13,13,13,13,13,13,13,13,13,13 },
		m_cnt(0),
		m_pos(pos),
		m_meshResName(mesh)

	{}

	CommentManager::CommentManager(const shared_ptr<Stage>& stagePtr,
		const int mojiNum,
		const int line,
		const float mtime,
		const float widthSize,
		const float heigthSize,
		const float sizeW,
		const float sizeH,
		const int bes,
		const int ver,
		const Vec3 pos,
		const wstring mesh
	):
		GameObject(stagePtr),
		m_mojiNum(mojiNum),//文字数
		m_addLine(line),//何行目から
		m_column(bes),   //何列
		m_line(ver),      //何行
		m_mtime(mtime),   //文字と文字の間を秒数
		m_widthSize(widthSize),//画像サイズ横
		m_heigthSize(heigthSize),//画像サイズ縦
		m_sizeW(sizeW),//大きさ横
		m_sizeH(sizeH),//大きさ縦
		m_count(m_mtime* m_column),//次の行までの時間
		m_moji{ bes,bes,bes,bes,bes,bes,bes,bes,bes,bes, },
		m_cnt(0),
		m_pos(pos),
		m_meshResName(mesh)
	{}




	void CommentManager::OnCreate() {
		//何行目か
		m_mojiLine = m_mojiNum / m_column;
		//何文字目か
		m_mojiColumn = m_mojiNum % m_column;

	}

	void CommentManager::OnUpdate() {
		float elapsed = App::GetApp()->GetElapsedTime();
		auto stage = GetStage();
		m_count -= elapsed;
		
		//必要な行数文字列を生成
		if (m_cnt <= m_mojiLine) {
			if (m_count < 0) {
				if (m_addLine > 0) {
					m_moji[m_mojiLine] = m_mojiNum % (m_column * (m_cnt + 1));
				}
				m_com[m_cnt] = stage->AddGameObject<Comment>(m_moji[m_cnt], m_cnt + m_addLine, m_mtime,
					m_widthSize, m_heigthSize, m_sizeW, m_sizeH,
					m_column,m_line, m_pos, m_meshResName);

				m_count = m_mtime * m_column;
				m_cnt++;
				int a = 0;
			}
		}
	}

	//現在の生成されている文字列を自分自身を削除
	void CommentManager::ThisDestroy() {
		GetStage()->RemoveGameObject<CommentManager>(GetThis<CommentManager>());
		for (int i = 0; i < m_cnt; i++) {
			m_com[i]->ThisDestroy();
		}
	}
}
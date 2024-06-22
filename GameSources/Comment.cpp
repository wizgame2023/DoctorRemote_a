/*!
@file Comment.cpp
@brief コメント実体
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Comment::Comment(const shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr),
		m_moji(0),
		m_mojiNum(13),//何文字目か
		m_line(0),    //何行目か
		m_countTime(0.2f),//次の文字までも間隔
		m_count(m_countTime),
		m_bes(13),//横の分割数
		m_ver(8), //縦の分割数
		m_widthSize(256.0f),//画像サイズ(横)
		m_heigthSize(256.0f),//画像サイズ(縦)
		m_sizeW(350.0f),//表示サイズ(横)
		m_sizeH(350.0f),//表示サイズ(縦)
		m_lineFlag(false),
		m_loopFlag(false),
		m_pos(Vec3(0)),
		m_meshResName(L"comment")
	{}

	Comment::Comment(const shared_ptr<Stage>& stagePtr, 
		const int mojiNum, 
		const int line,
		const bool loopFlag
	) :
		GameObject(stagePtr),
		m_moji(0),
		m_mojiNum(mojiNum),//何文字目か
		m_line(line),    //何行目か
		m_countTime(0.2f),//次の文字までも間隔
		m_count(m_countTime),
		m_bes(13),//横の分割数
		m_ver(8), //縦の分割数
		m_widthSize(256.0f),//画像サイズ(横)
		m_heigthSize(256.0f),//画像サイズ(縦)
		m_sizeW(350.0f),//表示サイズ(横)
		m_sizeH(350.0f),//表示サイズ(縦)
		m_lineFlag(false),
		m_loopFlag(loopFlag),
		m_pos(0),
		m_meshResName(L"comment")
	{}

	Comment::Comment(const shared_ptr<Stage>& stagePtr,
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
		const bool loopFlag
	):
		GameObject(stagePtr),
		m_moji(0),
		m_mojiNum(mojiNum),//何文字目か
		m_line(line),    //何行目か
		m_countTime(countTime),//次の文字までも間隔
		m_count(m_countTime),
		m_bes(ber),//横の分割数
		m_ver(ver), //縦の分割数
		m_widthSize(widthSize),//画像サイズ(横)
		m_heigthSize(heigthSize),//画像サイズ(縦)
		m_sizeW(sizeW),//表示サイズ(横)
		m_sizeH(sizeH),//表示サイズ(縦)
		m_lineFlag(false),
		m_loopFlag(loopFlag),
		m_pos(pos),
		m_meshResName(mesh)
	{}



	void Comment::OnCreate() {
		m_width = m_sizeW/m_bes;
		m_heigth = m_sizeH/m_ver;
		m_uvWidth = (m_widthSize / m_bes) / m_widthSize;
		m_uvHeigth = (m_heigthSize / m_ver) / m_heigthSize;

		int moji = 0;
		int mojiLine = moji % 13;
		int mojiColumn = moji / 13;

		m_color = Col4(1.0f, 1.0f, 1.0f, 1.0f);

		m_vertices = {
			{Vec3(0.0f,0.0f,0.0f),m_color,Vec2((m_uvWidth * moji),m_uvHeigth * mojiColumn)},
			{Vec3(m_width,0.0f,0.0f),m_color,Vec2((m_uvWidth * (moji + 1)),m_uvHeigth * mojiColumn)},
			{Vec3(0.0f,-m_heigth,0.0f),m_color,Vec2((m_uvWidth * moji),m_uvHeigth * (mojiColumn + 1))},
			{Vec3(m_width,-m_heigth,0.0f),m_color,Vec2((m_uvWidth * (moji + 1)),m_uvHeigth * (mojiColumn + 1))},
		};

		m_indices = {
			0,1,2,
			2,1,3
		};

		m_draw = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);
		m_draw->SetTextureResource(m_meshResName);
		m_draw->SetSamplerState(SamplerState::LinearWrap);
		m_draw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		SetAlphaActive(true);
		SetDrawLayer(3);
		m_trans = GetComponent<Transform>();
		m_trans->SetPosition(Vec3());

		m_trans = GetComponent<Transform>();
		m_trans->SetPosition(m_pos);

		m_numPtr = GetStage()->GetSharedGameObject<UIManager>(L"UIManager")->SetUiCommentPtr(GetThis<Comment>());//自分のポインタを配列に入れる

	}
	void Comment::OnUpdate() {
		float elapase = App::GetApp()->GetElapsedTime();
		m_count -= elapase;
		if (0.0f > m_count) {
			m_moji++;
			m_count = m_countTime;
		}
		if (m_moji < m_mojiNum) {
			if (!m_lineFlag) {
				UpdateLine(m_moji, m_line);
			}
		}
		if(m_moji > m_mojiNum) {
			m_lineFlag = true;
			if (m_loopFlag) {
				m_moji = 0;
				m_lineFlag = false;
			}
		}
		
	}

	

	//letterにいれた文字数まで表示
	void Comment::UpdateValue(int letter) {
		int mojiLine = letter / m_bes;
		int mojiColumn = letter % m_bes;

		m_vertices[1].textureCoordinate.x = m_uvWidth * (mojiColumn + 1);
		m_vertices[3].textureCoordinate.x = m_uvWidth * (mojiColumn + 1);
		m_vertices[1].textureCoordinate.y = m_uvHeigth * (mojiLine);
		m_vertices[3].textureCoordinate.y = m_uvHeigth * (mojiLine+1);


		m_vertices[0].textureCoordinate.y = m_uvHeigth * (mojiLine);
		m_vertices[2].textureCoordinate.y = m_uvHeigth * (mojiLine+1);

		m_vertices[1].position.x = m_width * (mojiColumn+1);
		m_vertices[3].position.x = m_width * (mojiColumn+1);
		m_vertices[1].position.y = -m_heigth * (mojiLine);
		m_vertices[3].position.y = -m_heigth * (mojiLine+1);


		m_vertices[0].position.y = -m_heigth * (mojiLine);
		m_vertices[2].position.y = -m_heigth * (mojiLine+1);

		m_draw->UpdateVertices(m_vertices);

	}

	//何列目の何文字目まで表示
	void Comment::UpdateLine(int letter,int line) {
		int mojiColumn = letter % m_bes;

		m_vertices[1].textureCoordinate.x = m_uvWidth * (mojiColumn + 1);
		m_vertices[3].textureCoordinate.x = m_uvWidth * (mojiColumn + 1);
		m_vertices[1].textureCoordinate.y = m_uvHeigth * (line);
		m_vertices[3].textureCoordinate.y = m_uvHeigth * (line + 1);


		m_vertices[0].textureCoordinate.y = m_uvHeigth * (line);
		m_vertices[2].textureCoordinate.y = m_uvHeigth * (line + 1);

		m_vertices[1].position.x = m_width * (mojiColumn + 1);
		m_vertices[3].position.x = m_width * (mojiColumn + 1);
		m_vertices[1].position.y = -m_heigth * (line);
		m_vertices[3].position.y = -m_heigth * (line + 1);

		m_vertices[0].position.y = -m_heigth * (line);
		m_vertices[2].position.y = -m_heigth * (line + 1);

		m_draw->UpdateVertices(m_vertices);

	}

	void Comment::OnClear(bool OnOff){
		if (OnOff == true){//オンなら
			m_draw->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, 0.0f));//透明にする
		}
		if (OnOff == false){//オフなら
			m_draw->SetDiffuse(m_color);//透明でなかった時の色に戻る
		}

	}

	void Comment::ThisDestroy() {
		GetStage()->RemoveGameObject<Comment>(GetThis<Comment>());
	}

	int Comment::GetNumPtr(){
		return m_numPtr;
	}

	void Comment::SetNumPtr(int num) {
		m_numPtr = num;
	}

}
//end namespace basecross

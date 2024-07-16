/*!
@file StageSelectSprite.cpp
@brief 動かすことができるスプライト
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StageSelectSprite::StageSelectSprite(const shared_ptr<Stage>& stagePtr,
		const Vec3 pos,
		const float sizeX,
		const float sizeY,
		const float widthUnit,
		const float heightUnit,
		const float widthNum,
		const float heightNum,
		const float frameSize, //フレーム部分の大きさ
		const wstring sprites,//選択する画像
		const wstring frame,  //フレームの画像
		const bool display,
		const bool displayNumber

	) :
		GameObject(stagePtr),
		m_pos(pos),//位置
		m_sizeX(sizeX),
		m_sizeY(sizeY),
		m_widthUnit(widthUnit),
		m_heightUnit(heightUnit),
		m_widthNum(widthNum),
		m_heightNum(heightNum),
		m_spritesName(sprites),
		m_frameName(frame),
		m_frameSize(frameSize),
		m_blinkTime(10.0f),
		m_stageNum(1),
		m_limitNum(0),
		m_checkU(false),
		m_checkD(false),
		m_checkR(false),
		m_checkL(false),
		m_moveCheck(false),
		m_display(display),
		m_displayNumber(displayNumber),
		m_closeNum{(false)},
		m_bButtonSEFlag(false)
	{}
	StageSelectSprite::StageSelectSprite(const shared_ptr<Stage>& stagePtr,
		const wstring sprites,//選択する画像
		const wstring frame  //フレームの画像
	):
		GameObject(stagePtr),
		m_pos(Vec3(-200.0f,70.0f,0.0f)),//位置
		m_sizeX(70.0f),
		m_sizeY(70.0f),
		m_widthUnit(100.0f),
		m_heightUnit(100.0f),
		m_widthNum(4),
		m_heightNum(3),
		m_frameSize(50.0f),
		m_blinkTime(10.0f),
		m_spritesName(sprites),
		m_frameName(frame),
		m_stageNum(1),
		m_limitNum(0),
		m_checkU(false),
		m_checkD(false),
		m_checkR(false),
		m_checkL(false),
		m_moveCheck(false),
		m_display(true),
		m_displayNumber(true),
		m_closeNum{ (false) },
		m_bButtonSEFlag(false)
	{}


	void StageSelectSprite::OnCreate() {
		m_trans = GetComponent<Transform>();
		m_trans->SetPosition(m_pos);

		//必要な情報を代入
		m_widthMax = m_pos.x + m_widthUnit * (m_widthNum - 1);
		m_widthMin = m_pos.x;
		m_width = m_pos.x;
		m_heightMax = m_pos.y;
		m_heightMin = m_pos.y - m_heightUnit * (m_heightNum - 1);
		m_height = m_pos.y;

		auto stage = GetStage();
		//同じスプライトを表示
		for (int j = 0; j < m_heightNum; j++) {
			for (int i = 0; i < m_widthNum; i++) {
				if (m_display) {
					//枠組みの表示
					m_baseSprite[(i + j * m_widthNum)] = stage->AddGameObject<Sprite>(m_sizeX, m_sizeY,
						m_spritesName, Vec3(m_pos.x + i * m_widthUnit, m_pos.y + j * -m_heightUnit, m_pos.z),1);
					m_baseSprite[(i + j * m_widthNum)]->SetColor(Col4(0.0f, 1.0f, 0.0f, 1.0f));
				}
				if (m_displayNumber) {
					//10までの数字を表示
					m_numberSprites[(i + j * m_widthNum)] = stage->AddGameObject<UITime>((i + j * m_widthNum) + 1,
						Vec3((m_pos.x - m_sizeX / 2) + i * m_widthUnit + m_widthUnit * 0.15,
							(m_pos.y + m_sizeY / 2) + j * -m_heightUnit - m_heightUnit * 0.20, 0.0f), m_sizeX * 0.5, m_sizeY * 0.7, L"Numbers10");
					m_numberSprites[(i + j * m_widthNum)]->SetColor(Col4(0.0f, 0.0f, 0.0f, 1.0f));
				}
			}
		}

		m_selectSprite = stage->AddGameObject<Sprite>(m_sizeX + m_frameSize, m_sizeY + m_frameSize, m_frameName, m_pos, 0);
		m_selectSprite->SetColor(Col4(0.0f, 1.0f, 0.0f, 1.0f));
		//stage->AddGameObject<Sprite>(100.0f, 100.0f, L"White", GetSpritePostion(3,1), 0);
	}
	void StageSelectSprite::OnUpdate() {
		float elapsed = App::GetApp()->GetElapsedTime();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto selectTrans = m_selectSprite->GetComponent<Transform>();

		if (m_moveCheck && m_blinkTime >= 0) {
			if ((int)m_blinkTime % 2 == 0) {
				m_selectSprite->SetColor(Col4(0, 0, 0, 0));
			}
			else if ((int)m_blinkTime % 2 == 1) {
				m_selectSprite->SetColor(Col4(0, 1, 0, 1));
			}

			m_blinkTime -= elapsed * 10.0f;
			if (m_blinkTime <= 0) {
				m_blinkTime = 0.0f;
			}
		}


		if (m_moveCheck) return;
		//左スティック
		if (cntlVec[0].fThumbLX < -0.9f || keyState.m_bPressedKeyTbl['A']) {
			if (m_widthMin < m_width && !m_checkL) {
				m_width -= m_widthUnit;
				m_checkL = true;
				m_stageNum--;
			}
		}
		else if (cntlVec[0].fThumbLX > -0.9f || keyState.m_bLastKeyTbl['A'] && m_checkL) {
			m_checkL = false;
		}
		//右スティック
		if (cntlVec[0].fThumbLX > 0.9f || keyState.m_bPressedKeyTbl['D']) {
			if (m_widthMax > m_width && !m_checkR) {
				m_width += m_widthUnit;
				m_checkR = true;
				m_stageNum++;
			}
		}
		else if (cntlVec[0].fThumbLX < 0.9f || keyState.m_bLastKeyTbl['D'] && m_checkR) {
			m_checkR = false;
		}

		//上スティック
		if (cntlVec[0].fThumbLY > 0.9f || keyState.m_bPressedKeyTbl['W']) {
			if (m_heightMax > m_height && !m_checkU) {
				m_height += m_heightUnit;
				m_checkU = true;
				m_stageNum -= m_widthNum;
			}
		}
		else if (cntlVec[0].fThumbLY < 0.9f || keyState.m_bLastKeyTbl['W'] && m_checkU) {
			m_checkU = false;
		}
		//下スティック
		if (cntlVec[0].fThumbLY < -0.9f || keyState.m_bPressedKeyTbl['S']) {
			if (m_heightMin < m_height && !m_checkD) {
				m_height -= m_heightUnit;
				m_checkD = true;
				m_stageNum += m_widthNum;
			}
		}
		else if (cntlVec[0].fThumbLY > -0.9f || keyState.m_bLastKeyTbl['S'] && m_checkD) {
			m_checkD = false;
		}

		selectTrans->SetPosition(Vec3(m_width, m_height, 0.0f));

		//Bボタンで確定
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B || keyState.m_bPressedKeyTbl[VK_SPACE]) {
			if (m_stageNum <= m_limitNum) {
				if (!m_closeNum[m_stageNum - 1]) {
					m_moveCheck = true;
				}
			}
			if (!m_bButtonSEFlag) {
				auto pieceSE = App::GetApp()->GetXAudio2Manager();
				pieceSE->Start(L"ChoiceSE", 0, 0.3f);
				m_bButtonSEFlag = true;
			}

		}


		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//auto gameStage = scene->GetGameStage();
		//wss << L"widthMax : "
		//	<<m_widthMax
		//	<< L"\nwidthMin : "
		//	<<m_widthMin
		//	<<L"\nwidth"
		//	<<m_width
		//	<<L"\nheightMax : "
		//	<<m_heightMax
		//	<< L"\nheightMin : "
		//	<<m_heightMin
		//	<<L"\nheight"
		//	<<m_height
		//	<<L"\nstageNum"
		//	<<m_stageNum
		//	<<L"\nblinkTime : "
		//	<<m_blinkTime
		//	<< endl;
		//scene->SetDebugString(wss.str());


	}
	
	//横何番目、縦何番目の画像の位置を取得
	Vec3 StageSelectSprite::GetSpritePostion(const int widthNum, const int HeightNum) {
		auto pos = Vec3();
		int w = widthNum - 1;
		int h = HeightNum - 1;
		auto stage = GetStage();
		pos = Vec3(m_pos.x + w * m_widthUnit, m_pos.y + h * -m_heightUnit, m_pos.z);

		return pos;
	}
	void StageSelectSprite::ThisDestroy() {
		GetStage()->RemoveGameObject<StageSelectSprite>(GetThis<StageSelectSprite>());
		m_selectSprite->ThisDestroy();
		for (int j = 0; j < m_heightNum; j++) {
			for (int i = 0; i < m_widthNum; i++) {
				m_baseSprite[(i + j * m_widthNum)]->ThisDestroy();
				m_numberSprites[(i + j * m_widthNum)]->ThisDestroy();
			}
		}
	}
	int StageSelectSprite::GetNum() {
		return m_stageNum;
	}
	float StageSelectSprite::GetBlinkTime() {
		return m_blinkTime;
	}
	void StageSelectSprite::SetLimitNum(int num) {
		m_limitNum = num;
	}
	void StageSelectSprite::SetCloseNum(int num,bool close) {
		m_closeNum[num] = close;
	}
	bool StageSelectSprite::StickFlag() {
		auto stick = false;
		if (m_checkD || m_checkU || m_checkL || m_checkR) {
			stick = true;
		}
		else {
			stick = false;
		}
		return stick;
	}
}
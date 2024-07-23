/*!
@file TitleManager.cpp
@brief タイトルの選択の実体
担当：逸見
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TitleManager::TitleManager(const shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr),
		m_anCollar(0.0f),
		m_NextStandMovie(0.0f)
	{}

	void TitleManager::OnCreate() {
		auto trans = GetComponent<Transform>();

		auto deg = -90;
		auto deg2 = -45;
		auto rad = XMConvertToRadians(deg);
		auto rad2 = XMConvertToRadians(deg2);

		trans->SetPosition(Vec3(-2.0f,0.0f,-2.0f));
		trans->SetRotation(Vec3(0.0f, rad, rad2));

		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.3f, 0.0f)
		);

		m_blackBoard = GetStage()->AddGameObject<Sprite>(1280, 800, L"Black", Vec3(0, 0, 0), 3);
		m_blackBoard->SetColor(Col4( 1, 1, 1, 0));


		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"Sensuikan_Mesh");
		//ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->AddAnimation(L"Default", 0, 90, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"Sensuikan_Mesh");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		m_selectSprite = GetStage()->GetSharedGameObject<SelectSprite>(L"SelectSprite");
	}

	void TitleManager::OnUpdate() {
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(elapsedTime);
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (m_selectSprite->GetStageMove())
		{
			float fadeSpeed = 1.0f;
			m_anCollar += fadeSpeed * elapsedTime;
			m_blackBoard->SetColor(Col4(1, 1, 1, m_anCollar));
			if (m_anCollar >= 0.9f) {
				m_selectSprite->SetStageStart(true);
			}
		}

		m_NextStandMovie += elapsedTime;
		StandTimeReset();
		if (m_NextStandMovie >= 45.0f)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToMovieStage");
		}
		if (m_StandTimeReset)
		{
			m_NextStandMovie = 0.0f;
			m_StandTimeReset = false;
		}
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//auto gameStage = scene->GetGameStage();
		//wss << L"m_NextStandMovie : "
		//	<<m_NextStandMovie
		//	<< endl;

		//scene->SetDebugString(wss.str());

	}

	void TitleManager::StandTimeReset()
	{
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto keyBoard = App::GetApp()->GetInputDevice().GetKeyState();//キーボード取得
		Vec2 AStick;//アナログスティック
		AStick.x = cntlVec[0].fThumbLX;
		AStick.y = cntlVec[0].fThumbLY;
		if (!AStick.x == 0 || !AStick.y == 0)
		{
			m_StandTimeReset = true;
		}
		if (cntlVec[0].wPressedButtons||keyBoard.m_KeyMessageActive)//コントローラーのボタンが押されたとき
		{
			m_StandTimeReset = true;
		}
		//if(cntlVec)
		//m_NextStandMovie = 0.0f;//待機時間をリセットする
	}
}
//end namespace basecross
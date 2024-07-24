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
		GetStage()->AddGameObject<BoneDraw1>(Vec3(-2.3f, 0.0f, -1.9f));
		GetStage()->AddGameObject<BoneDraw2>(Vec3(2.8f, 0.0f, -2.2f));
		GetStage()->AddGameObject<BoneDraw3>(Vec3(2.2f, 0.0f, -1.0f));

		m_blackBoard = GetStage()->AddGameObject<Sprite>(1280, 800, L"Black", Vec3(0, 0, 0), 3);
		m_blackBoard->SetColor(Col4(1, 1, 1, 0));
		m_selectSprite = GetStage()->GetSharedGameObject<SelectSprite>(L"SelectSprite");
	}

	void TitleManager::OnUpdate() {
		auto elapsedTime = App::GetApp()->GetElapsedTime();
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
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		auto gameStage = scene->GetGameStage();
		wss << L"m_NextStandMovie : "
			<<m_NextStandMovie
			<< endl;

		scene->SetDebugString(wss.str());
	}

	void TitleManager::StandTimeReset()
	{
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto keyBoard = App::GetApp()->GetInputDevice().GetKeyState();//キーボードを取得
		Vec2 AStick;//アナログスティック
		AStick.x = cntlVec[0].fThumbLX;
		AStick.y = cntlVec[0].fThumbLY;
		if (!AStick.x == 0 || !AStick.y == 0)
		{
			m_StandTimeReset = true;
		}
		if (cntlVec[0].wPressedButtons || keyBoard.m_KeyMessageActive)//コントローラーのボタンが押されたとき
		{
			m_StandTimeReset = true;
		}
	}

	BoneDraw1::BoneDraw1(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos)
	{
	}
	BoneDraw1::~BoneDraw1() {}

	//初期化
	void BoneDraw1::OnCreate() {
		//初期位置などの設定
		auto trans = GetComponent<Transform>();

		auto deg = -90;
		auto deg2 = -45;
		auto rad = XMConvertToRadians(deg);
		auto rad2 = XMConvertToRadians(deg2);

		trans->SetScale(1.0f, 1.0f, 1.0f);
		trans->SetRotation(Vec3(0.0f, rad, rad2));
		trans->SetPosition(m_StartPos);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.3f, 0.0f)
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();

		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Sensuikan_Mesh");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"Sensuikan_Mesh");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		ptrDraw->AddAnimation(L"Default", 0, 90, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		//透明処理
		SetAlphaActive(true);
	}

	void BoneDraw1::OnUpdate()
	{
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(elapsedTime);
	}

	BoneDraw2::BoneDraw2(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos)
	{
	}
	BoneDraw2::~BoneDraw2() {}

	//初期化
	void BoneDraw2::OnCreate() {
		//初期位置などの設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(1.0f, 1.0f, 1.0f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTrans->SetPosition(m_StartPos);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.3f, 0.0f)
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();

		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Kakera_Mesh");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"Kakera_Mesh");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		ptrDraw->AddAnimation(L"Default", 0, 90, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		//透明処理
		SetAlphaActive(true);
	}

	void BoneDraw2::OnUpdate()
	{
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(elapsedTime);
	}

	BoneDraw3::BoneDraw3(const shared_ptr<Stage>& StagePtr, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_StartPos(StartPos)
	{
	}
	BoneDraw3::~BoneDraw3() {}

	//初期化
	void BoneDraw3::OnCreate() {
		//初期位置などの設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(1.5f, 1.5f, 1.5f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTrans->SetPosition(m_StartPos);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.4f, 0.4f, 0.4f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.3f, 0.0f)
		);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();

		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"Kakera_Mesh4");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"Kakera_Mesh4");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		ptrDraw->AddAnimation(L"Default", 0, 60, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(L"Default");

		//透明処理
		SetAlphaActive(true);
	}

	void BoneDraw3::OnUpdate()
	{
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(elapsedTime);
	}
}
//end namespace basecross
/*!
@file UIManager.cpp
@brief Stageをプレイする際に必要なUIを管理
担当：三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	UIManager::UIManager(shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_comX(800.0f),
		m_ClearFlag(false),
		m_CreateFlag(true),
		m_ligthSEFlag(false),
		m_EraseUiCommentPtrNum(-1)
	{

	}

	UIManager::~UIManager()
	{

	}

	void UIManager::OnCreate()
	{
		auto stage = GetStage();
	}

	void UIManager::OnUpdate()
	{	
		if (m_CreateFlag)//Uiを作るフラグが立った時
		{	
			CreateUi();
			m_CreateFlag = false;
		}

		EraseUiPtr();
		//if (m_EraseUiPtrNum.size() >= 1)//Uiが消えたとき
		//{
		//	PushUiPtr();//配列の更新
		//	//m_EraseUiPtrNum = -1;//フラグリセット
		//}

		//if (m_EraseUiCommentPtrNum > -1)//コメントUiが消えたとき
		//{
		//	PushUiCommentPtr();//配列の更新
		//	m_EraseUiCommentPtrNum = -1;//フラグリセット
		//}



		auto stage = GetStage();
		auto& scene = App::GetApp()->GetScene<Scene>();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_comTrans = m_comFrame->GetComponent<Transform>();
		m_StageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");//ステージマネージャーを取得
		auto player = stage->GetSharedGameObject<Player>(L"GamePlayer");
		auto chargeRatio = player->GetBulletRatio();

		if (!m_cfFlag) //ステージ開始時にAIメッセージボックスが流れる
		{
			m_comX -= 500.0f * elapsedTime;
			m_comTrans->SetPosition(m_comX, -265.0f, 0.0f);
		}
		if (m_comX < 415) //移動位置に到着したら留まる
		{
			m_cfFlag = true;//移動し終わったことを伝える
			m_StageManager->SetComFrameFlag(m_cfFlag);
			m_comTrans->SetPosition(415.0f, -265.0f, 0.0f);
		}
		if (scene->GetGameStage() > 0) //今のステージがGameStage1以降なら
		{
			if (m_cfFlag) 
			{
				if (!m_comFlag) 
				{
					if (scene->GetGameStage() > 0) 
					{
						auto mojiNum = 13 * 1;
						if(scene->GetDashStatus()>0){
							mojiNum = 13 * 4;
						}
						m_com[0] = GetStage()->AddGameObject<CommentManager>(mojiNum, 0, Vec3(250, -180, 0.0f), L"SousaCom");
					}
					m_comFlag = true;
				}
			}
			//敵を倒したらコメント
			if (m_StageManager->GetEnemyFlag())
			{
				if (!m_comFlag2) 
				{
					m_com[0]->ThisDestroy();
					int a = 0;
					m_com[1] = GetStage()->AddGameObject<CommentManager>(13 * 3, 0, Vec3(250, -180, 0.0f), L"Dassyutu");
					m_comFlag2 = true;
				}
			}

		}

		//弾のチャージ力によって色を変える
		m_chargeGarge->UpdateValue(chargeRatio);
		if (chargeRatio >= 1.0) {
			m_chargeGarge->SetColor(Col4(1.0f, 0.0f, 0.0f, 0.8f));
		}
		else if (chargeRatio >= 1.0 / 1.5) {
			m_chargeGarge->SetColor(Col4(1.0f, 1.0f, 0.0f, 0.8f));
		}
		else if (chargeRatio >= 1.0 / 3.0) {
			m_chargeGarge->SetColor(Col4(0.0f, 1.0f, 0.0f, 0.8f));
		}
		else {
			m_chargeGarge->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.8f));
		}

		if (m_dashLight) {
			if (player->GetDashFlag()) {
				m_dashLight->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.6f));
				m_ligthSEFlag = false;

			}
			else {
				if (!m_ligthSEFlag) {
					auto lampSE = App::GetApp()->GetXAudio2Manager();
					lampSE->Start(L"LampSE", 0, 0.9f);
					m_ligthSEFlag = true;
				}
				
				m_dashLight->SetColor(Col4(0.0f, 1.0f, 0.0f, 0.8f));
			}

		}

		//デバック用
		//auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		//if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
		//	float a = 1.0f;
		//	AllClear();
		//}


	}

	bool UIManager::GetClearFlag()
	{
		return m_ClearFlag;
	}

	int UIManager::SetUiPtr(shared_ptr<Sprite> Ui)
	{
		m_AllUiPtr.push_back(Ui);//Uiのポインタを取得する
		return m_AllUiPtr.size();//戻り値にどの番号にポインタを入れたかを返す
	}
	int UIManager::SetUiTimePtr(shared_ptr<UITime> UiTime)
	{
		m_UiTimePtr.push_back(UiTime);//Uiのポインタを取得する
		return m_UiTimePtr.size();//戻り値にどの番号にポインタを入れたかを返す
	}
	int UIManager::SetUiGargePtr(shared_ptr<Garge> UiGarge)
	{
		m_UiGargePtr.push_back(UiGarge);//Uiのポインタを取得する
		return m_UiGargePtr.size();//戻り値にどの番号にポインタを入れたかを返す
	}
	int UIManager::SetUiCommentPtr(shared_ptr<Comment> UiComment)
	{
		m_UiCommentPtr.push_back(UiComment);//Uiのポインタを取得する
		return m_UiCommentPtr.size();//戻り値にどの番号にポインタを入れたかを返す
	}

	void UIManager::EraseUiPtr()//空き部屋になった配列を詰める関数
	{	
		list<weak_ptr<Sprite>> afterList;
		for (auto List : m_AllUiPtr)
		{		
			auto uiPtr = List.lock();//sharedを取得する
			if (uiPtr)
			{
				afterList.push_back(uiPtr);
			}
		}
		for (auto List : m_AllUiPtr)
		{
			auto uiPtr = List.lock();
			if (!uiPtr)
			{
				m_AllUiPtr.swap(afterList);
			}
		}
		//m_AllUiPtr.erase(m_AllUiPtr.begin() + ((num - 1) - m_EraseUiPtrNum.size()));//配列にあるUiのポインタを削除する
		//m_EraseUiPtrNum.push_back(num);//削除したポインタの配列番号を取得
		//m_EraseUiPtrNum = num;//削除したポインタの配列番号を取得
		//m_AllUiPtr.size();//デバック用
		//auto a = 0;//デバック用
	}

	void UIManager::EraseUiCommentPtr(int num)//配列にあるUiのポインタの要素を削除する
	{
		//m_UiCommentPtr.erase(m_UiCommentPtr.begin() + (num - 1));//配列にあるUiのポインタを削除する
		////m_EraseUiCommentPtrNum = num;//削除したポインタの配列番号を取得
		//m_UiCommentPtr.size();//デバック用
		//auto a = 0;//デバック用
	}

	void UIManager::PushUiPtr()//配列番号を前に詰めさせる
	{
		//for (auto ui : m_AllUiPtr)
		//{
		//	auto shUI = ui.lock();
		//	if (shUI) {

		//		auto afterNum = shUI->GetNumPtr();//今の配列番号を取得
		//		auto test = afterNum;
		//		for (int i = 0; i < m_EraseUiPtrNum.size(); i++)
		//		{
		//			auto a = 0;
		//			if (test > m_EraseUiPtrNum[i])//今の配列番号が消えた配列番号より後に生成されているなら
		//			{
		//				ui.lock()->SetNumPtr(afterNum - 1);//配列番号を前にさせる
		//				afterNum -= 1;
		//				auto a = 0;
		//			}
		//		}


		//	}
		//	//auto afterNum = ui.lock()->GetNumPtr();//今の配列番号を取得
		//	//auto test = afterNum;
		//	//for (int i = 0; i < m_EraseUiPtrNum.size(); i++)
		//	//{
		//	//	auto a = 0;
		//	//	if (test > m_EraseUiPtrNum[i])//今の配列番号が消えた配列番号より後に生成されているなら
		//	//	{
		//	//		ui.lock()->SetNumPtr(afterNum - 1);//配列番号を前にさせる
		//	//		afterNum -= 1;
		//	//		auto a = 0;
		//	//	}
		//	//}
		//}
		//m_EraseUiPtrNum.erase(m_EraseUiPtrNum.begin(), m_EraseUiPtrNum.end());//削除した要素番号を詰めたのでいったん中身を消す
		//auto a = m_EraseUiPtrNum.size();
		//auto b = 0;
	}

	void UIManager::PushUiCommentPtr()//配列番号を前に詰めさせる
	{
		for (auto uiComment : m_UiCommentPtr)
		{
			auto afterNum = uiComment.lock()->GetNumPtr();//今の配列番号を取得
			if (afterNum > m_EraseUiCommentPtrNum)//今の配列番号が消えた配列番号より後に生成されているなら
			{
				uiComment.lock()->SetNumPtr(afterNum - 1);//配列番号を前にさせる
			}
		}
	}

	void UIManager::CreateUi()//UIを生成する
	{
		auto stage = GetStage();
		auto& scene = App::GetApp()->GetScene<Scene>();

		auto frame = stage->AddGameObject<Sprite>(1280, 800, L"Frame", Vec3(), 1);//枠

		m_comFrame = stage->AddGameObject<Sprite>(256 * 1.5, 200, L"CommentFrame", Vec3(m_comX, -265.0f, 0.0f), 2);//415,265
		m_comFrame->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.6f));

		auto mapFrame = stage->AddGameObject<Sprite>(235, 235, L"CommentFrame", Vec3(475, 238, 0.0f), 2);
		mapFrame->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.8f));

		//画面上のライト
		auto light = stage->AddGameObject<Sprite>(1280, 800, L"Ligth2", Vec3(), 0);

		//弾のチャージを表すゲージ
		auto chargeFrame = stage->AddGameObject<Garge>(1024, 0, L"BarSide", 1.0f, 150, 15, Col4(1.0f), Col4(1.0f,1.0f,1.0f,0.5f), Vec3(-220.0f+150, -290.0f, 0.0f), Vec3(0.0f));//こいつのカラーを何とかする
		chargeFrame->SetDrawLayer(1);
		m_chargeGarge = stage->AddGameObject<Garge>(1024, 0, L"BarSide", 0.5f, 150, 15, Col4(1.0f), Col4(1.0f), Vec3(-220.0f, -290.0f, 0.0f), Vec3(0.0f));
		m_chargeGarge->SetDrawLayer(2);
		if (scene->GetDashStatus() > 0) {
			m_dashLight = stage->AddGameObject<Sprite>(70, 70, L"DashIcon", Vec3(-150.0f, -320.0f, 0.0f));
			m_dashLight->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.8f));

		}

		auto garge = stage->AddGameObject<PieceGarge2>();
		stage->SetSharedGameObject(L"Garge", garge);
		auto PGarge = stage->AddGameObject<PlayerGarge>();

	}

	void UIManager::AllClear()//UIをすべて透明にする
	{
		auto miniMapPlayer = GetStage()->GetSharedGameObject<MiniMapPlayer>(L"MiniMapPlayer");
		if (m_ClearFlag)
		{
			m_ClearFlag = false;
		}
		else
		{
			m_ClearFlag = true;
		}

		if (m_ClearFlag)
		{
			for (auto ui : m_AllUiPtr)
			{
				auto uiPtr = ui.lock();//shart_ptrにする
				if (uiPtr)
				{
					if (!uiPtr->FindTag(L"MovieSprite"))
					{
						//auto a = 0;
						uiPtr->OnClear(true);//透明にする
						miniMapPlayer->OnClear(true);
					}

				}

			}
			//for (auto uiTime : m_UiTimePtr)
			//{
			//	auto TimePtr = uiTime.lock();
			//	if (TimePtr)
			//	{
			//		TimePtr->OnClear(true);
			//	}
			//}
			for (auto uiGarge : m_UiGargePtr)
			{
				auto GargePtr = uiGarge.lock();
				if (GargePtr)
				{
					GargePtr->OnClear(true);

				}
			}
			//for (auto uiComment : m_UiCommentPtr)
			//{
			//	auto CommentPtr = uiComment.lock();
			//	if (CommentPtr)
			//	{
			//		CommentPtr->OnClear(true);
			//	}
			//}
		}
		else
		{

			for (auto ui : m_AllUiPtr)
			{
				auto uiPtr = ui.lock();
				if (uiPtr)
				{
					if (!uiPtr->FindTag(L"MovieSprite"))
					{
						auto a = 0;
						uiPtr->OnClear(false);//透明にする
						miniMapPlayer->OnClear(false);
					}

				}

				//if (!ui.lock()->FindTag(L"MovieSprite"))
				//{
				//	ui.lock()->OnClear(false);//透明から戻す
				//	miniMapPlayer->OnClear(false);
				//}
			}
			//for (auto uiTime : m_UiTimePtr)
			//{
			//	auto timePtr = uiTime.lock();
			//	if (timePtr)
			//	{
			//		timePtr->OnClear(false);//透明から戻す
			//	}
			//}
			for (auto uiGarge : m_UiGargePtr)
			{
				auto GargePtr = uiGarge.lock();
				if (GargePtr)
				{
					GargePtr->OnClear(false);
				}
			}
			//for (auto uiComment : m_UiCommentPtr)
			//{
			//	auto CommentPtr = uiComment.lock();
			//	if (CommentPtr)
			//	{
			//		CommentPtr->OnClear(false);
			//	}
			//}


		}
	}
}
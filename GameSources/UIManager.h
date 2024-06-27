/*!
@file UIManager.h
@brief Stageをプレイする際に必要なUIを管理
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"
#include "Garge.h"

//class Garge;//前方宣言（とりあえずこういうクラスがあると伝える）
//class PlayerGarge;

namespace basecross {
	class UIManager :public GameObject
	{
	private:
		bool m_CreateFlag;//生成するフラグ
		bool m_cfFlag;
		bool m_comFlag;
		bool m_comFlag2;
		bool m_ClearFlag;//透明にするかしないかのフラグ
		bool m_ligthSEFlag = false;
		int m_EraseUiCommentPtrNum;//消したポインタの番号を覚える変数(コメント版)
		float m_comX;
		vector<int> m_EraseUiPtrNum;//消したポインタの番号を覚える変数
		shared_ptr<Sprite> m_comFrame;
		shared_ptr<Transform> m_comTrans;
		shared_ptr<CommentManager> m_com[2];
		shared_ptr<StageManager> m_StageManager;
		shared_ptr<Garge> m_chargeGarge;
		shared_ptr<Sprite> m_dashLight;
		vector<weak_ptr<Sprite>> m_AllUiPtr;//ステージ上の全てのUiのポインタを取得
		vector<weak_ptr<UITime>> m_UiTimePtr;//制限時間のポインタ取得
		vector<weak_ptr<Garge>> m_UiGargePtr;//Gargeのポインタ取得
		vector<weak_ptr<Comment>> m_UiCommentPtr;//Commentのポインタ取得
	public:
		UIManager(shared_ptr<Stage>& stagePtr);
		~UIManager();

		void OnCreate()override;
		void OnUpdate()override;
		void AllClear();//UIが見えなくなる	
		void EraseUiPtr(int num);//配列にあるUiのポインタを消す
		void EraseUiCommentPtr(int num);//配列にあるUiのポインタを消す
		void PushUiPtr();//配列が小さくなった際、使わない番号を詰める
		void PushUiCommentPtr();//配列が小さくなった際、使わない番号を詰める(コメント版)
		int SetUiPtr(shared_ptr<Sprite> Ui);//UIのポインタを配列に入れる
		int SetUiTimePtr(shared_ptr<UITime> UiTime);//UiTimeのポインタを入れる
		int SetUiGargePtr(shared_ptr<Garge> UiGarge);//Gargeのポインタを入れる
		int SetUiCommentPtr(shared_ptr<Comment> UiComment);//Commentのポインタを入れる
		void CreateUi();//UIを生成
		//bool GetEnemyFlag();
	};
}
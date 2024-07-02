/*!
@file MiniMapBigPiece.cpp
@brief 敵のデカい欠片のミニマップの表示
担当：三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MiniMapBigPiece::MiniMapBigPiece(const shared_ptr<Stage>& stagePtr,float width,float height, wstring meshResName, Vec3 pos,int layer,wstring objName):
		Sprite(stagePtr,width,height,meshResName,pos,layer),
		m_ObjName(objName),
		m_Existence(true)
	{

	}
	MiniMapBigPiece::~MiniMapBigPiece()
	{
	}

	void MiniMapBigPiece::OnCreate()
	{
		Sprite::OnCreate();
	}

	void MiniMapBigPiece::OnUpdate()
	{	
		
		auto uiManager = GetStage()->GetSharedGameObject<UIManager>(L"UIManager");
		if (m_Existence == false)
		{
			//GetStage()->GetSharedGameObject<UIManager>(L"UIManager")->EraseUiPtr(m_numPtr);//自分を消す前に配列に自分のポインタを消す
			GetStage()->RemoveGameObject<MiniMapBigPiece>(GetThis<MiniMapBigPiece>());//自分を消す
			auto scene = App::GetApp()->GetScene<Scene>();
			scene->AddBigPieceCount(1);
		}
	}

	void MiniMapBigPiece::SetExistence(bool Existence)
	{
		m_Existence = Existence;
	}
}
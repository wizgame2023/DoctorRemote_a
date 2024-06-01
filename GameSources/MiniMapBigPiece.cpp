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
		if (m_Existence == false)
		{
			GetStage()->RemoveGameObject<MiniMapBigPiece>(GetThis<MiniMapBigPiece>());
		}
	}

	void MiniMapBigPiece::SetExistence(bool Existence)
	{
		m_Existence = Existence;
	}
}
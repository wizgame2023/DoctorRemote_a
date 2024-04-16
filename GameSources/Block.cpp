/*!
@file Block.cpp
@brief ブロックのオブジェクトの実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void Block::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(m_meshResName);
		drawComp->SetTextureResource(L"BLOCK"); // 読み込んだ時に付けたアセット名
		drawComp->SetOwnShadowActive(true);

		auto shadowComp = AddComponent<Shadowmap>();
		shadowComp->SetMeshResource(m_meshResName);
	}

}
//end basecross

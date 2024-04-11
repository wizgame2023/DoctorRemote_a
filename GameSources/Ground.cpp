/*!
@file Ground.cpp
@brief ’n–Ê
*/

#include "stdafx.h"
#include "Project.h"
#include "Ground.h"

namespace basecross {

	//‰Šú‰»
	void Ground::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetTextureResource(L"Internal");
		drawComp->SetOwnShadowActive(true); // ‰e‚Ì‰f‚è‚İ‚ğ”½‰f‚³‚¹‚é

		auto transComp = GetComponent<Transform>();
		transComp->SetScale(15.0f, 1.0f, 15.0f);
		transComp->SetPosition(0.0f, -0.5f, 0.0f);

	}

}
//end basecross

/*!
@file MyMovieStage.cpp
@brief ムービーを流す
担当：三瓶裕太
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	MyMovieStage::MyMovieStage()
	{

	}

	MyMovieStage::~MyMovieStage()
	{

	}

	void MyMovieStage::OnCreate()
	{
		//MovieStage::OnCreate();//親クラスのクリエイト呼び出し
		////wstring data;
		//auto path = App::GetApp()->GetDataDirWString();
		//wstring MoviePass = path + L"Movies/";
		//wstring strMovie = MoviePass + L"DoctorRemoteTitlever2.mp4";
		//SetMovieFileName(strMovie);
		//Play();

		AddGameObject<Sprite>(10.0f, 10.0f, L"TitleMoji", Vec3(0.0));
	}

	void MyMovieStage::OnUpdate()
	{
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<MyMovieStage>());
	}

	void MyMovieStage::OnPushA()
	{
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToStartStage");

	}

	void MyMovieStage::OnPushB()
	{
	}
}
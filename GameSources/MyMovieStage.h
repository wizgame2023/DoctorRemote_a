/*!
@file MyMovieStage.cpp
@brief ムービーを流す
担当：三瓶
*/

#pragma once
#include "stdafx.h"

namespace basecross 
{
	class MyMovieStage :public MovieStage
	{
	private:
		InputHandler<MyMovieStage> m_InputHandler;
	public:
		MyMovieStage();
		~MyMovieStage();

		void OnCreate();
		void OnUpdate();

		void OnPushA();
		void OnPushB();
	};
}

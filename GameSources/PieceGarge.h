/*!
@file PieceGarge.h
@brief “G‚ÌŒ‡•Ğ‚ÌƒQ[ƒW
’S“–FˆíŒ©
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PieceGarge :public GameObject{

	public:
		PieceGarge(const shared_ptr<Stage>& StagePtr);
		~PieceGarge(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end namespace basecross

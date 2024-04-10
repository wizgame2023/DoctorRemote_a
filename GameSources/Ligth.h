/*!
@file Light.h
@brief ŒõAŒõŒ¹‚Ì•\Œ»
’S“–@O•r—T‘¾
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MyLight : public GameObject
	{
	public:	
		MyLight(const shared_ptr<Stage>& stage);
		virtual ~MyLight();

	    virtual void OnCreate() override;
		//virtual void OnUpdate() override {};

	};
}
//end namespace basecross

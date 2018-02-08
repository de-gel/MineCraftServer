#pragma once

#include "../../ServerFramework/ServerFramework/ServerBase.h"

class CGateServer :
	public CServerBase
{
public:
	CGateServer();
	~CGateServer();


	//////////////////////////////////////////////
	virtual bool OnInit() override;

	virtual bool OnBeforeStart() override;

	virtual bool OnAfterStart() override;

	virtual void OnStop() override;

	virtual void OnRun() override;
};


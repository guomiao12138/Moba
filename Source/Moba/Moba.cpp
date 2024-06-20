// Copyright Epic Games, Inc. All Rights Reserved.

#include "Moba.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMobaModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;



private:

};


IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Moba, "Moba" );

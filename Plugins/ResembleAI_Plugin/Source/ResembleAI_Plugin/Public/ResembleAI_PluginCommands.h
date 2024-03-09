// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ResembleAI_PluginStyle.h"

class FResembleAI_PluginCommands : public TCommands<FResembleAI_PluginCommands>
{
public:

	FResembleAI_PluginCommands()
		: TCommands<FResembleAI_PluginCommands>(TEXT("ResembleAI_Plugin"), NSLOCTEXT("Contexts", "ResembleAI_Plugin", "ResembleAI_Plugin Plugin"), NAME_None, FResembleAI_PluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};
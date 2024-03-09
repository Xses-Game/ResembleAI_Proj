// Copyright Epic Games, Inc. All Rights Reserved.

#include "ResembleAI_PluginCommands.h"

#define LOCTEXT_NAMESPACE "FResembleAI_PluginModule"

void FResembleAI_PluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "ResembleAI_Plugin", "Bring up ResembleAI_Plugin window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE

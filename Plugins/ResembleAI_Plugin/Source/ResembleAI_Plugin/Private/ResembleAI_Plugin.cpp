// Copyright Epic Games, Inc. All Rights Reserved.

#include "ResembleAI_Plugin.h"
#include "ResembleAI_PluginStyle.h"
#include "ResembleAI_PluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName ResembleAI_PluginTabName("ResembleAI_Plugin");

#define LOCTEXT_NAMESPACE "FResembleAI_PluginModule"

void FResembleAI_PluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FResembleAI_PluginStyle::Initialize();
	FResembleAI_PluginStyle::ReloadTextures();

	FResembleAI_PluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FResembleAI_PluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FResembleAI_PluginModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FResembleAI_PluginModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(ResembleAI_PluginTabName, FOnSpawnTab::CreateRaw(this, &FResembleAI_PluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FResembleAI_PluginTabTitle", "ResembleAI_Plugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FResembleAI_PluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FResembleAI_PluginStyle::Shutdown();

	FResembleAI_PluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(ResembleAI_PluginTabName);
}

TSharedRef<SDockTab> FResembleAI_PluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FResembleAI_PluginModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("ResembleAI_Plugin.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FResembleAI_PluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(ResembleAI_PluginTabName);
}

void FResembleAI_PluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FResembleAI_PluginCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FResembleAI_PluginCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FResembleAI_PluginModule, ResembleAI_Plugin)
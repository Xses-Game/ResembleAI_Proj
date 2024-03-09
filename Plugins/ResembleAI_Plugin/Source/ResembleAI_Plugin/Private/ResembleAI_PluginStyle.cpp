// Copyright Epic Games, Inc. All Rights Reserved.

#include "ResembleAI_PluginStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FResembleAI_PluginStyle::StyleInstance = nullptr;

void FResembleAI_PluginStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FResembleAI_PluginStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FResembleAI_PluginStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("ResembleAI_PluginStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FResembleAI_PluginStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("ResembleAI_PluginStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("ResembleAI_Plugin")->GetBaseDir() / TEXT("Resources"));

	Style->Set("ResembleAI_Plugin.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FResembleAI_PluginStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FResembleAI_PluginStyle::Get()
{
	return *StyleInstance;
}

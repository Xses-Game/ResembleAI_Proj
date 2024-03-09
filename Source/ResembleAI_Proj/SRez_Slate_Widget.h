// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class RESEMBLEAI_PROJ_API SRez_Slate_Widget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRez_Slate_Widget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};

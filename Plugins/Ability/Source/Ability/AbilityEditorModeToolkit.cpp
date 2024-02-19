// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbilityEditorModeToolkit.h"
#include "AbilityEditorMode.h"
#include "Engine/Selection.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "AbilityEditorModeToolkit"

FAbilityEditorModeToolkit::FAbilityEditorModeToolkit()
{
}

void FAbilityEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
{
	FModeToolkit::Init(InitToolkitHost, InOwningMode);
}

void FAbilityEditorModeToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Add(NAME_Default);
}


FName FAbilityEditorModeToolkit::GetToolkitFName() const
{
	return FName("AbilityEditorMode");
}

FText FAbilityEditorModeToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("DisplayName", "AbilityEditorMode Toolkit");
}

#undef LOCTEXT_NAMESPACE

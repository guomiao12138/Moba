// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbilityEditorMode.h"
#include "AbilityEditorModeToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "AbilityEditorModeCommands.h"


//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
// AddYourTool Step 1 - include the header file for your Tools here
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
#include "Tools/AbilitySimpleTool.h"
#include "Tools/AbilityInteractiveTool.h"

// step 2: register a ToolBuilder in FAbilityEditorMode::Enter() below


#define LOCTEXT_NAMESPACE "AbilityEditorMode"

const FEditorModeID UAbilityEditorMode::EM_AbilityEditorModeId = TEXT("EM_AbilityEditorMode");

FString UAbilityEditorMode::SimpleToolName = TEXT("Ability_ActorInfoTool");
FString UAbilityEditorMode::InteractiveToolName = TEXT("Ability_MeasureDistanceTool");


UAbilityEditorMode::UAbilityEditorMode()
{
	FModuleManager::Get().LoadModule("EditorStyle");

	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(UAbilityEditorMode::EM_AbilityEditorModeId,
		LOCTEXT("ModeName", "Ability"),
		FSlateIcon(),
		true);
}


UAbilityEditorMode::~UAbilityEditorMode()
{
}


void UAbilityEditorMode::ActorSelectionChangeNotify()
{
}

void UAbilityEditorMode::Enter()
{
	UEdMode::Enter();

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// AddYourTool Step 2 - register the ToolBuilders for your Tools here.
	// The string name you pass to the ToolManager is used to select/activate your ToolBuilder later.
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////// 
	const FAbilityEditorModeCommands& SampleToolCommands = FAbilityEditorModeCommands::Get();

	RegisterTool(SampleToolCommands.SimpleTool, SimpleToolName, NewObject<UAbilitySimpleToolBuilder>(this));
	RegisterTool(SampleToolCommands.InteractiveTool, InteractiveToolName, NewObject<UAbilityInteractiveToolBuilder>(this));

	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, SimpleToolName);
}

void UAbilityEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FAbilityEditorModeToolkit);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UAbilityEditorMode::GetModeCommands() const
{
	return FAbilityEditorModeCommands::Get().GetCommands();
}

#undef LOCTEXT_NAMESPACE

// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityNodeEdGraphSchema.h"
#include "Ability/Editor/Node/AbilityNode.h"
#include "Ability/Runtime/MobaAbility.h"
#include "Ability/Editor/Node/Schema/AbilityConnectionDrawingPolicy.h"
#include "Ability/Editor/MobaAbilityEdGraph.h"
#include "Ability/AbilityModule.h"

#include "Framework/Commands/GenericCommands.h"
#include "SGraphNode.h"
#include "EdGraph/EdGraphSchema.h"
#include "Editor/AIGraph/Classes/AIGraphTypes.h"




UMobaAbilityNodeEdGraphSchema::UMobaAbilityNodeEdGraphSchema()
{
	AssetClass = UMobaAbility::StaticClass();
}

FGraphNodeClassHelper& UMobaAbilityNodeEdGraphSchema::GetClassCache() const
{
	const FAbilityModule& EditorModule = FModuleManager::GetModuleChecked<FAbilityModule>(TEXT("BehaviorTreeEditor"));
	FGraphNodeClassHelper* ClassHelper = EditorModule.GetClassCache().Get();
	check(ClassHelper);
	return *ClassHelper;
}


void UMobaAbilityNodeEdGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TArray<FName> FunctionArray;
	AssetClass->GenerateFunctionList(FunctionArray);

	FGraphNodeClassHelper& ClassCache = GetClassCache();

	TArray<FGraphNodeClassData> NodeClasses;
	ClassCache.GatherClasses(UAbilityNode::StaticClass(), NodeClasses);

	for (auto func : FunctionArray)
	{
		//if (AssetClass->FindFunction(func))
		//{

		//}
		
		const TSharedPtr<FMobaAbilityGraphSchemaAction> Action = MakeShareable(new FMobaAbilityGraphSchemaAction(FText::FromString("MobaAbility"), FText::FromName(func), FText()));
		ContextMenuBuilder.AddAction(Action);
	}





	
	Super::GetGraphContextActions(ContextMenuBuilder);
}



//bool UMobaAbilityNodeEdGraphSchema::CreatePromotedConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const
//{
//	PinA->Modify();
//	PinB->Modify();
//
//	PinA->MakeLinkTo(PinB);
//
//	//UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForNodeChecked(PinA->GetOwningNode());
//
//	return true;
//}

void UMobaAbilityNodeEdGraphSchema::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	if (Context->Node && !Context->Pin)
	{
		FToolMenuSection& Section = Menu->AddSection(TEXT("MobaAbilityEditor"), NSLOCTEXT("MobaAbilityEditor", "Our Node Context Menu Section Name", "Menu Section Name"));
		Section.AddMenuEntry(FGenericCommands::Get().Copy);
		Section.AddMenuEntry(FGenericCommands::Get().Cut);
		Section.AddMenuEntry(FGenericCommands::Get().Paste);
		Section.AddMenuEntry(FGenericCommands::Get().Delete);
	}
	//else if (Context->Pin)
	//{
	//	FToolMenuSection& Section = Menu->AddSection(TEXT("PinContextMenuSection"), NSLOCTEXT("Editor", "Our Node Pin Menu Section Name", "Menu Section Name"));
	//	Section.AddMenuEntry(FGenericCommands::Get().Delete);
	//}

	Super::GetContextMenuActions(Menu, Context);
}

const FPinConnectionResponse UMobaAbilityNodeEdGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Both are on the same node"));
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_A, TEXT(""));
}


FConnectionDrawingPolicy* UMobaAbilityNodeEdGraphSchema::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const
{
	return new FMobaAbilityNodeConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}

void UMobaAbilityNodeEdGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	auto* rootnode = Cast<UMobaAbilityEdGraph>(&Graph)->CreateDefaultNode(TEXT("Root"));
	Cast<UMobaAbility>(Graph.GetOuter())->RootNode = rootnode;
}

UEdGraphNode* FMobaAbilityGraphSchemaAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	return CreateNode(ParentGraph, Location);
}

UAbilityNode* FMobaAbilityGraphSchemaAction::CreateNode(UEdGraph* ParentGraph, const FVector2D Location)
{
	UFunction* Function = UMobaAbility::StaticClass()->FindFunctionByName(FunctionName);

	ParentGraph->Modify();
	//node->SetFlags(RF_Transactional);

	//node->Rename(nullptr, ParentGraph, REN_NonTransactional);


	FGraphNodeCreator<UAbilityNode> NodeCreator(*ParentGraph);
	UAbilityNode* node = NodeCreator.CreateNode(false);
	node->SetFromFunction(Function);
	node->SetFlags(RF_Transactional);
	node->NodePosX = Location.X;
	node->NodePosY = Location.Y;
	node->AllocateDefaultPins();
	NodeCreator.Finalize();


	return node;
}


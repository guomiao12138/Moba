// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityNodeEdGraphSchema.h"
#include "Ability/Node/AbilityNode.h"
#include "Ability/Node/UAbilityNode_Root.h"
#include "Ability/MobaAbility.h"
#include "Ability/Node/Schema/AbilityConnectionDrawingPolicy.h"

#include "Framework/Commands/GenericCommands.h"
#include "SGraphNode.h"
#include "EdGraph/EdGraphSchema.h"



UMobaAbilityNodeEdGraphSchema::UMobaAbilityNodeEdGraphSchema()
{
	AssetClass = UMobaAbility::StaticClass();
}

void UMobaAbilityNodeEdGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TArray<UClass*> res;
	GetDerivedClasses(UAbilityNode::StaticClass(), res, true);
	

	//TArray<FName> FunctionArray;
	//AssetClass->GenerateFunctionList(FunctionArray);

	//FGraphNodeClassHelper& ClassCache = GetClassCache();

	//TArray<FGraphNodeClassData> NodeClasses;
	//ClassCache.GatherClasses(UAbilityNode::StaticClass(), NodeClasses);

	for (auto s : res)
	{
		//if (AssetClass->FindFunction(func))
		//{

		//}
		if (s->GetName() ==  "Root")
		{
			continue;
		}
		const TSharedPtr<FMobaAbilityGraphSchemaAction> Action = MakeShareable(new FMobaAbilityGraphSchemaAction(FText::FromString("MobaAbility"), FText::FromName(s->GetFName()), FText(), s));
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
	//auto* rootnode = Cast<UMobaAbilityEdGraph>(&Graph)->CreateDefaultNode(TEXT("Root"));

	UAbilityNode_Root* ResultGraphNode = NewObject<UAbilityNode_Root>(&Graph);
	Graph.Modify();
	ResultGraphNode->SetFlags(RF_Transactional);
	ResultGraphNode->Rename(nullptr, &Graph, REN_NonTransactional);
	ResultGraphNode->CreateNewGuid();
	ResultGraphNode->NodePosX = 0;
	ResultGraphNode->NodePosY = 0;

	ResultGraphNode->AllocateDefaultPins();
	Graph.AddNode(ResultGraphNode);

	Cast<UMobaAbility>(Graph.GetOuter())->RootNode = ResultGraphNode;
}

UEdGraphNode* FMobaAbilityGraphSchemaAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	return CreateNode(ParentGraph, Location);
}

UAbilityNode* FMobaAbilityGraphSchemaAction::CreateNode(UEdGraph* ParentGraph, const FVector2D Location)
{
	ParentGraph->Modify();
	//node->SetFlags(RF_Transactional);

	//node->Rename(nullptr, ParentGraph, REN_NonTransactional);
	FGraphNodeCreator<UAbilityNode> NodeCreator(*ParentGraph);
	UAbilityNode* node = NodeCreator.CreateNode(false, NodeClass);
	node->SetFlags(RF_Transactional);
	node->NodePosX = Location.X;
	node->NodePosY = Location.Y;
	node->AllocateDefaultPins();
	//node->PostPlacedNewNode();
	NodeCreator.Finalize();


	return node;
}


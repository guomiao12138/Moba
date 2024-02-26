// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityNodeEdGraphSchema.h"
#include "Framework/Commands/GenericCommands.h"
#include "Ability/Node/MobaAbilityEdGraphNodeBase.h"
#include "Ability/MobaAbility.h"

UMobaAbilityNodeEdGraphSchema::UMobaAbilityNodeEdGraphSchema()
{
	AssetClass = UMobaAbility::StaticClass();
}

void UMobaAbilityNodeEdGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TArray<FName> FunctionArray;
	AssetClass->GenerateFunctionList(FunctionArray);

	for (auto func : FunctionArray)
	{
		const TSharedPtr<FMobaAbilityGraphSchemaAction> Action = MakeShareable(new FMobaAbilityGraphSchemaAction(FText::FromString("MobaAbility"), FText::FromName(func), FText()));
		ContextMenuBuilder.AddAction(Action);
	}


	const TSharedPtr<FMobaAbilityGraphSchemaAction_NewSubNode> NewSubNodeAction = MakeShareable(new FMobaAbilityGraphSchemaAction_NewSubNode);
	ContextMenuBuilder.AddAction(NewSubNodeAction);
	
	Super::GetGraphContextActions(ContextMenuBuilder);
}

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

UEdGraphNode* FMobaAbilityGraphSchemaAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UMobaAbilityEdGraphNodeBase* node = NewObject<UMobaAbilityEdGraphNodeBase>(ParentGraph);
	node->Init(functionName, functionName);
	node->SetFromFunction(UMobaAbility::StaticClass()->FindFunctionByName(functionName));
	ParentGraph->Modify();
	node->SetFlags(RF_Transactional);

	node->Rename(nullptr, ParentGraph, REN_NonTransactional);
	node->CreateNewGuid();
	node->NodePosX = Location.X;
	node->NodePosY = Location.Y;

	node->AllocateDefaultPins();

	ParentGraph->AddNode(node);

	//if (FromPin)
	//{
	//	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("Editor Print Action With Pin Hello World with point %s"), *functionName.ToString())));
	//}
	//else
	//{
	//	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("Editor Print Action Without Pin Hello World %s"), *functionName.ToString())));
	//}

	return node;
}

UMobaAbilityEdGraphNodeBase* FMobaAbilityGraphSchemaAction::CreateNode()
{
	return nullptr;
}

UEdGraphNode* FMobaAbilityGraphSchemaAction_NewSubNode::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	check(ParentGraph != nullptr)
	FGraphNodeCreator<UMobaAbilityEdGraphNodeBase> NodeCreator(*ParentGraph);
	UMobaAbilityEdGraphNodeBase* ResultGraphNode = NodeCreator.CreateUserInvokedNode(bSelectNewNode);
	//UMobaAbilityEdGraphNodeBase* ResultGraphNode = NewObject<UMobaAbilityEdGraphNodeBase>(ParentGraph);
	ParentGraph->Modify();
	ResultGraphNode->SetFlags(RF_Transactional);

	ResultGraphNode->Rename(nullptr, ParentGraph, REN_NonTransactional);
	ResultGraphNode->CreateNewGuid();
	ResultGraphNode->NodePosX = Location.X;
	ResultGraphNode->NodePosY = Location.Y;
	ResultGraphNode->AllocateDefaultPins();

	NodeCreator.Finalize();

	return ResultGraphNode;
}

//UEdGraphNode* FMobaAbilityGraphSchemaAction_NewSubNode::PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode)
//{
//	return nullptr;
//}

//void FMobaAbilityGraphSchemaAction_NewSubNode::AddReferencedObjects(FReferenceCollector& Collector)
//{
//	FEdGraphSchemaAction::AddReferencedObjects(Collector);
//
//	// These don't get saved to disk, but we want to make sure the objects don't get GC'd while the action array is around
//	Collector.AddReferencedObject(NodeTemplate);
//	Collector.AddReferencedObject(ParentNode);
//}
//	return nullptr;
//}

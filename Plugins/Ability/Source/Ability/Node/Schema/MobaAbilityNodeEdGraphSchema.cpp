// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityNodeEdGraphSchema.h"
#include "Framework/Commands/GenericCommands.h"
<<<<<<< HEAD
#include "Ability/Node/MobaAbilityEdGraphNodeBase.h"
=======
>>>>>>> 595b50cfd57cee54cfddcf2bb92eddc25d608d11

void UMobaAbilityNodeEdGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	const TSharedPtr<FMobaAbilityGraphSchemaAction> Action = MakeShareable(new FMobaAbilityGraphSchemaAction);
	ContextMenuBuilder.AddAction(Action);
<<<<<<< HEAD

	const TSharedPtr<FMobaAbilityGraphSchemaAction_NewSubNode> NewSubNodeAction = MakeShareable(new FMobaAbilityGraphSchemaAction_NewSubNode);
	ContextMenuBuilder.AddAction(NewSubNodeAction);
	
=======
>>>>>>> 595b50cfd57cee54cfddcf2bb92eddc25d608d11
	Super::GetGraphContextActions(ContextMenuBuilder);
}

void UMobaAbilityNodeEdGraphSchema::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	if (Context->Node && !Context->Pin)
	{
<<<<<<< HEAD
		FToolMenuSection& Section = Menu->AddSection(TEXT("AAAA"), NSLOCTEXT("Editor", "Our Node Context Menu Section Name", "Menu Section Name"));
=======
		FToolMenuSection& Section = Menu->AddSection(TEXT("NodeContextMenuSection"), NSLOCTEXT("Editor", "Our Node Context Menu Section Name", "Menu Section Name"));
>>>>>>> 595b50cfd57cee54cfddcf2bb92eddc25d608d11
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
	if (FromPin)
	{
<<<<<<< HEAD
=======
		
>>>>>>> 595b50cfd57cee54cfddcf2bb92eddc25d608d11
		FMessageDialog::Open(EAppMsgType::Ok, NSLOCTEXT("Editor", "Print Action With Pin", "Hello World with point"));
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, NSLOCTEXT("Editor", "Print Action Without Pin", "Hello World"));
	}
	return nullptr;
}

UEdGraphNode* FMobaAbilityGraphSchemaAction_NewSubNode::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
<<<<<<< HEAD
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
=======
	return nullptr;
}

UEdGraphNode* FMobaAbilityGraphSchemaAction_NewSubNode::PerformAction(UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2D Location, bool bSelectNewNode)
{
	return nullptr;
}

void FMobaAbilityGraphSchemaAction_NewSubNode::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);

	// These don't get saved to disk, but we want to make sure the objects don't get GC'd while the action array is around
	Collector.AddReferencedObject(NodeTemplate);
	Collector.AddReferencedObject(ParentNode);
}
>>>>>>> 595b50cfd57cee54cfddcf2bb92eddc25d608d11

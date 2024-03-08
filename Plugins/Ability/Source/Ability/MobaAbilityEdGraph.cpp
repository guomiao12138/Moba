// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityEdGraph.h"
#include "GraphEditAction.h"
#include "EdGraph/EdGraphNode.h"
#include "Node/MobaAbilityNode_Default.h"

UMobaAbilityEdGraph::UMobaAbilityEdGraph()
{
	//BeginNode = ;
}

void UMobaAbilityEdGraph::NotifyGraphChanged(const FEdGraphEditAction& Action)
{
	if (auto asset = GetOuter())
	{
		asset->GetPackage()->SetDirtyFlag(true);
	}


	Super::NotifyGraphChanged(Action);
}

void UMobaAbilityEdGraph::BuildNode()
{
	//TArray<FFrame> framestack;
	//auto linkPins = BeginNode->GetThenPin()->LinkedTo;
	//for (auto p : linkPins)
	//{
	//	if (auto n = Cast<UMobaAbilityEdGraphNodeBase>(p->GetOuter()))
	//	{
	//		n->CallFunction();
	//	}

	//}

}

void UMobaAbilityEdGraph::ActiveEventNode(FName eventname)
{
	if (!EventNodeMap.Contains(eventname))
	{
		return;
	}
	TArray<UEdGraphPin*> links = EventNodeMap[eventname]->GetThenPin()->LinkedTo;

	TArray<UMobaAbilityEdGraphNodeBase*> nodes;

	UMobaAbilityEdGraphNodeBase* next = nullptr;
	for (auto link : links)
	{
		next = Cast<UMobaAbilityEdGraphNodeBase>(link->GetOuter());
		while (next)
		{
			nodes.Add(next);
			if (next->GetThenPin()->LinkedTo.Num() > 0)
			{
				next = Cast<UMobaAbilityEdGraphNodeBase>(next->GetThenPin()->LinkedTo[0]->GetOuter());
			}
			else
			{
				break;
			}
		}
	}

	for (auto n : nodes)
	{
		n->CallFunction();
	}
}

UMobaAbilityEdGraphNodeBase* UMobaAbilityEdGraph::CreateDefaultNode(FName eventname)
{
	UMobaAbilityNode_Default* ResultGraphNode = NewObject<UMobaAbilityNode_Default>(this);
	Modify();
	ResultGraphNode->SetFlags(RF_Transactional);
	ResultGraphNode->SetNodeTitle(eventname);
	ResultGraphNode->Rename(nullptr, this, REN_NonTransactional);
	ResultGraphNode->CreateNewGuid();
	ResultGraphNode->NodePosX = 0;
	ResultGraphNode->NodePosY = EventNodeMap.Num() * 5;

	ResultGraphNode->AllocateDefaultPins();
	AddNode(ResultGraphNode);
	EventNodeMap.Add(eventname, ResultGraphNode);
	return ResultGraphNode;
}

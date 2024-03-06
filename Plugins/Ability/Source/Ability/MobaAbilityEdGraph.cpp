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
	TArray<FFrame> framestack;
	auto linkPins = BeginNode->GetThenPin()->LinkedTo;
	for (auto p : linkPins)
	{
		if (auto n = Cast<UMobaAbilityEdGraphNodeBase>(p->GetOuter()))
		{
			n->CallFunction();
		}

	}

}

UMobaAbilityEdGraphNodeBase* UMobaAbilityEdGraph::CreateBeginNode()
{
	UMobaAbilityNode_Default* ResultGraphNode = NewObject<UMobaAbilityNode_Default>(this);
	Modify();
	ResultGraphNode->SetFlags(RF_Transactional);
	ResultGraphNode->SetNodeTitle(TEXT("Begin"));
	ResultGraphNode->Rename(nullptr, this, REN_NonTransactional);
	ResultGraphNode->CreateNewGuid();
	ResultGraphNode->NodePosX = 0;
	ResultGraphNode->NodePosY = 0;

	ResultGraphNode->AllocateDefaultPins();
	AddNode(ResultGraphNode);
	BeginNode = ResultGraphNode;
	return ResultGraphNode;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilityEdGraph.h"
#include "GraphEditAction.h"
#include "EdGraph/EdGraphNode.h"

UMobaAbilityEdGraph::UMobaAbilityEdGraph()
{
}

void UMobaAbilityEdGraph::NotifyGraphChanged(const FEdGraphEditAction& Action)
{
	if (auto asset = GetOuter())
	{
		asset->GetPackage()->SetDirtyFlag(true);
	}


	Super::NotifyGraphChanged(Action);
}


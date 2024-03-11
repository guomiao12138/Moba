// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityConnectionDrawingPolicy.h"
#include "EdGraph/EdGraphSchema.h"


FMobaAbilityNodeConnectionDrawingPolicy::FMobaAbilityNodeConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj)
	:FConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements), GraphObj(InGraphObj)
{
	ArrowImage = nullptr;
	ArrowRadius = FVector2D(0.0f, 0.0f);
}

void FMobaAbilityNodeConnectionDrawingPolicy::DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params)
{
	FConnectionDrawingPolicy::DetermineWiringStyle(OutputPin, InputPin, Params);

	if (HoveredPins.Contains(InputPin) && HoveredPins.Contains(OutputPin))
	{
		Params.WireThickness = Params.WireThickness * 3;
	}

	if (ensure(GraphObj))
	{
		const UEdGraphSchema* Schema = GraphObj->GetSchema();

		Params.WireColor = Schema->GetPinTypeColor(OutputPin->PinType);
	}
}
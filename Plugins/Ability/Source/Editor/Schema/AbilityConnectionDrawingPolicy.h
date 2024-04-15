// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include"Editor/GraphEditor/Public/ConnectionDrawingPolicy.h"

/**
 * 
 */
struct FConnectionParams;
class FMobaAbilityNodeConnectionDrawingPolicy : public FConnectionDrawingPolicy
 {
 public:
 	FMobaAbilityNodeConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj);
 	virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, /*inout*/ FConnectionParams& Params) override;
 	UEdGraph* GraphObj;
 };

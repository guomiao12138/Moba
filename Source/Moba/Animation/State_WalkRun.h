// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "StateMachine.h"

struct FState_WalkRun : public TSharedFromThis<FState_WalkRun>, public FStateMachine
{
public:
	virtual void Update(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node) override;
	virtual void PreUpdate(UMobaAnimInstance* InAnimInstance, float DeltaSeconds) override;

	FState_WalkRun() {};
	FState_WalkRun(UMobaAnimInstance* InMobaAnimInstance, APawn* InOnwer) : FStateMachine(InMobaAnimInstance, InOnwer) {};
	virtual ~FState_WalkRun() {};
};

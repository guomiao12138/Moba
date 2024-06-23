// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "StateMachine.h"

struct FState_Skill : public TSharedFromThis<FState_Skill>, public FStateMachine
{
public:

	virtual void InitialUpdate(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node) override {};

	virtual void PreUpdate(UMobaAnimInstance* InAnimInstance, float DeltaSeconds) override {};
	virtual void Update(FAnimUpdateContext& UpdateContext, FAnimNodeReference& Node) override {};

	FState_Skill() {};
	FState_Skill(UMobaAnimInstance* InMobaAnimInstance, APawn* InOnwer) : FStateMachine(InMobaAnimInstance, InOnwer) {};
	virtual ~FState_Skill() {};
};

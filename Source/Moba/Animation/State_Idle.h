// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StateMachine.h"

struct FState_Idle : public TSharedFromThis<FState_Idle>, public FStateMachine
{
public:
	FState_Idle() {};
	FState_Idle(UMobaAnimInstance* InMobaAnimInstance, APawn* InOnwer) : FStateMachine(InMobaAnimInstance, InOnwer) {};
	virtual ~FState_Idle() {};

	//MobaAnimInstanceProxy
	virtual void PreUpdate(UMobaAnimInstance* InAnimInstance, float DeltaSeconds) override;
};

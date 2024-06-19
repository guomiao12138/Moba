// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UObject/ObjectMacros.h"
#include "Engine.h"

#define ENUM_EX(t) \
namespace t \
{ \
	FORCEINLINE const UEnum* GetEnumClass()\
	{\
		static const UEnum* enumClass = FindObject<UEnum>(nullptr, TEXT("/Script/Moba." #t), true);\
		return enumClass;\
	}\
	FORCEINLINE FName GetName(t::Type n)\
	{\
		FString name = GetEnumClass()->GetNameStringByValue((int)n);\
		return *name;\
	}\
	FORCEINLINE FName GetFullName(t::Type n)\
	{\
		FString name = GetEnumClass()->GetNameStringByValue((int)n);\
		name = GetEnumClass()->GenerateFullEnumName(*name);\
		return *name;\
	}\
	FORCEINLINE t::Type GetValueByName(FName name)\
	{\
		return (t::Type)GetEnumClass()->GetValueByName(name);\
	}\
	FORCEINLINE FString GetName()\
	{\
		return GetEnumClass()->GetName();\
	}\
}\

UENUM(BlueprintType)
namespace EInputAction
{
	enum Type : int
	{
		//Axis
		MoveForward,
		MoveRight,
		//Action
		ClickPosition,
		Q,
		W,
		E,
		R,
		Max,
	};
}
ENUM_EX(EInputAction);


UENUM(BlueprintType)
namespace ECharacterType
{
	enum Type : int
	{
		Idle,
		WalkRun,
		Skil,
		Max UMETA(Hidden),
	};
}
ENUM_EX(ECharacterType);
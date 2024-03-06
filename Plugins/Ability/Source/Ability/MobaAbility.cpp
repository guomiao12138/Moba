// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbility.h"
#include "MobaAbilityEdGraph.h"

//void UMobaAbility::ProcessEvent(UFunction* Function, void* Parms)
//{
//	checkf(!IsUnreachable(), TEXT("%s  Function: '%s'"), *GetFullName(), *Function->GetPathName());
//	checkf(!FUObjectThreadContext::Get().IsRoutingPostLoad, TEXT("Cannot call UnrealScript (%s - %s) while PostLoading objects"), *GetFullName(), *Function->GetFullName());
//
//#if TOTAL_OVERHEAD_SCRIPT_STATS
//	FBlueprintEventTimer::FScopedVMTimer VMTime;
//#endif // TOTAL_OVERHEAD_SCRIPT_STATS
//
//	// Reject.
//	if (!IsValid(this))
//	{
//		return;
//	}
//
//#if WITH_EDITORONLY_DATA
//	// Cannot invoke script events when the game thread is paused for debugging.
//	if (GIntraFrameDebuggingGameThread)
//	{
//		if (GFirstFrameIntraFrameDebugging)
//		{
//			UE_LOG(LogScriptCore, Warning, TEXT("Cannot call UnrealScript (%s - %s) while stopped at a breakpoint."), *GetFullName(), *Function->GetFullName());
//		}
//
//		return;
//	}
//#endif	// WITH_EDITORONLY_DATA
//
//	if ((Function->FunctionFlags & FUNC_Native) != 0)
//	{
//		int32 FunctionCallspace = GetFunctionCallspace(Function, NULL);
//		if (FunctionCallspace & FunctionCallspace::Remote)
//		{
//			CallRemoteFunction(Function, Parms, NULL, NULL);
//		}
//
//		if ((FunctionCallspace & FunctionCallspace::Local) == 0)
//		{
//			return;
//		}
//	}
//	//else if (Function->Script.Num() == 0)
//	//{
//	//	return;
//	//}
//	checkSlow((Function->ParmsSize == 0) || (Parms != NULL));
//
//#if PER_FUNCTION_SCRIPT_STATS
//	SCOPE_CYCLE_UOBJECT(FunctionScope, Function);
//#endif // PER_FUNCTION_SCRIPT_STATS
//
//	SCOPE_CYCLE_UOBJECT(ContextScope, GVerboseScriptStats ? this : nullptr);
//
//#if LIGHTWEIGHT_PROCESS_EVENT_COUNTER
//	TGuardValue<int32> PECounter(ProcessEventCounter, ProcessEventCounter + 1);
//	CONDITIONAL_SCOPE_CYCLE_COUNTER(STAT_BlueprintTime, IsInGameThread() && ProcessEventCounter == 1);
//#endif

//#if DO_BLUEPRINT_GUARD
//	FBlueprintContextTracker& BlueprintContextTracker = FBlueprintContextTracker::Get();
//	const int32 ProcessEventDepth = BlueprintContextTracker.GetScriptEntryTag();
//	BlueprintContextTracker.EnterScriptContext(this, Function);
//
//	// Only start stat if this is the top level context
//	//CONDITIONAL_SCOPE_CYCLE_COUNTER(STAT_BlueprintTime, IsInGameThread() && BlueprintContextTracker.GetScriptEntryTag() == 1);
//#endif
//
//#if UE_BLUEPRINT_EVENTGRAPH_FASTCALLS
//	// Fast path for ubergraph calls
//	int32 EventGraphParams;
//	if (Function->EventGraphFunction != nullptr)
//	{
//		// Call directly into the event graph, skipping the stub thunk function
//		EventGraphParams = Function->EventGraphCallOffset;
//		Parms = &EventGraphParams;
//		Function = Function->EventGraphFunction;
//
//		// Validate assumptions required for this optimized path (EventGraphFunction should have only been filled out if these held)
//		checkSlow(Function->ParmsSize == sizeof(EventGraphParams));
//		checkSlow(Function->FirstPropertyToInit == nullptr);
//		checkSlow(Function->PostConstructLink == nullptr);
//	}
//#endif
//
//	// Scope required for scoped script stats.
//	{
//		uint8* Frame = NULL;
//#if USE_UBER_GRAPH_PERSISTENT_FRAME
//		if (Function->HasAnyFunctionFlags(FUNC_UbergraphFunction))
//		{
//			Frame = Function->GetOuterUClassUnchecked()->GetPersistentUberGraphFrame(this, Function);
//		}
//#endif
//		FVirtualStackAllocator* VirtualStackAllocator = FBlueprintContext::GetThreadSingleton()->GetVirtualStackAllocator();
//		UE_VSTACK_MAKE_FRAME(ProcessEventBookmark, VirtualStackAllocator);
//		const bool bUsePersistentFrame = (NULL != Frame);
//		if (!bUsePersistentFrame)
//		{
//			Frame = (uint8*)UE_VSTACK_ALLOC_ALIGNED(VirtualStackAllocator, Function->PropertiesSize, Function->GetMinAlignment());
//			// zero the local property memory
//			const int32 NonParmsPropertiesSize = Function->PropertiesSize - Function->ParmsSize;
//			if (NonParmsPropertiesSize)
//			{
//				FMemory::Memzero(Frame + Function->ParmsSize, NonParmsPropertiesSize);
//			}
//		}
//
//		// initialize the parameter properties
//		if (Function->ParmsSize)
//		{
//			FMemory::Memcpy(Frame, Parms, Function->ParmsSize);
//		}
//
//		// Create a new local execution stack.
//		FFrame NewStack(this, Function, Frame, NULL, Function->ChildProperties);
//
//		checkSlow(NewStack.Locals || Function->ParmsSize == 0);
//
//
//
//		// if the function has out parameters, fill the stack frame's out parameter info with the info for those params 
//		if (Function->HasAnyFunctionFlags(FUNC_HasOutParms))
//		{
//			FOutParmRec** LastOut = &NewStack.OutParms;
//			for (FProperty* Property = (FProperty*)(Function->ChildProperties); Property && (Property->PropertyFlags & (CPF_Parm)) == CPF_Parm; Property = (FProperty*)Property->Next)
//			{
//				// this is used for optional parameters - the destination address for out parameter values is the address of the calling function
//				// so we'll need to know which address to use if we need to evaluate the default parm value expression located in the new function's
//				// bytecode
//				if (Property->HasAnyPropertyFlags(CPF_OutParm))
//				{
//					CA_SUPPRESS(6263)
//						FOutParmRec* Out = (FOutParmRec*)UE_VSTACK_ALLOC(VirtualStackAllocator, sizeof(FOutParmRec));
//					// set the address and property in the out param info
//					// note that since C++ doesn't support "optional out" we can ignore that here
//					Out->PropAddr = Property->ContainerPtrToValuePtr<uint8>(Parms);
//					Out->Property = Property;
//
//					// add the new out param info to the stack frame's linked list
//					if (*LastOut)
//					{
//						(*LastOut)->NextOutParm = Out;
//						LastOut = &(*LastOut)->NextOutParm;
//					}
//					else
//					{
//						*LastOut = Out;
//					}
//				}
//			}
//
//			// set the next pointer of the last item to NULL to mark the end of the list
//			if (*LastOut)
//			{
//				(*LastOut)->NextOutParm = NULL;
//			}
//		}
//
//		if (!bUsePersistentFrame)
//		{
//			for (FProperty* LocalProp = Function->FirstPropertyToInit; LocalProp != nullptr; LocalProp = (FProperty*)LocalProp->PostConstructLinkNext)
//			{
//				LocalProp->InitializeValue_InContainer(NewStack.Locals);
//			}
//		}
//
//		// Call native function or UObject::ProcessInternal.
//		const bool bHasReturnParam = Function->ReturnValueOffset != MAX_uint16;
//		uint8* ReturnValueAddress = bHasReturnParam ? ((uint8*)Parms + Function->ReturnValueOffset) : nullptr;
//		Function->Invoke(this, NewStack, ReturnValueAddress);
//
//		if (!bUsePersistentFrame)
//		{
//			// Destroy local variables except function parameters.!! see also UObject::CallFunctionByNameWithArguments
//			// also copy back constructed value parms here so the correct copy is destroyed when the event function returns
//			for (FProperty* P = Function->DestructorLink; P; P = P->DestructorLinkNext)
//			{
//				if (!P->IsInContainer(Function->ParmsSize))
//				{
//					P->DestroyValue_InContainer(NewStack.Locals);
//				}
//				else if (!(P->PropertyFlags & CPF_OutParm))
//				{
//					FMemory::Memcpy(P->ContainerPtrToValuePtr<uint8>(Parms), P->ContainerPtrToValuePtr<uint8>(NewStack.Locals), P->ArrayDim * P->ElementSize);
//				}
//			}
//		}
//	}
//
//#if DO_BLUEPRINT_GUARD
//	BlueprintContextTracker.ExitScriptContext();
//#endif
//}

void UMobaAbility::Activate()
{
	//Super::ProcessEvent(FindFunctionChecked(FName(TEXT("Start"))), NULL);
	if (Graph)
	{
		Graph->BuildNode();
	}
}

void UMobaAbility::AAAA(FName name, int& num)
{
	UE_LOG(LogTemp, Display, TEXT("UMobaAbility UMobaAbilityUMobaAbilityUMobaAbilityUMobaAbilityUMobaAbilityUMobaAbility"));
}

void UMobaAbility::CCCC(UAnimationAsset* asset)
{
}

void UMobaAbility::XXXX()
{
	UE_LOG(LogTemp, Display, TEXT("UMobaAbility UMobaAbilityUMobaAbilityUMobaAbilityUMobaAbilityUMobaAbilityUMobaAbility"));
}

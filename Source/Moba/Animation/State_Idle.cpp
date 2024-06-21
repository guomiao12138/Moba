
#include "State_Idle.h"
#include "MobaAnimInstance.h"

void FState_Idle::PreUpdate(UMobaAnimInstance* InAnimInstance, float DeltaSeconds)
{
	if (InAnimInstance)
	{
		if (InAnimInstance->GetSpeed() > 0.f)
		{
			InAnimInstance->SetChangeState(ECharacterType::WalkRun);
		}
	}
}
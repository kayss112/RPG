// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilities/AbilityTasks/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"
#include"Player/AuraPlayerController.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	bool bIsClient = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsClient) {
		SendMouseCursorData();
	}
	else {

	}
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());

	FHitResult HitResult;
	APlayerController* AuraPlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	AuraPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	
	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = HitResult;
	DataHandle.Add(Data);

	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates()) {
		ValidData.Broadcast(DataHandle);
	}
}

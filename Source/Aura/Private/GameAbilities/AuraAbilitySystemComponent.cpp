// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilities/AuraAbilitySystemComponent.h"
#include "GameAbilities/Abilities/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::ClientEffectApplied);
}

void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer  TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilitise)
{
	for (TSubclassOf<UGameplayAbility> Abilities : StartupAbilitise) {
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Abilities, 1);
		if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability)) {
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartUpInputTag);
			GiveAbility(AbilitySpec);
			//GiveAbilityAndActivateOnce(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) { return;}

	for(FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities()) {
		if(AbilitySpec.DynamicAbilityTags.HasTag(InputTag)) {
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive()) {
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) { return; }

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities()) {
		if (AbilitySpec.DynamicAbilityTags.HasTag(InputTag)) {
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}
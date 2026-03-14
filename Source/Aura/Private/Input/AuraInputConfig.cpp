// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"
#include "EnhancedInputLibrary.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FAuraInputAction& Attribute : AbilityInputActions) {
		if (InputTag.MatchesTagExact(Attribute.InputTag)) {
			return Attribute.InputAction;
		}
	}
	return nullptr;
}

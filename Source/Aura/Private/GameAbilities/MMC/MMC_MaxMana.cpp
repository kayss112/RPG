// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilities/MMC/MMC_MaxMana.h"
#include "GameAbilities/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTag = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTag = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters AggregatorEvaluationParams;
	AggregatorEvaluationParams.SourceTags = SourceTag;
	AggregatorEvaluationParams.TargetTags = TargetTag;

	float Intelligence=0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, AggregatorEvaluationParams, Intelligence);
	Intelligence = FMath::Max(0.f, Intelligence);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	int32 Level = CombatInterface->GetPlayerLevel();

	return 50.5f + 2.f * Intelligence + 5.f * Level;
}

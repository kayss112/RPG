// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include <GameAbilities/AuraAbilitySystemComponent.h>

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);


}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

FVector AAuraCharacterBase::GetCombatSocketLocation()
{
	check(weapon);
	FVector ans = weapon->GetSocketLocation(WeaponTipSocketName);
	return ans;
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
void AAuraCharacterBase::InitAbilityActorInfo() {

}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffect);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffect, level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitializedDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AAuraCharacterBase::AddCharacterAbilities()
{
	UAuraAbilitySystemComponent* ASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) { return; }
	ASC->AddCharacterAbilities(StartupAbilitise);
}




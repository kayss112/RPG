// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"
#include "GameAbilities/AuraAbilitySystemComponent.h"
#include "GameAbilities/AuraAttributeSet.h"
#include "GameAbilities/AuraAbilitySystemLibrary.h"
#include "UI/Widget/AuraUserWidget.h"
#include "Components/WidgetComponent.h"
#include"Aura/Aura.h"
AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBarWidgetComponent->SetupAttachment(GetRootComponent());

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}
void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	weapon->SetRenderCustomDepth(true);
	weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHightlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	weapon->SetRenderCustomDepth(false);
}

int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	
	if (UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBarWidgetComponent->GetUserWidgetObject())) {
		AuraUserWidget->SetWidgetController(this);
	}

	UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);
	if (AuraAS) {
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {
			OnHealthChanged.Broadcast(Data.NewValue);
		});
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});
		OnHealthChanged.Broadcast(AuraAS->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
	}
}

void AAuraEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializedDefaultAttributes();
}

void AAuraEnemy::InitializedDefaultAttributes() const
{
	UAuraAbilitySystemLibrary::InitalizeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

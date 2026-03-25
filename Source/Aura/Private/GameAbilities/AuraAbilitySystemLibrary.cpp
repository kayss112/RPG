// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilities/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/AuraHUD.h"
#include "GameAbilities/Data/CharacterClassInfo.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include <Player/AuraPlayerState.h>
#include <Game/AuraGameModeBase.h>
UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0)) {
        if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD())) {
            AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
            UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
            UAttributeSet* AS = PS->GetAttributeSet();
            const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
            return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
        }
    }
    return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0)) {
        if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD())) {
            AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
            UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
            UAttributeSet* AS = PS->GetAttributeSet();
            const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
            return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
        }
    }
    return nullptr;
}

void UAuraAbilitySystemLibrary::InitalizeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float level, UAbilitySystemComponent* ASC)
{
	AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
    if (AuraGameMode == nullptr) { return; }

    AActor* AvatarActor = ASC->GetAvatarActor();

    UCharacterClassInfo* CharacterClassInfo = AuraGameMode->CharacterClassInfo;
    FCharacaterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

    FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
    PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
    const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimartyAttributes, level, PrimaryAttributesContextHandle);
    ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

    FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
    SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
    const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, level, SecondaryAttributesContextHandle);
    ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

    FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
    VitalAttributesContextHandle.AddSourceObject(AvatarActor);
    const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, level, VitalAttributesContextHandle);
    ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

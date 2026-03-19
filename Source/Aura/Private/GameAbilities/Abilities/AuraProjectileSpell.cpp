// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilities/Abilities/AuraProjectileSpell.h"
#include "Actor/AuraProjectile.h"
#include <Interaction/CombatInterface.h>

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile()
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) { return; }


	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface) {
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		//TODO: Set rotation of the projectile to be the same as the player's control rotation

		AAuraProjectile* AuraProjectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, GetAvatarActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TODO: Give the projectile a GameplayEffect
		AuraProjectile->FinishSpawning(SpawnTransform);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay()override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const struct FInputActionValue& InputActionValue);
	void CursorTrce();
	/*这边视频中为注释过的代码，但是由于报错，修改为下面代码*/
	//TObjectPtr<IEnemyInterface> LastActor;
	//TObjectPtr<IEnemyInterface> ThisActor;
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
};

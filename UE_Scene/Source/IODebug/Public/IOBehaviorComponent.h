// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IOBehaviorComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeParamDelegate, float, ParamValue);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IODEBUG_API UIOBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UIOBehaviorComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeParamChanged(FString NParamName, float NParamValue);
public:	
	UPROPERTY(BlueprintAssignable)
	FOnChangeParamDelegate OnParamChanged;
	UPROPERTY(EditDefaultsOnly)
	FString ParamName;
	UPROPERTY(EditDefaultsOnly)
	double ParamValue;
		
	UFUNCTION(BlueprintCallable)
	void UpdateParam(double NewValue);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

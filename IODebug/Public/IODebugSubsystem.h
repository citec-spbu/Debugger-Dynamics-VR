
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "IODebugSubsystem.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMultiDynamicDelegate, FString, ParamName, float, ParamValue);

class FileProtocol;
/**
 *  This subsystem is a debug port for the dynamic behavior visualization object.
 */
UCLASS()
class IODEBUG_API UIODebugSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UPROPERTY(BlueprintAssignable)
	FMultiDynamicDelegate OnParamChanged;

	/**
	* Change param and send it to IOProtocol
	**/
	UFUNCTION(BlueprintCallable)
	bool ChangeParam(FString Param, double Value);
	UFUNCTION(BlueprintCallable)
	bool AddParam(FString Param, double Value);
	UFUNCTION(BlueprintCallable)
	void SendAllParams();
	/**
	* Set new timer with "Amount" updates per second
	**/
	UFUNCTION(BlueprintCallable)
	void SetUPS(int32 Amount);
	UPROPERTY(EditDefaultsOnly)
	int32 UpdatesPerSecond = 10;
private:	
	FTimerHandle TimerHandle;
	void TimerLoop();

	FileProtocol* IOHandler;	
	TMap<FString, double> ParamsMap;
};

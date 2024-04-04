

#include "IOBehaviorComponent.h"
#include "IODebugSubsystem.h"

UIOBehaviorComponent::UIOBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UIOBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	auto* IODebugSubsystemHandler = GetWorld()->GetSubsystem<UIODebugSubsystem>();
	if (IODebugSubsystemHandler)
	{
		IODebugSubsystemHandler->OnParamChanged.AddDynamic(this, &UIOBehaviorComponent::TakeParamChanged);
	}
}	


void UIOBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UIOBehaviorComponent::UpdateValue(double NewValue)
{
	auto* IODebugSubsystemHandler = GetWorld()->GetSubsystem<UIODebugSubsystem>();
	if (IODebugSubsystemHandler) 
	{
		IODebugSubsystemHandler->ChangeParam(ParamName, NewValue);
	}
}

void UIOBehaviorComponent::TakeParamChanged(FString NParamName, float NParamValue)
{
	if (ParamName == NParamName)
	{
		OnParamChanged.Broadcast(NParamValue);
	}
}

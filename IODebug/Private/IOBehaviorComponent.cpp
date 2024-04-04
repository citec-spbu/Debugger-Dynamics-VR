

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
	if (IODebugSubsystemHandler && !ParamName.IsEmpty())
	{
		IODebugSubsystemHandler->AddParam(ParamName, ParamValue);
		IODebugSubsystemHandler->OnParamChanged.AddDynamic(this, &UIOBehaviorComponent::TakeParamChanged);
	}
}	


void UIOBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UIOBehaviorComponent::UpdateParam(double NewValue)
{
	auto* IODebugSubsystemHandler = GetWorld()->GetSubsystem<UIODebugSubsystem>();
	if (IODebugSubsystemHandler && !ParamName.IsEmpty())
	{
		ParamValue = NewValue;
		IODebugSubsystemHandler->ChangeParam(ParamName, ParamValue);
	}
}

void UIOBehaviorComponent::TakeParamChanged(FString NParamName, float NParamValue)
{
	if (ParamName == NParamName)
	{
		ParamValue = NParamValue;
		OnParamChanged.Broadcast(NParamValue);
	}
}

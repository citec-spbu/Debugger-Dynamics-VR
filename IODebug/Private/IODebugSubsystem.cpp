// Fill out your copyright notice in the Description page of Project Settings.


#include "IODebugSubsystem.h"
#include "FileProtocol.h"


void UIODebugSubsystem::Initialize(FSubsystemCollectionBase& Collection) 
{

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	FString MyConfigDirectory = FPaths::GameDevelopersDir();
	FString InputPath = MyConfigDirectory + "/input.txt";
	FString OutputPath = MyConfigDirectory + "/output.txt";

	if (!FileManager.FileExists(*InputPath)) 
	{
		auto handle = FileManager.OpenWrite(*InputPath);
		delete handle;
	}
	if (!FileManager.FileExists(*OutputPath))
	{
		auto handle = FileManager.OpenWrite(*OutputPath);
		delete handle;
	}
	IOHandler = new FileProtocol(TCHAR_TO_UTF8(*InputPath), TCHAR_TO_UTF8(*OutputPath));

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle, // handle to cancel timer at a later time
		this, // the owning object
		&UIODebugSubsystem::TimerLoop, // function to call on elapsed
		1.0 / UpdatesPerSecond, // float delay until elapsed
		true); // looping true
}

void UIODebugSubsystem::Deinitialize() 
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	delete IOHandler;
	IOHandler = nullptr;
}

void UIODebugSubsystem::TimerLoop()
{
	if (IOHandler->getStatus())
	{
		auto List = IOHandler->exchange();
		for (auto& value : List)
		{				
			OnParamChanged.Broadcast(UTF8_TO_TCHAR(value.first.c_str()), value.second);
		}
	}
}

void UIODebugSubsystem::SetUPS(int32 Amount)
{
	UpdatesPerSecond = Amount;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle, // handle to cancel timer at a later time
		this, // the owning object
		&UIODebugSubsystem::TimerLoop, // function to call on elapsed
		1.0 / UpdatesPerSecond, // float delay until elapsed
		true); // looping true
}

void UIODebugSubsystem::ChangeParam(FString Param, double Value)
{
	IOHandler->changeParam(TCHAR_TO_UTF8(*Param), Value);
}
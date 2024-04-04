// Fill out your copyright notice in the Description page of Project Settings.


#include "IODebugSubsystem.h"
#include "FileProtocol.h"


void UIODebugSubsystem::Initialize(FSubsystemCollectionBase& Collection) 
{

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	FString MyDevelopDirectory = FPaths::GameDevelopersDir();
	FString InputPath = MyDevelopDirectory + "/input.txt";
	FString OutputPath = MyDevelopDirectory + "/output.txt";

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
		TimerHandle,
		this, 
		&UIODebugSubsystem::TimerLoop, 
		1.0 / UpdatesPerSecond,
		true); 
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
			if (value.first == " ") // Request all params '?'
			{
				SendAllParams();
			}
			else 
			{
				OnParamChanged.Broadcast(UTF8_TO_TCHAR(value.first.c_str()), value.second);
			}
		}
	}
}

void UIODebugSubsystem::SetUPS(int32 Amount)
{
	UpdatesPerSecond = Amount;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&UIODebugSubsystem::TimerLoop,
		1.0 / UpdatesPerSecond,
		true);
}

bool UIODebugSubsystem::ChangeParam(FString Param, double Value)
{
	if (ParamsMap.Contains(Param))
	{
		ParamsMap[Param] = Value;
		IOHandler->changeParam(TCHAR_TO_UTF8(*Param), Value);
		return true;
	}
	return false;
}

bool UIODebugSubsystem::AddParam(FString Param, double Value)
{
	if (ParamsMap.Contains(Param))
	{
		return false;
	}
	ParamsMap.Add(Param, Value);
	IOHandler->changeParam(TCHAR_TO_UTF8(*Param), Value);
	return true;
}

void UIODebugSubsystem::SendAllParams()
{
	for (auto It = ParamsMap.CreateConstIterator(); It; ++It)
	{
		IOHandler->changeParam(TCHAR_TO_UTF8(*It.Key()), It.Value());
	}
}


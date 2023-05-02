// Fill out your copyright notice in the Description page of Project Settings.


#include "VoicePeakFunctionLibrary.h"

#include "Components/AudioComponent.h"

#if WITH_EDITORONLY_DATA
#include "Editor.h"
#endif // WITH_EDITORONLY_DATA

URunProcessAsyncFunction::URunProcessAsyncFunction(const FObjectInitializer& ObjectInitializer)
{
	
}

URunProcessAsyncFunction* URunProcessAsyncFunction::RunProcessAsyncFunction(UObject* WorldContextObject, FString InExePath, FString InArgs)
{
	URunProcessAsyncFunction* Action = NewObject<URunProcessAsyncFunction>();
	Action->RegisterWithGameInstance(WorldContextObject);
	Action->ExePath = InExePath;
	Action->Args = InArgs;
	return Action;
}

void URunProcessAsyncFunction::Activate()
{
	ProcHandle =FPlatformProcess::CreateProc(
		*ExePath, *Args, true, false,
		false, nullptr, 0, nullptr, nullptr);

#if WITH_EDITOR
	GEditor->GetTimerManager()->SetTimer(TimerHandle,this,&URunProcessAsyncFunction::OnCheckProcess,0.1f,true, 0.1f);
#else
	GWorld->GetTimerManager().SetTimer(TimerHandle,this,&URunProcessAsyncFunction::OnCheckProcess,0.1f,true, 0.1f);	
#endif
	
}
	

void URunProcessAsyncFunction::OnCheckProcess()
{
	if (ProcHandle.IsValid() && FPlatformProcess::IsProcRunning(ProcHandle))
	{
		return;
	}

#if WITH_EDITOR
	GEditor->GetTimerManager()->ClearTimer(TimerHandle);
#else
	GWorld->GetTimerManager().ClearTimer(TimerHandle);
#endif
	
	SetReadyToDestroy();
	Completed.Broadcast();
}

URunProcessAsyncFunction* URunVoicePeakProcess::RunVoicePeakProcess(UObject* WorldContextObject, FString VoicePeakExePath,
	FString Script, FString OutFilePath, EVoicePeakNarrator Narrator, FVoicePeakEmotion Emotion, int32 Speed, int32 Pitch)
{
	URunProcessAsyncFunction* Action = NewObject<URunProcessAsyncFunction>();
	Action->RegisterWithGameInstance(WorldContextObject);
	Action->ExePath = VoicePeakExePath;
	
	FString CommandLine = FString::Printf(TEXT(" -s \"%s\" -o \"%s\" "), *Script, *OutFilePath);
	CommandLine += FString::Printf(TEXT(" -n \"%s\" "), *(UEnum::GetDisplayValueAsText(Narrator).ToString()));
	CommandLine += FString::Printf(TEXT(" -e \"happy=%d,sad=%d,angry=%d,fun=%d\" "), Emotion.Happy, Emotion.Sad, Emotion.Angry, Emotion.Fun);
	CommandLine += FString::Printf(TEXT(" --speed \"%d\" --pitch \"%d\" "), Speed, Pitch);
	
	Action->Args = CommandLine;
	return Action;
}


#if WITH_EDITOR
void UVoicePeakFunctionLibrary::PlayEditorSound(USoundBase* InSound)
{
	GEditor->PlayEditorSound(InSound);
}

void UVoicePeakFunctionLibrary::StopEditorSound()
{
	if(UAudioComponent* PreviewAudioComponent = GEditor->GetPreviewAudioComponent())
	{
		PreviewAudioComponent->Stop();
	}
}

UAudioComponent* UVoicePeakFunctionLibrary::GetEditorPreviewAudioComponent()
{
	return GEditor->GetPreviewAudioComponent();
}

#endif
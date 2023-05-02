// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VoicePeakFunctionLibrary.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCompletedProcessAsyncFunction);

/**
 * 
 */
UCLASS()
class VOICEPEAKUE5_API URunProcessAsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString ExePath;
	UPROPERTY()
	FString Args;

	UPROPERTY(BlueprintAssignable)
	FCompletedProcessAsyncFunction Completed;

private:
	FTimerHandle TimerHandle;
	FProcHandle ProcHandle;
	
public:
	URunProcessAsyncFunction(const FObjectInitializer& ObjectInitializer);


	UFUNCTION(BlueprintCallable,meta = ( WorldContext = "WorldContextObject",BlueprintInternalUseOnly = "true", DisplayName = "Run Process Async"))
	static URunProcessAsyncFunction* RunProcessAsyncFunction(UObject* WorldContextObject, FString InExePath, FString InArgs);
	
	virtual void Activate() override;
	void OnCheckProcess();
};

UENUM(BlueprintType)
enum class EVoicePeakNarrator : uint8
{
	JapaneseMale1 UMETA(DisplayName="Japanese Male 1"),
	JapaneseMale2 UMETA(DisplayName="Japanese Male 2"),
	JapaneseMale3 UMETA(DisplayName="Japanese Male 3"),
	JapaneseFemale1 UMETA(DisplayName="Japanese Female 1"),
	JapaneseFemale2 UMETA(DisplayName="Japanese Female 2"),
	JapaneseFemale3 UMETA(DisplayName="Japanese Female 3"),
	JapaneseFemaleChild UMETA(DisplayName="Japanese Female Child"),
};

USTRUCT(BlueprintType)
struct FVoicePeakEmotion
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))
	int32 Happy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))
	int32 Fun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))
	int32 Angry;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))
	int32 Sad;
};

UCLASS()
class VOICEPEAKUE5_API URunVoicePeakProcess : public URunProcessAsyncFunction
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable,meta = ( WorldContext = "WorldContextObject",BlueprintInternalUseOnly = "true"))
	static URunProcessAsyncFunction* RunVoicePeakProcess(UObject* WorldContextObject, FString VoicePeakExePath, 
		FString Script, FString OutFilePath, EVoicePeakNarrator Narrator, FVoicePeakEmotion Emotion, int32 Speed, int32 Pitch);
	
};
	
/**
 * 
 */
UCLASS()
class VOICEPEAKUE5_API UVoicePeakFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

#if WITH_EDITOR
	UFUNCTION(BlueprintCallable)
	static void PlayEditorSound( USoundBase* InSound );
	
	UFUNCTION(BlueprintCallable)
	static void StopEditorSound();
	
	UFUNCTION(BlueprintCallable)
	static UAudioComponent* GetEditorPreviewAudioComponent();
#endif
};

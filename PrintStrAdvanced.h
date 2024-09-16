// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PrintStrAdvanced.generated.h"

UENUM(BlueprintType)
enum class EStrColor : uint8
{
	Red,
	Green,
	Yellow,
	Blue,
};

UCLASS()
class PRINTSTR_API UPrintStrAdvanced : public UObject
{
	GENERATED_BODY()
public:

	//!
	//! @param Actor The Actor or Blueprint context from which the print operation originates. This helps identify the source of the print operation.
	//! @param Text The text string that you want to print or display.
	//! @param color The color in which the text will be displayed. This is an enum of type `EStrColor`.
	//! @param FromActor Whether to print the text from the actor's perspective or context. This is a boolean flag.
	//! @param PrintToLogs Whether to print the text to the output log. This is a boolean flag.
	//! @param PrintToScreen Whether to print the text to the screen. This is a boolean flag.
	//! @param TimeToDisplay The duration in seconds for which the text will be displayed on the screen (if `PrintToScreen` is true). Default is 2 seconds.
	//! @param Key An optional key that can be used to uniquely identify the printed text, which can be useful for updating or removing specific texts. Default is "-1".
	UFUNCTION(BlueprintCallable, Category = "PrintStringAdvanced")

	static void PrintStringAdvanced(AActor* Actor, const FString& Text, EStrColor color, bool FromActor, bool PrintToLogs, bool
	                                PrintToScreen, float TimeToDisplay = 2.f, FName Key = "-1");
};

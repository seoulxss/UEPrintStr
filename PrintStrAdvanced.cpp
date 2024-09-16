// Fill out your copyright notice in the Description page of Project Settings.
#include "PrintStrAdvanced.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"

//Message holder so we dont spam it
static FString LastLoggedMessage = TEXT("");
void UPrintStrAdvanced::PrintStringAdvanced(AActor* Actor, const FString& Text, EStrColor color, bool FromActor, bool PrintToLogs, bool
                                            PrintToScreen, float TimeToDisplay, FName Key)
{
#if !UE_BUILD_SHIPPING
    //Check if the key is -1 and generate random numbers then, to have unique keys
    if (Key.IsNone() or Key == "-1")
    {
        // Generate a random FName
        Key = FName(*FString::Printf(TEXT("%d"), FMath::Rand()));
    }

    //Pre defines
    FColor col;
    FString finalString;

    //Reserve 50 chars
    finalString.Reserve(50);

    switch (color)
    {
    case EStrColor::Blue:
        col = FColor::Blue;
        finalString.Append(TEXT("[Information] "));
        break;

    case EStrColor::Green:
        col = FColor::Green;
        finalString.Append(TEXT("[Success] "));
        break;

    case EStrColor::Red:
        col = FColor::Red;
        finalString.Append(TEXT("[Failure] "));
        break;

    case EStrColor::Yellow:
        col = FColor::Yellow;
        finalString.Append(TEXT("[ProgressInfo] "));
        break;

    default:
        col = FColor::White;
        break;
    }

    if (FromActor)
    {
        AActor* MyActor = Cast<AActor>(Actor);
        if (Actor)
        {
            //Add the BP name
            finalString.Append(TEXT("[")).Append(MyActor->GetClass()->GetFName().ToString()).Append(TEXT("] : "));
            //finalString.Append(TEXT("[")).Append(MyActor->GetFName().ToString()).Append(TEXT("] : 
        }
    }

    //Add final text to the end
    finalString.Append(Text);

    // Add the message on screen
    if (GEngine != nullptr && PrintToScreen == true)
    {
        GEngine->AddOnScreenDebugMessage(FCString::Atoi(*Key.ToString()), TimeToDisplay, col, finalString);
    }

    // Log only if PrintToLogs is true and the message is new
    if (PrintToLogs && finalString != LastLoggedMessage)
    {
        //Another switch for the LOG
        switch (color)
        {
        case EStrColor::Blue:
            UE_LOG(LogTemp, Type::Display, TEXT("%s"), *finalString);
            break;

        case EStrColor::Green:
            UE_LOG(LogTemp, Type::All, TEXT("%s"), *finalString);
            break;

        case EStrColor::Red:
            UE_LOG(LogTemp, Type::Error, TEXT("%s"), *finalString);
            break;

        case EStrColor::Yellow:
            UE_LOG(LogTemp, Type::Log, TEXT("%s"), *finalString);
            break;

        default:

            break;
        }

        //Set the last logged message
        LastLoggedMessage = finalString;
    }
#endif
}
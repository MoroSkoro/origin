// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Player/LMAPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

ALMAPlayerController::ALMAPlayerController()//FObjectInitializer& ObjectInitializer)
{
	/* static ConstructorHelpers::FClassFinder<UUserWidget> DeathMenu(TEXT(
		"/Game/LeaveMeAlone/Widgets/UI/WBP_Death")); /// Script/UMGEditor.WidgetBlueprint'/Game/LeaveMeAlone/Widgets/UI/WBP_Death.WBP_Death'
	if (!ensure(DeathMenu.Class != nullptr))
		return;
	DeathMenuWidgetClass = DeathMenu.Class;*/
}

void ALMAPlayerController::BeginPlay() {
	Super::BeginPlay();

	//SetInputMode(FInputModeGameOnly());
	//bShowMouseCursor = false;
}

void ALMAPlayerController::BeginSpectatingState()
{
	SetControlRotation(FRotator(-75.0f, 0.0f, 0.0f));
	Super::BeginSpectatingState();
}

void ALMAPlayerController::Init()
{
	//UE_LOG(LogTemp, Warning, TEXT("Founded class DeathMenu %s"), *DeathMenuWidgetClass->GetClass());
}
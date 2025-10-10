


#include "MyController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Slate/MySlate.h"

AMyController::AMyController()
{

}

void AMyController::BeginPlay()
{
	bShowMouseCursor = true;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	SetInputMode(InputMode);
}

void AMyController::OpenChat(const FInputActionValue& Value)
{
	MyUI->OpenChatting();
}

void AMyController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(UIMapping, 0);
		Subsystem->AddMappingContext(CharacterMapping, 0);
	}

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent))
	{
		Input->BindAction(ChatAction, ETriggerEvent::Triggered, this, &AMyController::OpenChat);
	}

	MyUI = SNew(SMySlate);
	GEngine->GameViewport->AddViewportWidgetContent(MyUI.ToSharedRef(), 10);
}
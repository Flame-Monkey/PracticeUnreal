


#include "MyController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Slate/MySlate.h"

#include "Network/ChattingClient.h"

AMyController::AMyController():
	Client()
{

}

void AMyController::BeginPlay()
{
	bShowMouseCursor = true;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	SetInputMode(InputMode);
	Client.Init();
	Client.Connect("127.0.0.1", 5000);
	Client.Login("Jin");
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
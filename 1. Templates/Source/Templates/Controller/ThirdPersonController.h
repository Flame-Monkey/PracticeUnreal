

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThirdPersonController.generated.h"

/**
 * 
 */

class UInputMappingContext;

UCLASS()
class TEMPLATES_API AThirdPersonController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;
};

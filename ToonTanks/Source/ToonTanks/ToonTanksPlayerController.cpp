#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerInputState(const bool Enable)
{
	if (Enable)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = Enable;
}
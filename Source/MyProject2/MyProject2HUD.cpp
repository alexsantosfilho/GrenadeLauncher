// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MyProject2.h"
#include "MyProject2HUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

AMyProject2HUD::AMyProject2HUD()
{
	// Set the crosshair texture
	//static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("Texture2D'/Game/mira/mira.mira'"));
	//CrosshairTex = CrosshiarTexObj.Object;

	//static ConstructorHelpers::FObjectFinder<UFont>
	//	Font(TEXT("Font'/Engine/EngineFonts/RobotoDistanceField.RobotoDistanceField'"));
	//if (Font.Succeeded()) {
	//	HUDFont = Font.Object;
	//}

	//	static ConstructorHelpers::FObjectFinder<UTexture2D>
	//	Texture(TEXT("Texture2D'/Game/Green_Texture.Green_Texture'"));
	//if (Texture.Succeeded()) {
	//MyTexture = Texture.Object;
	//}
	//static ConstructorHelpers::FObjectFinder<UTexture2D>
	//Texture2(TEXT("Texture2D'/Game/Green_Texture.Green_Texture'"));
	//if (Texture2.Succeeded()) {
	//MyTexture2 = Texture2.Object;
	//}
	//ConstructorHelpers::FObjectFinder<UTexture2D>
	//	PotionTexture(TEXT("Texture2D'/Game/IconHPotionGreater.IconHPotionGreater'"));
	//if (PotionTexture.Succeeded()) {
	//	Potion = PotionTexture.Object;
	//}

	//ConstructorHelpers::FObjectFinder<UTexture2D>
	//	LogoTexture(TEXT("Texture2D'/Game/trasparente128.trasparente128'"));
	//if (LogoTexture.Succeeded()) {
	//	Logo = LogoTexture.Object;
	//}

}


void AMyProject2HUD::DrawHUD()
{
	Super::DrawHUD();


	// Draw very simple crosshair

	// find center of the Canvas
	//const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	//const FVector2D CrosshairDrawPosition((Center.X),
	//(Center.Y));

	// draw the crosshair
	//FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	//TileItem.BlendMode = SE_BLEND_Translucent;
	//Canvas->DrawItem(TileItem);





	//FVector2D ScreenDimensions = FVector2D(Canvas->SizeX,
	//	Canvas->SizeY);

	//AMyProject2Character* MyProject2Character = Cast<AMyProject2Character>(
	//UGameplayStatics::GetPlayerPawn(this, 0));

	//FString ColetavelLifeString = FString::Printf(TEXT("ColetavelLife: %d"),
	//	MyCharacter->GetColetavel());
	//	DrawText(ColetavelLifeString, FColor::Red, 50, 50, HUDFont);

	//FString ColetavelLifeString = FString::Printf(TEXT("Life: %d"),
	//MyProject2Character->GetColetavelLife());
	//DrawText(ColetavelLifeString, FColor::Green, 20, 40, HUDFont);


	//DrawTextureSimple(Potion, ScreenDimensions.X - Potion->GetSizeX() * 2,
	//	50, 1.0f, false);

	//FString PotionAmount = FString::Printf(TEXT("X %d"), MyProject2Character->GetInventory().Num());
	//DrawText(PotionAmount, FColor::Red, ScreenDimensions.X - Potion->GetSizeX(),
	//	50, HUDFont);



	//DrawTextureSimple(Logo, ScreenDimensions.X - Potion->GetSizeX() * 2,
	//	10, 1.0f, false);


	//DrawTextureSimple(MyTexture, 50, 50, 1.0f, false);

	//	DrawTexture(MyTexture, 200, 50, MyProject2Character->GetColetavelLife() * 35,
	//	MyTexture->GetSizeY(), 0, 0, MyProject2Character->GetColetavelLife() * 4,
	//	MyTexture->GetSizeY(), FLinearColor::White,
	//	EBlendMode::BLEND_Translucent, 1.0f, false, 0.0f,
	//	FVector2D::ZeroVector);



	//DrawTexture(MyTexture2, 20, 70, MyProject2Character->GetColetavelLife() * 35,
	//MyTexture2->GetSizeY(), 0, 0, MyProject2Character->GetColetavelLife() * 4,
	//MyTexture2->GetSizeY(), FLinearColor::White,
	//EBlendMode::BLEND_Translucent, 1.0f, false, 0.0f,
	//FVector2D::ZeroVector);
}


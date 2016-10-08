// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class RPGPROJ_API SMainCharacterHUD : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainCharacterHUD)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};

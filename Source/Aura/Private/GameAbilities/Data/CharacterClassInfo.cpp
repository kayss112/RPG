// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilities/Data/CharacterClassInfo.h"

FCharacaterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass) const
{
	return CharacterClassInfomation.FindChecked(CharacterClass);
}

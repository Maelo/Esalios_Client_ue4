// Fill out your copyright notice in the Description page of Project Settings.
//Code inspired from https://forums.unrealengine.com/community/community-content-tools-and-tutorials/105-saxonrahs-tutorial-thread-random-maze-generation-solving/page2?47-SaxonRahs-Tutorial-Thread-Random-Maze-Generation-amp-Solving=&viewfull=1
//Thanks!

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Grid.generated.h"

USTRUCT()
struct FGridRow
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FString> Columns;

	void AddNewColumn()
	{
		Columns.Add("");
	}

	//default properties
	FGridRow()
	{

	}
};

/**
 * 
 */
class ESCAPEFTALIENS_API Grid
{
public:
	Grid() {};
	~Grid() {};

	UPROPERTY()
	TArray<FGridRow> Rows;

	void AddNewRow()
	{
		Rows.Add(FGridRow());
	}

	void AddUninitialized(const int32 RowCount, const int32 ColCount)
	{
		//Add Rows
		for (int32 v = 0; v < RowCount; v++)
		{
			AddNewRow();
		}

		//Add Columns
		for (int32 v = 0; v < RowCount; v++)
		{
			for (int32 b = 0; b < ColCount; b++)
			{
				Rows[v].AddNewColumn();
			}
		}
	}
};

#include "../../include/solve/Sort.h"

Grid Sort(Grid Datagrid)     
{
	Datagrid->horizontally->coordinates = QuickSort(Datagrid->horizontally->coordinates, 0, Datagrid->horizontally->words_count-1);
	Datagrid->vertically->coordinates = QuickSort(Datagrid->vertically->coordinates, 0, Datagrid->vertically->words_count-1);
    return Datagrid;
}

Coordinates QuickSort(Coordinates Coordinates, int Up, int Down)
{
	int start, end;
	start = Up;
	end = Down;

	while (Up < Down)
	{
		while (Coordinates[Up].length >= Coordinates[Down].length && Up < Down)
			Down--;
	
		if (Up != Down)
		{
			Swap(&Coordinates[Up], &Coordinates[Down]);
			Up++;
		}

		while (Coordinates[Up].length >= Coordinates[Down].length && Up < Down)
			Up++;

		if (Up != Down)
		{
			Swap(&Coordinates[Up], &Coordinates[Down]);
			Down--;
		}
	}
	if (start < Up-1)
		Coordinates = QuickSort(Coordinates, start, Up-1);
	if (end > Down+1)
		Coordinates = QuickSort(Coordinates, Down+1, end);	
	return Coordinates;	
}

void Swap(Coordinates Coordinates1, Coordinates Coordinates2)
{
	struct GridCOORDINATES temp;

    temp.length = Coordinates1->length;
    temp.word_possibilities = Coordinates1->word_possibilities;
    temp.start_row = Coordinates1->start_row;
    temp.start_col = Coordinates1->start_col;
    temp.end_row = Coordinates1->end_row;
    temp.end_col = Coordinates1->end_col;
	temp.flag = Coordinates1->flag;
	temp.solution = Coordinates1->solution;
	temp.intersections = Coordinates1->intersections;

    Coordinates1->length = Coordinates2->length;
    Coordinates1->word_possibilities = Coordinates2->word_possibilities;
    Coordinates1->start_row = Coordinates2->start_row;
    Coordinates1->start_col = Coordinates2->start_col;
    Coordinates1->end_row = Coordinates2->end_row;
    Coordinates1->end_col = Coordinates2->end_col;
	Coordinates1->flag = Coordinates2->flag;
	Coordinates1->solution = Coordinates2->solution;
	Coordinates1->intersections = Coordinates2->intersections;

    Coordinates2->length = temp.length;
    Coordinates2->word_possibilities = temp.word_possibilities;
    Coordinates2->start_row = temp.start_row;
    Coordinates2->start_col = temp.start_col;
    Coordinates2->end_row = temp.end_row;
    Coordinates2->end_col = temp.end_col;
	Coordinates2->flag = temp.flag;
	Coordinates2->solution = temp.solution;
	Coordinates2->intersections = temp.intersections;
}
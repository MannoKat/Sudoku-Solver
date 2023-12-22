#pragma once

#include "sudoku.h"
typedef struct HiddenPair_impl 
{
    Cell *p_cell1;
    Cell *p_cell2;
    int value1;
    int value2;
} HiddenPair;

int hidden_pairs(SudokuBoard *p_board);
void find_hidden_pairs(Cell **p_cells, HiddenPair *p_hidden_pairs, int *p_counter);
int find_hidden_pairs_values(Cell **p_cells, int *hidden_pairs_values);
int overlaps_hidden_pairs(HiddenPair *p_hidden_pairs, int counter);

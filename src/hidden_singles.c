#include <stdbool.h>
#include "hidden_singles.h"

int find_hidden_single_values(Cell **p_cells, int *hidden_single_values) {
    int unique_candidates = 0;
    int the_array_of_hidden_single_values[BOARD_SIZE]={0};
    // Count the occurrences of candidates in the row, avoiding duplicates
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (p_cells[i]->num_candidates > 1) {
            int *candidates = get_candidates(p_cells[i]);
            for (int j = 0; j < p_cells[i]->num_candidates; ++j) {
                int candidate = candidates[j];
                the_array_of_hidden_single_values[candidate - 1]++;
            }
            free(candidates);
        }
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (the_array_of_hidden_single_values[i] == 1) {
                hidden_single_values[unique_candidates++]=i + 1;
        }   
    }

    return unique_candidates;
}

void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles, int *p_counter) {
    int hidden_single_values[BOARD_SIZE];
    for (int i = 0; i < find_hidden_single_values(p_cells, hidden_single_values); ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
           if (is_candidate(p_cells[j], hidden_single_values[i])) {
                HiddenSingle hidden_singles_object;
                hidden_singles_object.value = hidden_single_values[i];
                hidden_singles_object.p_cell = p_cells[j];
                p_hidden_singles[(*p_counter)++] = hidden_singles_object;
            }
        }
    }
}

int overlaps_candidates(HiddenSingle *p_hidden_singles, int *counter) {
    int overlap = *counter;

    for (int i = 0; i < *counter; ++i) {
        int not_overlap = 0;
        Cell *hidden_single_cell = p_hidden_singles[i].p_cell;
        int *candidates = get_candidates(hidden_single_cell);
        int num_candidates = hidden_single_cell->num_candidates;

        for (int j = 0; j < num_candidates; ++j) {
            if (candidates[j] != p_hidden_singles[i].value) {
                unset_candidate(hidden_single_cell, candidates[j]);
                not_overlap = 1;
            }
        }
        overlap -= not_overlap;
        free(candidates);
    }
    return overlap;
}
int hidden_singles(SudokuBoard *p_board) {
    HiddenSingle hidden_singles[BOARD_SIZE*BOARD_SIZE];
    int counter = 0;
    int overlap = 0;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        find_hidden_single(p_board->p_rows[i], hidden_singles, &counter);
        find_hidden_single(p_board->p_cols[i], hidden_singles, &counter);
        find_hidden_single(p_board->p_boxes[i], hidden_singles, &counter);
    }
    overlap = overlaps_candidates(hidden_singles, &counter);
    
    return counter- overlap;
}


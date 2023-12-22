#include <stdbool.h>
#include "hidden_pairs.h"

// Implement other necessary functions and structures here

int find_hidden_pairs_values(Cell **p_cells, int *hidden_pairs_values) {
    int pair_candidates = 0;
    int the_array_of_hidden_pairs_values[BOARD_SIZE] = {0};
    // Count the occurrences of candidates in the row, avoiding duplicates
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (p_cells[i]->num_candidates > 1) {
            int *candidates = get_candidates(p_cells[i]);
            for (int j = 0; j < p_cells[i]->num_candidates; ++j) {
                int candidate = candidates[j];
                the_array_of_hidden_pairs_values[candidate - 1]++;
            }
            free(candidates);
        }
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (the_array_of_hidden_pairs_values[i] == 2) {
            hidden_pairs_values[pair_candidates++] = i + 1;
        }
    }
    return pair_candidates;
}

void find_hidden_pairs(Cell **p_cells, HiddenPair *p_hidden_pairs, int *p_counter) {
    int hidden_pairs_values[BOARD_SIZE];
    int num_pairs = find_hidden_pairs_values(p_cells, hidden_pairs_values);

    for (int i = 0; i < num_pairs-1; ++i) {
        for (int k = i + 1; k < num_pairs; ++k) {
            // Check if the values are in the same cells
            if (are_values_in_same_cells(p_cells, hidden_pairs_values[i], hidden_pairs_values[k])) {
                // Check if it is a hidden pair and not a naked pair
                for (int j = 0; j < BOARD_SIZE-1; j++) {
                    for (int l = j+1; l < BOARD_SIZE; l++) {
                        if ((is_candidate(p_cells[j], hidden_pairs_values[i]) &&
                            is_candidate(p_cells[j], hidden_pairs_values[k])) &&
                            (is_candidate(p_cells[l], hidden_pairs_values[i]) &&
                            is_candidate(p_cells[l], hidden_pairs_values[k]))) {

                            HiddenPair hidden_pair_obj;
                            hidden_pair_obj.value1 = hidden_pairs_values[i];
                            hidden_pair_obj.value2 = hidden_pairs_values[k];
                            hidden_pair_obj.p_cell1 = p_cells[j];
                            hidden_pair_obj.p_cell2 = p_cells[l];
                            p_hidden_pairs[(*p_counter)++] = hidden_pair_obj;
                            break;
                        }
                    }
                }
            }
        }
    }
}

int overlaps_hidden_pairs(HiddenPair *p_hidden_pairs, int counter) {
    int overlap = counter;

    for (int i = 0; i < counter; ++i) {
        int not_overlap = 0;
        Cell *hidden_pair_cell1 = p_hidden_pairs[i].p_cell1;
        Cell *hidden_pair_cell2 = p_hidden_pairs[i].p_cell2;
        int *candidates1 = get_candidates(hidden_pair_cell1);
        int num_candidates = hidden_pair_cell1->num_candidates;

        for (int j = 0; j < num_candidates; ++j) {
            if (candidates1[j] != p_hidden_pairs[i].value1 && candidates1[j] != p_hidden_pairs[i].value2) {
                unset_candidate(hidden_pair_cell1, candidates1[j]);
                not_overlap = 1;
            }
        }
        free(candidates1);
        
        int *candidates2 = get_candidates(hidden_pair_cell2);
        num_candidates = hidden_pair_cell2->num_candidates;
        for (int j = 0; j < num_candidates; ++j) {
            if (candidates2[j] != p_hidden_pairs[i].value1 && candidates2[j] != p_hidden_pairs[i].value2) {
                unset_candidate(hidden_pair_cell2, candidates2[j]);
                not_overlap = 1;
            }
        }
        free(candidates2);
        overlap -= not_overlap;
    }
    return overlap;
}


int hidden_pairs(SudokuBoard *p_board) {
    HiddenPair hidden_pairs[BOARD_SIZE * BOARD_SIZE];
    int counter = 0;
    int overlap = 0;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        find_hidden_pairs(p_board->p_rows[i], hidden_pairs, &counter);
        find_hidden_pairs(p_board->p_cols[i], hidden_pairs, &counter);
        find_hidden_pairs(p_board->p_boxes[i], hidden_pairs, &counter);
    }
    overlap = overlaps_hidden_pairs(hidden_pairs, counter);
    return (counter - overlap);
}

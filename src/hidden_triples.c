#include "hidden_triples.h"

#define MAX_CELLS 100
// Implement other necessary functions and structures here

int find_hidden_triples_values(Cell **p_cells, int *hidden_triples_values) {
    int triple_candidates = 0;
    
    int the_array_of_hidden_triples_values[BOARD_SIZE] = {0};
    // Count the occurrences of candidates in the row, avoiding duplicates
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (p_cells[i]->num_candidates > 1) {
            int *candidates = get_candidates(p_cells[i]);
            for (int j = 0; j < p_cells[i]->num_candidates; ++j) {
                int candidate = candidates[j];
                the_array_of_hidden_triples_values[candidate - 1]++;
            }
            free(candidates);
        }
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (the_array_of_hidden_triples_values[i] == 2||the_array_of_hidden_triples_values[i] == 3) {
            hidden_triples_values[triple_candidates++] = i + 1;
        }
    }

    return triple_candidates;
}

void find_hidden_triples(Cell **p_cells, HiddenTriple *p_hidden_triples, int *p_counter) {
    int hidden_triples_values[BOARD_SIZE];
    int num_triples = find_hidden_triples_values(p_cells, hidden_triples_values);


    // Check if at least one value is present in at least two of the three cells
    for (int i = 0; i < num_triples - 2; ++i) {
        for (int k = i + 1; k < num_triples - 1; ++k) {
            for (int l = k + 1; l < num_triples; ++l) {
                // Check if each value is in at least two of the three cells
                if ((are_values_in_same_cells(p_cells, hidden_triples_values[i], hidden_triples_values[k]) &&
                    are_values_in_same_cells(p_cells, hidden_triples_values[i], hidden_triples_values[l]) &&
                    are_values_in_same_cells(p_cells, hidden_triples_values[k], hidden_triples_values[l]))
                    // Check if at least one value is common among all three cells
                    ) {

                    for (int j = 0; j < BOARD_SIZE - 2; ++j) {
                        for (int h = j + 1; h < BOARD_SIZE - 1; ++h) {
                            for (int g = h + 1; g < BOARD_SIZE; ++g) {
                                // Check if values are candidates in at least 2 per 3 of the cells
                                if ((is_candidate(p_cells[j], hidden_triples_values[i]) &&
                                     is_candidate(p_cells[j], hidden_triples_values[k]) &&
                                     is_candidate(p_cells[j], hidden_triples_values[l])) ||
                                    (is_candidate(p_cells[g], hidden_triples_values[i]) &&
                                     is_candidate(p_cells[g], hidden_triples_values[k]) &&
                                     is_candidate(p_cells[g], hidden_triples_values[l])) ||
                                    (is_candidate(p_cells[h], hidden_triples_values[i]) &&
                                     is_candidate(p_cells[h], hidden_triples_values[k]) &&
                                     is_candidate(p_cells[h], hidden_triples_values[l]))) {
                                    HiddenTriple hidden_triple_obj;
                                    hidden_triple_obj.value1 = hidden_triples_values[i];
                                    hidden_triple_obj.value2 = hidden_triples_values[k];
                                    hidden_triple_obj.value3 = hidden_triples_values[l];
                                    hidden_triple_obj.p_cell1 = p_cells[j];
                                    hidden_triple_obj.p_cell2 = p_cells[h];
                                    hidden_triple_obj.p_cell3 = p_cells[g];
                                    p_hidden_triples[(*p_counter)++] = hidden_triple_obj;

                                    // Break the loop after finding a valid triple in the cells
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


int overlaps_hidden_triples(HiddenTriple *p_hidden_triples, int counter) {
    int overlap = counter;
    
    for (int i = 0; i < counter; ++i) {
        int not_overlap = 0;
        Cell *hidden_triple_cell1 = p_hidden_triples[i].p_cell1;
        Cell *hidden_triple_cell2 = p_hidden_triples[i].p_cell2;
        Cell *hidden_triple_cell3 = p_hidden_triples[i].p_cell3;
        
        int *candidates1 = get_candidates(hidden_triple_cell1);
        int num_candidates = hidden_triple_cell1->num_candidates;
        
        for (int j = 0; j < num_candidates; ++j) {
            if (candidates1[j] != p_hidden_triples[i].value1 && candidates1[j] != p_hidden_triples[i].value2 && candidates1[j] != p_hidden_triples[i].value3) {
                unset_candidate(hidden_triple_cell1, candidates1[j]);
                not_overlap = 1;
            }
        }
        free(candidates1);

        int *candidates2 = get_candidates(hidden_triple_cell2);
        num_candidates = hidden_triple_cell2->num_candidates;
        for (int j = 0; j < num_candidates; ++j) {
            if (candidates2[j] != p_hidden_triples[i].value1 && candidates2[j] != p_hidden_triples[i].value2 && candidates2[j] != p_hidden_triples[i].value3) {
                unset_candidate(hidden_triple_cell2, candidates2[j]);
                not_overlap = 1;
            }
        }
        free(candidates2);

        int *candidates3 = get_candidates(hidden_triple_cell3);
        num_candidates = hidden_triple_cell3->num_candidates;
        for (int j = 0; j < num_candidates; ++j) {
            if (candidates3[j]!= p_hidden_triples[i].value1 && candidates3[j]!= p_hidden_triples[i].value2 && candidates3[j]!= p_hidden_triples[i].value3) {
                unset_candidate(hidden_triple_cell3, candidates3[j]);
                not_overlap = 1;
            }
        }
        free(candidates3);
       

        overlap -= not_overlap;

    }

    return overlap;
}


int hidden_triples(SudokuBoard *p_board) {
    HiddenTriple hidden_triples[BOARD_SIZE * BOARD_SIZE];
    int counter = 0;
    int overlap = 0;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        find_hidden_triples(p_board->p_rows[i], hidden_triples, &counter);
        find_hidden_triples(p_board->p_cols[i], hidden_triples, &counter);
        find_hidden_triples(p_board->p_boxes[i], hidden_triples, &counter);
    }
    overlap = overlaps_hidden_triples(hidden_triples, counter);
    return (counter - overlap);
}

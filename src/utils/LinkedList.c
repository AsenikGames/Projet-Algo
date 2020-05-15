/**
 * @file LinkedList.c
 * @brief contain Linkedlist functions
 */

#ifndef LinkedList
#define LinkedList

#include <stdlib.h>

#define foreach(i,list) for(Cell * i = list; i != NULL; i = i -> next) //iterate through a list

typedef struct cell Cell;
struct cell {
	void* value;
	Cell* next;
};

/**
 * @fn void addValue(Cell ** header, void * value)
 * @brief add a value at begining
 *
 * @param header the list to which add
 * @param value a pointer toward the value to add
 *
 * @return nothing
 */
void addValue(Cell** header, void* value) {
	Cell* cell = (Cell*)malloc(sizeof(Cell));
	cell->value = value;
	cell->next = *header;
	*header = cell;
}



/**
 * @fn void addEndValue(Cell ** header, void * value)
 * @brief add a value at end
 *
 * @param header the list to which add
 * @param value a pointer toward the value to add
 *
 * @return nothing
 */
void addEndValue(Cell** header, void* value) {
	Cell* cell = (Cell*)malloc(sizeof(Cell));
	cell->value = value;
	cell->next = NULL;

	if (*header == NULL) {
		*header = cell;
	} else {
		Cell* j = NULL;
		foreach(i, *header) {
			j = i;
		}
		j->next = cell;
	}
}

/**
 * @fn int removeCell(Cell ** header, Cell * cell)
 * @brief remove a cell of the list. DO NOT FREE (desired for later use possibility)
 *
 * @param header the list
 * @param cell the cell to remove
 *
 * @return 0 if cell has been remove or -1 otherwise
 */
int removeCell(Cell** header, Cell* cell) {
	if (cell == NULL) return -1;

	if (*header == cell) {
		*header = cell->next;
		return 0;
	}
	foreach(i, *header) {
		if (i->next == cell) {
			i->next = cell->next;
			return 0;
		}
	}
	return -1;
}

/**
 * @fn void freeAll(Cell* header)
 * @brief free all Cell of a list. BUT DO NOT FREE VALUE !
 *
 * @param header the first element a the list
 *
 * @return nothing
 */
void freeAll(Cell* header) {
	if (header != NULL) {
		Cell* next = header->next;

		freeAll(next);
		free(header);
	}
}

#endif
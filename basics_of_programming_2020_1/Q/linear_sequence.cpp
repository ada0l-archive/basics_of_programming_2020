#include<stdio.h>

#include"linear_sequence.h"

#define LSQ_TRUE 1
#define LSQ_FALSE 0
#define LSQ_DEFAULT_SIZE 5
#define LSQ_MULTIPLIER(x) ((11 * x) / 10) + 1
#define LSQ_DEBUG 0

typedef struct LSQ_Handle {
    LSQ_IntegerIndexT capacity;
    LSQ_IntegerIndexT size;
    LSQ_BaseTypeT* data;
} LSQ_Handle;

typedef struct LSQ_Iterator {
    LSQ_Handle* handle;
    LSQ_IntegerIndexT index;
} LSQ_Iterator;

/*
 * Utility functions
 */

void
LSQ_AllocateData(LSQ_Handle* handle_n, LSQ_IntegerIndexT size)
{
    LSQ_BaseTypeT* new_data = (LSQ_BaseTypeT*) malloc(
            size * sizeof(LSQ_BaseTypeT));
    if(NULL != new_data) {
        handle_n->data = new_data;
        handle_n->size = 0;
        handle_n->capacity = size;
    }
}

void
LSQ_ReallocateData(LSQ_Handle* handle_n, LSQ_IntegerIndexT size)
{

    LSQ_BaseTypeT* new_data = (LSQ_BaseTypeT*) realloc(
            handle_n->data, sizeof(LSQ_BaseTypeT) * size);
    if(new_data != NULL) {
        handle_n->data = new_data;
        handle_n->capacity = size;
    }
}

void
LSQ_BalancingDataSize(LSQ_Handle* handle_n)
{
    if(LSQ_DEBUG)
        printf("%d %d\n", handle_n->size, handle_n->capacity);
    if(NULL == handle_n->data) {
        if(LSQ_DEBUG)
            printf("alloc\n");
        LSQ_AllocateData(handle_n, LSQ_DEFAULT_SIZE);
    } else if(handle_n->size >= handle_n->capacity) {
        LSQ_IntegerIndexT new_size =
            LSQ_MULTIPLIER(handle_n->size);
        if(LSQ_DEBUG)
            printf("realloc, new_size %d\n", new_size);
        LSQ_ReallocateData(handle_n, new_size);
    }
}

void
LSQ_PrintData(LSQ_HandleT handle)
{
    LSQ_Handle* handle_n = (LSQ_Handle*) handle;
    LSQ_BaseTypeT* handle_n_data = (LSQ_BaseTypeT*) handle_n->data;
    for(int i = 0; i < handle_n->size; ++i) {
        printf("%d ", *(handle_n_data + i));
    }
    printf("\n");
}

/*
 * API implementation
 */

extern LSQ_HandleT
LSQ_CreateSequence(void)
{
    LSQ_Handle* handle_n = (LSQ_Handle*) malloc(sizeof(LSQ_Handle));
    handle_n->capacity = 0;
    handle_n->size = 0;
    handle_n->data = NULL;
    return (LSQ_HandleT) handle_n;
}

extern void
LSQ_DestroySequence(LSQ_HandleT handle)
{
    if(NULL != handle) {
        LSQ_Handle* handle_n = (LSQ_Handle*) handle;
        free(handle_n->data);
        handle_n->data = NULL;
        free(handle);
        handle_n = NULL;
    }
}

extern LSQ_IntegerIndexT
LSQ_GetSize(LSQ_HandleT handle)
{
    // handle must be allocated and not equel NULL
    LSQ_Handle* handle_n = (LSQ_Handle*) handle;
    return handle_n->size;
}

extern int
LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator)
{
    if(NULL == iterator) return LSQ_FALSE;
    LSQ_Iterator* iterator_n = (LSQ_Iterator*) iterator;
    LSQ_Handle* handle_n = (LSQ_Handle*) iterator_n->handle;
    if(0 <= iterator_n->index && iterator_n->index < handle_n->size)
        return LSQ_TRUE;
    return LSQ_FALSE;
}

extern int
LSQ_IsIteratorPastRear(LSQ_IteratorT iterator)
{
    if(NULL == iterator) return LSQ_FALSE;
    LSQ_Iterator* iterator_n = (LSQ_Iterator*) iterator;
    LSQ_Handle* handle_n = (LSQ_Handle*) iterator_n->handle;
    if(iterator_n->index == handle_n->size) return LSQ_TRUE;
    return LSQ_FALSE;
}

extern int
LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator)
{
    if(NULL == iterator) return LSQ_FALSE;
    LSQ_Iterator* iterator_n = (LSQ_Iterator*) iterator;
    LSQ_Handle* handle_n = (LSQ_Handle*) iterator_n->handle;
    if(iterator_n->index == -1) return LSQ_TRUE;
    return LSQ_FALSE;
}

extern LSQ_BaseTypeT*
LSQ_DereferenceIterator(LSQ_IteratorT iterator)
{
    LSQ_Iterator* iterator_n = (LSQ_Iterator*) iterator;
    LSQ_Handle* handle_n = (LSQ_Handle*) iterator_n->handle;
    return handle_n->data + iterator_n->index;
}

extern LSQ_IteratorT
LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index)
{
    LSQ_Iterator* iterator_n = (LSQ_Iterator*) malloc(sizeof(LSQ_Iterator));
    iterator_n->handle = (LSQ_Handle*) handle;
    iterator_n->index = index;
    return (LSQ_IteratorT) iterator_n;
}

extern LSQ_IteratorT
LSQ_GetFrontElement(LSQ_HandleT handle)
{
    return LSQ_GetElementByIndex(handle, 0);
}

extern LSQ_IteratorT
LSQ_GetPastRearElement(LSQ_HandleT handle)
{
    LSQ_Handle* handle_n = (LSQ_Handle*) handle;
    LSQ_IntegerIndexT index = handle_n->size;
    return LSQ_GetElementByIndex(handle, index);
}

extern void
LSQ_DestroyIterator(LSQ_IteratorT iterator)
{
    free(iterator);
    iterator = NULL;
}

extern void
LSQ_AdvanceOneElement(LSQ_IteratorT iterator)
{
    LSQ_ShiftPosition(iterator, 1);
}

extern void
LSQ_RewindOneElement(LSQ_IteratorT iterator)
{
    LSQ_ShiftPosition(iterator, -1);
}

extern void
LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift)
{
    LSQ_Iterator* iterator_n = (LSQ_Iterator*) iterator;
    iterator_n->index += shift;
}

extern void
LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos)
{
    LSQ_Iterator* iterator_n = (LSQ_Iterator*) iterator;
    iterator_n->index = pos;
}

extern void
LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    LSQ_IteratorT iterator = LSQ_GetElementByIndex(handle, 0);
    LSQ_InsertElementBeforeGiven(iterator, element);
    LSQ_DestroyIterator(iterator);
}

extern void
LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
    LSQ_Handle* handle_n = (LSQ_Handle*) handle;
    LSQ_IteratorT iterator =
        LSQ_GetElementByIndex(handle, handle_n->size);
    LSQ_InsertElementBeforeGiven(iterator, element);
    LSQ_DestroyIterator(iterator);
}

extern void
LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator,
                             LSQ_BaseTypeT newElement)
{
    LSQ_Iterator* iterator_n = (LSQ_Iterator*) iterator;
    LSQ_Handle* handle_n = (LSQ_Handle*) iterator_n->handle;
    LSQ_BalancingDataSize(handle_n);
    LSQ_BaseTypeT* handle_n_data =
        (LSQ_BaseTypeT*) handle_n->data;
    for(int i = handle_n->size; i > iterator_n->index; --i) {
        handle_n_data[i] = handle_n_data[i - 1];
    }
    handle_n_data[iterator_n->index] = newElement;
    ++handle_n->size;
}

extern void LSQ_DeleteFrontElement(LSQ_HandleT handle)
{
    LSQ_IteratorT iterator =
        LSQ_GetElementByIndex(handle, 0);
    LSQ_DeleteGivenElement(iterator);
    LSQ_DestroyIterator(iterator);
}

extern void LSQ_DeleteRearElement(LSQ_HandleT handle)
{
    LSQ_Handle* handle_n = (LSQ_Handle*) handle;
    LSQ_IteratorT iterator =
        LSQ_GetElementByIndex(handle, handle_n->size);
    LSQ_DeleteGivenElement(iterator);
    LSQ_DestroyIterator(iterator);
}

extern void LSQ_DeleteGivenElement(LSQ_IteratorT iterator)
{
    LSQ_Iterator* iterator_n = (LSQ_Iterator*) iterator;
    LSQ_Handle* handle_n = (LSQ_Handle*) iterator_n->handle;
    LSQ_BalancingDataSize(handle_n);
    LSQ_BaseTypeT* handle_n_data =
        (LSQ_BaseTypeT*) handle_n->data;
    for(int i = iterator_n->index; i < handle_n->size; i++) {
        handle_n_data[i] = handle_n_data[i + 1];
    }
    handle_n->size--;
}

#include "linear_sequence.h"

#include <iostream>

#define DEBUG

#ifdef DEBUG
    #define LSQ_SEP_BLOCK "----------------------------------------------------"
    #define LSQ_SEP_ELEMENT "; "
#endif

struct Node {
    LSQ_BaseTypeT data;
    Node *prev, *next;

    Node(Node *prev, Node *next, int data) : prev(prev), next(next), data(data)
    {}

    Node()
    {}
};

struct List {
    LSQ_IntegerIndexT size { 0 };
    Node *first, *last;

    List() {
        first = new Node(nullptr, nullptr, 0);
        last = new Node(first, nullptr, 0);
        first->next = last;
    }

    ~List() {
        for (int i = 0; i < size; ++i) {
            LSQ_DeleteRearElement(this);
        }
        delete first;
        delete last;
    }
};

struct Iterator {
    List *list;
    Node *node;
    LSQ_IntegerIndexT index;

    Iterator(LSQ_HandleT handle, Node *node, LSQ_IntegerIndexT index) :
                                                    node(node), index(index) {
        list = (List *) handle;
    }
};

typedef List *PHandle;
typedef Iterator *PIterator;

#ifdef DEBUG
void LSQ_PrintHandle_Debug(LSQ_HandleT handle) {
    std::cout << LSQ_SEP_BLOCK << "\n"
              << "list"                                     << LSQ_SEP_ELEMENT
              << "pointer: "    << handle                   << LSQ_SEP_ELEMENT
              << "size: "       << PHandle(handle)->size    << LSQ_SEP_ELEMENT
              << "\n";
    int i = 0;
    LSQ_IteratorT it = LSQ_GetFrontElement(handle);
    while (LSQ_IsIteratorDereferencable(it)) {
        Node *node = PIterator(it)->node;
        std::cout << "index: "      << i            << LSQ_SEP_ELEMENT
                  << "value: "      << node->data   << LSQ_SEP_ELEMENT
                  << "current: "    << node         << LSQ_SEP_ELEMENT
                  << "prev: "       << node->prev   << LSQ_SEP_ELEMENT
                  << "next: "       << node->next   << LSQ_SEP_ELEMENT
                  << "\n";
        LSQ_AdvanceOneElement(it);
        i++;
    }
    std::cout << LSQ_SEP_BLOCK << "\n";
}
void LSQ_PrintIterator_Debug(LSQ_IteratorT iterator) {
    std::cout << LSQ_SEP_BLOCK << "\n"
              << "iterator" << LSQ_SEP_ELEMENT
              << "pointer: " << iterator << LSQ_SEP_ELEMENT
              << "index: " << PIterator(iterator)->index << LSQ_SEP_ELEMENT
              << "data: " << *LSQ_DereferenceIterator(iterator) << LSQ_SEP_ELEMENT
              << "node: "  << PIterator(iterator)->node << LSQ_SEP_ELEMENT
              << "\n==============================================\n\n";
}
#endif

extern LSQ_HandleT LSQ_CreateSequence(void) {
    return (LSQ_HandleT) new List();
}

extern void LSQ_DestroySequence(LSQ_HandleT handle) {
    delete PHandle(handle);
}

extern LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle) {
    return PHandle(handle)->size;
}

extern int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator) {
    return !LSQ_IsIteratorPastRear(iterator) &&
           !LSQ_IsIteratorBeforeFirst(iterator);
}

extern int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator) {
    return PIterator(iterator)->node == PIterator(iterator)->list->last;
}

extern int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator) {
    return PIterator(iterator)->node == PIterator(iterator)->list->first;
}

extern LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator) {
    return &PIterator(iterator)->node->data;
}

extern LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle,
                                           LSQ_IntegerIndexT index) {
    Node *node = PHandle(handle)->first;
    for (int i = -1; i < index; ++i) {
        node = node->next;
    }
    return (LSQ_IteratorT) new Iterator(handle, node, index);
}

extern LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle) {
    return LSQ_GetElementByIndex(handle, 0);
}

extern LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle) {
    return LSQ_GetElementByIndex(handle, PHandle(handle)->size);
}

extern void LSQ_DestroyIterator(LSQ_IteratorT iterator) {
    delete PIterator(iterator);
}

extern void LSQ_AdvanceOneElement(LSQ_IteratorT iterator) {
    PIterator(iterator)->node = PIterator(iterator)->node->next;
    ++PIterator(iterator)->index;
}

extern void LSQ_RewindOneElement(LSQ_IteratorT iterator) {
    PIterator(iterator)->node = PIterator(iterator)->node->prev;
    --PIterator(iterator)->index;
}

extern void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift) {
    for (int i = 0; i < abs(shift); ++i) {
        if (shift > 0)  LSQ_AdvanceOneElement(iterator);
        else            LSQ_RewindOneElement(iterator);
    }
}

extern void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos) {
    LSQ_ShiftPosition(iterator, -1 * (PIterator(iterator)->index - pos));
}

extern void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element) {
    LSQ_IteratorT iterator = LSQ_GetFrontElement(handle);
    LSQ_InsertElementBeforeGiven(iterator, element);
    LSQ_DestroyIterator(iterator);
}

extern void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element) {
    LSQ_IteratorT iterator = LSQ_GetPastRearElement(handle);
    LSQ_InsertElementBeforeGiven(iterator, element);
    LSQ_DestroyIterator(iterator);
}

extern void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator,
                                         LSQ_BaseTypeT newElement) {
    Node *node = new Node(PIterator(iterator)->node->prev,
                          PIterator(iterator)->node,
                          newElement);
    PIterator(iterator)->node->prev->next = node;
    PIterator(iterator)->node->prev = node;
    PIterator(iterator)->node = node;
    ++PIterator(iterator)->list->size;
}

extern void LSQ_DeleteFrontElement(LSQ_HandleT handle) {
    LSQ_IteratorT iterator = LSQ_GetFrontElement(handle);
    LSQ_DeleteGivenElement(iterator);
    LSQ_DestroyIterator(iterator);
}

extern void LSQ_DeleteRearElement(LSQ_HandleT handle) {
    LSQ_IteratorT iterator = LSQ_GetPastRearElement(handle);
    LSQ_RewindOneElement(iterator);
    LSQ_DeleteGivenElement(iterator);
    LSQ_DestroyIterator(iterator);
}

extern void LSQ_DeleteGivenElement(LSQ_IteratorT iterator) {
    Node *node = PIterator(iterator)->node->next;
    PIterator(iterator)->node->prev->next = PIterator(iterator)->node->next;
    PIterator(iterator)->node->next->prev = PIterator(iterator)->node->prev;
    delete PIterator(iterator)->node;
    PIterator(iterator)->node = node;
    --PIterator(iterator)->list->size;
}

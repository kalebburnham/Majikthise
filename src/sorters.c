#include "sorters.h"

int MoveComparatorNumerical (const void * a, const void * b) {
    struct Move *moveA = (struct Move *)a;
    struct Move *moveB = (struct Move *)b;

    if (moveA->from - moveB->from != 0) {
        return moveA->from - moveB->from;
    }

    if (moveA->to - moveB->to != 0) {
        return moveA->to - moveB->to;
    }

    return moveA->flag - moveB->flag;
}

int MoveComparatorNumericalDesc (const void * a, const void * b) {
    struct Move *moveA = (struct Move *)a;
    struct Move *moveB = (struct Move *)b;

    if (moveA->from - moveB->from != 0) {
        return moveB->from - moveA->from;
    }

    if (moveA->to - moveB->to != 0) {
        return moveB->to - moveA->to;
    }

    return moveB->flag - moveA->flag;
}

#ifndef OPERATION_H
#define OPERATION_H

#include "OperationType.h"

class Operation{
public:
    OperationType type;
    char character;
    int position;

    Operation(){
        type=OperationType::INSERT;
        character='\0';
        position=0;
    }

    Operation(OperationType type,char character,int position){
        this->type=type;
        this->character=character;
        this->position=position;
    }
};

#endif
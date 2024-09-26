#include "typeoperations.h"
#include "types.h"

void OperationA(TypeA& type)
{
    type.SetInt(1);
}

void OperationA(TypeB& type)
{
    type.SetFloat(1.0f);
}

void OperationB(TypeA& type)
{
    type.SetInt(-1);
}

void OperationB(TypeB& type)
{
    type.SetFloat(-1.0f);
}

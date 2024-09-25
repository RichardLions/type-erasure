#include "typeoperations.h"
#include "types.h"

void OperationA(TypeA& item)
{
    item.SetInt(1);
}

void OperationA(TypeB& item)
{
    item.SetFloat(1.0f);
}

void OperationB(TypeA& item)
{
    item.SetInt(-1);
}

void OperationB(TypeB& item)
{
    item.SetFloat(-1.0f);
}

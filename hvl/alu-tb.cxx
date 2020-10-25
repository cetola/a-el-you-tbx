#include "tbxbindings.h"
#include "svdpi.h"
#include "stdio.h"
 
static int a = 0 ;
static int b = 0;
static int operandA = 0;
static int operandB = 0;
static int op = 0;
static int opcode = 0;
static int result = 0;
static int err = 0;

int doReset() {
    printf("---reset---\n");
    return 0;
}

int getData(svBitVecVal* data1, svBitVecVal* data2, svBitVecVal* data3, svBitVecVal* ready) {
    *ready = 1;
        
    if(a <= 10) {
        operandA = a++;
    } else {
        operandB = b++;
        a = 0;
    }
    
    if(b == 11) {
        op++;
        a = 0;
        b = 0;
    }

    opcode = op;

    *data1 = operandA;
    *data2 = operandB;
    *data3 = opcode;
    
    if(opcode == 3 && b == 10) {
        *ready = 0;
    }
    return 0;
}

int putData(const svBitVecVal* data1) {
    long int expected = 0;
    result = *data1;

    switch (opcode) {
        case 0: expected = operandA + operandB; break;
        case 1: expected = operandA - operandB; break;
        case 2: expected = operandA & operandB; break;
        case 3: expected = operandA | operandB; break;
    }

    if(result != expected) {
        err ++ ;
        printf ("error:\ta=%0d\tb=%0d\topcode=%0d\texpected=%0d\tresult=%0d\n",operandA, operandB, opcode, expected, result);
    }

    return 0;
}

int doFinish() {
    if (!err) {
        printf("---All tests passed---\n");
    } else {
        printf("---%0d Tests Failed---\n",err);
    }
    return 0;
}


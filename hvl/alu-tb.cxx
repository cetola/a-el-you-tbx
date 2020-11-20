#include "tbxbindings.h"
#include "svdpi.h"
#include "stdio.h"

int a = -1;
int b = 0;
int operandA = 0;
int operandB = 0;
int op = 0;
int opcode = 0;
int result = 0;
int err = 0;
int total = 0;
bool debug = false;

int doReset() {
    printf("---reset---\n");
    sayHello();
    return 0;
}

int getData(svBitVecVal* data1, svBitVecVal* data2, svBitVecVal* data3, svBitVecVal* ready) {
    *ready = 1;
        
    if(a <= 50) {
        a++;
    }
    
    if(a == 51){
        b++;
        a = 0;
    }
    
    if(b == 51) {
        op++;
        b = 0;
    }

    operandA = a;
    operandB = b;
    opcode = op;

    *data1 = operandA;
    *data2 = operandB;
    *data3 = opcode;

    if(opcode == 4) {
        *ready = 0;
    }

    if(debug)
        printf ("OPCODE:\t\ta=%0d\topa=%0d\tb=%0d\topb=%0d\top=%0d\topcode=%0d\n",a,operandA,b,operandB,op,opcode);
    
    return 0;
}

int putData(const svBitVecVal* data1) {
    long int expected = 0;
    result = *data1;
    total++;

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

    if(debug)
        printf ("info:\ta=%0d\tb=%0d\topcode=%0d\texpected=%0d\tresult=%0d\n",operandA, operandB, opcode, expected, result);
    
    return 0;
}

int doFinish() {
    if (!err) {
        printf("---All tests passed---\n");
    } else {
        printf("---%0d Tests Failed---\n",err);
    }
    printf("---%0d Total Tests---\n", total);
    return 0;
}


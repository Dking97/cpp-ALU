#include "gates.h"
#include <iostream>

using namespace std;

//     Declarations-feel free to define these or add more.
//         delete // after you define one to use the declaration.
//               define functions at the bottom! 


bool* carryLookAheadGenerator(bool* generate, bool* propogate, bool c0);
bool* eightBitCarryPropogate(bool* in1, bool* in2);
bool* eightBitCarryGenerate(bool* in1, bool* in2);
bool CLA_generate(bool in1, bool in2);
bool CLA_propogate(bool in1, bool in2);
bool mux(bool add, bool subtract, bool AND, bool OR, bool comparison, bool NOTA, bool NOTB, bool* opCode);
bool* selector(bool* add, bool* subtract, bool* AND, bool* OR, bool* comparison, bool* NOTA, bool*NOTB, bool* opCode);
bool* eightBitNOT(bool* in1);
bool equalBit(bool in1, bool in2);
bool greaterThanBit(bool in1, bool in2);
bool lessThanBit(bool in1, bool in2);
bool* eightBitCompare(bool* in1, bool* in2);
bool* twosCompliment(bool *in);
bool* CLA(bool* in1, bool* in2, bool* carry);//returns sums
bool* carryLookAheadGenerator(bool* generate, bool* propogate, bool c0); 


//bool AND(bool in1, bool in2); //Gate functions are already defined in "gates.h" header.
//bool XOR(bool in1, bool in2);
//bool OR(bool in1, bool in2);
//bool NOT(bool in);

//main use this to test functions. 
int main() {
 
    
    bool A[8];
    bool B[8];
    bool opCode[3];
    bool empty[8] = {0};


    cout << "Enter A: ";
    string strA;
    cin >> strA;
    for (int i = 0; i < 8; i++) {
        A[i] = (strA[i] == '1');  // Convert '1'/'0' to bool
    }
    cout << "Enter B: ";
     string B_str;
    cin >> B_str;
    for (int i = 0; i < 8; i++) {
        B[i] = (B_str[i] == '1');  // Convert '1'/'0' to bool
    }
    cout << "Enter Opcode: ";
    string opCode_str;
    cin >> opCode_str;
    for (int i = 0; i < 3; i++) {
        opCode[i] = (opCode_str[i] == '1');  // Convert '1'/'0' to bool
    }
    bool* cla = CLA(A, B, 0);
    cout << " generate: ";
    for(int i = 0; i < 8; i++) {
        cout << eightBitCarryGenerate(A, B)[i];
    }
    cout << " Propogate: ";
    for(int i = 0; i < 8; i++) {
        cout << eightBitCarryPropogate(A, B)[i];
    }
    cout << " Carry Generator: ";
    for(int i = 0; i < 9; i++) {
        cout << carryLookAheadGenerator(eightBitCarryGenerate(A, B),eightBitCarryPropogate(A, B), 0)[i];
    }
    cout << " CLA: ";
    for(int i = 0; i < 9; i++) {
        cout << cla[i];
    }
    

    
/*
    bool* result = selector(
            addSubtract(A, B, 1),
            CLA(A, B, carryLookAheadGenerator(eightBitCarryGenerate(A, B),eightBitCarryPropogate(A, B), 0)),
            CLA(A, B, carryLookAheadGenerator(eightBitCarryGenerate(A, B),eightBitCarryPropogate(A, B), 0)),
            CLA(A, B, carryLookAheadGenerator(eightBitCarryGenerate(A, B),eightBitCarryPropogate(A, B), 0)),
            CLA(A, B, carryLookAheadGenerator(eightBitCarryGenerate(A, B),eightBitCarryPropogate(A, B), 0)),
            CLA(A, B, carryLookAheadGenerator(eightBitCarryGenerate(A, B),eightBitCarryPropogate(A, B), 0)),
            CLA(A, B, carryLookAheadGenerator(eightBitCarryGenerate(A, B),eightBitCarryPropogate(A, B), 0)),
            opCode);
            */
    return 0;
} 




//Function definitions go down here.



bool* eightBit_AND_AB(bool* in1, bool* in2){
	static bool AND_AB[8];
	for(int i = 0; i < 8; i++){
		AND_AB[i] = AND(in1[i], in2[i]);
		// cout << AND_AB[i];
	}
	
	return AND_AB;
}

bool* eightBit_OR_AB(bool* in1, bool* in2){
	static bool OR_AB[8];
	for(int i = 0; i < 8; i++){
		OR_AB[i] = OR(in1[i], in2[i]);
		// cout << OR_AB[i];
	}
	
	return OR_AB;
}

bool* CLA(bool* in1, bool* in2, bool C) {
    bool B[8];
    for (int i = 0; i < 8; i++) {
        B[i] = XOR(in2[i], C);
    }
    bool* generate = eightBitCarryGenerate(in1, B);
    bool* propogate = eightBitCarryPropogate(in1, B);
    bool* carry = carryLookAheadGenerator(generate, propogate, C); 
    static bool sum[10];
    sum[1] = carry[0]; // carry out flag
    sum[0] = XOR(carry[0], carry[1]); //overflow flag
    for (int i = 2; i < 10; i++) {
        sum[i] = XOR(XOR(in1[i-2], B[i-2]), carry[i-1]);
    }
    cout << endl << "carry generator: ";
    for (int i = 0; i < 9; i++) {
       cout << carry[i];
    } 
    return sum;
}

	
    bool* generate = eightBitCarryGenerate(in1, B);
    bool* propogate = eightBitCarryPropogate(in1, B);
    bool* carry = carryLookAheadGenerator(generate, propogate, C); 
    static bool sum[10];
    sum[1] = carry[0]; // carry out flag
    sum[0] = XOR(carry[0], carry[1]); //overflow flag
    for (int i = 2; i < 10; i++) {
        sum[i] = XOR(XOR(in1[i-2], B[i-2]), carry[i-1]);
    }
   cout << endl << "carry generator: ";
   for (int i = 0; i < 9; i++) {
       cout << carry[i];
   }
 
       return sum;
}




bool* carryLookAheadGenerator(bool* generate, bool* propogate, bool c0) {
    static bool carry[9];
    carry[8] = c0;

    carry[7] = OR(generate[7], AND(propogate[7], carry[8]));
    
    carry[6] = OR(generate[6], AND(propogate[6], (
                    /*carry[7]*/OR(generate[7], AND(propogate[7], carry[8])))));

    carry[5] = OR(generate[5], AND(propogate[5], (
                    /*carry[6]*/  OR(generate[6], AND(propogate[6], (
                                /*carry[7]*/ OR(generate[7], AND(propogate[7], carry[8]))))))));

    carry[4] = OR(generate[4], AND(propogate[4], (
                    /*carry[5]*/ OR(generate[5], AND(propogate[5], (
                                /*carry[6]*/OR(generate[6], AND(propogate[6], (
                                            /*carry[7]*/OR(generate[7], AND(propogate[7], carry[8])))))))))));

    carry[3] = OR(generate[3], AND(propogate[3], (
                    /*carry[4]*/ OR(generate[4], AND(propogate[4], (
                                /*carry[5]*/ OR(generate[5], AND(propogate[5], (
                                            /*carry[6]*/OR(generate[6], AND(propogate[6], (
                                                        /*carry[7]*/OR(generate[7], AND(propogate[7], carry[8]))))))))))))));

    carry[2] = OR(generate[2], AND(propogate[2], (
                    /*carry[3]*/OR(generate[3], AND(propogate[3], (
                                /*carry[4]*/OR(generate[4], AND(propogate[4], (
                                            /*carry[5]*/ OR(generate[5], AND(propogate[5], (
                                                        /*carry[6]*/OR(generate[6], AND(propogate[6],  (
                                                                    /*carry[7]*/OR(generate[7], AND(propogate[7], carry[8])))))))))))))))));

    carry[1] = OR(generate[1], AND(propogate[1], (
                    /*carry[2]*/OR(generate[2], AND(propogate[2], (
                                /*carry[3]*/OR(generate[3], AND(propogate[3], (
                                            /*carry[4]*/OR(generate[4], AND(propogate[4], (
                                                        /*carry[5]*/ OR(generate[5], AND(propogate[5], (
                                                                    /*carry[6]*/OR(generate[6], AND(propogate[6], (
                                                                                /*carry[7]*/OR(generate[7], AND(propogate[7], carry[8]))))))))))))))))))));

    carry[0] = OR(generate[0], AND(propogate[0], (
                    /*carry[1]*/OR(generate[1], AND(propogate[1], (
                                /*carry[2]*/OR(generate[2], AND(propogate[2], (
                                            /*carry[3]*/OR(generate[3], AND(propogate[3], (
                                                        /*carry[4]*/OR(generate[4], AND(propogate[4], (
                                                                    /*carry[5]*/OR(generate[5], AND(propogate[5], (
                                                                                /*carry[6]*/OR(generate[6], AND(propogate[6], (
                                                                                            /*carry[7]*/OR(generate[7], AND(propogate[7], carry[7])))))))))))))))))))))));

    
    return carry;
}




bool* eightBitCarryGenerate(bool* in1, bool* in2) {
    static bool G[8]; 
    for (int i = 0; i < 8; i++) {
        G[i] = CLA_generate(in1[i], in2[i]); 
    }
    return G; 
}

bool* eightBitCarryPropogate(bool* in1, bool* in2) {
    static bool prop[9];
    for (int i = 0; i < 8; i++) {
        prop[i] = XOR(in1[i], in2[i]); //the inputs are A and B
    }
    return prop;
}

bool CLA_generate(bool A, bool B) {
    return AND(A, B);
}

bool CLA_propagate(bool A, bool B) {
    return XOR(A, B);
}

bool equalBit(bool in1, bool in2){
    return NOT(XOR(in1,in2));
}

bool greaterThanBit(bool in1, bool in2){
    return AND(in1,NOT(in2));
}

bool lessThanBit(bool in1, bool in2){
    return AND(NOT(in1),in2);
}

bool* eightBitCompare(bool* in1, bool* in2){
    bool compare[3] = {0};
    bool greater[8] = {0};
    bool less[8] = {0};
    bool equal[8] = {0};

    for (int i = 0; i < 8; i++){
        greater[i] = greaterThanBit(in1[i],in2[i]);
        less[i] = lessThanBit(in1[i],in2[i]);        
        equal[i] = equalBit(in1[i],in2[i]);
    }

    //100 A>B, 010 A<B, 001 A=B
    compare[0] = OR8(greater);
    compare[1] = OR8(less);
    compare[2] = AND8(equal);
}

bool* eightBitNOT(bool* in1){ 
	static bool out[8];
	for(int i = 0; i < 8; i++){
		out[i] = NOT(in1[i]);
	}
	return out;
}

bool* selector(bool* add, bool* subtract, bool* AND, bool* OR, bool* comparison, bool* NOTA, bool*NOTB, bool* opCode) {
    static bool result[9] = {0};
    for(int i = 0; i < 9; i++) {
        result[i] = mux(add[i], subtract[i], AND[i], OR[i], comparison[i], NOTA[i], NOTB[i], opCode);
    }
    return result;
}

bool mux(bool add, bool subtract, bool AND, bool OR, bool comparison, bool NOTA, bool NOTB, bool* opCode){ 
	static bool notOpCode[3] = {NOT(opCode[0]), NOT(opCode[1]), NOT(opCode[2])};
	
	return OR7(
		AND4(add, notOpCode[0], notOpCode[1], notOpCode[2]),
		AND4(subtract, notOpCode[0], notOpCode[1], opCode[2] ),
		AND4(AND, notOpCode[0], opCode[1] , notOpCode[2]),
		AND4(OR, notOpCode[0], opCode[1] , opCode[2] ),
		AND4(comparison, opCode[0] , notOpCode[1], notOpCode[2]),
		AND4(NOTA, opCode[0] , notOpCode[1], opCode[2] ),
		AND4(NOTB, opCode[0] , opCode[1] , notOpCode[2] )
	);
}


    //in1>in2 in1 + 2's comp in2 discard MSB
    if (compare_A_B(in1,in2)[1] == 1){
        in2 = twosCompliment(eightBitNOT_A(in2));
        diff = CLA(in1, in2, carryLookAheadGenerator(eightBitCarryPropogate(in1,in2),eightBitCarryGenerate(in1,in2),0));
        diff[0] = 0;
        return diff;
    }
    //in1<in2 in1 + 2's comp in2, 2's comp step 1, add negative sign
    if(compare_A_B(in1,in2)[1] == 0){
        in2 = twosCompliment(eightBitNOT_A(in2));
        diff = CLA(in1, in2, carryLookAheadGenerator(eightBitCarryPropogate(in1,in2),eightBitCarryGenerate(in1,in2),0));
        diff = twosCompliment(eightBitNOT_A(diff));
        diff[0] = NOT(diff[0]);
        return diff;
    } 
    //in1==in2
    else{
        for(int i = 0; i < 9;i++){
            diff[i] = false;
        }
	return diff;
    }
}

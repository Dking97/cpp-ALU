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
bool* eightBitNOT_B(bool* in2);
bool* eightBitNOT_A(bool* in1);
void replace(bool* in1, bool* in2);
//bool* compare_A_B(bool* in1, bool* in2);
//bool* subtract(bool *in1, bool* in2);
bool* twosCompliment(bool *in);
bool* CLA(bool* in1, bool* in2, bool* carry);//returns sums
bool* carryLookAheadGenerator(bool* generate, bool* propogate, bool c0); 


//bool AND(bool in1, bool in2); //Gate functions are already defined in "gates.h" header.
//bool XOR(bool in1, bool in2);
//bool OR(bool in1, bool in2);
//bool NOT(bool in);

//main use this to test functions. (this just gets A B and opCode. write your own test lines.)
int main() {
    bool Carry[9] = {0}; // carry 
    cout << "Enter A: ";
    string strA;
    cin >> strA;
    bool A[8];
    for (int i = 0; i < 8; i++) {
        A[i] = (strA[i] == '1');  // Convert '1'/'0' to bool
    }
    cout << "Enter B: ";
    string B_str;
    cin >> B_str;
    bool B[8];
    for (int i = 0; i < 8; i++) {
        B[i] = (B_str[i] == '1');  // Convert '1'/'0' to bool
    }
    cout << "Enter Opcode: ";
    string opCode_str;
    cin >> opCode_str;
    bool opCode[3];
    for (int i = 0; i < 3; i++) {
        opCode[i] = (opCode_str[i] == '1');  // Convert '1'/'0' to bool
    }

    return 0;
}



//Function definitions go down here.
bool* CLA(bool* in1, bool* in2, bool* carry) {
    static bool sum[9];
    for (int i = 0; i < 8; i++) {
        sum[i] = XOR(XOR(in1[i], in2[i]), carry[i]);
    }
    return sum;
}

bool* carryLookAheadGenerator(bool* generate, bool* propogate, bool c0) { //working but still need to implement gate functions
    static bool carry[9];
    carry[0] = c0;

    carry[1] = OR(generate[0], AND(propogate[0], carry[0]));
    
    carry[2] = OR(generate[1], AND(propogate[1], (/*carry[1]*/OR(generate[0], AND(propogate[0], carry[0])))));

    carry[3] = OR(generate[2], AND(propogate[2], (/*carry[2]*/OR(generate[1], AND(propogate[1], (/*carry[1]*/OR(generate[0], AND(propogate[0], carry[0]))))))));

    carry[4] = OR(generate[3], AND(propogate[3], (/*carry[3]*/ OR(generate[2], AND(propogate[2], (/*carry[2]*/OR(generate[1], AND(propogate[1], (/*carry[1]*/OR(generate[0], AND(propogate[0], carry[0])))))))))));

    carry[5] = OR(generate[4], AND(propogate[4], (/*carry[4]*/OR(generate[3], AND(propogate[3], (/*carry[3]*/ OR(generate[2], AND(propogate[2], (/*carry[2]*/OR(generate[1], AND(propogate[1], (/*carry[1]*/OR(generate[0], AND(propogate[0], carry[0]))))))))))))));

    carry[6] = OR(generate[5], AND(propogate[5], (/*carry[5]*/OR(generate[4], AND(propogate[4], (/*carry[4]*/OR(generate[3], AND(propogate[3], (/*carry[3]*/ OR(generate[2], AND(propogate[2], (/*carry[2]*/OR(generate[1], AND(propogate[1],  (/*carry[1]*/OR(generate[0], AND(propogate[0], carry[0])))))))))))))))));

    carry[7] = OR(generate[6], AND(propogate[6], (/*carry[6]*/OR(generate[5], AND(propogate[5], (/*carry[5]*/OR(generate[4], AND(propogate[4], (/*carry[4]*/OR(generate[3], AND(propogate[3], (/*carry[3]*/ OR(generate[2], AND(propogate[2], (/*carry[2]*/OR(generate[1], AND(propogate[1], (/*carry[1]*/OR(generate[0], AND(propogate[0], carry[0]))))))))))))))))))));

    carry[8] = OR(generate[7], AND(propogate[7], (/*carry[7]*/OR(generate[6], AND(propogate[6], (/*carry[6]*/OR(generate[5], AND(propogate[5], (/*carry[5]*/OR(generate[4], AND(propogate[4], (/*carry[4]*/OR(generate[3], AND(propogate[3], (/*carry[3]*/OR(generate[2], AND(propogate[2], (/*carry[2]*/OR(generate[1], AND(propogate[1], (/*carry[1]*/OR(generate[0], AND(propogate[0], carry[0])))))))))))))))))))))));
  
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
    static bool prop[8];
    for (int i = 0; i < 8;i++) {
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


bool* compare_A_B(bool* in1, bool* in2){
	bool compare[3] = {0};
	
	for(int i = 7; i >= 0; i--){
		if (NOT(XOR(in1[i], in2[i])) == 1){
			continue;
		} else {
			if (in1[i] > in2[i]){
				compare[1] = 1;
				return compare; // A is bigger than B
			} else {
				compare[2] = 1;
				return compare; // B is bigger than A
			} 
		}
	}
	compare[0] = 1;
	return compare; // 001 for B // 010 for A // 100 for B = A
	
}

bool eightBitNOT_A(bool* in1){ // returns Not A
	static bool NOT_A[8];
	for(int i = 0; i < 8; i++){
		NOT_A[i] = NOT(in1[i]);
		cout << NOT_A[i];
	}
	return NOT_A;
}

bool eightBitNOT_B(bool* in2){ // returns Not B
	static bool NOT_B[8];
	for(int i = 0; i < 8; i++){
		NOT_B[i] = NOT(in2[i]);
		cout << NOT_B[i];
	}
	return NOT_B;
}

// 11/18/24 im not sure if im doing this right since the mux usually doenst take in a the entire 8 bits, it usually has an individual mux for each bit. - collin

void replace(bool* in1, bool* in2){
	for (i = 0; i < 8; i++) { 
        in1[i] = in2[i]; 
}

bool selector( bool I0, bool I1, bool I2, bool I3, bool I4, bool I5, bool I6, bool* selector){ 
	static bool S2 = selector[0], S1 = selector[1], S0 = selector[2];
	static bool SI2 = NOT(S2), SI1 = NOT(S1), SI0 = NOT(SI0);
	
	return OR7(
		AND4(I0, SI2, SI1, SI0),
		AND4(I1, SI2, SI1, S0 ),
		AND4(I2, SI2, S1 , SI0),
		AND4(I3, SI2, S1 , S0 ),
		AND4(I4, S2 , SI1, SI0),
		AND4(I5, S2 , SI1, S0 ),
		AND4(I6, S2 , S1 , S0 )
	);
	
}


//needs to take in the onesCompliment of in, just NOT in
bool* twosCompliment(bool *in){
    bool carry = true;
    for (int i = 0; i < in.size(); i++){
        if (in[i] == true && carry == true){
            in[i] = false;
            carry = true;
        } else if(in[i] == false && carry == true){
            in[i] = true;
            carry = false;
        }
    }
    return in;
}

bool* subtract(bool *in1, bool* in2){
    static bool[9] diff;
    bool gen[8];
    bool prop[8];
    bool carrys[9];

    //in1>in2 in1 + 2's comp in2 discard MSB
    if (compare_A_B(in1,in2)[1] == 1){
        in2 = twosCompliment(eightBitNOT_A(in2));
	prop = eightBitCarryPropogate(in1,in2);
	gen = eightBitCarryGenerate(in1,in2);
	carrys = carryLookAheadGenerator(prop,gen,0);
        diff = CLA(in1, in2, carrys);
        diff[0] = 0;
        return diff;
    }
    //in1<in2 in1 + 2's comp in2, 2's comp step 1, add negative sign
    if(compare_A_B(in1,in2)[1] == 0){
        in2 = twosCompliment(eightBitNOT_A(in2));
	prop = eightBitCarryPropogate(in1,in2);
	gen = eightBitCarryGenerate(in1,in2);
	carrys = carryLookAheadGenerator(prop,gen,0);
        diff = CLA(in1, in2, carrys);
        diff = twosCompliment(eightBitNOT_A(diff));
        diff[0] = NOT(diff[0]);
        return diff;
    } 
    //in1==in2
    if(compare_A_B(in1,in2)[0] == 1){
        for(int i = 0; i < in1.size();i++){
            diff[i] = false;
        }
	return diff;
    }
}

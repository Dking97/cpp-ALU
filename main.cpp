#include "gates.h"
#include <iostream>

using namespace std;

//     Declarations-feel free to define these or add more.
//         delete // after you define one to use the declaration.
//               define functions at the bottom! 

//bool* eightBitCarryLookAheadAdder(bool* in1, bool* in2, bool carry); 
//bool* eightBitCarryLookAhead(bool* in1, bool* in2, bool carry);
//bool* eightBitCarryPropogate(bool* in1, bool* in2, bool carry);
bool* eightBitCarryGenerate(bool* in1, bool* in2);
//bool carryGenerate(bool in1, bool in2);
//bool carryPropogate(bool in1, bool in2, bool carry);
//bool* fullAdder(bool in1, bool in2, bool carry); probably not need this

bool nextCarry(bool propCarry, bool genCarry, bool lastCarry);
bool* eightBitCLSums(bool* propCarry, bool* Carrys);
bool* eightBitCarryLA(bool* propCarry, bool* genCarry, bool Carryin);
bool AND(bool in1, bool in2); //Gate functions are already defined in "gates.h" header.
bool XOR(bool in1, bool in2);
bool OR(bool in1, bool in2);
bool NOT(bool in);

int main() { //test function. (for now)
    cout << "test what?" << endl; //menu
    cout << "1: single bit inputs" << endl;
    cout << "2: 8-bit lookahead adder" << endl;
    int selection;
    cin >> selection;

    if (selection == 1) { //Selection 1: single bit inputs (gates and full adder)
        bool in1;
        bool in2;
        bool carry;
        cin >> in1;
        cin >> in2;
        cin >> carry;
        //bool* full = fullAdder(in1, in2, carry);
        cout << "NOT(1) = " << NOT(in1) << endl;
        cout << "AND(1,2) = " << AND(in1, in2) << endl;
        cout << "OR(1,2) = " << OR(in1, in2) << endl;
        cout << "XOR(1,2) = " << XOR(in1, in2) << endl;
        cout << "fullAdder (1 ,2 ,C) = " << full[0] << full[1] << endl;
        return 0;
    }
    else if (selection == 2) { //selection 3 lookahead adder
        bool in1[4];
        bool in2[4];
        bool carry;

        cout << "Enter A: " << endl;
        for (int i = 0; i < 8; i++) {
            cin >> in1[i];
        }
        cout << "Enter B: " << endl;
        for (int i = 0; i < 8; i++) {
            cin >> in2[i];
        }
        cout << "Enter carry: " << endl;
        cin >> carry;
        cout << "A: ";
        for (int i = 0; i < 8; i++) {
            cout << in1[i];
        }
        cout << endl;
        cout << "B: ";
        for (int i = 0; i < 8; i++) {
            cout << in2[i];
        }
        cout << endl;
        cout << "carry: " << carry << endl;
        bool* Generate = eightBitCarryGenerate(in1, in2, carry);
        cout << "generate = ";
        for (int i = 0; i < 8; i++) {
            cout << Generate[i];
        }
        cout << "-" << Generate[8] << endl;
        bool* Propogate = eightBitCarryPropogate(in1, in2, carry);
        cout << "Propogate = ";
        for (int i = 0; i < 8; i++) {
            cout << Propogate[i];
        }
        cout << "-" << Propogate[8] << endl;
        bool* lookAhead = eightBitCarryLookAhead(in1, in2, carry);
        cout << "lookahead = ";
        for (int i = 0; i < 8; i++) {
            cout << lookAhead[i];
        }
        cout << "-" << lookAhead[8] << endl;
        bool* lookAheadAdder = eightBitCarryLookAheadAdder(in1, in2, carry);
        cout << "lookahead sum = ";
        for (int i = 0; i < 8; i++) {
            cout << lookAheadAdder[i];
        }
        cout << endl;
    }
    return 0;
}

//Function definitions go down here.
bool* CLA(bool* in1, bool* in2, bool* carry) {
    static bool sum[8];
    for (int i = 0; i < 8; i++) {
        sum[i] = XOR(XOR(in1[i], in2[i]), carry[i]);
    }
    return sum;
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
	bool compare[2] = {0};
	
	for(int i = 7; i >= 0; i--){
		if (NOT(XOR(in1[i], in2[i])) == 1){
			continue;
		} else {
			if (in1[i] > in2[i]){
				compare[1] = 1;
				return compare; // A is bigger than B
			} else {
				compare[1] = 0;
				return compare; // B is bigger than A
			} 
		}
	}
	compare[0] = 1;
	return compare; // 00 for B // 01 for A // 10 for B = A
	
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

bool replace(bool* in1, bool* in2){
	for (i = 0; i < 8; i++) { 
        in1[i] = in2[i]; 
}

bool selector(bool* in1, bool* in2, bool* selector){ // 
	static bool S2 = selector[0], S1 = selector[1], S0 = selector[2];
	static bool SI2 = NOT(S2), SI1 = NOT(S1), SI0 = NOT(SI0);
	static bool output[8];
	
	if(AND(SI2, AND(SI1, SI0))){
		
	}
	else if(AND(SI2, AND(SI1, S0 ))){
		
	}
	else if(AND(SI2, AND(S1 , SI0))){
		
	}
	else if(AND(SI2, AND(S1 , S0 ))){
		
	}
	else if(AND(S2 , AND(SI1, SI0))){
		replace(output, compare_A_B(in1, in2));
	}
	else if(AND(S2 , AND(SI1, S0 ))){
		replace(output, eightBitNOT_A(in1));
	}
	else if(AND(S2 , AND(S1 , SI0))){
		replace(output, eightBitNOT_B(in2));
	}
}


//needs to take in the onesCompliment of in
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

    //in1>in2 in1 + 2's comp in2 discard MSB
    if (compare_A_B(in1,in2) == 1){
        in2 = twosCompliment(eightBitNOT_A(in2));
        diff = CLA(in1, in2, carrys);
        diff[0] = 0;
        return diff;
    }
    //in1<in2 in1 + 2's comp in2, 2's comp step 1, add negative sign
    if(compare_A_B(in1,in2) == 0){
        in2 = twosCompliment(eightBitNOT_A(in2));
        diff = CLA(in1, in2, carrys);
        diff = twosCompliment(eightBitNOT_A(diff));
        diff[0] = NOT(diff[0]);
        return diff;
    } 
    //in1==in2
    if(case3){
        for(int i = 0; i < in1.size();i++){
            diff[i] = false;
        }
    }
    return diff;
}

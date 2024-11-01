#include "gates.h"
#include <iostream>

using namespace std;

//     Declarations-feel free to define these or add more.
//         delete // after you define one to use the declaration.
//               define functions at the bottom! 

//bool* eightBitCarryLookAheadAdder(bool* in1, bool* in2, bool carry); 
//bool* eightBitCarryLookAhead(bool* in1, bool* in2, bool carry);
//bool* eightBitCarryPropogate(bool* in1, bool* in2, bool carry);
//bool* eightBitCarryGenerate(bool* in1, bool* in2, bool carry);
//bool carryGenerate(bool in1, bool in2);
//bool carryPropogate(bool in1, bool in2, bool carry);
//bool* fullAdder(bool in1, bool in2, bool carry); probably not need this

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
        cout << "AND(1,2) = " << AND(in1, in2) <<endl;
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


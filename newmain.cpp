#include <iostream>
#include <vector>
using namespace std;

//Gate Logic

inline bool NOT(bool in) {
    return !in; // NOT operation
}

inline bool AND(bool in1, bool in2) {
    return in1 && in2; // AND operation
}

inline bool OR(bool in1, bool in2) {
    return in1 || in2; // OR operation
}

inline bool XOR(bool in1, bool in2) {
    return in1 ^ in2; // XOR operation
}

inline bool AND4(bool in1, bool in2, bool in3, bool in4) {
    return in1 && in2 && in3 && in4;
}

inline bool OR7(bool in1, bool in2, bool in3, bool in4, bool in5, bool in6, bool in7) {
    return in1 || in2 || in3 || in4 || in5 || in6 || in7;
}

bool OR8(bool* in) {
    return in[0] || in[1] || in[2] || in[3] || in[4] || in[5] || in[6] || in[7];
}

bool AND8(bool* in) {
    return in[0] && in[1] && in[2] && in[3] && in[4] && in[5] && in[6] && in[7];
}


//Declarations
bool* carryLookAheadGenerator(bool* generate, bool* propogate, bool c0);
bool* eightBitCarryPropogate(bool* in1, bool* in2);
bool* eightBitCarryGenerate(bool* in1, bool* in2);
bool CLA_generate(bool in1, bool in2);
bool CLA_propogate(bool in1, bool in2);
bool mux(bool add, bool subtract, bool ANDop, bool ORop, bool comparison, bool NOTA, bool NOTB, bool* opCode);

vector<bool> selector(const vector<bool>& add, const vector<bool>& subtract, const vector<bool>& ANDop, const vector<bool>& ORop, const vector<bool>& comparison, const vector<bool>& NOTA, const vector<bool>& NOTB, bool* opCode);
vector<bool> eightBitNOT(const bool* in1);
bool equalBit(bool in1, bool in2);
bool greaterThanBit(bool in1, bool in2);
bool lessThanBit(bool in1, bool in2);
vector<bool> eightBitCompare(const bool* in1, const bool* in2);
vector<bool> CLA(bool* in1, bool* in2, bool C);//returns sums
vector<bool> eightBit_AND_AB(const bool* in1, const bool* in2);
vector<bool> eightBit_OR_AB(const bool* in1, const bool* in2);


//main
int main() {
    bool A[8];
    bool B[8];
    bool opCode[3];

    cout << "Enter A (8 bits): ";
    string strA;
    cin >> strA;
    for (int i = 0; i < 8; i++) {
        A[i] = (strA[i] == '1');
    }

    cout << "Enter B (8 bits): ";
    string B_str;
    cin >> B_str;
    for (int i = 0; i < 8; i++) {
        B[i] = (B_str[i] == '1');
    }

    cout << "Enter Opcode (3 bits): ";
    string opCode_str;
    cin >> opCode_str;
    for (int i = 0; i < 3; i++) {
        opCode[i] = (opCode_str[i] == '1');
    }

    vector<bool> add_result = CLA(A, B, 0);
    vector<bool> sub_result = CLA(A, B, 1);
    vector<bool> and_result = eightBit_AND_AB(A, B);
    vector<bool> or_result = eightBit_OR_AB(A, B);
    vector<bool> cmp_result = eightBitCompare(A, B);
    vector<bool> nota_result = eightBitNOT(A);
    vector<bool> notb_result = eightBitNOT(B);

    vector<bool> result = selector(
        add_result,
        sub_result,
        and_result,
        or_result,
        cmp_result,
        nota_result,
        notb_result,
        opCode
    );

    bool overflow = result[0];
    bool carryout = result[1];
    vector<bool> Y_bits(8);
    for (int i = 0; i < 8; i++) {
        Y_bits[i] = result[i + 2];
    }
    bool comp0 = result[10];
    bool comp1 = result[11];

    cout << "\n----- Result Breakdown -----" << endl;
    cout << "Overflow: " << overflow << endl;
    cout << "Carryout: " << carryout << endl;
    cout << "Y: ";
    for (int i = 0; i < 8; i++) {
        cout << (Y_bits[i] ? '1' : '0');
    }
    cout << endl;
    cout << "Comparison bits: " << comp1 << comp0 << endl;

    return 0;
}


//Function Definitions

bool CLA_generate(bool A, bool B) {
    return AND(A, B);
}

bool CLA_propagate(bool A, bool B) {
    return XOR(A, B);
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
        prop[i] = XOR(in1[i], in2[i]);
    }
    return prop;
}

bool* carryLookAheadGenerator(bool* generate, bool* propogate, bool c0) {
    static bool carry[9];
    carry[8] = c0;

    bool c7_part = AND(propogate[7], carry[8]);
    carry[7] = OR(generate[7], c7_part);

    bool c6_inner = OR(generate[7], AND(propogate[7], carry[8]));
    carry[6] = OR(generate[6], AND(propogate[6], c6_inner));

    bool c5_inner = OR(generate[6], AND(propogate[6], OR(generate[7], AND(propogate[7], carry[8]))));
    carry[5] = OR(generate[5], AND(propogate[5], c5_inner));

    bool c4_inner = OR(generate[5], AND(propogate[5], OR(generate[6], AND(propogate[6], OR(generate[7], AND(propogate[7], carry[8]))))));;
    carry[4] = OR(generate[4], AND(propogate[4], c4_inner));

    bool c3_inner = OR(generate[4], AND(propogate[4], OR(generate[5], AND(propogate[5], OR(generate[6], AND(propogate[6], OR(generate[7], AND(propogate[7], carry[8]))))))));;
    carry[3] = OR(generate[3], AND(propogate[3], c3_inner));

    bool c2_inner = OR(generate[3], AND(propogate[3], OR(generate[4], AND(propogate[4], OR(generate[5], AND(propogate[5], OR(generate[6], AND(propogate[6], OR(generate[7], AND(propogate[7], carry[8]))))))))));;
    carry[2] = OR(generate[2], AND(propogate[2], c2_inner));

    bool c1_inner = OR(generate[2], AND(propogate[2], OR(generate[3], AND(propogate[3], OR(generate[4], AND(propogate[4], OR(generate[5], AND(propogate[5], OR(generate[6], AND(propogate[6], OR(generate[7], AND(propogate[7], carry[8]))))))))))));
    carry[1] = OR(generate[1], AND(propogate[1], c1_inner));

    bool c0_inner = OR(generate[1], AND(propogate[1], OR(generate[2], AND(propogate[2], OR(generate[3], AND(propogate[3], OR(generate[4], AND(propogate[4], OR(generate[5], AND(propogate[5], OR(generate[6], AND(propogate[6], OR(generate[7], AND(propogate[7], carry[7]))))))))))))));
    carry[0] = OR(generate[0], AND(propogate[0], c0_inner));

    return carry;
}

vector<bool> CLA(bool* in1, bool* in2, bool C) {
    vector<bool> sum(12, 0);

    bool B[8];
    for (int i = 0; i < 8; i++) {
        B[i] = XOR(in2[i], C);
    }

    bool* generate = eightBitCarryGenerate(in1, B);
    bool* propogate = eightBitCarryPropogate(in1, B);
    bool* carry = carryLookAheadGenerator(generate, propogate, C);

    sum[1] = carry[0];  // Carryout
    sum[0] = XOR(carry[0], carry[1]); // Overflow

    for (int i = 2; i < 10; i++) {
        sum[i] = XOR(XOR(in1[i - 2], B[i - 2]), carry[i - 1]);
    }
    return sum;
}

vector<bool> eightBit_AND_AB(const bool* in1, const bool* in2) {
    vector<bool> AND_AB(12, 0);
    for (int i = 0; i < 8; i++) {
        AND_AB[i + 2] = AND(in1[i], in2[i]);
    }
    return AND_AB;
}

vector<bool> eightBit_OR_AB(const bool* in1, const bool* in2) {
    vector<bool> OR_AB(12, 0);
    for (int i = 0; i < 8; i++) {
        OR_AB[i + 2] = OR(in1[i], in2[i]);
    }
    return OR_AB;
}

bool equalBit(bool in1, bool in2) {
    return NOT(XOR(in1, in2));
}

bool greaterThanBit(bool in1, bool in2) {
    return AND(in1, NOT(in2));
}

bool lessThanBit(bool in1, bool in2) {
    return AND(NOT(in1), in2);
}

vector<bool> eightBitCompare(const bool* in1, const bool* in2) {
    bool greater[8] = { 0 };
    bool less[8] = { 0 };
    bool equal[8] = { 0 };

    for (int i = 0; i < 8; i++) {
        greater[i] = greaterThanBit(in1[i], in2[i]);
        less[i] = lessThanBit(in1[i], in2[i]);
        equal[i] = equalBit(in1[i], in2[i]);
    }

    bool A_greater = OR8(greater);
    bool A_less = OR8(less);
    bool A_equal = AND8(equal);

    vector<bool> compResult(12, 0);
    if (A_greater) {
        compResult[10] = 1;
        compResult[11] = 1;
    }
    else if (A_equal) {
        compResult[10] = 0;
        compResult[11] = 1;
    }
    else if (A_less) {
        compResult[10] = 1;
        compResult[11] = 0;
    }

    return compResult;
}

vector<bool> eightBitNOT(const bool* in1) {
    vector<bool> out(12, 0);
    for (int i = 0; i < 8; i++) {
        out[i + 2] = NOT(in1[i]);
    }
    return out;
}

vector<bool> selector(const vector<bool>& add, const vector<bool>& subtract, const vector<bool>& ANDop, const vector<bool>& ORop, const vector<bool>& comparison, const vector<bool>& NOTA, const vector<bool>& NOTB, bool* opCode) {
    vector<bool> result(12, 0);
    for (int i = 0; i < 12; i++) {
        result[i] = mux(add[i], subtract[i], ANDop[i], ORop[i], comparison[i], NOTA[i], NOTB[i], opCode);
    }
    return result;
}

bool mux(bool add, bool subtract, bool ANDop, bool ORop, bool comparison, bool NOTA, bool NOTB, bool* opCode) {
    bool notOpCode[3] = { NOT(opCode[0]), NOT(opCode[1]), NOT(opCode[2]) };
    // Opcode:
    // 000: add
    // 001: subtract
    // 010: AND
    // 011: OR
    // 100: comparison
    // 101: NOT A
    // 110: NOT B
    return OR7(
        AND4(add, notOpCode[0], notOpCode[1], notOpCode[2]),
        AND4(subtract, notOpCode[0], notOpCode[1], opCode[2]),
        AND4(ANDop, notOpCode[0], opCode[1], notOpCode[2]),
        AND4(ORop, notOpCode[0], opCode[1], opCode[2]),
        AND4(comparison, opCode[0], notOpCode[1], notOpCode[2]),
        AND4(NOTA, opCode[0], notOpCode[1], opCode[2]),
        AND4(NOTB, opCode[0], opCode[1], notOpCode[2])
    );
}

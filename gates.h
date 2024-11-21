#ifndef GATES_H
#define GATES_H

// Logic gate functions

inline bool NOT(bool in) { 
    return !in; // NOT operation
}

inline bool AND(bool in1, bool in2) {
    return in1 && in2; // AND operation
}

inline bool OR(bool in1, bool in2) {
    return in1 || in2; // OR operation
}

inline bool XOR(bool in1, bool in2) { //Dakota 
    return in1 ^ in2; // XOR operation
}

inline bool AND4(bool in1, bool in2, bool in3, bool in4) {
    return in1 && in2 && in3 && in4; // AND operation
}

inline bool OR7(bool in1, bool in2, bool in3, bool in4, bool in5, bool in6, bool in7) {
    return in1 || in2 || in3 || in4 || in5 || in6 || in7; // OR operation
}

#endif // GATES_H

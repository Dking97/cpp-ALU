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

#endif // GATES_H

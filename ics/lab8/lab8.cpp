#include <cstdint>
#include <iostream>
#include <fstream>
#include <bitset>

//#define LENGTH 3
#define MAXLEN 3000
#define STUDENT_ID_LAST_DIGIT 2

void remove(int16_t& board, int i);
void put(int16_t& board, int i);
void R(int16_t& board, int16_t *memory, int n, int16_t& step);
void P(int16_t& board, int16_t *memory, int n, int16_t& step);

void remove(int16_t& board, int i){    //change board[i] to 1
    int16_t mask = 1;
    for(int j = 1; j<i; j++){
        mask += mask;
    }
    board = board | mask;
}

void put(int16_t& board, int i){        //change board[i] to 0
    int16_t mask = 1;
    for(int j = 1; j < i; j++){
        mask += mask;
    }
    mask = ~ mask;
    board = board & mask;
}

void R(int16_t& board, int16_t *memory, int n, int16_t& step){
    if(n == 0){
        return;
    }
    else if(n == 1){
        remove(board, 1);
        memory[step] = board;
        step++;
    }
    else{
        R(board, memory, n-2, step);
        remove(board, n);
        memory[step] = board;
        step++;
        P(board, memory, n-2, step);
        R(board, memory, n-1, step);
    }
}

void P(int16_t& board, int16_t *memory, int n, int16_t& step){
    if(n == 0){
        return;
    }
    else if(n == 1){
        put(board, 1);
        memory[step] = board;
        step++;
    }
    else{
        P(board, memory, n-1, step);
        R(board, memory, n-2, step);
        put(board, n);
        memory[step] = board;
        step++;
        P(board, memory, n-2, step);
    }
}

int16_t lab1(int16_t n) {
    // initialize
    int16_t ans = 0;

    // calculation
    int16_t mask = 1;   //0000 0000 0000 0001 to determine if n is odd or even
    if((n & mask) == 0){  //even
        n = 0 - n;
    }
    for(int i = 0; i<16; i++){  //find how many 0 in the code
        if(n>=0){
            ans++;
        }
        n = n + n;
    }

    // return value
    return ans + STUDENT_ID_LAST_DIGIT;
}

int16_t lab2(int16_t n) {
    // initialize
    int16_t v_n = 3;
    bool d_n = true;

    // calculation
    for(int i=0; i<n-1; i++){
        if(d_n){
            v_n = v_n + v_n + 2;
        }
        else{
            v_n = v_n + v_n - 2;
        }
        //check if d_n need to change
        int16_t temp = v_n;
        while(temp > 0){
            temp -= 8;
        }
        if(temp == 0){  //v_n is divisible by 8
            d_n = !d_n;
        }
        else{
            temp = v_n - 8;
            while(temp > 0){
                temp -= 10;
            }
            if(temp == 0){  //the last digit of v_n is 8
                d_n = !d_n;
            }
        }
        int16_t mask = 4095;    //0000 1111 1111 1111 used as the mask to do modulo calculation
        d_n = (d_n & mask);     //d_n mod 2^12
    }

    // return value
    return v_n;
}

int16_t lab3(char s1[], char s2[]) {
    // initialize
    int i = 0;

    // calculation
    while(true){
        int16_t ans = s1[i] - s2[i];
        if(ans != 0){
            return ans;
        }
        else{
            if(s1[i] == 0 && s2[i] == 0){
                return ans;
            }
        }
        i++;
    }

    // return value
}


int16_t lab4(int16_t *memory, int16_t n) {
    // initialize
    int16_t board = 0;
    int16_t steps = 0;

    // calculation
    R(board, memory, n, steps);

    // return value
    return steps;
}

int main() {
    std::fstream file;
    file.open("test.txt", std::ios::in);

    // lab1
    int16_t n = 0;
    std::cout << "===== lab1 =====" << std::endl;
    for (int i = 0; i < LENGTH; ++i) {
        file >> n;
        std::cout << lab1(n) << std::endl;
    }

    // lab2
    std::cout << "===== lab2 =====" << std::endl;
    for (int i = 0; i < LENGTH; ++i) {
        file >> n;
        std::cout << lab2(n) << std::endl;
    }

    // lab3
    std::cout << "===== lab3 =====" << std::endl;
    char s1[MAXLEN]; char s2[MAXLEN];
    for (int i = 0; i < LENGTH; ++i) {
        file >> s1 >> s2;
        std::cout << lab3(s1, s2) << std::endl;
    }
    
    // lab4
    std::cout << "===== lab4 =====" << std::endl;
    int16_t memory[MAXLEN], move;
    for (int i = 0; i < LENGTH; ++i) {
        file >> n;
        int16_t state = 0;
        move = lab4(memory, n);
        for(int j = 0; j < move; ++j){
            std::cout << std::bitset<16>(memory[j]) << std::endl;
        }
    }
    
    file.close();
    return 0;
}
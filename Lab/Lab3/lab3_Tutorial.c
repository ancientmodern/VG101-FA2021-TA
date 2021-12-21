/* Welcome to VG101 FA2021 lab3!
 *
 * In this part, you need to re-write some statement
 * in each function to make sure this code could be complied correctly.
 * To find the tasks you need to do, use ctrl+F to search for "TODO" comment in this file.
 *
 * You may feel a little bit boring when doing this part of lab, but believe me
 * all the content here is extremely important for your future learning in C/C++
 *
 * We strongly recommend you try to finish all the tasks by hand
 * rather than simply running the code to print the result
*/

// Please do not modify the including header files here.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>

// Please do not modify these functoins below!
int add1(int x) {
    x += 1;
    return x;
}

// What is the * symbol here mean?
int add2(int *x) {
    *x = *x + 1;
    return *x;
}

// Your tasks starts here:

int typeConvension() {
    // This part is designed for you to better understand the
    // types in C/C++.

    // TODO: Please replace the void type below with correct data type
    // Notice that the type you entered should be exactly the
    // same as the final type of the calculation result
    void x1 = 1;
    void x2 = 1.5;
    void x3 = 2.345e6;
    void x4 = 1 + 2.5;
    void x5 = 5 / 2;  // what is the difference between x5 and x6?
    void x6 = 5 / 2.0;
    void x7 = 3 + 2.5 * 2;
    void x8 = 'c' + 4;
    void x9 = '\n';
    void x10 = "this is a c string!\0";

    // TODO: For the statement below, please replace the given data
    // type before each variable with correct one so that there will not be any implicit type convension
    // and the final result will not lose any precision or overflow
    long y1 = 3.54321;
    short y2 = 65536;
    unsigned int y3 = -1;
    char y4 = 12;
    float y5 = 5.34e40;
    int y6 = '9';

    // TODO: please replace the format specifier (after % mark) in
    // the following printf functions with correct ones so that
    // they match the data provided
    printf("x5 is: %d\n", x5);
    printf("x6 is: %d\n", x6);
    printf("x7 is: %d\n", x7);
    printf("x8 is: %d\n", x8);
    printf("x10 is: %d\n", x10);
    printf("y1 is: %ld\n", y1);
    printf("y2 is: %d\n", y2);
    printf("y6 is: %d\n", y6);

    // Do not modify these lines!
    int z1 = 0;
    short z2 = 0;
    char z3 = '0';
    unsigned char z4 = '0';
    double z5 = 0;
    float z6 = 0;
    unsigned int z7 = 0;
    long long z8 = 0;
    unsigned short z9 = 0;
    unsigned long long z10 = 0;

    // TODO: please replase the zeros in each line below with the correct number
    // please do not modify any thing else other than number after == symbol.
    // Hint: assert function will check the logical condition given to it.
    //       It will continue the program if the given condition is correct,
    //       stop the program directly if is it wrong.
    assert(sizeof(z1) == 0);
    assert(sizeof(z2) == 0);
    assert(sizeof(z3) == 0);
    assert(sizeof(z4) == 0);
    assert(sizeof(z5) == 0);
    assert(sizeof(z6) == 0);
    assert(sizeof(z7) == 0);
    assert(sizeof(z8) == 0);
    assert(sizeof(z9) == 0);
    assert(sizeof(z10) == 0);

    // Do not modify lines below!
    (void)x1;
    (void)x2;
    (void)x3;
    (void)x4;
    (void)x5;
    (void)x6;
    (void)x7;
    (void)x8;
    (void)x9;
    (void)x10;
    (void)y1;
    (void)y2;
    (void)y3;
    (void)y4;
    (void)y5;
    (void)y6;

    return 0;
}

void operatorAndStatement() {
    // This part is designed for you to better understand the operation priority,
    // usage, and statement control flow in C/C++

    // Do not modify this line
    int a = 10, b = 12, x = 1;

    // TODO: Replace the number 0 in each assert function after "==" symbol
    // below to make the program works

    // Notice how the logical operations works below, why it works like this?
    // we call this feature short circut, and it is very useful in condition judgement
    int x1 = (b) && (a & 2) && (b /= 3);
    assert(x1 == 0);
    assert(a == 0);
    assert(b == 0);

    int x2 = (++b) || (a -= 10);
    assert(x2 == 0);
    assert(a == 0);
    assert(b == 0);

    // what is the difference?
    int x3 = (a -= 10) || (b++);
    assert(x3 == 0);
    assert(a == 0);
    assert(b == 0);

    int x4 = ((a++) + (++b)) / (++x3);
    assert(x4 == 0);
    assert(a == 0);
    assert(b == 0);

    // What is the difference?
    a = 1; // do not modify this line
    assert((a++) == 0);
    assert((++a) == 0);

    x = 1; // do not modify this line
    assert(add1(x) == 0);
    assert(x == 0);

    // What is the difference?
    x = 1; // do not modify this line
    assert(add2(&x) == 0);
    assert(x == 0);

    x = 0; // do not modify this line
    for (int i = 0; i < 100; ++i) {
        x += 2;
    }
    assert(x == 0);

    x = 0; // do not modify this line
    for (int i = 0; i <= 100; i++) {
        x += 3;
    }
    assert(x == 0);

    x = 0; // do not modify this line
    for (int i = 100; i > 0; i -= 1) {
        x += 4;
        i--;
    }
    assert(x == 0);

    x = 0; // do not modify this line
    for (int i = 100; i > 1; i /= 2) {
        x += 1;
    }
    assert(x == 0);

    return; // why there is no return value?
}

// Please do not modify any lines below!

int main() {
    typeConvension();
    operatorAndStatement();

    return 0;
}

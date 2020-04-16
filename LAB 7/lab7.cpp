/* Gladys Roman
 * CSE460 LAB7
 *

5.) The addresses get larger as variables are added to the stack.


6.) Yes. Variables such as lc3 and lc5 have the same address.q


7.) I would expect variables of recursive functions to be stored in the stack. I was correct. 


	//diagram
 
       +------------------+
       |  TEXT            | 
       |                  |
       |  instructions in | 0x401367 = proc1       
       |  machine code    | 0x40144d = proc2
       |                  |
       +------------------+ 0x4015f5 = etext
       |  DATA            | 0x404034 = g1   global initialized
       |  - initialized   | 0x404038 = g3
       |    variables     | 0x40403c = ls1  static initialized
       |                  | 0x404040 = ls3
       |                  | 
       | ---------------  | 0x404044 = edata
       |                  | 0x404084 = g0   global uninitialized
       |                  | 0x4040a0 = g2   big array 
       |                  | 0x404080 = g4
       |  - uninitialized | 0x404064 = ls0  static uninitialized
       |    variables     | 0x404068 = ls2
       |                  |
       |                  | 
       | ---------------  | 0x405810  = end 
       |  - heap for      | 0xff1260 pointed to by heap1
       |  dynamic         | 0xff1280 pointed to by heap2
       |  allocation      |
       |                  |
       |                  |
       +------------------+ 
                |
                |
                V

                .
                .
                .

                ^
                |
                |
       +------------------+
       |  STACK           | 0x7ffd66454da08 = lc4, lc6   | Activation record for 
       |  - function      | 0x7ffd6454da0c = lc3, lc5   | proc1 or proc2
       |    activation    |
       |    records       |
       |  - local         | 0x7ffd6454da24 = lc2       | Activation record for
       |    automatic     | 0x7ff6454da28 = lc1       | main
       |    variables     | 0x7ffd6454da2c = lc0       |
       +------------------+
*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

//factorial function will be called from main
int factorial(int n)
{
    if(n >= 1) //recursive step
    {
        return n * factorial(n - 1);
    }
    else
        printf("%14p (%15lu): Address of code for factorial (function)\n", &factorial, &factorial); //address of the factorial function
        printf("%14p (%15lu): Address of input variable (argument)\n", &n, &n); //addess of the argument passed to the factorial function
        return 1;
}


int main()
{
    cout << "Enter an integer for factorial calculation: " << endl;
    int input;
    cin >> input;
    int answer = factorial(input);
    cout << input << "!: " << answer << endl;

    return 0;
}

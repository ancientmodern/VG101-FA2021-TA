# VG101 Mid 1 Review Part1

**Author: Lu Haorong**



## Base Conversion

+ **BASIC:** Get familiar with the form of **binary and hexadecimal** number system

  <img src="C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211013011731814.png" alt="image-20211013011731814" style="zoom:67%;" />

+ **BASIC:** Get familiar with the conversion mechanisms between **binary, decimal and hexadecimal** numbers
  
  + Bin/Hex --> Dec:  $\sum_{i=0}^{n} digit(i) \times (2\ or\ 16)^i$
  + Dec --> Bin/Hex:  **Successive dividing + remainder** (check Page 31/33, Lecture 1 for detail)
  + Bin <--> Hex: **4 digits in binary <--> 1 digit in hexadecimal**
    + This is a quite useful trick in future ECE courses, like in VE270 and VE370.
  
+ **IMPORTANT: **Some built-in base conversion functions in MATLAB
  
  + `bin2dec('1111') = 15`  **string to double**
  + `hex2dec('FF') = 255`  **string to double**
  + `dec2bin(15) = '1111'`  **num (double, int32, int64...) to string**
  + `dec2bin(15, 8) = '00001111'`  **Pads the output to the specified minimum digits**
  + `dec2hex(255) = 'FF'`  **num (double, int32, int64...) to string**
  + `dec2hex(255, 4) = '00FF'`  **Pads the output to the specified minimum digits**
  + `D = base2dec(baseStr, n)`  **Convert base n to decimal**
  + `baseStr = dec2base(D, n, minDigits)` **Convert decimal to base n (`minDigits` can be omitted)**



### Examples

+ ***2019 Q3***

<img src="C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211013015525077.png" alt="image-20211013015525077" style="zoom: 50%;" />

+ ***2018 Q4***

<img src="C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211013015631546.png" alt="image-20211013015631546" style="zoom: 50%;" />



## Function

### Syntax

**GENERAL** prototype:

```matlab
function [rets...] = name(args...)
	% do something
end
```

In the case of **SINGLE** return value:

```matlab
function ret = name(args...)
	% do something
end
```

In the case of **NO** return value:

```matlab
function name(args...)
	% do something
end
```

In EXAM, just copy the prototype given by Jigang.



### Something You Need To Know

- If it requires to write a function on the paper, and you write a script, there will be a great deduction.
- If you give value to some return values, when the function returns, the value will be returned.
- Use `return` to directly return the function.



### Why we need a function?

**Function is the abstraction of real implementation.**

For example, sum an array

+ Without function:

```matlab
sum1 = 0;
for i = 1:length(arr1)
	sum1 = sum1 + arr1(i);
end

sum2 = 0;
for i = 1:length(arr2)
	sum2 = sum2 + arr2(i);
end

sum3 = 0;
for i = 1:length(arr3)
	sum3 = sum3 + arr3(i);
end

% ...
```

+ With function:

```matlab
function ret = sum(arr)
    ret = 0;
    for i = 1:length(arr)
        ret = ret + arr(i);
    end
end

sum1 = sum(arr1); % No need to implement it again!
sum2 = sum(arr2);
sum3 = sum(arr3);
```



### How to implement/invoke a new function?

Take **lab2** as an example,

First, carefully read through the **function description and prototype**, and after reading, you should be able to conclude following messages

+ What does the function do?
+ What's the meaning of each input and return value?

```matlab
% Return a 0/1 matrix given the size of the matrix and propotion of alive cells
% 0 represents a dead cell, 1 represents an alive cell
% a: Board rows
% b: Board columns
% p: Propotion of alive cells
% board: Initialized lifegame matrix
function board = init_board(a, b, p)

% Return the board of next step given the current board
% The board of next step is generated through the rule of lifegame
% in_board: Current board
% board: The board of next step
function board = update_board(in_board)

% Display the board in a picture
% in_board: The board you want to display
function view_board(in_board)
```

Now you should be quite clear about what the function does, and when you implement the function, always remember to keep it **independent and invariant!** You should test each function separately with several test cases, just like what TA did in lab2.

Then, when you want to invoke your new functions, just refer to **its high-level definition instead of its low-level implementation**. Function is the abstraction of the implementation, for example, when you invoke `fprintf("%d\n", num)` to print something, you never consider how it is implemented (OS system call, very complex). You just know it's a function that can **print something to the command window given a format string and some variables**. The same is true when you invoke a function written by yourself.

For example, you want to write a script initializing a $5\times 8$ lifegame board with proportion $0.3$, and display the original board and the board after one step. 

```matlab
clear;clf;
orig_board = init_board(5, 8, 0.3);   % initialize the original board
view_board(orig_board);               % display the original board
new_board = update_board(orig_board); % update the original board for one step
view_board(new_board);                % display the new board
```



## Data Types

### Why is data type needed?

It tells the compiler/interpreter how to interpret the data, for example,

For a variable `var`, its data (binary form) in the memory is `01100001`

+ If the data type for `var` is `uint8, uint16, ...`, it's value is `97`

+ If the data type for `var` is `double` (MATLAB default data type), it's value is $4.79243676466009147851271729082 \times 10^{-322}$

+ If the data type for `var` is `char`, it's value is `'a'` (ASCII Code)



### Data Types in MATLAB

![image-20211013161814330](C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211013161814330.png)

![image-20211013161917200](C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211013161917200.png)

Signed integer: Use the first bit to represent positive/negative, 2's complement (detail in VE270)

Unsigned integer: Only represent non-negative values, natural binary form



### Float-Point Numbers (Just for fun)

**Scientific notation in binary form**



![General double precision float.png](https://upload.wikimedia.org/wikipedia/commons/7/76/General_double_precision_float.png)



$Float = (-1)^{S} \times 2^{E-1023} \times (1 + M)$

Since it use 52 bits to represent the mantissa, its relative accuracy (`eps` in MATLAB) will be greater than 1 when the exponent is greater than 52, namely when the number is greater than $2^{52}$. Therefore, it's not precise to use `single/double` to represent big numbers, though their ranges are quite huge.



### Application in MATLAB (Only for Lab 1)

Since MATLAB is a weakly and dynamically typed language, usually we do not need to care about the actual data type, especially in VG101. However, there are some special cases that MATLAB's default data type will cause problem, for example,

In Lab1, we have to deal with a lot of huge integers, but we know that the `double` data type will have an `eps` greater than 1 when the number is greater than $2^{52}$, namely it cannot precisely represent a huge integer. To extend the range of integers that can be accepted for this program, we may convert the integer from `double` to `uint64`, and then the upper limit (precisely) of integer will become $2^{64}-1$, which is much larger than `double`.



## Characters and strings

### Overview

![image-20211013163722247](C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211013163722247.png)

+ Use single quotation for string

+ String is an array of characters,  so you can connect several strings through matrix ways

  + `['ab', 'cd', 'ef'] = 'abcdef'`

+ Traverse a string char by char,

  + ```matlab
    str = 'abc1def';
    for i = 1:length(str)
    	fprintf("%s ", str(i));
    end
    fprintf("\n");
    % a b c 1 d e f 
    ```

+ In MATLAB, char is actually encoded using the *UTF-16* encoding, which occupies 2 bytes in the memory, but in VG101, you can always treat it as the *ASCII* code.

  + https://www.ascii-code.com/

+ As it's *ASCII* code, there are some useful tricks,

  + ```matlab
    % check if a char is a digit
    if ch >= '0' && ch <= '9'
    	disp('is digit');
    end
    
    % calculate the sum of digits
    % 1. without char
    sumD = 0;
    while num > 1
    	sumD = sumD + mod(num, 10);
    	num = floor(num / 10);
    end
    
    % 2. with char
    sumD = sum(num2str(num) - '0');
    ```



### Useful functions for strings

```matlab
tf = strcmp(s1, s2);
k = strfind(str,pat);
newStr = strrep(str,old,new);
s = num2str(A);
X = str2double(str);
```

Use `help` function in MATLAB to get more information about these functions

Example:

![image-20211013170929012](C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211013170929012.png)



### Another useful function to split/count words

+ ***2020 Q3***

![image-20211013171406721](C:\Users\ancientmodern\AppData\Roaming\Typora\typora-user-images\image-20211013171406721.png)

```matlab
function count = CountWords(str)
    arr = split(str, ' ');
    count = length(arr);
end
% What happens if there are spaces at the begin/end of the string?
```



## Control Statements and Loops

Actually this is the most important part in the exam, and nearly appear in all exam problems, but it's hard to teach how to use them without real practice. Practice on every sample problems in VG101, and then I believe you can master control statements and loops.

### IF/ELSEIF/ELSE Branch

**Syntax:**

```matlab
if BOOLEAN
	BLOCK1
elseif BOOLEAN % be careful about the syntax
	BLOCK2
else
	BLOCK3
end
```



### Switch/Case Branch

**Syntax:**

```matlab
switch EXPRESSION
case VALUE1
	BLOBK1
case {VALUE2, VALUE3, VALUE4}
	BLOBK2
otherwise
	BLOCK3
end
```

**When to use switch/case**

1. Condition is simple
2. Duplicated expressions
3. Long branches



### While Loop

**Syntax:**

```matlab
while CONDITION
	BLOCK
end
```



### For Loop

**Syntax:**

```matlab
for element = ARRAY
	BLOCK
end
```



### Example for `break` and `continue`

```matlab
% Find the first Palindrome with even digits in an array
% e.g.
% arr = [12321 4423 1221 3232 121]
% ret = 1221
function ret = EvenPalindrome(arr)
    for i = 1:length(arr)
        str = num2str(arr(i)); % convert double into string
        n = length(str);
        if mod(n, 2) == 1 % if odd digits, jump to next iteration
            continue;
        end
        % check Palindrome
        isPalindrome = true;
        for j = 1:n/2
            if str(i) ~= str(n+1-i)   % if one char pair is not equivalent, 
                isPalindrome = false; % directly exit the check loop
                break;
            end
        end
        if isPalindrome   % if one Palindrome with even digits is found, 
            ret = arr(i); % give the value to ret and exit the loop,
            break;        % since we only need to find the first one
        end
    end
end
```





## Reminder

+ Read the problem carefully before you start writing the code, as it's an open-internet exam, you may use translation tools to help you understand the problem. (But do not blindly trust translation tools)
+ For all functions appear in today's RC, go checking the MATLAB official documentation if you do not understand how to use them.
+ If you cannot guarantee the correctness of your code, you can add some simple comments to describe the function of each part of your code, because we will give partial scores based on your code.



## Reference

1. Kaibin Wang (TA in VG101 2020FA), VG101 Jigang RC2 - Control statements, loops, functions and MATLAB in practice.md
2. Kaibin Wang, VG101 Mid1 Review.md
3. Yuexi Du (TA in VG1012020FA), ExampleExam.pdf
4. Jigang Wu, VG101 2021FA Lecture Slides


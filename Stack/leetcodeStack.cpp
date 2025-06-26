//* LeetCode questions on stack

#include <bits/stdc++.h>
using namespace std;

//? 224. Basic Calculator
//? Given a string s representing a valid expression, implement a basic
//calculator to evaluate it, and return the result of the evaluation.

//! Note: You are not allowed to use any built-in function which evaluates
//! strings as mathematical expressions, such as eval().

//* Topics: Stack

//* Intuition :
/*
Here we need to break the calculating step into different process according to
each character in string we encounter. We traverse the string from left to
right. If we find a digit then we make a number . If we find a '+' - we decide
that the sign will store value +1, then we know that surely a full number is
created before the plus sign appears, so we add number to result after
multiplying it with the initial sign, we restore value of number back to 0 and
value of sign back to +1. If we find a '-' - we decide that the sign will store
value -1, then we know that surelly a full number is created before the minus
sign appears, so we add the number to the result after multiplying with the
initial sign, we store value of number back to 0 and value of sign now becomes
-1. If we find a '(', this is the start of a sub-expression so we need to save
what we did till now, we push our result and sign to the stack and reset
variables number to 0, result to 0 and sign to +1. If we find ')', this means we
reached the end of a sub-expression, finish processing the sub-expression inside
parentheses, add the last number in sub-expression, reset number by 0, restore
previous state from stack - that is Sign before the opening parenthesis and
Result before the opening parenthesis, apply the sign to the sub-expression
result and add to previous result. Finally after traversing the string ends dont
miss to add the final number to result (handles case where string doesn't end
with operator). Return the result
*/

//* Solution :

class Solution {
public:
  int calculate(string s) {
    int n = s.length();
    stack<int> st; // Stack to store previous results and signs when
                   // encountering parentheses

    int number = 0; // Current number being built digit by digit
    int result = 0; // Current result of the expression
    int sign = 1;   // Current sign (1 for +, -1 for -)

    for (int i = 0; i < n; i++) {
      char ch = s[i];

      if (isdigit(ch)) {
        // Build the current number digit by digit
        // Convert char to int and add to existing number
        number = number * 10 + (ch - '0');
      } else if (ch == '+') {
        // Add the current number (with its sign) to result
        result += number * sign;
        // Reset for next number and set sign to positive
        number = 0;
        sign = 1;
      } else if (ch == '-') {
        // Add the current number (with its sign) to result
        result += number * sign;
        // Reset for next number and set sign to negative
        number = 0;
        sign = -1;
      } else if (ch == '(') {
        // Save current state before processing sub-expression
        // Push current result and sign onto stack
        st.push(result);
        st.push(sign);

        // Reset variables for the sub-expression inside parentheses
        result = 0;
        number = 0;
        sign = 1;
      } else if (ch == ')') {
        // Finish processing the sub-expression inside parentheses
        result += number * sign; // Add the last number in sub-expression
        number = 0;

        // Restore previous state from stack
        int stackSign = st.top(); // Sign before the opening parenthesis
        st.pop();
        int lastResult = st.top(); // Result before the opening parenthesis
        st.pop();

        // Apply the sign to the sub-expression result and add to previous
        // result
        result *= stackSign;
        result += lastResult;
      }
      // Skip spaces (they don't affect the calculation)
    }

    // Add the final number to result (handles case where string doesn't end
    // with operator)
    result += number * sign;
    return result;
  }
};

//* Time Complexity : O(n)
//* Space Complexity : O(n)

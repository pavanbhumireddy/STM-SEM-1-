# STM-SEM-1-
Certainly! Here’s a brief **overview** and explanation of what this C program does:

### **Overview of the Code**

**Purpose:**  
The program calculates the sine (sin) of a user-provided number that must lie strictly between 0 and 1 (not including 0 or 1). It checks input validity and displays an appropriate message or the computed value.

### **Key Components**

1. **Header Files:**
   - `#include `: For input/output (e.g., `printf`, `scanf`)
   - `#include `: For the `sin()` mathematical function

2. **Variables:**
   - `inputValue`: Stores the user input as a double-precision floating-point number.
   - `result`: Stores the result of the sine computation.

3. **User Input:**
   - Prompts the user to enter a value strictly between 0 and 1.
   - Uses `scanf` to read the value into `inputValue`.

4. **Input Validation:**
   - Checks if `inputValue` is **not** in the exclusive range (0, 1).
   - If it’s not, the program outputs an error and exits.

5. **Sine Calculation:**
   - If the input is valid, it computes the sine of the value (in radians) using the `sin()` function.

6. **Output:**
   - Displays the sine of the input, formatted to six decimal places.

### **Typical Output Example**

**Input:**  
`Enter a value between 0 and 1 (exclusive): 0.5`

**Output:**  
`The sine of 0.500000 is 0.479426`

### **Highlights & Notes**

- The `sin()` function expects radians, so the input should be interpreted in radians.
- The program **excludes** 0 and 1 as valid inputs.
- If the user enters a value outside (0,1), an error message is printed, and the program exits with a non-zero status.
- The code is simple and demonstrates input validation, use of library math functions, and formatted output.

**Summary:**  
This program demonstrates robust user input validation, basic mathematical computation (sine of a value), and clear formatted output—an excellent example for learning user prompt, validation, and C math library basics.

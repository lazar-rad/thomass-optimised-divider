# Thomas’s optimised divider

A class that computes the quotient and the remainder of integer division without the use of classic division

This was written, for the most part, as an excercise. Performance hasn’t been tested yet.

## Use cases

Useful if you are doing a lot of divisions with a same divisor and need both the quotient and the remainder

## How  to use

Include the header "tod.h".
Instantiate an object of the class `Divider`, specifying its divisor and optionally the number of shift bits.
Use its overriden `operator ()` method to perform a divison on your dividend.
The returned value is of type `struct divres` (see in "tod.h") and contains in its fields both the quotient and the remainder.

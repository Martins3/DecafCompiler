# TAC IR Introduction to TAC: ● TAC for simple expressions.  ● TAC for functions and function calls.  ● TAC for objects.  ● TAC for arrays

> 暂时不去处理优化的问题


## low level probelms
You must also take care of some low-level details:
● Assign all parameters, local variables, and temporaries positions
in a stack frame.
● Assign all global variables positions in the global memory
segment.
● Assign all fields in a class an offset from the base of the object


Uses vtables for dynamic dispatch

Evaluating an expression with more than three subexpressions requires the introduction of temporary variables

tac allows for instructions with two operants

## control flow
TAC allows for named labels indicating
particular points in the code that can be
jumped to.
● There are two control flow instructions:
● Goto label;
● IfZ value Goto label;
● Note that IfZ is always paired with Goto.

## Stack Management in TAC
● The BeginFunc N; instruction only needs to
reserve room for local variables and
temporaries.
● The EndFunc; instruction reclaims the room
allocated with BeginFunc N;
● A single parameter is pushed onto the stack by
the caller using the PushParam var instruction.
● Space for parameters is reclaimed by the caller
using the PopParams N; instruction.
● N is measured in bytes, not number of arguments.

## Storage Allocation
As described so far, TAC does not specify
where variables and temporaries are
stored.
● For the final programming project, you
will need to tell the code generator where
each variable should be stored.
● This normally would be handled during
code generation, but Just For Fun we
thought you should have some experience
handling this.

## global variable

Remember:
● Parameters start at fp + 4 and grow upward.
● Locals start at fp – 8 and grow downward.
● Globals start at gp + 0 and grow upward


## create objects
调用mem alloc 的函数， 参数是地址

```
int main() {
Base b;
b = new Derived;
b.hi();
}
main:

BeginFunc 20;

// alloc objects
_t0 = 4;
PushParam _t0;
b = LCall _Alloc;
PopParams 4;

// set vtable
_t1 = Derived;
*b = _t1;


_t2 = *b;
_t3 = *_t2;
PushParam b;
ACall _t3;
PopParams 4;
EndFunc;
```


## vtable
https://en.wikipedia.org/wiki/Virtual_method_table

为了支持动态绑定， 而不是动态分配

The address of an object's vtable can be
referenced via the name assigned to the vtable
(usually the object name).
● e.g. _t0 = Base;
● When creating objects, you must remember to
set the object's vtable pointer or any method
call will cause a crash at runtime.
● The ACall instruction can be used to call a
method given a pointer to the first instruction.
Generating TA

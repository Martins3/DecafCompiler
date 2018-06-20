# 动态绑定的方法
Create a single instance of the vtable for each class.
● Have each object store a pointer to the vtable.
● Can follow the pointer to the table in O(1).
● Can index into the table in O(1).
● Can set the vtable pointer of a new object in O(1).
● Increases the size of each object by O(1).

A General Inheritance Framework
● Each object stores a pointer to a descriptor for its
class.
● Each class descriptor stores
● A pointer to the base class descriptor(s).
● A pointer to a method lookup table.
● To invoke a method:
● Follow the pointer to the method table.
● If the method exists, call it.
● Otherwise, navigate to the base class and repeat.
● This is slow but can be optimized in many cases;
we'll see this later.

# 指针是做什么

fp frame pointer
sp 计算的位置总是真正stack 的位置， 但是fp 记录的进入之前sp 的位置
ra 记录返回的位置

函数参数的处理方法，在进入函数之前开始处理的东西

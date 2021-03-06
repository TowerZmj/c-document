# 10 名字控制

## 10.1 来自c语言中的静态元素

* 在c和c++中，static都有两种基本的含义：
  * 在固定的地址上进行存储分配，也就是说对象是在一个特殊的静态数据区上创建的，而不是每次函数调用时在堆栈上产生的。这也是静态存储的概念。
  * 对一个特定的编译单位来说是局部的。这样，static控制名字的可见性，所以这个名字在这个单元或类之外是不可见的。
* c和c++中都允许在函数内部定义一个static对象，这个对象将存储在程序的静态数据区中，而不是在堆栈中。这个对象只在函数第一次调用时初始化一次，以后它在函数调用之间保持它的值。
* 如果定义一个静态对象时没有指定构造函数参数，这个类就必须有默认的构造函数。

## 10.2 名字空间

* namespace与class、struct、union和enum有着明显的区别：

  * namespace只能在全局范围内定义，但它们之间可以相互嵌套
  * 在namespace定义的结尾，右花括号的后面不必跟一个分号
  * 一个namespace可以在多个头文件中用一个标识符来定义，就好像重复定义一个类一样
  * 一个namespace的名字可以用另一个名字来作它的别名` namespace Bob =BobsSuperDuperLibrary; `  
  * 不能像类那用去创建一个名字空间的实例
* 每个翻译单元都可包含一个未命名的名字空间，在这个空间中的名字自动地在翻译单元内无限制地有效。但要确保每个翻译单元只有一个未命名的名字空间。
* 在一个名字空间中引用一个名字可以采取三种方法：
  * 作用域运算符
  * using指令把所有名字引入到名字空间中
  * using声明 一次性引用名字
* 对于一个实现文件来说，全局using指令通常是一个好方法，因为只有在文件编译结束时，using指令才会起作用。也就是说，它不会影响任何其他的文件，所以可以每次在一个实现文件中调整对名字空间的控制。头文件的情况与此不同，不要把一个全局using指令引入到一个头文件中，因为那将意味着包含这个头文件的任何其他头文件也会打开这个名字空间。

## 10.3 c++z中静态成员

* 因为类的静态数据成员有着单一的存储空间而不管产生多少个对象，所以存储空间必须在一个单独的地方定义。编译器不会分配存储空间。如果一个静态数据成员被声明但没有定义时，连接器会报告一个错误。定义必须出现在类的外部而且只能定义一次，因此它通常放在一个类的实现文件中。这种规定常常让人感到很麻烦，但它实际上是很合理的。

```c++
class A{
  	static int i;
public:
    //...
};
//之后必须在定义文件中为静态数据成员定义存储区：
int A::i = 1;
```

可能会对A::i是私有的这点感到疑惑，但是有两个原因可以保证它绝对的安全。第一，这些变量初始化唯一合法的地方是在定义时。事实上，如果静态数据成员是一个带构造函数的对象时，可以调用构造函数来代替“=”操作符；第二，一旦这些数据被定义了，最终的用户就不能在定义它——否则连接器会报告错误。

* 利用全部类型的静态常量，可以在类内提供这些定义，但是对于其他的对象，必须为这些成员提供专门的外部定义。这些定义是内部连接的，所以可以把他们放在头文件中，初始化静态数组的方法和其他集合类型的初始化一样，包括自动计数。
* 也可以创建类的静态常量对象和这样的对象的数组。不过，不能使用“内联语法”初始化他们，这种语法对全部的内部类型的静态常量有效。类对象的常量和非常量静态数组的初始化必须以相同的方式执行。
* 可以很容易的把一个静态数据成员放在另一个类的嵌套类中。然而不能在局部类（在函数内部定义的类）中有静态数据成员。
* 像静态数据成员一样，也可以创建一个静态成员函数，它为类的全体对象服务而不是为一个类的特殊对象服务。这样就不需要定义一个全局函数，减少了全局或局部名字空间的占用，把这个函数移到了类的内部。
* 可以用普通的方法调用静态成员函数，用点"."和箭头"->"把它和一个对象相联系。然而，调用静态成员函数的一个更典型的方法是自我调用，这不需要任何具体的对象，而是像下面使用作用域运算符：

```c++
class X{
public:
	static void f(){};    	
};

int main(){
    X::f();
}
```

* 静态成员函数不能访问一般的数据成员，而只能访问静态数据成员，也只能调用其他的静态成员函数。

## 10.4 静态初始化的相依性

* 在一个指定的翻译单元中，静态对象的初始化顺序严格按照对象在该单元中定义出现的顺序。而清除的顺序则与初始化的顺序正好相反。但是，对于作用域为多个翻译单元的静态对象来说，不能保证严格的初始化顺序，也没有办法指定这种顺序。这可能会引起一些问题。


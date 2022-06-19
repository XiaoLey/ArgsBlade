[中文](#Chinese) [English](#English)

 [![GitHub](https://img.shields.io/github/license/xiaoley/ArgsBlade?style=flat-square)](https://github.com/XiaoLey/ArgsBlade/blob/main/LICENSE) [![Codecov](https://img.shields.io/codecov/c/github/xiaoley/ArgsBlade?logo=Codecov&style=flat-square)](https://codecov.io/gh/XiaoLey/ArgsBlade) [![GitHub Workflow Status (branch)](https://img.shields.io/github/workflow/status/xiaoley/ArgsBlade/CMake/main?logo=Github&style=flat-square)](https://github.com/XiaoLey/ArgsBlade/actions)

# <a id="Chinese" style="color: inherit;">ArgBlade - 参数切割工具</a>

ArgBlade可以根据自己的意愿切割main函数传入的参数，使得参数能够正确用于各种用途。

### 使用方式

以下是一个最简单的例子：

```c++
#include "argblade.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    ArgBlade::ArgVec vecSign{"-h", "-help"};
    ArgBlade::Blade b(argc, argv, vecSign);
    b.slicing();
    
    if(b.containsSign("-h") || b.containsSign("-help")) {
        std::cout << "------帮助------\n" << "---------------" << std::endl;
    }
    else {
        std::cout << "-- 错误参数 --\n-- 请输入 -help 或 -h 查看帮助" << std::endl;
    }
    
    return 0;
}

// 执行：./test1 -help
```

编译后，执行相应的传参操作，效果如下：

```shell
$ ./test1 -help
------帮助------
---------------
$ ./test1 -h
------帮助------
---------------
$ ./test1 -o
-- 错误参数 --
-- 请输入 -help 或 -h 查看帮助
$ 
```

还可以给标识符设置参数值，ArgBlade将会正确识别并且进行分类：

```shell
$ ./test2 -o f1 f2 f3 -i s1 s2 s3
```

当标识符重复了，ArgBlade会将相同标识符的参数值组合起来，以供程序使用：

```c++
// ./test3 -s s3 -o f1 -i s1 -o f2
ArgBlade::Blade b(argc, argv, {"-o", "-i", "-h"});
b.slicing();
size_t count = b["-o"].size();	// 2
```

还可以判断某个参数标识符是否含有某个参数值，并且能获取参数值数量：

```c++
bool b1 = b.contain("-o", "f2");	// true
bool b2 = b.contain("", "-s");		// true, 空字符串表示不属于任何标识符的参数组，此处"-s"并不是标识符，且紧跟着程序后面，因此它属于 "" 的参数
bool b3 = b.contain("", "s3");		// true
bool b4 = b.contain("", "-o");		// false, "-o"是标识符，不被当作 "" 的参数值
bool b5 = b.containsSign("-s");		// false
bool b6 = b.containsSign("-o");		// true
int n1 = b.getArgCount();			// 5
int n2 = b.getDirectArgCount();		// 2, "-s" and "s3"
```

可以获取实际标识符额数量：

```c++
// ./test4 -a -b -c
ArgBlade::Blade b(argc, argv);
b.setSigns({"-a", "-b", "-c", "-d", "-e", "-f", "-h"});
size_t count = getSignRealCount();	// 3
```



# <a id="English" style="color: inherit;">ArgBlade - Parameter Cutting Tool</a>

------

ArgBlade can cut the parameters passed in by the main function according to its own wishes, so that the parameters can be used correctly for various purposes.

### Usage

Here is the simplest example:

```c++
#include "argblade.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    ArgBlade::ArgVec vecSign{"-h", "-help"};
    ArgBlade::Blade b(argc, argv, vecSign);
    b.slicing();
    
    if(b.containsSign("-h") || b.containsSign("-help")) {
        std::cout << "------help------\n" << "----------------" << std::endl;
    }
    else {
        std::cout << "-- Error Param --\n-- Please enter -help or -h to show help" << std::endl;
    }
    
    return 0;
}

// execute: ./test1 -help
```

After compilation, perform the corresponding parameter transfer operation, the effect is as follows:

```shell
$ ./test1 -help
------help------
----------------
$ ./test1 -h
------help------
---------------
$ ./test1 -o
-- Error Param --
-- Please enter -help or -h to show help
$ 
```

It is also possible to set parameter values for identifiers, and ArgBlade will correctly identify and classify them:

```c++
// ./test3 -s s3 -o f1 -i s1 -o f2
ArgBlade::Blade b(argc, argv, {"-o", "-i", "-h"});
b.slicing();
size_t count = b["-o"].size();	// 2
```

You can also determine whether a parameter identifier contains a parameter value, and you can get the number of parameter values:

```c++
bool b1 = b.contain("-o", "f2");	// true
bool b2 = b.contain("", "-s");		// true, An empty string represents a parameter group that does not belong to any identifier, where ""-s" is not an identifier, it immediately follows the program, so it belongs to an "" parameter.
bool b3 = b.contain("", "s3");		// true
bool b4 = b.contain("", "-o");		// false, "-o" is an identifier that is not treated as a parameter value for ""
bool b5 = b.containsSign("-s");		// false
bool b6 = b.containsSign("-o");		// true
int n1 = b.getArgCount();			// 5
int n2 = b.getDirectArgCount();		// 2, "-s" and "s3"
```

The actual number of identifiers can be obtained:

```c++
// ./test4 -a -b -c
ArgBlade::Blade b(argc, argv);
b.setSigns({"-a", "-b", "-c", "-d", "-e", "-f", "-h"});
size_t count = getSignRealCount();	// 3
```


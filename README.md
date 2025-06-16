# GECS
A simple ECS library designed to build a software architecture and manage the lifecycle of objects. Here are some of the library's highlights:

* free license and source code;
* using the ECS design pattern;
* the library is written in C++20;
* a custom memory manager;
* the interaction of entities takes place using an events;
* logging with different levels of message importance;

The creation of this library was inspired by this article: https://tsprojectsblog.wordpress.com/portfolio/entity-component-system/

## Compilation
This library can be built using the Microsoft Visual Studio IDE. Just open the solution file and configure the configuration.

## Code example
```cpp
#include <iostream>
#define DT 1.0f

int main()
{
    GECS::Initialize();
 
    bool quit = false;
 
    while(quit == false) // game loop
    {
       // ...
       // some logic
       // ...
       GECS::GECSInstance->Update(DT);
    }
    ECS::Terminate();
    return 0;
}
```

## Other
The code for the logger has been modified and used from here: https://bitbucket.org/volkanozyilmaz/logcpp/src/master/

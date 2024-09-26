# Type Erasure

This pattern was inspired by Klaus Iglberger's presentations:
* [Type Erasure 2021](https://youtu.be/4eeESJQk-mw)
* [Type Erasure 2022](https://youtu.be/qn6OqefuH08)
* [Type Erasure 2023](https://youtu.be/7MNyAHp0h7A)

## When To Use

Type Erasure decouples operations from types by using external polymorphism. Allowing for easy addition of new types.

General:

* Easy to add types over adding operations.
* Types do not have dependency on operations.
* Restricts the operations to the public interface of the types.
* Enables a value semantic interface to promote simple natural code.

## Features

Create a Type:
```cpp
class TypeA
{
public:
};
```

Create an Operation:
```cpp
// Free function to handle TypeA
void OperationA(TypeA& type)
{
}

// Add OperationA to Type::TypeConcept. See typeerasuretype.h
class TypeConcept
{
public:
    ...
    virtual void OperationA() = 0;
};

// Call OperationA within Type::TypeModel. See typeerasuretype.h
template<class TType>
class TypeModel final : public TypeConcept
{
public:
    ...
    void OperationA() override
    {
        ::OperationA(m_Type); // Call the free function that handles this Operation/TType combination.
    }

    TType m_Type{};
};
```

Call an Operation:
```cpp
using Types = std::vector<Type>;

Types types{}
types.emplace_back(TypeA{});
for(Type& type : types)
{
    type.OperationA();
}
```

## Setup

This repository uses the .sln/.proj files created by Visual Studio 2022 Community Edition.
Using MSVC compiler, Preview version(C++23 Preview). 

### Catch2
The examples for how to use the pattern are written as Unit Tests.

Launching the program in Debug or Release will run the Unit Tests.

Alternative:
Installing the Test Adapter for Catch2 Visual Studio extension enables running the Unit Tests via the Test Explorer Window. Setup the Test Explorer to use the project's .runsettings file.

### vcpkg
This repository uses vcpkg in manifest mode for it's dependencies. To interact with vcpkg, open a Developer PowerShell (View -> Terminal).

To setup vcpkg, install it via the Visual Studio installer. To enable/disable it run these commands from the Developer PowerShell:
```
vcpkg integrate install
vcpkg integrate remove
```

To add additional dependencies run:
```
vcpkg add port [dependency name]
```

To update the version of a dependency modify the overrides section of vcpkg.json. 

To create a clean vcpkg.json and vcpkg-configuration.json file run:
```
vcpkg new --application
```

### TODO
- [x] Implementation
- [x] Unit Tests
- [x] Benchmarks

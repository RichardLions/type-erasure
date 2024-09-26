#pragma once

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

#include "typeerasuretype.h"
#include "types.h"

TEST_CASE("Type Erasure - Unit Tests")
{
    Types types{};
    REQUIRE(types.size() == 0);

    SECTION("Call Operations")
    {
        types.emplace_back(TypeA{});
        types.emplace_back(TypeB{});
        REQUIRE(types.size() == 2);
        REQUIRE(types[0].IsType<TypeA>());
        REQUIRE(types[1].IsType<TypeB>());
        REQUIRE_FALSE(types[0].IsType<TypeB>());
        REQUIRE_FALSE(types[1].IsType<TypeA>());

        // Type A
        {
            Type& type{types[0]};
            const TypeA* const typeA{type.IsType<TypeA>()};
            REQUIRE(typeA->GetInt() == 0);
            type.OperationA();
            REQUIRE(typeA->GetInt() == 1);
            type.OperationB();
            REQUIRE(typeA->GetInt() == -1);
        }

        // Type B
        {
            Type& type{types[1]};
            const TypeB* const typeB{type.IsType<TypeB>()};
            REQUIRE(typeB->GetFloat() == 0.0f);
            type.OperationA();
            REQUIRE(typeB->GetFloat() == 1.0f);
            type.OperationB();
            REQUIRE(typeB->GetFloat() == -1.0f);
        }
    }

    SECTION("Assign Types")
    {
        types.emplace_back(TypeA{});
        types.emplace_back(TypeB{});
        REQUIRE(types.size() == 2);
        REQUIRE(types[0].IsType<TypeA>());
        REQUIRE(types[1].IsType<TypeB>());
        REQUIRE_FALSE(types[0].IsType<TypeB>());
        REQUIRE_FALSE(types[1].IsType<TypeA>());

        types[0] = types[1];
        REQUIRE(types.size() == 2);
        REQUIRE(types[0].IsType<TypeB>());
        REQUIRE(types[1].IsType<TypeB>());
        REQUIRE_FALSE(types[0].IsType<TypeA>());
        REQUIRE_FALSE(types[1].IsType<TypeA>());

        // 0
        {
            Type& type{types[0]};
            const TypeB* const typeB{type.IsType<TypeB>()};
            REQUIRE(typeB->GetFloat() == 0.0f);
            type.OperationA();
            REQUIRE(typeB->GetFloat() == 1.0f);
            type.OperationB();
            REQUIRE(typeB->GetFloat() == -1.0f);
        }

        // 1
        {
            Type& type{types[1]};
            const TypeB* const typeB{type.IsType<TypeB>()};
            REQUIRE(typeB->GetFloat() == 0.0f);
            type.OperationA();
            REQUIRE(typeB->GetFloat() == 1.0f);
            type.OperationB();
            REQUIRE(typeB->GetFloat() == -1.0f);
        }

        types[0] = TypeA{};
        REQUIRE(types.size() == 2);
        REQUIRE(types[0].IsType<TypeA>());
        REQUIRE(types[1].IsType<TypeB>());
        REQUIRE_FALSE(types[0].IsType<TypeB>());
        REQUIRE_FALSE(types[1].IsType<TypeA>());

        // Type A
        {
            Type& type{types[0]};
            const TypeA* const typeA{type.IsType<TypeA>()};
            REQUIRE(typeA->GetInt() == 0);
            type.OperationA();
            REQUIRE(typeA->GetInt() == 1);
            type.OperationB();
            REQUIRE(typeA->GetInt() == -1);
        }

        // Type B
        {
            Type& type{types[1]};
            const TypeB* const typeB{type.IsType<TypeB>()};
            REQUIRE(typeB->GetFloat() == -1.0f);
            type.OperationA();
            REQUIRE(typeB->GetFloat() == 1.0f);
            type.OperationB();
            REQUIRE(typeB->GetFloat() == -1.0f);
        }
    }

    SECTION("Copy Types")
    {
        types.emplace_back(TypeA{});
        types.emplace_back(TypeB{});
        REQUIRE(types.size() == 2);
        REQUIRE(types[0].IsType<TypeA>());
        REQUIRE(types[1].IsType<TypeB>());
        REQUIRE_FALSE(types[0].IsType<TypeB>());
        REQUIRE_FALSE(types[1].IsType<TypeA>());

        // 1
        {
            Type& type{types[1]};
            const TypeB* const typeB{type.IsType<TypeB>()};
            REQUIRE(typeB->GetFloat() == 0.0f);
            type.OperationA();
            REQUIRE(typeB->GetFloat() == 1.0f);
        }

        types[0] = types[1];
        REQUIRE(types.size() == 2);
        REQUIRE(types[0].IsType<TypeB>());
        REQUIRE(types[1].IsType<TypeB>());
        REQUIRE_FALSE(types[0].IsType<TypeA>());
        REQUIRE_FALSE(types[1].IsType<TypeA>());

        // 0
        {
            const TypeB* const typeB{types[0].IsType<TypeB>()};
            REQUIRE(typeB->GetFloat() == 1.0f);
        }
    }
}

TEST_CASE("Type Erasure - Benchmarks")
{
    BENCHMARK("Benchmark")
    {
        constexpr uint32_t creationCount{100'000};
        Types types{};

        for(uint32_t i{0}; i != creationCount; ++i)
        {
            types.emplace_back(TypeA{});
            types.emplace_back(TypeB{});
        }

        for(Type& type : types)
        {
            type.OperationA();
            type.OperationB();
        }
    };
}

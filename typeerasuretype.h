#pragma once

#include <memory>
#include <vector>

#include "typeoperations.h"

class Type
{
public:
    template<class TType>
    Type(TType&& type)
        : m_Pimpl{std::make_unique<TypeModel<TType>>(std::move(type))}
    {
    }

    Type(const Type& other)
        : m_Pimpl{other.m_Pimpl->Clone()}
    {
    }

    Type& operator=(const Type& other)
    {
        if(this == &other)
            return *this;

        other.m_Pimpl->Clone().swap(m_Pimpl);
        return *this;
    }

    Type(Type&& other) = default;
    Type& operator=(Type&& other) = default;

    void OperationA()
    {
        m_Pimpl->OperationA();
    }

    void OperationB()
    {
        m_Pimpl->OperationB();
    }

    /// Unsafe - Used by Unit Tests
    template<class T>
    const T* IsType() const
    {
        const TypeModel<T>* const type{dynamic_cast<TypeModel<T>*>(m_Pimpl.get())};
        if(!type)
            return nullptr;

        return dynamic_cast<const T*>(&type->m_Type);
    }

private:
    class TypeConcept
    {
    public:
        virtual ~TypeConcept() = default;
        virtual std::unique_ptr<TypeConcept> Clone() const = 0;
        virtual void OperationA() = 0;
        virtual void OperationB() = 0;
    };

    template<class TType>
    class TypeModel final : public TypeConcept
    {
    public:
        TypeModel(TType&& type)
            : m_Type{std::move(type)}
        {
        }

        std::unique_ptr<TypeConcept> Clone() const override
        {
            return std::make_unique<TypeModel>(*this);
        }

        void OperationA() override
        {
            ::OperationA(m_Type);
        }

        void OperationB() override
        {
            ::OperationB(m_Type);
        }

        TType m_Type{};
    };

    std::unique_ptr<TypeConcept> m_Pimpl{};
};

using Types = std::vector<Type>;

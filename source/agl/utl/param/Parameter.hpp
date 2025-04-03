#pragma once

#include <sead/prim/seadSafeString.hpp>

#include "ParameterBase.hpp"

namespace agl::utl {
    template<typename T>
    struct Parameter : public ParameterBase {
        T mData;

        virtual ParameterType getParameterType();
        virtual const void* ptr() const;
        virtual void* ptr();
        /* TODO: how tf did they do this */
        // virtual const T* typePtr() const;
        // virtual T* typePtr();
        virtual const void* typePtr() const;
        virtual void* typePtr();
        virtual int size() const;
        virtual int calcBinarizeSize();
        virtual Parameter<T>* clone(sead::Heap*, IParameterObj*) const;
    };
}
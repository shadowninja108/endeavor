#pragma once

#include <common.hpp>

#include <sead/heap/seadHeap.h>

/* TODO: */
namespace sead {
    struct XmlElement;
}

namespace agl::utl {
    struct IParameterObj;
    struct ParameterBase {
        enum class ParameterType {
            Bool,
            F32,
            Int,
            Vec2,
            Vec3,
            Vec4,
            Color,
            String32,
            String64,
            Curve1,
            Curve2,
            Curve3,
            Curve4,
            BufferInt,
            BufferF32,
            String256,
            Quat,
            U32,
            BufferU32,
            BufferBinary,
            StringRef
        };
        
        uint mHash;
        ParameterBase* mNext;

        virtual ~ParameterBase();
        virtual bool copy(ParameterBase const&);
        virtual void copyUnsafe(ParameterBase const&);
        virtual bool copyLerp(ParameterBase const&, ParameterBase const&, float);
        virtual void writeToXML(sead::XmlElement*, sead::Heap*);
        virtual void readFromXML(sead::XmlElement const&, bool);
        virtual ParameterType getParameterType() = 0;
        virtual const void* ptr() const = 0;
        virtual void* ptr() = 0;
        virtual const void* typePtr() const = 0;
        virtual void* typePtr() = 0;
        virtual int size() const = 0;
        virtual int calcBinarizeSize() = 0;
        virtual ParameterBase* clone(sead::Heap*, IParameterObj*) const = 0;
        virtual void postApplyResource_(void const*, ulong);
        virtual bool isBinary() const;
        virtual bool isBinaryInternalBuffer() const;
    };
    static_assert(sizeof(ParameterBase) == 0x18);
}
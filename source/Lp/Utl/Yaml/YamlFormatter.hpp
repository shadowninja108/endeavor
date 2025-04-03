#pragma once

#include <common.hpp>

#include <sead/math/seadVector.hpp>
#include <sead/math/seadBoundBox.hpp>
#include <sead/gfx/seadColor.h>
#include <sead/hostio/seadHostIOCurve.h>
#include <sead/stream/seadStream.h>

namespace Lp::Utl {
    struct YamlFormatter {
        sead::Stream* mStream;
        int mDepth;

        void startDocument(void);
        void startHash(char const*);
        void writeIndent(void);
        void endHash(void);
        void startArray(void);
        void endArray(void);
        void writeComment(char const*);
        void writeHashBool(char const*,bool);
        void writeHashInt(char const*,int);
        void writeHashInt64(char const*,long);
        void writeHashInt(char const*,int const*,int);
        void writeHashUInt(char const*,uint);
        void writeHashUInt(char const*,uint const*,int);
        void writeHashUIntHex(char const*,uint);
        void writeHashUIntHex(char const*,uint const*,int);
        void writeHashUInt64(char const*,ulong);
        void writeHashUInt64Hex(char const*,ulong);
        void writeHashFloat(char const*,float);
        void writeHashDouble(char const*,double);
        void writeHashFloat(char const*,float const*,int);
        void writeHashString(char const*,char const*);
        void writeBlockString(char const*,char const*);
        void writeHashV2f(char const*,sead::Vector2f const&);
        void writeHashV2s32(char const*,sead::Vector2<int> const&);
        void writeHashV3f(char const*,sead::Vector3f const&);
        void writeHashV4f(char const*,sead::Vector4f const&);
        void writeHashBox3f(char const*,sead::BoundBox3f const&);
        void writeHashColor(char const*,sead::Color4f const&);
        void writeHashCurve(char const*,sead::hostio::Curve<float> const&);
        void writeHashNull(char const*);
        void writeArrayBool(bool);
        void writeArrayInt(int);
        void writeArrayInt(int const*,int);
        void writeArrayUInt(uint);
        void writeArrayUInt(uint const*,int);
        void writeArrayUIntHex(uint);
        void writeArrayUIntHex(uint const*,int);
        void writeArrayFloat(float);
        void writeArrayFloat(float const*,int);
        void writeArrayString(char const*);
        void writeArrayInt64(long);
        void writeArrayUInt64(ulong);
        void writeArrayUInt64Hex(ulong);
        void writeArrayDouble(double);
        void setStream(sead::WriteStream *);

        virtual ~YamlFormatter();
        virtual void writeString(const char*, ...);
    };
}
#pragma once

#include <agl/utl/param/ParameterList.hpp>

#include <sead/heap/seadHeap.h>

#include "ParamNode.hpp"

namespace Lp::Sys {
    struct Params : public ParamNode {
        SEAD_RTTI_OVERRIDE(Params, ParamNode);

        agl::utl::ParameterList mAglList;
        ParamNode* mHead;
        sead::Heap* mLoadHeap;

        virtual void pathName(sead::BufferedSafeStringBase<char>*) const;
        virtual const char* extName() const;
        virtual bool makePathName(sead::BufferedSafeStringBase<char>*, bool);
        virtual void save(sead::SafeStringBase<char> const&);
        virtual bool load(sead::SafeStringBase<char> const&);
        virtual void convertTool_(sead::SafeStringBase<char> const&);
        virtual void commit_(sead::SafeStringBase<char> const&);
        virtual void writeAglParam(sead::SafeStringBase<char> const&, sead::SafeStringBase<char> const&) const;
        virtual void readAglParam(unsigned char const*);
    };
    static_assert(sizeof(Params) == 0xA0);
}
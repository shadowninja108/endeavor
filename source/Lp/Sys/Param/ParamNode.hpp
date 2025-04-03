#pragma once

#include <common.hpp>

#include <sead/container/seadTreeNode.h>
#include <sead/prim/seadSafeString.hpp>
#include <sead/prim/seadRuntimeTypeInfo.h>
#include <sead/prim/seadFormatPrint.h>
#include <sead/stream/seadStream.h>

#include <Lp/Utl/Byaml/Iter/ByamlIter.hpp>
#include <Lp/Utl/Byaml/Writer/ByamlWriter.hpp>
#include <Lp/Utl/Yaml/YamlWriter.hpp>

namespace Lp::Sys {
    struct Params;
    struct ParamNode {
        SEAD_RTTI_BASE(ParamNode);

        struct Arg {
            sead::SafeString mName;
            sead::SafeString mComment;
            sead::SafeString mArgs;
            /* TODO: */
            uint mFlags;
        };

        uintptr_t field_8;
        sead::IntrusiveTreeNode<ParamNode> mTreeNode;
        sead::SafeString mName;
        /* TODO: */
        uint mFlags;

        virtual ~ParamNode();
        virtual void key(sead::BufferedSafeString*) const;
        virtual void label(sead::BufferedSafeString*) const;
        virtual void meta(sead::BufferedSafeString*) const;
        virtual bool isEqual(ParamNode const&) const;
        virtual void copy(ParamNode const&);
        virtual void lerp(ParamNode const&, ParamNode const&, float);
        virtual void onApply();
        virtual void readByaml(Lp::Utl::ByamlIter&);
        virtual void writeByaml(Lp::Utl::ByamlWriter&) const;
        virtual void writeYaml(Lp::Utl::YamlWriter&) const; /* This should really take a YamlFormatter...? */
        virtual void readStream(sead::ReadStream&);
        virtual void writeStream(sead::WriteStream&) const;
        virtual void copyAglParam() const;
        virtual void applyAglParam(void const*, unsigned long);
        virtual void formatPrint_(char const*, sead::PrintOutput*) const;
        virtual void addToParent(Params*);
        virtual void removeFromParent(Params*);
    };
    static_assert(sizeof(ParamNode) == 0x50);
}
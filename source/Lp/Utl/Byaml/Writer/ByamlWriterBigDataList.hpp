#pragma once

#include <sead/container/seadTList.h>

#include "Primitives/ByamlWriterBigData.hpp"

namespace Lp::Utl  {
    struct ByamlWriterBigDataList {
        sead::TList<ByamlWriterBigData*> mChildren;

        virtual ~ByamlWriterBigDataList();
        void addData(ByamlWriterBigData*);
        int calcPackSize() const;
        void setOffset(int);
        void write(sead::WriteStream*);
    };
}
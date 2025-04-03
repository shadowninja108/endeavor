#pragma once

#include "../TextSave.hpp"
#include "YamlFormatter.hpp"

namespace Lp::Utl {
    struct YamlWriter : public YamlFormatter, public TextSave {

        YamlWriter(sead::SafeString const& fileName, uint bufferSize);

        virtual ~YamlWriter();
        virtual void writeString(const char*, ...);
    };
}
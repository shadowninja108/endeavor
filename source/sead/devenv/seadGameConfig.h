#pragma once

#include "heap/seadDisposer.h"
#include "hostio/seadHostIONode.h"
#include "prim/seadSafeString.h"

namespace sead
{
class GameConfig : public hostio::Node
{
    SEAD_SINGLETON_DISPOSER(GameConfig)

    struct String {
        sead::BufferedSafeString* mString;
        ulong field_8;
        int mMaxLength;
    };

    GameConfig();
    virtual ~GameConfig();

public:
    bool* findBoolImpl_(sead::SafeString const&, bool) const;
    float* findF32Impl_(sead::SafeString const&, bool) const;
    s32* findS32Impl_(sead::SafeString const&, bool) const;
    String* findStringImpl_(sead::SafeString const&, bool) const;
    u32* findU32Impl_(sead::SafeString const&, bool) const;

    static const SafeString cNodeName;

protected:
    struct FileWriteCallback
    {
        virtual ~FileWriteCallback();
        virtual void save();
    };
};
}  // namespace sead

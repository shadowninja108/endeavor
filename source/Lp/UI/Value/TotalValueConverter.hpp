#pragma once

namespace Lp::UI {
    struct ValueConverter;
    struct TypeInfo;
    struct TotalValueConverter {
        ValueConverter* field_0;
        ValueConverter* field_8;
        ValueConverter* field_10;
        const TypeInfo* mFromType;
        const TypeInfo* mToType;
        bool mInitialized;
    };
}
#pragma once

#include "Menu/DbgMenuPage.hpp"

namespace Cmn {
    DbgMenuPage* FindOrCreateDbgMenuPage(sead::SafeString const&, bool doCreate);
}
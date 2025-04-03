#pragma once

/* Their runtime is based on 5.1.3. Seems to have very little customization beyond a few additional calls. */

struct lua_State;

typedef int (*lua_CFunction)(lua_State *L);
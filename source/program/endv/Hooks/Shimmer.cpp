#include <lib.hpp>
#include "../../shimmer/socket.hpp"
#include "../../shimmer/client.hpp"

namespace endv::hooks::shimmer {
    HOOK_DEFINE_TRAMPOLINE(SocketInit) {
        static Result Callback(nn::socket::Config const& config) {
            Logging.Log("[endeavor] Socket initialize");

            static bool s_Initialized = false;
            if(s_Initialized) {
                return 0;
            }
   
            auto res = Orig(config);
            R_ABORT_UNLESS(res);

            ::shimmer::client::Start();

            s_Initialized = true;
            
            return res;

        }
    };

    HOOK_DEFINE_TRAMPOLINE(SocketFinalize) {
        static Result Callback() {
            return 0;
        }
    };
    
    void Install() {
        SocketInit::InstallAtFuncPtr(nn::socket::detail::InitializeCommon);
        SocketFinalize::InstallAtFuncPtr(nn::socket::Finalize);
    }
}
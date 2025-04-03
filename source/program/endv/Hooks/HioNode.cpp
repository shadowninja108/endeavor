#include "HioNode.hpp"

#include <lib.hpp>

#include <Lp/Utl/Hio.hpp>

#include <shimmer/client.hpp>
#include <shimmer/protocol.hpp>

#include <cstdarg>
#include <cstring>

#include "../Memory.hpp"

namespace endv::hooks::hio_node {
    /* 
        For whatever reason, the callers sometimes are missing the meta arg. 
        No sane way to check this other than special casing every caller, so there's some dumb shit I have to do. 
        TODO: dear god I hope this works reliably 
    */

    HOOK_DEFINE_REPLACE(AddNodeToCategoryStationed) {
        static void* Callback(void* child, const char* name, const char* parent, const char* meta, ...) {
            std::va_list args;
            va_start(args, meta);
            va_end(args);

            Logging.Log("addNodeToCategoryStationed %s %s", name, parent);
            
            if(!memory::IsValidStringPointer(meta)) {
                meta = nullptr;
            }

            shimmer::protocol::AddNodeToCategoryStationedType packet {};
            packet.mutable_key() = reinterpret_cast<uintptr_t>(child);
            packet.mutable_parentLabel() = parent;
            packet.mutable_label() = name;
            if(meta != nullptr) {
                packet.mutable_meta() = meta;
            }
            shimmer::client::Send(packet);

            return nullptr;
        }
    };
    HOOK_DEFINE_REPLACE(AddNodeToCategory) {
        static void* Callback(void* child, const char* name, const char* parent, const char* meta, ...) {
            std::va_list args;
            va_start(args, meta);
            va_end(args);

            Logging.Log("addNodeToCategory %s", name);

            // if(!memory::IsValidStringPointer(meta)) {
                meta = nullptr;
            // }

            shimmer::protocol::AddNodeToCategoryType packet {};
            packet.mutable_key() = reinterpret_cast<uintptr_t>(child);
            packet.mutable_parentLabel() = parent;
            packet.mutable_label() = name;
            if(meta != nullptr) {
                packet.mutable_meta() = meta;
            }
            shimmer::client::Send(packet);

            return nullptr;
        }
    };
    HOOK_DEFINE_REPLACE(AddNodeToParent) {
        static void* Callback(void* parent, void* child, const char* name, const char* meta, ...) {
            std::va_list args;
            va_start(args, meta);
            va_end(args);

            Logging.Log("addNodeToParent %s", name);

            // if(!memory::IsValidStringPointer(meta)) {
                meta = nullptr;
            // }

            shimmer::protocol::AddNodeToParentType packet {};
            packet.mutable_key() = reinterpret_cast<uintptr_t>(child);
            packet.mutable_parentKey() = reinterpret_cast<uintptr_t>(parent);
            packet.mutable_label() = name;
            if(meta != nullptr) {
                packet.mutable_meta() = meta;
            }
            shimmer::client::Send(packet);

            return nullptr;
        }
    };
    HOOK_DEFINE_REPLACE(AddNodeToParentStationed) {
        static void* Callback(void* parent, void* child, const char* name, const char* meta, ...) {
            std::va_list args;
            va_start(args, meta);
            va_end(args);

            Logging.Log("addNodeToParentStationed %s", name);

            // if(!memory::IsValidStringPointer(meta)) {
                meta = nullptr;
            // }

            shimmer::protocol::AddNodeToParentStationedType packet {};
            packet.mutable_key() = reinterpret_cast<uintptr_t>(child);
            packet.mutable_parentKey() = reinterpret_cast<uintptr_t>(parent);
            packet.mutable_label() = name;
            if(meta != nullptr) {
                packet.mutable_meta() = meta;
            }
            shimmer::client::Send(packet);

            return nullptr;
        }
    };
    HOOK_DEFINE_REPLACE(AddNodeToRoot) {
        static void* Callback(void* child, const char* name, const char* meta ...) {
            std::va_list args;
            va_start(args, meta);
            va_end(args);

            Logging.Log("addNodeToRoot %s", name);

            if(!memory::IsValidStringPointer(meta)) {
                meta = nullptr;
            }

            shimmer::protocol::AddNodeToRootType packet {};
            packet.mutable_key() = reinterpret_cast<uintptr_t>(child);
            packet.mutable_label() = name;
            if(meta != nullptr) {
                packet.mutable_meta() = meta;
            }
            shimmer::client::Send(packet);

            return nullptr;    
        }
    };
    HOOK_DEFINE_REPLACE(AddNodeToRootStationed) {
        static void* Callback(void* child, const char* name, const char* meta, ...) {
            std::va_list args;
            va_start(args, meta);
            va_end(args);

            Logging.Log("addNodeToRootStationed %s", name);

            if(!memory::IsValidStringPointer(meta)) {
                meta = nullptr;
            }

            shimmer::protocol::AddNodeToRootStationedType packet {};
            packet.mutable_key() = reinterpret_cast<uintptr_t>(child);
            packet.mutable_label() = name;
            if(meta != nullptr) {
                packet.mutable_meta() = meta;
            }
            shimmer::client::Send(packet);

            return nullptr;    
        }
    };
    HOOK_DEFINE_REPLACE(InvalidateNode) {
        static void Callback(void* node, ...) {

        }
    };
    HOOK_DEFINE_REPLACE(SelectNode) {
        static void Callback(void* node, const char* name,...) {

        }
    };
    HOOK_DEFINE_REPLACE(FindNode) {
        static void* Callback(const char* name, void* parent, ...) {
            return nullptr;
        }
    };
    HOOK_DEFINE_REPLACE(AddEmptyNodeToRoot) {
        static void* Callback(const char* name, const char* meta, ...) {
            std::va_list args;
            va_start(args, meta);
            va_end(args);

            Logging.Log("addEmptyNodeToRoot %s", name);

            if(!memory::IsValidStringPointer(meta)) {
                meta = nullptr;
            }

            shimmer::protocol::AddEmptyNodeToRootType packet {};
            packet.mutable_label() = name;
            if(meta != nullptr) {
                packet.mutable_meta() = meta;
            }
            shimmer::client::Send(packet);

            return nullptr;
        }
    };
    HOOK_DEFINE_REPLACE(AddEmptyNodeToRootStationed) {
        static void* Callback(const char* name, const char* meta, ...) {
            std::va_list args;
            va_start(args, meta);
            va_end(args);

            Logging.Log("addEmptyNodeToRootStationed %s", name);

            if(!memory::IsValidStringPointer(meta)) {
                meta = nullptr;
            }
            
            shimmer::protocol::AddEmptyNodeToRootStationedType packet {};
            packet.mutable_label() = name;
            if(meta != nullptr) {
                packet.mutable_meta() = meta;
            }
            shimmer::client::Send(packet);

            return nullptr;
        }
    };
    HOOK_DEFINE_REPLACE(UpdateMemoryNode) {
        static void Callback(void* node, ...) {

        }
    };
    HOOK_DEFINE_REPLACE(AddEmptyNode) {
        static void* Callback(const char* name, const char* parent, ...) {
            std::va_list args;
            va_start(args, parent);
            va_end(args);

            Logging.Log("addEmptyNode %s", name);

            shimmer::protocol::AddEmptyNodeType packet {};
            packet.mutable_label() = name;
            packet.mutable_parent() = parent;
            shimmer::client::Send(packet);

            return nullptr;
        }
    };
    
    void Install() {
        /* While type safety is all fine and dandy, unfortunately the devs used variadic functions with no args??? Seems like it's impossible to access the args like this. So, workaround by casting the function pointer to the callback's type. */
        #define NODE_INSTALL(nameUpper, name)   \
            nameUpper::InstallAtFuncPtr(reinterpret_cast<decltype(&nameUpper::Callback)>(&Lp::Utl::name))

        NODE_INSTALL(AddNodeToCategoryStationed, addNodeToCategoryStationed);
        NODE_INSTALL(AddNodeToCategory, addNodeToCategory);
        NODE_INSTALL(AddNodeToParent, addNodeToParent);
        NODE_INSTALL(AddNodeToParentStationed, addNodeToParentStationed);
        NODE_INSTALL(AddNodeToRoot, addNodeToRoot);
        NODE_INSTALL(AddNodeToRootStationed, addNodeToRootStationed);
        NODE_INSTALL(InvalidateNode, invalidateNode);
        NODE_INSTALL(SelectNode, selectNode);
        NODE_INSTALL(FindNode, findNode);
        NODE_INSTALL(AddEmptyNodeToRoot, addEmptyNodeToRoot);
        NODE_INSTALL(AddEmptyNodeToRootStationed, addEmptyNodeToRootStationed);
        NODE_INSTALL(UpdateMemoryNode, updateMemoryNode);
        NODE_INSTALL(AddEmptyNode, addEmptyNode);

        #undef NODE_INSTALL
    }
}
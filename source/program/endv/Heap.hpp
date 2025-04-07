#pragma once

#include <lib.hpp>
#include <sead/heap/seadHeap.h>
#include <sead/heap/seadExpHeap.h>

namespace endv::heap {
    extern bool s_IsProd;

    namespace impl {
        /* Leave the game enough room for it's own work. */
        //static constexpr size_t s_RequiredHeapLeft = 0x7A7B0000 + sizeof(sead::ExpHeap);
        static constexpr size_t s_HeapSize = 400 * 1024 * 1024;
        static constexpr size_t s_HeapSizeProd = 52 * 1024 * 1024;
        
        inline sead::Heap*& GetRootRef() {
            static sead::Heap* root = nullptr;
            return root;
        }
        template<typename Key> sead::Heap*& GetRef() {
            static sead::Heap* heap = nullptr;
            return heap;
        }
    }

    inline sead::Heap* GetRoot() { return impl::GetRootRef(); }

    inline void Initialize(sead::Heap* heap) {
        Logging.Log("[endeavor] Initializing heap...");
        
        /* Ensure the parent heap exists and we haven't created our root heap yet. */
        EXL_ASSERT(heap != nullptr);
        EXL_ASSERT(GetRoot() == nullptr);

        Logging.Log("parent size: %08llx parent free size: %08llx", heap->getSize(), heap->getFreeSize());

        /* Choose the appropriate heap size. */
        size_t heapSize = s_IsProd ? impl::s_HeapSizeProd : impl::s_HeapSize;
        Logging.Log("Using %s heap config", s_IsProd ? "prod" : "dev");

        /* Ensure we leave enough room for the game to do it's thang. */
        auto room = heap->getMaxAllocatableSize(8);
        EXL_ABORT_UNLESS(room > heapSize);

        /* Create root heap. */
        sead::Heap* root = sead::ExpHeap::tryCreate(
            heapSize, 
            "endv::RootHeap", 
            heap, 
            8, 
            sead::Heap::HeapDirection::cHeapDirection_Forward, 
            false
        );
        EXL_ABORT_UNLESS(root != nullptr);
        
        Logging.Log("[endeavor] Root heap created:");
        Logging.Log("heap size: %08llx free size: %08llx", root->getSize(), root->getFreeSize());

        impl::GetRootRef() = root;
    }

    template<typename Key>
    struct Disposer : public sead::IDisposer {

        explicit Disposer(sead::Heap* heap) : sead::IDisposer(heap) {}

        virtual ~Disposer() {
            /* If we are disposing this heap, clean up the pointers. */
            if(this == s_Instance) {
                Logging.Log("[endeavor] Destroying %s heap...", Key::Name);
                s_Instance = nullptr;
                impl::GetRef<Key>() = nullptr;
            }
        }

        static inline Disposer<Key>* s_Instance = nullptr;
    };

    template<typename Key>
    sead::Heap* Get() {
        using Disposer = Disposer<Key>;

        /* Lazily create heap. */
        auto& heap = impl::GetRef<Key>();
        if(EXL_UNLIKELY(heap == nullptr)) {
            Logging.Log("[endeavor] Creating %s heap...", Key::Name);

            /* Ensure the root heap is available. */
            auto root = GetRoot();
            EXL_ABORT_UNLESS(root != nullptr);

            /* Create heap within root heap. */
            heap = sead::ExpHeap::tryCreate(
                Key::Size, 
                sead::SafeString(Key::Name), 
                root, 
                Key::Alignment, 
                sead::Heap::HeapDirection::cHeapDirection_Forward, 
                false
            );
            /* Ensure the heap was created. */
            EXL_ABORT_UNLESS(heap != nullptr);

            /* Setup disposer for this heap. */
            Disposer::s_Instance = new (heap) Disposer(heap);

            Logging.Log("size: %08llx free size: %08llx", heap->getSize(), heap->getFreeSize());
        }

        return heap;
    }
}
#pragma once

#include <lib.hpp>
#include <nn.hpp>
#include <span>

#include <sead/thread/seadThread.h>

#include <WriteBufferFixedSize.h>
#include <Errors.h>
#include "../endv/Heap.hpp"
#include "socket.hpp"
#include "protocol.hpp"

namespace shimmer::client {
    namespace impl {

        struct HeapKey {
            static constexpr char Name[] = "shimmer::client";
            static constexpr size_t Size = 0x8000;
            static constexpr size_t Alignment = 0;
        };
        constexpr inline bool s_Enabled = false;

        constexpr inline size_t s_ThreadStackSize = 0x4000;
        constexpr inline size_t s_ThreadMessageQueueSize = 256;
        constexpr sead::MessageQueue::Element s_QuitMessage = -1;
        constexpr inline auto s_SocketPort = 4696;

        extern EmbeddedProto::WriteBufferFixedSize<1024> s_SerializeBuffer;
        extern nn::os::MutexType s_SerializeBufferMutex;
        extern exl::util::TypedStorage<sead::DelegateThread> s_ThreadStorage;
        extern s32 s_TcpSocket;
        extern sead::Delegate2Func<sead::Thread*, sead::MessageQueue::Element> s_ThreadDelegate;
        
        inline sead::Heap* GetHeap() {
            return endv::heap::Get<HeapKey>();
        }

        inline sead::DelegateThread& GetThread() {
            return exl::util::GetReference(s_ThreadStorage);
        }
        
    }

    inline void Initialize() {
        Logging.Log("[shimmer::client] Initializing...");

        exl::util::ConstructAt(impl::s_ThreadStorage,
            sead::SafeString("shimmer::client::Thread"),
            &impl::s_ThreadDelegate,
            impl::GetHeap(),
            sead::Thread::cDefaultPriority,
            sead::MessageQueue::BlockType::Blocking,
            impl::s_QuitMessage,
            impl::s_ThreadStackSize,
            impl::s_ThreadMessageQueueSize
        );
        impl::GetThread().sendMessage(1, sead::MessageQueue::BlockType::NonBlocking);

        nn::os::InitializeMutex(&impl::s_SerializeBufferMutex, false, 0);
        
        // thread.sendMessage(2, sead::MessageQueue::BlockType::NonBlocking);
        // thread.sendMessage(3, sead::MessageQueue::BlockType::NonBlocking);
        // nn::os::InitializeMessageQueue(&impl::s_SendQueue, impl::s_QueueBuffer, impl::s_QueueBufferSize);
    }

    inline void Start() {
        if(!impl::s_Enabled)
            return;

        Logging.Log("[shimmer::client] Starting thread...");
        auto& thread = impl::GetThread();
        thread.setAffinity(sead::CoreIdMask(sead::CoreId::cSub1));
        
        /* Start thread. First message is the arg for the thread and kickstarts the thread. */
        EXL_ABORT_UNLESS(thread.start());
    }

    template<typename T>
    requires std::derived_from<T, EmbeddedProto::MessageInterface>
    inline void Send(const T& packet) {
        if(!impl::s_Enabled)
            return;

        /* Use the client heap within this function. */
        sead::ScopedCurrentHeapSetter heap(impl::GetHeap());

        auto& lock = impl::s_SerializeBufferMutex;
        auto& sharedBuffer = impl::s_SerializeBuffer;

        /* Take exclusive access to the shared serialization buffer. */
        nn::os::LockMutex(&lock);

        /* Serialize to shared buffer. */
        EXL_ABORT_UNLESS(packet.serialize(sharedBuffer) == EmbeddedProto::Error::NO_ERRORS);

        /* Construct raw packet. */
        int size = sharedBuffer.get_size();
        auto msg = protocol::Packet::Create(size, protocol::TypeToId<T>::Type);
        std::memcpy(msg->GetBody(), sharedBuffer.get_data(), msg->GetBodySize());

        sharedBuffer.clear();

        /* We are done with the shared buffer. */
        nn::os::UnlockMutex(&lock);
        
        /* Push packet into queue to be sent. */
        impl::GetThread().sendMessage(reinterpret_cast<sead::MessageQueue::Element>(msg), sead::MessageQueue::BlockType::NonBlocking);
    }
}
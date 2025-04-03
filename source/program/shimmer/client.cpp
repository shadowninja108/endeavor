#include "client.hpp"

namespace shimmer::client {

    namespace impl {
        EmbeddedProto::WriteBufferFixedSize<1024> s_SerializeBuffer;
        nn::os::MutexType s_SerializeBufferMutex;
        exl::util::TypedStorage<sead::DelegateThread> s_ThreadStorage;
        s32 s_TcpSocket = -1;

        namespace {
            void SendPacket(protocol::Packet* packet) {
                Logging.Log("[shimmer::client] Sending message %llx %llx...", reinterpret_cast<uintptr_t>(packet), packet->GetSize());
                nn::socket::Send(s_TcpSocket, packet, packet->GetSize(), 0);
            }
        }

        void ThreadMain(sead::Thread* thread, sead::MessageQueue::Element arg) {
            sead::ScopedCurrentHeapSetter heap(GetHeap());

            Logging.Log("[shimmer::client] Thread started.");
            s_TcpSocket = nn::socket::Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            EXL_ABORT_UNLESS(s_TcpSocket >= 0);

            /* Set socket to keep-alive. */
            int flags = true;
            nn::socket::SetSockOpt(s_TcpSocket, SOL_SOCKET, SO_KEEPALIVE, &flags, sizeof(flags));

            /* Open and wait for connection. */
            struct sockaddr_in serverAddr;
            serverAddr.sin_family = AF_INET;
            serverAddr.sin_port = nn::socket::InetHtons(s_SocketPort);
            EXL_ABORT_UNLESS(nn::socket::InetPton(AF_INET, "192.168.0.234", &serverAddr.sin_addr) == 1);
            EXL_ABORT_UNLESS(nn::socket::Connect(s_TcpSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == 0);

            Logging.Log("[shimmer::client] Connected.");

            sead::MessageQueue::Element element;
            while((element = thread->recvMessage(sead::MessageQueue::BlockType::Blocking)) != sead::MessageQueue::cNullElement) {
                
                auto packet = reinterpret_cast<protocol::Packet*>(element);
                SendPacket(packet);
                delete packet;

                nn::os::SleepThread(nn::TimeSpan::FromMilliSeconds(10));
            }
        }
        sead::Delegate2Func<sead::Thread*, sead::MessageQueue::Element> s_ThreadDelegate(ThreadMain);
    }
}
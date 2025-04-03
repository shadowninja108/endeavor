#pragma once

#include <common.hpp>
#include <sys/socket.h>
#include <arpa/inet.h>

/* TODO: move this into nn. */
namespace nn::socket {

    struct InAddr {
        u32 addr;
    };

    /* Unofficial name. */
    enum class TargetService : uchar {
        User,
        System
    };

    struct Config
    {
        uint mVersion           = 2; /* 3.0.0+ ABI. */
        TargetService mService  = TargetService::User;
        void *mPool;            /* Must not be nullptr. */
        size_t mPoolSize;       /* Must be page aligned. Must be at least 0x9'0000 if target service is user. */
        size_t mAllocPoolSize;  /* Must be page aligned. */
        ulong mTcpTxBufSize     = 0x8000;
        ulong mTcpRxBufSize     = 0x10000;
        ulong mTcpTxBufMaxSize  = 0x40000;
        ulong mTcpRxBufMaxSize  = 0x40000;
        ulong mUdpTxBufSize     = 0x2400;
        ulong mUdpRxBufSize     = 0xA500;
        ulong mSbEfficiency     = 4;
        int mConcurLimit;

        Config(void* pool, ulong poolSize, ulong allocPoolSize, int concurLimit) :
            mPool(pool), 
            mPoolSize(poolSize), 
            mAllocPoolSize(allocPoolSize),
            mConcurLimit(concurLimit) {}
    };


    Result Initialize(void* pool, ulong poolSize, ulong allocPoolSize, int concurLimit);
    Result Finalize();
    s32 SetSockOpt(s32 socket, s32 socketLevel, s32 option, void const*, u32 len);
    u64 Send(s32 socket, void const* buffer, u64 bufferLength, s32 flags);
    s32 Socket(s32 domain, s32 type, s32 proto);
    u16 InetHtons(u16);
    u32 InetPton(int, char const*, void*);
    u32 Connect(s32 socket, const sockaddr* addr, u32 addrLen);
    u32 Bind(s32 socket, const sockaddr* addr, u32 addrLen);
    u32 Listen(s32 socket, s32 backlog);
    u32 Accept(s32 socket, sockaddr* addrOut, u32* addrLenOut);

    namespace detail {
        Result InitializeCommon(Config const&);
    }
};

#pragma once

#include <WriteBufferFixedSize.h>

#include <protobuf/AddEmptyNode.h>
#include <protobuf/AddEmptyNodeToRoot.h>
#include <protobuf/AddEmptyNodeToRootStationed.h>
#include <protobuf/AddNodeToCategory.h>
#include <protobuf/AddNodeToCategoryStationed.h>
#include <protobuf/AddNodeToParent.h>
#include <protobuf/AddNodeToParentStationed.h>
#include <protobuf/AddNodeToRoot.h>
#include <protobuf/AddNodeToRootStationed.h>
#include <protobuf/InvalidateNode.h>
#include <protobuf/SelectNode.h>

namespace shimmer::protocol {
    static constexpr size_t MaxStringLength = 256;
    using AddEmptyNodeType                = protobuf::AddEmptyNode<MaxStringLength, MaxStringLength>;
    using AddEmptyNodeToRootType          = protobuf::AddEmptyNodeToRoot<MaxStringLength, MaxStringLength>;
    using AddEmptyNodeToRootStationedType = protobuf::AddEmptyNodeToRootStationed<MaxStringLength, MaxStringLength>;
    using AddNodeToCategoryType           = protobuf::AddNodeToCategory<MaxStringLength, MaxStringLength, MaxStringLength>;
    using AddNodeToCategoryStationedType  = protobuf::AddNodeToCategoryStationed<MaxStringLength, MaxStringLength, MaxStringLength>;
    using AddNodeToParentType             = protobuf::AddNodeToParent<MaxStringLength, MaxStringLength>;
    using AddNodeToParentStationedType    = protobuf::AddNodeToParentStationed<MaxStringLength, MaxStringLength>;
    using AddNodeToRootType               = protobuf::AddNodeToRoot<MaxStringLength, MaxStringLength>;
    using AddNodeToRootStationedType      = protobuf::AddNodeToRootStationed<MaxStringLength, MaxStringLength>;
    using InvalidateNodeType              = protobuf::InvalidateNode;
    using SelectNodeType                  = protobuf::SelectNode<MaxStringLength>;

    enum class PacketType : u16 {
        AddEmptyNode = 0,
        AddEmptyNodeToRoot = 1,
        AddEmptyNodeToRootStationed = 2,
        AddNodeToCategory = 3,
        AddNodeToCategoryStationed = 4,
        AddNodeToParent = 5,
        AddNodeToParentStationed = 6,
        AddNodeToRoot = 7,
        AddNodeToRootStationed = 8,
        InvalidateNode = 9,
        SelectNode = 10,
    };

    template<typename T>
    struct TypeToId {};

    #define DECL_PACKET(name)   \
    template<>                  \
    struct TypeToId<name##Type> { static constexpr PacketType Type = PacketType::name; }

    DECL_PACKET(AddEmptyNode);
    DECL_PACKET(AddEmptyNodeToRoot);
    DECL_PACKET(AddEmptyNodeToRootStationed);
    DECL_PACKET(AddNodeToCategory);
    DECL_PACKET(AddNodeToCategoryStationed);
    DECL_PACKET(AddNodeToParent);
    DECL_PACKET(AddNodeToParentStationed);
    DECL_PACKET(AddNodeToRoot);
    DECL_PACKET(AddNodeToRootStationed);
    DECL_PACKET(InvalidateNode);
    DECL_PACKET(SelectNode);

    #undef DECL_PACKET

    class PACKED Packet {
        uint m_Size;
        PacketType m_Type;
        uint8_t m_Body[];

        public:
        inline uint8_t* GetBody() {
            return m_Body;
        }

        inline uint GetBodySize() const {
            return m_Size;
        }

        inline PacketType GetType() const {
            return m_Type;
        }

        inline size_t GetSize() const {
            return sizeof(Packet) + m_Size;
        }

        static size_t SizeFor(size_t size) {
            return sizeof(Packet) + size;
        }

        static Packet* Create(size_t size, PacketType type) {
            /* Be sure the size fits in the smaller integer. */
            EXL_ASSERT(size == static_cast<uint>(size));

            void* raw = std::malloc(SizeFor(size));
            auto ret = reinterpret_cast<Packet*>(raw);
            ret->m_Size = size;
            ret->m_Type = type;
            return ret;
        }
    };
}
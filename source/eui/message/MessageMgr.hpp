#pragma once

#include <sead/prim/seadRuntimeTypeInfo.h>
#include <sead/heap/seadHeap.h>
#include <sead/container/seadBuffer.h>
#include <sead/container/seadOffsetList.h>
#include <sead/gfx/seadColor.h>

#include "MessageSet.hpp"
#include "../archive/SharcArchive.hpp"

namespace eui {
    struct MessageMgr {
        SEAD_SINGLETON_DISPOSER(MessageMgr);
        SEAD_RTTI_BASE(MessageMgr);

        public:
        struct Archive : sead::IDisposer {
            SEAD_RTTI_BASE(Archive);
            
            public:
            sead::ListNode mListNode;
            SharcArchive mArchive;
            sead::Buffer<MessageSet> mMessageSets;
            MessageMgr* mMgr;
            void* mBin;

            bool findMessageSetName(sead::BufferedSafeString* out, MessageSet const*);

            virtual ~Archive();
            virtual void load(sead::Heap* heap, void* data, int size);
            virtual void unload();
        };

        struct GradationColor {
            sead::Color4u8 mColor1;
            sead::Color4u8 mColor2;
        };

        sead::OffsetList<Archive> mArchives;
        sead::Buffer<GradationColor> mGradationColors;
        char field_50;

        MessageSet* getMessageSet(sead::SafeString const&) const;
        MessageSet* getLayoutMessageSet(sead::SafeString const&) const;
        void setGradationColor(uint, sead::Color4u8, sead::Color4u8);
        void setTextBoxWidthSizeOverColor(sead::Color4u8);
        void dumpLastGotMessageSetInfo();
        void archiveDisposeCallback_(Archive*);

        virtual bool loadArchive(sead::Heap* heap, void* data, int size);
        virtual void unloadArchive(void* data);
        virtual ~MessageMgr();
    };
}
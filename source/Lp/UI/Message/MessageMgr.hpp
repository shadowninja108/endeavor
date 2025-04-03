#pragma once

#include <sead/container/seadPtrArray.h>
#include <sead/prim/seadDelegate.h>
#include <sead/resource/message/seadMesssageProject.h>
#include <eui/message/MessageMgr.hpp>
#include <eui/message/MessageSet.hpp>

#include "TagProcessor.hpp"

namespace Lp::UI {
    struct MessageMgr {
        struct LibMsgMgr : public eui::MessageMgr {
            SEAD_RTTI_OVERRIDE(LibMsgMgr, eui::MessageMgr);

            public:
            struct ArchiveEx : public eui::MessageMgr::Archive {
                SEAD_RTTI_OVERRIDE(ArchiveEx, eui::MessageMgr::Archive);

                public:
                /* Unofficial name. */
                struct Entry {
                    sead::FixedSafeString<128> mFileName;
                    uint mNameHash;
                    int mIndex;  
                };
                
                sead::FixedSafeString<128> mFileName;
                sead::PtrArray<Entry> mEntries;
                bool mClearCMInitializeConsoleReferenceCache;

                ArchiveEx(eui::MessageMgr*, sead::Heap*);
                eui::MessageSet* getMessageSetEx(sead::SafeString const&) const;
                bool foreachMessageSet(sead::IDelegate2R<eui::MessageSet const&, sead::SafeString const&, bool>*) const;
                void load(sead::Heap*, void*, unsigned int);
                void unload();
                void dbgPrintMsbtList();

                virtual ~ArchiveEx();
            };

            LibMsgMgr();
            void loadArchiveEx(sead::Heap*, void*, unsigned int, sead::SafeString const&, bool);
            eui::MessageSet* getMessageSetEx(sead::SafeString const&) const;
            eui::MessageSet* getMessageSetEx(sead::SafeString const&, sead::SafeString const&) const;
            eui::MessageSet* getReferenceMessageSetEx(sead::SafeString const&) const;
            bool foreachReferenceMessageSet(sead::IDelegate2R<eui::MessageSet const&, sead::SafeString const&, bool>*) const;
            bool findArcName(sead::FixedSafeString<256>*, sead::SafeString const&) const;
            bool isExistArchive(sead::SafeString const&) const;
            int getGradationColorNum() const;
        };

        LibMsgMgr* mMsgMgr;
        TagProcessor* mTagProcessor;
        sead::MessageProject* mProject;

        MessageMgr();
        void loadResMgrStaticHeap(sead::SafeString const&, bool);
        void loadDecompHeap(sead::SafeString const&, bool, sead::Heap*);
        void unload(void*);
        void setGradationColor(unsigned int, sead::Color4u8, sead::Color4u8);
        void initialize();
        void loadMsgProj();
        void initGradationColorByMsgProj();
        eui::MessageSet* getMessageSet(sead::SafeString const&);
        eui::MessageSet* getLayoutMessageSet(sead::SafeString const&);
        eui::MessageSet* getReferenceMessageSet(sead::SafeString const&);
        bool foreachReferenceMessageSet(sead::IDelegate2R<eui::MessageSet const&, sead::SafeString const&, bool>*) const;
        bool findArcName(sead::FixedSafeString<256>*, sead::SafeString const&) const;
        bool isExistArchive(sead::SafeString const&) const;
        void dbgReload(sead::SafeString const&, void*, unsigned int, sead::Heap*);

        virtual ~MessageMgr();
    };
}
#pragma once

#include <sead/heap/seadDisposer.h>
#include <sead/thread/seadCriticalSection.h>
#include <sead/thread/seadReadWriteLock.h>
#include <sead/prim/seadSafeString.h>
#include <sead/container/seadRingBuffer.h>

#include "HioTreeViewNode.hpp"
#include "HioTreeViewAddNodeParam.hpp"
#include "HioContext.hpp"
#include "HioTreeViewNodeVisitor.hpp"
#include "HioPropertyEvent.hpp"
#include "HioTreeViewFindParam.hpp"

namespace Lp::Sys {
    struct HioTreeViewMgr : public HioTreeViewNode {
        sead::CriticalSection mCS;
        sead::ReadWriteLock mRWLock;

        SEAD_SINGLETON_DISPOSER(HioTreeViewMgr);

        int field_378;
        sead::FixedSafeString<256> field_380;
        char field_498;

        virtual ~HioTreeViewMgr();
        virtual void genMessage(sead::hostio::Context*);
        virtual void listenPaletteEvent(sead::hostio::PaletteEvent const*);

        void createPalleteCmdArg(sead::hostio::PaletteEvent const*);
        HioTreeViewNode* createAndAddNodeToParent(HioTreeViewNode*, HioTreeViewAddNodeParam const&);
        int countChild(HioTreeViewNode*);
        void callAllNodeRootGenMessage(HioContext*);
        void traverse(HioTreeViewNode *, HioTreeViewNodeVisitor *);
        void calcAllNodeRootListenPropertyEvent(HioPropertyEvent const*);
        void resetCache();
        void addNode(HioTreeViewAddNodeParam const&);
        Lp::Sys::HioTreeViewNode* find(HioTreeViewNode*, HioTreeViewFindParam const&);
        Lp::Sys::HioTreeViewNode* findOrCreateParentNode(HioTreeViewNode*, const char*, const char*, bool);
        Lp::Sys::HioTreeViewNode* findTreeViewNodeFromChildrenNoRecursive(HioTreeViewNode*, const char*);
        Lp::Sys::HioTreeViewNode* find(HioTreeViewFindParam const&);
        void sortChildrenNode(const char*);
        void sortChildrenNode(HioTreeViewNode*);
        /* TODO: better understand this. tf is HioTreeViewNodeLess? */
        template<typename T>
        void sortTreeViewNodeChildrenNoRecursive(HioTreeViewNode*, T const&)
        void removeNodeIfHasNoChildren(HioTreeViewNode*);
        void deleteTreeViewNode(HioTreeViewNode*, const char*, bool);
        void dump(HioTreeViewNode*, int);

        static sead::FixedRingBuffer<HioTreeViewNode*, 30>* sFindNodeCache;
    };
}
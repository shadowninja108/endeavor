#pragma once

#include <sead/hostio/seadHostIONode.h>
#include <sead/container/seadTreeNode.h>

#include "IUseHioNode.hpp"

namespace Lp::Sys {
    struct HioTreeViewNode : public sead::hostio::Node {
        sead::IntrusiveTreeNode<HioTreeViewNode> mTreeNode;
        IUseHioNode* mObj;
        const char* mName;
        bool field_40;
        bool mIsGroupNode;
        bool field_42;
        bool field_43;

        sead::hostio::Node* mChildNodeList[64+1];

        virtual ~HioTreeViewNode();
        virtual void genMessage(sead::hostio::Context* context);
        virtual void listenPropertyEvent(const sead::hostio::PropertyEvent* event);
        virtual void listenNodeEvent(const sead::hostio::NodeEvent* event);
        virtual void disposeHostIO();
        virtual sead::hostio::Reflexible* searchNode(const sead::SafeString& name);
        virtual void calcURL(sead::BufferedSafeString* url) const;

        void appendChild(HioTreeViewNode*);
        bool isAppended();
        void detatchAll();
        void detatch();
        void destroyAllChild();
        HioTreeViewNode* getFirstChild();
        HioTreeViewNode* getParent();
        HioTreeViewNode* getNextSibling();
        void pushFrontChild(HioTreeViewNode*);
        void setViewName(const char*);
        void addChildNode(sead::hostio::Node*);
        void copyChildNodeLisT(HioTreeViewNode const*);
        void calcURLImpl_(sead::BufferedSafeString*, bool);
    };
}
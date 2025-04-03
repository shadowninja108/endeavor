#pragma once

#include "IUseHioNode.hpp"

namespace Lp::Sys {
    struct HioTreeViewNode;
    struct HioTreeViewAddNodeParam {
        const char* mView;
        IUseHioNode* mNode;
        const char* mName;
        const char* mParentName;
        bool mIsCreateParent;
        bool mIsGroupNode;
        const IUseHioNode* mParentNode;
        const char* mMeta;
        const char* mDispName;
        const char* mClassName;
        HioTreeViewNode* mParentTreeViewNode;

        HioTreeViewAddNodeParam(const char* view, IUseHioNode* node, const char* name);
        void setParentName(const char*);
        void setParentNode(IUseHioNode const*);
        void setParentTreeViewNode(HioTreeViewNode*);
        void setMeta(const char*);
        void setIsCreateParent(bool);
        void setIsGroupNode(bool);
        void setDispName(const char*);
        void setClassName(const char*);
    };
}
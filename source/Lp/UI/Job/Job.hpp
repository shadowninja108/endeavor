#pragma once

#include <sead/container/seadOffsetList.h>
#include <sead/container/seadTList.h>

namespace Lp::UI {
    struct Job {
        struct Restriction {
            int field_0;
            int field_4;
            int field_8;
        };
        /* TODO: what's going on here? */
        struct RestrictionNode {
            sead::ListNode mListNode;
            Restriction* mRestriction;
        };

        sead::ListNode mListNode;
        sead::OffsetList<Job> mSucceedingJobs;
        sead::OffsetList<RestrictionNode> mAttributeRestrictions;
        sead::OffsetList<RestrictionNode> mExclusiveRestrictions;
        sead::OffsetList<RestrictionNode> mPrecedingRestrictions;

        virtual ~Job();
        virtual void onProcess();
    };
    static_assert(sizeof(Job) == 0x78);
}
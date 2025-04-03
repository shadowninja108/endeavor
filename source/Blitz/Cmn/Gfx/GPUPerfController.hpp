#pragma once

#include <sead/prim/seadEnum.h>
#include <sead/container/seadRingBuffer.h>

namespace Cmn {
    struct GPUPerfController {
        /* TODO: their text_ func uses the japanese text, so there's probably a SEAD_ENUM specialization to handle that. */
        SEAD_ENUM(DispControl,
            Effects,          // エフェクト,
            Post_Effects,     // ポストエフェクト,
            Debug_Display,    // デバッグ表示,
            Player,           // プレイヤー,
            Gear,             // ギア,
            Weapons,          // 武器,
            NPCs_and_Enemies, // NPC & 敵,
            Objects,          // オブジェ,
            Terrain_Main,     // 地形(メイン),
            Terrain_Distant,  // 地形(遠景),
            VR                // 天球
        );

        /* TODO: their text_ func doesn't have the `Resolution_` prefix, enum macro probably needs improvement. */
        public:
        SEAD_ENUM_EX(Resolution, 
            Resolution_360, 
            Resolution_420, 
            Resolution_480, 
            Resolution_540, 
            Resolution_600, 
            Resolution_720, 
            Resolution_900, 
            Resolution_1080
        );
        // SEAD_ENUM_EX_VALUES(Resolution, 360, 420, 480, 540, 600, 720, 900, 1080);

        struct Unk {
            int field_0;
            int field_4;
            char field_8;
        };
        static_assert(sizeof(Unk) == 0xC);

        public:
        static constexpr int s_MaxDispControl = 11;

        float mFrameBufferMinScale;
        float mMaintainStressPer;
        float mAdjustSpeedDown;
        float mSpringConstantDown;
        float mAdjustSpeedUp;
        float mSpringConstantUp;

        Resolution mBaseDockInResolution;
        Resolution mBasePortableResolution;
        Resolution mDockInResolution;
        Resolution mPortableResolution;

        float field_30;
        float field_34;

        bool mEnableDispControls[s_MaxDispControl];
        bool mDrawDispControls[s_MaxDispControl];

        int mDispControlEnumEntryCount[s_MaxDispControl];

        using String = const char*;
        String* mDispControlEnumEntries[s_MaxDispControl];
        
        bool mScreenshotModeEnabled;

        sead::FixedRingBuffer<Unk, 60> field_e0;
        
        int field_3C8;
        int field_3CC;
        int field_3D0;
        int field_3D4;

        virtual ~GPUPerfController();
    };
    static_assert(GPUPerfController::s_MaxDispControl == 11);
    static_assert(GPUPerfController::DispControl::size() == GPUPerfController::s_MaxDispControl);
    static_assert(GPUPerfController::Resolution::size() == 8);
    static_assert(sizeof(GPUPerfController) == 0x3D8);
}
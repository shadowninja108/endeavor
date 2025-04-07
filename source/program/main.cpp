#include "lib.hpp"

#include <cstdarg>

#include <agl/utl/ScreenShotMgr.hpp>

#include <Lp/Sys/HeapInfo.hpp>
#include <Lp/Sys/Cstm/ISceneInfoCstm.hpp>
#include <Lp/Sys/HeapGroup.hpp>
#include <Lp/Sys/FileDeviceHolder.hpp>
#include <Lp/Sys/Framework.hpp>
#include <Lp/Sys/Scene/SceneMgr.hpp>
#include <Lp/Sys/Model/ModelArc.hpp>
#include <Lp/Sys/Debug/DbgTextWriter.hpp>
#include <Lp/Sys/Debug/DbgCameraMgr.hpp>
#include <Lp/Sys/FileDeviceHolder.hpp>
#include <Lp/Sys/Ctrl/CtrlMgr.hpp>
#include <Lp/Utl/Math.hpp>
#include <Lp/Utl/Scene.hpp>
#include <Lp/Utl/Layer.hpp>
#include <Lp/Utl/Yaml/YamlFormatter.hpp>
#include <Lp/SampleLua.hpp>

#include <gsys/SystemTask.hpp>

#include <sead/heap/seadHeap.h>
#include <sead/heap/seadExpHeap.h>
#include <sead/controller/seadControllerMgr.h>
#include <sead/framework/nx/seadGameFrameworkNx.h>
#include <sead/devenv/seadGameConfig.h>
#include <sead/stream/seadFileDeviceStream.h>
#include <sead/filedevice/seadFileDeviceMgr.h>

#include <Blitz/Cmn/Camera/CameraAnimResource.hpp>
#include <Blitz/Cmn/Gfx/AppUBOMgr.hpp>
#include <Blitz/Cmn/Actor.hpp>
#include <Blitz/Cmn/Gfx/GfxUtl.hpp>
#include <Blitz/Cmn/SceneBase.hpp>
#include <Blitz/Cmn/ViewerEnvChanger.hpp>
#include <Blitz/Cmn/Debug/Util.hpp>
#include <Blitz/Cmn/Debug/Menu/DbgMenuItemValue.hpp>
#include <Blitz/Cmn/Debug/Menu/DbgMenuItemBool.hpp>
#include <Blitz/Cmn/Debug/Menu/DbgMenuItemPush.hpp>
#include <Blitz/Game/CmnScene.hpp>
#include <Blitz/Game/GfxMgr.hpp>
#include <Blitz/Game/Paint/PaintMgr.hpp>
#include <Blitz/Game/Paint/PaintTextureArchiver.hpp>
#include <Blitz/Game/Actor/Obj.hpp>
#include <Blitz/Game/Actor/Field.hpp>
#include <Blitz/Game/Actor/Lift.hpp>
#include <Blitz/Game/Actor/BulletMgr.hpp>
#include <Blitz/Game/FilmingSupporter.hpp>
#include <Blitz/Game/Actor/MainMgr.hpp>
#include <Blitz/Scene/Viewer/BlitzViewer.hpp>
#include <Blitz/Scene/Viewer/EnemyObjViewer.hpp>
#include <Blitz/Scene/IconCapture.hpp>
#include <Blitz/Scene/JintTest.hpp>
#include <Blitz/Scene/NisdTest.hpp>
#include <Blitz/Scene/Viewer/PlayerViewer/Scene.hpp>

#include "endv/Cstm/Scene.hpp"
#include "endv/Version.hpp"
#include "endv/Hooks/Core.hpp"
#include "endv/Hooks/HioNode.hpp"
#include "endv/Hooks/Shimmer.hpp"
#include "endv/Hooks/Nvn.hpp"
#include "endv/Heap.hpp"
#include "endv/LpParamTypes.hpp"
#include "endv/StackTrace.hpp"

#include "shimmer/client.hpp"

#include <elua/GlueStaticFunction.hpp>
#include <elua/GlueClassMemberFunction.hpp>

// HOOK_DEFINE_INLINE(DbgSettingSceneFix) {
//     static void Callback(exl::hook::InlineCtx* ctx) {
//         if(ctx->W[8] != static_cast<u32>(-1))
//             return;
//         Logging.Log("Fixing %d", Lp::Sys::SceneMgr::sInstance->mNextSceneId);
//         ctx->W[8] = Lp::Sys::SceneMgr::sInstance->mNextSceneId;
//     }
// };
// HOOK_DEFINE_TRAMPOLINE(ReqChangeScene1) {
//     static void Callback(sead::SafeString const& name, const char* meta) {
//         Logging.Log("reqChangeScene %s %s", name.cstr(), meta);
//         Orig(name, meta);
//     }
// };
// HOOK_DEFINE_TRAMPOLINE(ReqChangeScene2) {
//     static void Callback(int id, const char* meta) {
//         Logging.Log("reqChangeScene %d %s", id, meta);
//         // if(id == 29)
//         //     id = 30;
//         Orig(id, meta);
//     }
// };



struct YamlLogger : public Lp::Utl::YamlWriter {

    YamlLogger() : Lp::Utl::YamlWriter(sead::SafeString::cEmptyString, 0) {}

    virtual ~YamlLogger() {}
    virtual void writeString(const char* fmt, ...) {
        std::va_list args;
        va_start(args, fmt);
        Logging.VLog(fmt, args);
        va_end(args);
    }
};

static void PrintParamPrimitive(const Lp::Sys::ParamNode* node) {
    auto name = node->mName.cstr();
    ptrdiff_t offset = reinterpret_cast<uintptr_t>(node) - reinterpret_cast<uintptr_t>(node->mTreeNode.parent()->valuePtr());

    /* 
        Primitives inherit Lp::Sys::Param<T>, but currently we are limited with sead's RTTI, so I can't just attempt to use it to type check.
        For whatever reason, typeId() belongs to Param<T> instead of ParamNode, but we assume it's a Param, so upcast it to a dummy one
        just so we can call typeId() and size(). After that, then we can infer the actual type and upcast it to that.
    */
    const auto& dummyUpcast = *reinterpret_cast<const Lp::Sys::Param<void*>*>(node);

    /* Define to handle to proper check and upcasting. */
    #define CASE(lp, prim, ...)                                                 \
        case ::endv::LpParamType::lp: {                                         \
            auto upcast = reinterpret_cast<const Lp::Sys::Param<prim>*>(node);  \
            __VA_ARGS__                                                         \
            break;                                                              \
        }

    using Curvef = sead::hostio::Curve<float>;
    using Rangef = Lp::Utl::Math::RangeBase<float>;
    using Rangei = Lp::Utl::Math::RangeBase<int>;
    switch(static_cast<endv::LpParamType>(dummyUpcast.typeId())) {
        CASE(U8, u8,
            Logging.Log("%s@%x: %lx", name, offset, upcast->ref());
        )
        CASE(S8, s8, 
            Logging.Log("%s@%x: %lx", name, offset, upcast->ref());
        )
        CASE(U16, u16, 
            Logging.Log("%s@%x: %lx", name, offset, upcast->ref());
        )
        CASE(S16, s16, 
            Logging.Log("%s@%x: %lx", name, offset, upcast->ref());
        )
        CASE(U32, u32, 
            Logging.Log("%s@%x: %lx", name, offset, upcast->ref());
        )
        CASE(S32, s32, 
            Logging.Log("%s@%x: %lx", name, offset, upcast->ref());
        )
        CASE(F32, float, 
            Logging.Log("%s@%x: %f", name, offset, upcast->ref());
        )
        CASE(U64, u64, 
            Logging.Log("%s@%x: %lx", name, offset, upcast->ref());
        )
        CASE(S64, s64, 
            Logging.Log("%s@%x: %lx", name, offset, upcast->ref());
        )
        CASE(F64, double, 
            Logging.Log("%s@%x: %f", name, offset, offset, upcast->ref());
        )
        CASE(Bool, bool, 
            Logging.Log("%s@%x: %f", name, offset, upcast->ref() ? "true" : "false");
        )
        CASE(Str, sead::BufferedSafeString,
            Logging.Log("%s@%x: %s", name, offset, upcast->ref().cstr());
        )
        CASE(Enum, int,
            Logging.Log("%s@%x: %lx", name, offset, upcast->ref());
        )
        CASE(V2f, sead::Vector2f,
            const auto& v = upcast->ref();
            Logging.Log("%s@%x: %f %f", name, offset, v.x, v.y);
        )
        CASE(V2i, sead::Vector2<int>,
            const auto& v = upcast->ref();
            Logging.Log("%s@%x: %d %d", name, offset, v.x, v.y);
        )
        CASE(V3f, sead::Vector3f,
            const auto& v = upcast->ref();
            Logging.Log("%s@%x: %f %f %f", name, offset, v.x, v.y, v.z);
        )
        CASE(V3i, sead::Vector3<int>,
            const auto& v = upcast->ref();
            Logging.Log("%s@%x: %d %d %d", name, offset, v.x, v.y, v.z);
        )
        CASE(V4f, sead::Vector4f,
            const auto& v = upcast->ref();
            Logging.Log("%s@%x: %f %f %f %f", name, offset, v.x, v.y, v.z, v.w);
        )
        CASE(V4i, sead::Vector4<int>,
            const auto& v = upcast->ref();
            Logging.Log("%s@%x: %d %d %d %d", name, offset, v.x, v.y, v.z, v.w);
        )
        CASE(Q4f, sead::Quatf,
            const auto& v = upcast->ref();
            Logging.Log("%s@%x: %f %f %f %f", name, offset, v.w, v.x, v.y, v.z);
        )
        CASE(Curvef, Curvef,
            const auto& r = upcast->ref();
            /* TODO: test this */
            auto str = std::string();
            for(size_t i = 0; i < r.mInfo.numUse; i++) {
                str += std::to_string(r.mFloats[i]);
            }
            Logging.Log("%s@%x: $s", name, offset, str.c_str());
        )
        CASE(Rangef, Rangef,
            const auto& r = upcast->ref();
            Logging.Log("%s@%x: %f,%f", name, offset, r.mLow, r.mHigh);
        )
        CASE(Rangei, Rangei,
            const auto& r = upcast->ref();
            Logging.Log("%s@%xs: %d,%d", name, offset, r.mLow, r.mHigh);
        )
        CASE(C4f, sead::Color4f,
            const auto& c = upcast->ref();
            Logging.Log("%s@%x: %f, %f, %f, %f", name, offset, c.r, c.g, c.b, c.a);
        )
        CASE(C4u8, sead::Color4u8,
            const auto& c = upcast->ref();
            Logging.Log("%s@%x: #%02x%02x%02x%02x", name, offset, c.r, c.g, c.b, c.a);
        )
        case endv::LpParamType::Bit: {
            /* Infer the type based on the param's size(). */
            switch(dummyUpcast.size()) {
                #define CASE2(type)                                                                     \
                case sizeof(type): {                                                                    \
                    auto upcast = reinterpret_cast<const Lp::Sys::Param<sead::BitFlag<type>>*>(node);   \
                    auto bits = std::bitset<sizeof(type)>(upcast->ref());                               \
                    auto str = bits.to_string();                                                        \
                    Logging.Log("%s@%x: 0b%s", name, offset, str.c_str());                              \
                    break;                                                                              \
                }
                CASE2(u8)
                CASE2(u16)
                CASE2(u32)
                CASE2(u64)
                #undef CASE2
                default:
                    /* Wut? */
                    Logging.Log("%s@%x: TODO Bit %d", name, offset, dummyUpcast.size());
                    break;
            }
            break;
        }
        default:
            /* Don't recognize the typeId, probably invalid or I'm dumb. */
            Logging.Log("Unknown type %s for %s@%x", dummyUpcast.typeName(), name, offset);
            break;
    }
    #undef CASE
}

static void PrintParam(const Lp::Sys::ParamNode* node);

static void PrintParamObject(const Lp::Sys::Params* node) {
    const auto* parentNode = node->mTreeNode.parent();

    /* If there's a parent, display the name + offset within parent. Otherwise, just display the name. */
    if(parentNode == nullptr) {
        Logging.Log("%s:", node->mName.cstr());
    } else {
        ptrdiff_t offset = reinterpret_cast<uintptr_t>(node) - reinterpret_cast<uintptr_t>(parentNode->valuePtr());
        Logging.Log("%s@%x:", node->mName.cstr(), offset);
    }

    /* Iterate the children nodes. */
    for(auto treeNode = node->mTreeNode.child(); treeNode != nullptr; treeNode = treeNode->next()) {
        PrintParam(treeNode->valuePtr());
    }
}

static void PrintParam(const Lp::Sys::ParamNode* node) {
    // YamlLogger logger {};
    // Lp::Utl::YamlWriter writer(sead::SafeString("sd:/test.yaml"), 0x5000);
    // node->writeYaml(writer);
    // writer.save(false);

    if(node->mTreeNode.child() != nullptr) {
        /* If this node has children, treat it as an object. */
        PrintParamObject(reinterpret_cast<const Lp::Sys::Params*>(node));
    } else {
        /* Otherwise, treat as a primitive. */
        PrintParamPrimitive(node);
    }
}


namespace endv { 
    struct HeapGroupDbgHeapKey;
    struct HeapGroupDbgHeapKeyProd;
    sead::Heap *getDbgHeap() {
        return endv::heap::s_IsProd ? 
            endv::heap::Get<endv::HeapGroupDbgHeapKeyProd>() : 
            endv::heap::Get<endv::HeapGroupDbgHeapKey>();
    }
}

HOOK_DEFINE_TRAMPOLINE(CameraAnimResourceLoad) {
    inline static bool s_EnableDbgTextWriter = true;
    static void OnEnableDbgTextWriterChanged() {
        if(s_EnableDbgTextWriter) {
            Logging.Log("Enabling DbgTextWriter...");
            //SEAD_INSTANCE(Lp::Sys::DbgTextWriter)->pauseDraw(true);
        } else {
            Logging.Log("Disabling DbgTextWriter...");
            //SEAD_INSTANCE(Lp::Sys::DbgTextWriter)->pauseDraw(false);
        }
    }

    inline static bool s_EnablePlayerViewerBlueBG = false;
    static void OnEnablePlayerViewerBlueBGChanged() {
        if(s_EnablePlayerViewerBlueBG) {
            Logging.Log("Enabling PlayerViewer Blue BG...");
        } else {
            Logging.Log("Disabling PlayerViewer Blue BG...");
        }
    }

    inline static bool s_UseShopForFieldFix = false;
    static void OnUseShopForFieldFixChanged() {
        if(s_UseShopForFieldFix) {
            Logging.Log("Enabling Use Shop For Field Fix...");
        } else {
            Logging.Log("Disabling Use Shop For Field Fix...");
        }
    }

    static void OnCapture() {
        auto mgr = SEAD_INSTANCE(Game::PaintMgr);
        auto tex = mgr->GetPaintTexture();
        auto wallPaintMgr = &tex->mWallPaintMgr;
        auto screenshot = SEAD_INSTANCE(agl::utl::ScreenShotMgr);
        agl::RenderTargetColor* texArr = tex->mRenderTargetColorsByPaintFaceType;
        char nameBuffer[512];
        for(size_t i = 0; i < 5; i++) { 
            auto faceTex = &texArr[i];
            std::snprintf(nameBuffer, sizeof(nameBuffer), "sd:/Test%ld.tga", i);

            screenshot->captureToFile_(
                /* Retail doesn't use this, and neither does Pilot. However, Pilot does validate it is not null. So, fuck you guys. */
                reinterpret_cast<agl::DrawContext*>(1),
                &faceTex->mTextureData,
                static_cast<agl::TextureDataSerializerTGA::TGAFormat>(2),
                sead::SafeString(nameBuffer),
                screenshot->mHeap
            );
        }

        auto archiver = SEAD_INSTANCE(Game::PaintTextureArchiver);
        for(size_t i = 0; i < 5; i++) {
            auto& entry = archiver->mWorldArchives[i];
            if(!entry.mUsed)
                continue;

            std::snprintf(nameBuffer, sizeof(nameBuffer), "sd:/World%ld.tga", i);

            screenshot->captureToFile_(
                /* Retail doesn't use this, and neither does Pilot. However, Pilot does validate it is not null. So, fuck you guys. */
                reinterpret_cast<agl::DrawContext*>(1),
                entry.mArchiveTex,
                static_cast<agl::TextureDataSerializerTGA::TGAFormat>(2),
                sead::SafeString(nameBuffer),
                screenshot->mHeap
            );
        }

        sead::FileHandle handle;
        SEAD_INSTANCE(Lp::Sys::FileDeviceHolder)->mSD->open(
            &handle,
            sead::SafeString("Grid.yaml"),
            sead::FileDevice::cFileOpenFlag_WriteOnly,
            0
        );
        sead::BufferFileDeviceWriteStream stream(&handle, sead::Stream::Modes::Binary);
        Lp::Utl::YamlFormatter formatter {};
        formatter.setStream(&stream);
        formatter.startDocument();
        for(size_t bufferI = 0; bufferI < 4; bufferI++) {
            auto& buffer = wallPaintMgr->mGridInfo[bufferI];
            formatter.startArray();
            for(auto& grid : buffer) {
                if(grid.mIndex == 4095)
                    continue;
                formatter.startArray();
                formatter.writeHashFloat("field_0", grid.field_0);
                formatter.writeHashFloat("field_4", grid.field_4);
                formatter.writeHashV3f("field_8", grid.field_8);
                formatter.writeHashInt("mIndex", grid.mIndex);
                formatter.endArray();
            }
            formatter.endArray();
        }
        formatter.endHash();
    }

    static bool Callback(Cmn::CameraAnimResource* self, Lp::Sys::ModelArc* arc, sead::SafeString const& str1, sead::SafeString const* str2, int a, bool b) {
        Logging.Log("Cmn::CameraAnimResourceLoad::loadImpl");
        endv::LogStackTrace();

        auto gfxMgr = reinterpret_cast<Game::GfxMgr*>(Cmn::GfxUtl::getGfxMgr());
        auto fieldEnvSet = gfxMgr->mFieldEnvSet;
        if(fieldEnvSet != nullptr) {
            //PrintParam(fieldEnvSet);
        }
        /* TODO: fix sead RTTI... */
        // Logging.Log("Hour: %d", static_cast<int>(sead::DynamicCast<Cmn::SceneBase>(Lp::Utl::getCurScene())->mGfxMgr->mHour));
        // if(str2 != nullptr)
        //     Logging.Log("%s %s", str1.cstr(), str2->cstr());
        // else
        //     Logging.Log("%s", str1.cstr());
        // Orig(self, arc, str1, str2, a, b);

        sead::ScopedCurrentHeapSetter heap(endv::getDbgHeap());
        static int ivalue = 420;
        static float fvalue = 69;
        static bool init = false;
        if(!init) {
            init = true;
            auto page = Cmn::FindOrCreateDbgMenuPage(sead::SafeString("Endeavor"), true);
            page->addItem(
                Cmn::DbgMenuItemValue::Create<int>(
                    sead::SafeString("Hello"),
                    ivalue,
                    0,
                    1000
                )
            );
            page->addItem(
                Cmn::DbgMenuItemValue::Create<int>(
                    sead::SafeString("world!"),
                    ivalue,
                    0,
                    1000
                )
            );
            page->addItem(
                Cmn::DbgMenuItemValue::Create<int>(
                    sead::SafeString("Shadow"), /* L EPD for not supporting UTF8. */
                    ivalue,
                    0,
                    1000
                )
            );
            page->addItem(
                Cmn::DbgMenuItemValue::Create<int>(
                    sead::SafeString("here"),
                    ivalue,
                    0,
                    1000
                )
            );
            page->addItem(
                Cmn::DbgMenuItemValue::Create<float>(
                    sead::SafeString(":3"),
                    fvalue,
                    0,
                    100
                )
            );
            page->addItem(
                Cmn::DbgMenuItemBool::Create(
                    sead::SafeString("DbgTextWriter"),
                    s_EnableDbgTextWriter,
                    OnEnableDbgTextWriterChanged
                )
            );
            page->addItem(
                Cmn::DbgMenuItemBool::Create(
                    sead::SafeString("PlayerViewer Blue BG"),
                    s_EnablePlayerViewerBlueBG,
                    OnEnablePlayerViewerBlueBGChanged
                )
            );
            if(!Lp::Sys::ModelArc::checkResExist("TestfieldDummy00")){
                s_UseShopForFieldFix = true; // default to shop if a replacement field is not found.
            }
            page->addItem(
                Cmn::DbgMenuItemBool::Create(
                    sead::SafeString("Use Shop For Field Fix"),
                    s_UseShopForFieldFix,
                    OnUseShopForFieldFixChanged
                )
            );
            page->addItem(
                Cmn::DbgMenuItemPush::Create(
                    sead::SafeString("Capture"),
                    OnCapture
                )
            );
        }
        return Orig(self, arc, str1, str2, a, b);
    }
};

static Game::FilmingSupporter* sFilmingSupporter;
static bool sIsFixedAim = false;

HOOK_DEFINE_TRAMPOLINE(MainMgrEnter) {
    static void OnAimModeChanged() {
        if(sFilmingSupporter) sFilmingSupporter->changeMode_(sIsFixedAim ? Game::FilmingSupporter::AimMode_FixedAim : Game::FilmingSupporter::AimMode_None);
    }
    static void Callback(Game::MainMgr* self) {
        Orig(self);
        if(sFilmingSupporter == nullptr) {
            sead::ScopedCurrentHeapSetter heap(endv::getDbgHeap());

            sIsFixedAim = false;

            sFilmingSupporter = new Game::FilmingSupporter();
            sFilmingSupporter->enter();

            auto page = Cmn::FindOrCreateDbgMenuPage(sead::SafeString("Filming"), true);
            page->addItem(
                Cmn::DbgMenuItemBool::Create(
                    sead::SafeString("[Endeavor] FixedAim"),
                    sIsFixedAim,
                    OnAimModeChanged
                )
            );
            page->addItem(
                Cmn::DbgMenuItemValue::Create<int>(
                    sead::SafeString("[Endeavor] Focus Player"),
                    sFilmingSupporter->mPlayerId,
                    -1,
                    9
                )
            );
        }
    }
};

HOOK_DEFINE_TRAMPOLINE(MainMgrCalcGameFrame) {
    static void Callback(Game::MainMgr* self) {
        if(sFilmingSupporter != nullptr) {
            sFilmingSupporter->calc();
            if(sIsFixedAim) {
                int i = Cmn::GfxUtl::getGfxMgr()->getLyrIdx_3D_Main();
                auto mgr = Lp::Sys::DbgCameraMgr::sInstance;
                if(mgr->mLayerNum > i && mgr->mLayerCameras[i] != nullptr) {
                    mgr->mLayerCameras[i]->calc(true);
                }
            }
        }
        Orig(self);
    }
};

HOOK_DEFINE_TRAMPOLINE(MainMgrExit) {
    static void deleteItem(Cmn::DbgMenuPage* page, sead::SafeString const& name) {
        auto item = page->findItem(name, true);
        page->removeItem(item);
    }
    static void Callback(Game::MainMgr* self) {
        if(sFilmingSupporter != nullptr) {
            sead::ScopedCurrentHeapSetter heap(endv::getDbgHeap());

            // Additional cleanup since dtor is not present
            auto page = Cmn::FindOrCreateDbgMenuPage(sead::SafeString("Filming"), true);
            deleteItem(page, sead::SafeString("Clear"));
            deleteItem(page, sead::SafeString("Hide Layout"));
            deleteItem(page, sead::SafeString("Hide ShotGuide"));
            deleteItem(page, sead::SafeString("Hide DbgDraw"));
            deleteItem(page, sead::SafeString("[Endeavor] FixedAim"));
            deleteItem(page, sead::SafeString("[Endeavor] Focus Player"));

            delete sFilmingSupporter;
            sFilmingSupporter = nullptr;

            sIsFixedAim = false;

        }
        Orig(self);
    }
};

HOOK_DEFINE_TRAMPOLINE(LayerGetCamera) {
    static sead::Camera* Callback(const agl::lyr::Layer* layer) {
         if(sIsFixedAim && sFilmingSupporter && layer->mId == Cmn::GfxUtl::getGfxMgr()->getLyrIdx_3D_Main()) {
            auto mgr = Lp::Sys::DbgCameraMgr::sInstance;
            int i = layer->mId;
            if(mgr->mLayerNum > i && mgr->mLayerCameras[i] != nullptr) return &mgr->mLayerCameras[i]->mCamera;
        }
        return Orig(layer);
    }
};
HOOK_DEFINE_TRAMPOLINE(LpDbgTextWriterEntry) {

    /* TODO: resolve via symbol. */
    static constexpr uintptr_t s_PlayerViewerPlayerCalcForDrawRangeStart = 0x00EF7B28;
    static constexpr uintptr_t s_PlayerViewerPlayerCalcForDrawRangeEnd = 0x00EF87D0;
    static constexpr uintptr_t s_PlayerViewerCursorIconCalcForDrawRangeStart = 0x00EEF820;
    static constexpr uintptr_t s_PlayerViewerCursorIconCalcForDrawRangeEnd = 0x00EEFC4C;

    static exl::util::Range GetFuncRange (uintptr_t start, uintptr_t end) {
        auto base = exl::util::GetMainModuleInfo().m_Text.m_Start + start;
        return { base, end - start };
    }

    inline static const auto s_PlayerViewerPlayerCalcForDrawRange = GetFuncRange(s_PlayerViewerPlayerCalcForDrawRangeStart, s_PlayerViewerPlayerCalcForDrawRangeEnd);
    inline static const auto s_PlayerViewerCursorIconCalcForDrawRange = GetFuncRange(s_PlayerViewerCursorIconCalcForDrawRangeStart, s_PlayerViewerCursorIconCalcForDrawRangeEnd);

    static void Callback(
        Lp::Sys::DbgTextWriter* writer, 
        int layerId, 
        sead::Vector2f const& pos, 
        Lp::Sys::DbgTextWriter::ArgEx const* ex, 
        Lp::Sys::DbgTextWriter::Info* info
    ) {
        /* If the text writer is enabled, just fallthrough. */
        if(CameraAnimResourceLoad::s_EnableDbgTextWriter) {
            Orig(writer, layerId, pos, ex, info);
            return;
        }
        
        /* Otherwise, try to infer the caller to decide if we should actually draw it. */
        endv::StackTraceIterator it;
        auto delegate = [](uintptr_t lr) {
            if(s_PlayerViewerPlayerCalcForDrawRange.InRange(lr))
                return true;
            if(s_PlayerViewerCursorIconCalcForDrawRange.InRange(lr))
                return true;
            return false;
        };
        while(it.IsValid()) {
            /* If the delegate returns true, we should return to not draw this at all. */
            if(delegate(it.GetReturnAddress())){
                return;
            }
            /* Continue walking up the stack trace. */
            it.Step();
        }

        /* If we make it here, we are drawing the text anyways. */
        Orig(writer, layerId, pos, ex, info);
    }
};

HOOK_DEFINE_TRAMPOLINE(ModelArcInit) {
    static void Callback(Lp::Sys::ModelArc* self, sead::SafeString const& name, sead::Heap* heap1, sead::Heap* heap2, bool unk, gsys::ModelResource::CreateArg const* arg) {
        if(Lp::Sys::ModelArc::checkResExist(name))
            return Orig(self, name, heap1, heap2, unk, arg);

        Logging.Log("Missing Model: %s", name.mStringTop);
        auto altName = name;
        altName.mStringTop = "Obj_Box00S";
        return Orig(self, altName, heap1, heap2, unk, arg);
        
    }
};

HOOK_DEFINE_TRAMPOLINE(ModelArcCheckIfResModel) {
    static bool Callback(sead::SafeStringBase<char> const&archiveName, sead::SafeStringBase<char> const&resName) {
        if(!Lp::Sys::ModelArc::checkResExist(archiveName))
            return false;
        return Orig(archiveName, resName);
    }
};

HOOK_DEFINE_INLINE(FieldLoadModerArcPtr) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        Cmn::ActorDBData* actorDBData = reinterpret_cast<Cmn::ActorDBData*>(ctx->X[1] - 0xB8);
        if( !Lp::Sys::ModelArc::checkResExist(actorDBData->mResName)){
            Logging.Log("Missing Field: %s", actorDBData->mResName.mStringTop);
            const char *name = (CameraAnimResourceLoad::s_UseShopForFieldFix) ? "Fld_Room_Gear" : "TestfieldDummy00";
            actorDBData->mResName = sead::SafeString(name);
            actorDBData->mJmpName = sead::SafeString(name);
            actorDBData->mFmdbName = sead::SafeString(name);
            actorDBData->mLinkUserName = sead::SafeString(name);
        }
    }
};

HOOK_DEFINE_INLINE(ObjCreateModelArc) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        sead::SafeString* resName = reinterpret_cast<sead::SafeString*>(ctx->X[1]);
        if( !Lp::Sys::ModelArc::checkResExist(*resName)){
            Logging.Log("Missing Obj: %s", resName->mStringTop);
            *resName = sead::SafeString("Obj_Box00S");
            *reinterpret_cast<sead::SafeString*>(ctx->X[2]) = sead::SafeString("Obj_Box00S");
        }
    }
};

HOOK_DEFINE_INLINE(CollisionFix) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        Game::Lift* obj = reinterpret_cast<Game::Lift*>(ctx->X[19]);
        if(obj->getBlock(0) == nullptr) ctx->W[0] = 0;
    }
};

HOOK_DEFINE_INLINE(BulletMgrCreateActorsRocketFix) {
    static void Callback(exl::hook::InlineCtx* ctx) {
        *reinterpret_cast<int*>(ctx->X[29] - 0x4A0 + 0x2E4) = 1;
    }
};

HOOK_DEFINE_TRAMPOLINE(CtrlMgrChangeCtrlJoy) {
    static void Callback(Lp::Sys::CtrlMgr* self, int ctrlType, int ctrlId) {
        Orig(self, ctrlType, (ctrlId <= 8 ? ctrlId : 0));
    }
};

namespace endv {

    namespace heap { 
        bool s_IsProd = false;
    }

    /* Heap Configuration. We use less ram for prod to fit in 4gb.*/
    struct HeapGroupDbgHeapKey {
        static constexpr char Name[] = "HeapGroup::cDbg";
        static constexpr size_t Size = 0xA00'0000;
        static constexpr size_t Alignment = 0;
    };

    struct HeapGroupDbgHeapKeyProd {
        static constexpr char Name[] = "HeapGroup::cDbg";
        static constexpr size_t Size = 0x280'0000;
        static constexpr size_t Alignment = 0;
    };

    struct SceneDbgHeapKey {
        static constexpr char Name[] = "SceneDbgHeap";
        static constexpr size_t Size = 0xC00'0000;
        static constexpr size_t Alignment = 0;
    };

    struct SceneDbgHeapKeyProd {
        static constexpr char Name[] = "SceneDbgHeap";
        static constexpr size_t Size = 0xA0'0000;
        static constexpr size_t Alignment = 0;
    };

    void OnCreateScene(Lp::Sys::Scene* scene) {
        /* Populate DbgHeap for the scene. For prod we will use a smaller heap. */
        Lp::Sys::SceneMgr::sInstance->mCurrentScene->mDbgHeap = endv::heap::s_IsProd ? 
            endv::heap::Get<SceneDbgHeapKeyProd>() : 
            endv::heap::Get<SceneDbgHeapKey>();

        /* If we are in the PlayerViewer scene, overwrite the clear color. */
        auto sceneInfo = Lp::Utl::getSceneInfo(Lp::Sys::SceneMgr::sInstance->mCurrentSceneId, false);
        if(sceneInfo != nullptr && std::strcmp(sceneInfo->mName, "PlayerViewer") == 0 && CameraAnimResourceLoad::s_EnablePlayerViewerBlueBG) {
            Lp::Utl::getGfxLayer3D(Cmn::GfxUtl::getGfxMgr()->getLyrIdx_3D_Main())->mClearColor = sead::Color4f::cBlue;
        }
    }

    static constexpr size_t s_AdditionalMemForDynamicTextureAllocator = 0x200'00000;
    void OnSetHeapInfo(Lp::Sys::HeapInfo* heapInfo) {
        /* Query the available memory size to determine if we are in prod. */
        nn::os::MemoryInfo info;
        nn::os::QueryMemoryInfo(&info);

        endv::heap::s_IsProd = info.availaible_size <= (4ULL * 0x40000000ULL); // if <= 4gb, we're prod (dev is at least 6)
        Logging.Log("Available size: %08llx; Using %s config.", info.availaible_size, endv::heap::s_IsProd ? "prod" : "dev");

        /* Reserve more memory for agl's dynamic texture allocator, which is allocated from HeapGroup Gfx heap. 
           This is only done in dev builds, on prod we do not have enough ram for this. */
        if(!endv::heap::s_IsProd) heapInfo->mGfxSize += endv::s_AdditionalMemForDynamicTextureAllocator;
    }

    void OnOverwriteFrameworkCreateArg(sead::GameFrameworkNx::CreateArg* arg) {
        // arg->mClearColor = sead::Color4f::cRed;
    } 

    void OnCreateGsysCreateArg(gsys::SystemTask::CreateArg& arg) {
        /* Create screenshot mgr as *Viewer scenes use it. */
        arg.mCreateScreenshotMgr = true;
        /* Bump up the dynamic texture allocator's heap size as the 3x screenshots in *Viewer scenes require it. 
           This is only done in dev builds, on prod we do not have enough ram for this. */
        if(!endv::heap::s_IsProd) arg.mDynamicTextureAllocatorMemSize += endv::s_AdditionalMemForDynamicTextureAllocator;
    }

    void OnPostRootTaskCreateVariousParts() {
        /* Enable this option to allow Lp to use our controller for debugging stuff. */
        *sead::GameConfig::instance()->findBoolImpl_(sead::SafeString("ValidSceneDbgCtrlPilot"), true) = true;

        /* Modify scene table to populate the constructors for the fun scenes. */
        auto cstm = Lp::Sys::ISceneInfoCstm::spCstm;
        EXL_ABORT_UNLESS(cstm != nullptr);
        
        int count = cstm->getSceneNum();
        for(int i = 0; i < count; i++) {
            auto info = cstm->getSceneInfo(i);
            #define CASE(name, scene)                                   \
                else if(std::strcmp(info->mName, name) == 0) {          \
                    info->TypedCtor<scene>() = endv::Cstm::newScene;    \
                }
            if(false) {}
            CASE("PlayerViewer",        PlayerViewer::Scene)
            CASE("Viewer",              BlitzViewer::Scene)
            CASE("EnemyViewer",         EnemyObjViewer::Scene)
            CASE("NpcViewer",           EnemyObjViewer::Scene)
            CASE("ObjViewer",           EnemyObjViewer::Scene)
            CASE("IconCapture",         IconCapture::Scene)
            CASE("Test/JintTest",       JintTest::Scene)
            CASE("Test/NisdTest",       NisdTest::Scene)
            CASE("Sample/DebugMenu",    SampleLua::Scene)
            #undef CASE
        }

        /* Initialize Lp's Dbg heap. */
        auto& dbgHeap = SEAD_INSTANCE(Lp::Sys::HeapGroup)->mHeaps[Lp::Sys::HeapGroup::Group_Dbg];
        if(dbgHeap == nullptr) {
            dbgHeap = endv::getDbgHeap();

            // auto others = SEAD_INSTANCE(Lp::Sys::HeapGroup)->mHeaps[Lp::Sys::HeapGroup::Group_Others];
            // dbgHeap = sead::ExpHeap::create(
            //     others->getFreeSize() / 2,
            //     sead::SafeString("HeapGroup::cDbg"),
            //     others,
            //     0,
            //     sead::Heap::cHeapDirection_Forward,
            //     false
            // );
        }
    }
}

void func1();
long func2() ;
void func3(long arg1);
long func4(long arg1);
long func5(long arg1, long arg2);
long func6(long arg1, int arg2);

struct Test {

    void Func1();
    void Func2() const;

    void Func3(int);
    void Func4(int) const;

    void Func5(int, long);
    void Func6(int, long) const;

    int Func7();
    int Func8() const;

    int Func9(int);
    int Func10(int) const;

    int Func11(int, long);
    int Func12(int, long) const;
};

namespace elua {
    template<>                                          
    bool GlueArgument::checkType<Test*>(lua_State*, int);
    template<>                                          
    Test* GlueArgument::get<Test*>(lua_State*, int);      
    template<>                                          
    void GlueArgument::push<Test*>(lua_State*, Test*);

    template<>                                          
    bool GlueArgument::checkType<const Test*>(lua_State*, int);
    template<>                                          
    const Test* GlueArgument::get<const Test*>(lua_State*, int);      
    template<>                                          
    void GlueArgument::push<const Test*>(lua_State*, const Test*);
}

HOOK_DEFINE_INLINE(TestHook) {
    static void Callback(exl::hook::InlineFloatCtx* ctx) {
        Lp::Sys::Actor::create<Cmn::Actor>(nullptr, nullptr);
        //ctx->V<1, 1, 'Q'>()[4] = 69;
    };
};

auto f1 = &elua::GlueStaticFunction::Static<void, func1>;
auto f2 = &elua::GlueStaticFunction::Static<long, func2>;
auto f3 = &elua::GlueStaticFunction::Static<void, long, func3>;
auto f4 = &elua::GlueStaticFunction::Static<long, long, func4>;
auto f5 = &elua::GlueStaticFunction::Static<long, long, long, func5>;
auto f6 = &elua::GlueStaticFunction::Static<long, long, int, func6>;

auto fc1  = &elua::GlueClassMemberFunction::Member<Test, void, &Test::Func1>;
auto fc2  = &elua::GlueClassMemberFunction::Member<Test, void, &Test::Func2>;
auto fc3  = &elua::GlueClassMemberFunction::Member<Test, void, int, &Test::Func3>;
auto fc4  = &elua::GlueClassMemberFunction::Member<Test, void, int, &Test::Func4>;
auto fc5  = &elua::GlueClassMemberFunction::Member<Test, void, int, long, &Test::Func5>;
auto fc6  = &elua::GlueClassMemberFunction::Member<Test, void, int, long, &Test::Func6>;
auto fc7  = &elua::GlueClassMemberFunction::Member<Test, int, &Test::Func7>;
auto fc8  = &elua::GlueClassMemberFunction::Member<Test, int, &Test::Func8>;
auto fc9  = &elua::GlueClassMemberFunction::Member<Test, int, int, &Test::Func9>;
auto fc10 = &elua::GlueClassMemberFunction::Member<Test, int, int, &Test::Func10>;
auto fc11 = &elua::GlueClassMemberFunction::Member<Test, int, int, long, &Test::Func11>;
auto fc12 = &elua::GlueClassMemberFunction::Member<Test, int, int, long, &Test::Func12>;

extern "C" void exl_main(void* x0, void* x1) {
    /* Setup hooking environment. */
    exl::hook::Initialize();

    Logging.Log("[endeavor] Initializing...");
    endv::version::Initialize();
    Logging.Log("[endeavor] Hash: %x", static_cast<uint>(endv::version::GetValue()));
    if(endv::version::IsValid()) {
        Logging.Log("[endeavor] Version: %s", endv::version::Get().text());
    } else {
        Logging.Log("[endeavor] Unknown version!");
    }
    // TestHook::InstallAtOffset(69);

    // R_ABORT_UNLESS(nn::socket::Initialize(s_SocketPool, SocketPoolSize, AllocatorPoolSize, 14));

    // /* Open socket. */
    // g_TcpSocket = nn::socket::Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // EXL_ABORT_UNLESS(g_TcpSocket >= 0);

    // /* Set socket to keep-alive. */
    // // int flags = true;
    // // nn::socket::SetSockOpt(g_TcpSocket, SOL_SOCKET, SO_KEEPALIVE, &flags, sizeof(flags));

    // /* Open and wait for connection. */
    // struct sockaddr_in serverAddr;
    // serverAddr.sin_family = AF_INET;
    // serverAddr.sin_port = nn::socket::InetHtons(SocketPort);
    // EXL_ABORT_UNLESS(nn::socket::InetPton(AF_INET, "192.168.0.206", &serverAddr.sin_addr) == 1);

    // EXL_ABORT_UNLESS(nn::socket::Connect(g_TcpSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) >= 0);

    // using NodeCreated = shimmer::protobuf::NodeCreated<128>;
    // NodeCreated e;
    // e.mutable_key() = 1;
    // e.mutable_parentKey() = 0;
    // e.mutable_label() = "test";

    // EmbeddedProto::WriteBufferFixedSize<256> buffer;
    // if(e.serialize(buffer) != EmbeddedProto::Error::NO_ERRORS) {
    //     EXL_ABORT("Failed to serialize");
    // }

    // uint length = buffer.get_size();
    // nn::socket::Send(g_TcpSocket, &length, sizeof(length), 0);
    // nn::socket::Send(g_TcpSocket, buffer.get_data(), buffer.get_size(), 0);
 
    // p.WriteInst(exl::armv8::inst::Nop());
    // p.WriteInst(exl::armv8::inst::Movz(exl::armv8::reg::W8, 0));
    // p.Seek(0x0120DE0C);
    // p.WriteInst(exl::armv8::inst::Nop());
    // p.Seek(0x0120DE1C);
    // p.WriteInst(exl::armv8::inst::Movz(exl::armv8::reg::W0, 0));

    // DbgSettingSceneFix::InstallAtOffset(0x00E266DC);
    // ReqChangeScene1::InstallAtFuncPtr<void, sead::SafeString const&, const char*>(&Lp::Utl::reqChangeScene);
    // ReqChangeScene2::InstallAtFuncPtr<void, int, const char*>(&Lp::Utl::reqChangeScene);
    // GetCurScene::InstallAtFuncPtr(Lp::Utl::getCurScene);


    endv::hooks::core::Install();
    endv::hooks::hio_node::Install();
    endv::hooks::shimmer::Install();
    endv::hooks::nvn::Install();

    /* Hooks for FixedAim and FilmingSupporter*/
    LayerGetCamera::InstallAtFuncPtr(&agl::lyr::Layer::getRenderCamera);
    MainMgrEnter::InstallAtFuncPtr(&Game::MainMgr::enter);
    MainMgrCalcGameFrame::InstallAtFuncPtr(&Game::MainMgr::calcGameFrame);
    MainMgrExit::InstallAtFuncPtr(&Game::MainMgr::exit);

    CameraAnimResourceLoad::InstallAtFuncPtr(&Cmn::CameraAnimResource::loadImpl);
    LpDbgTextWriterEntry::InstallAtFuncPtr(&Lp::Sys::DbgTextWriter::entryCmn);

    /* Hooks for missing model replacement */
    void (Lp::Sys::ModelArc::*modelArcLoadPtr)(sead::SafeString const&, sead::Heap*, sead::Heap*, bool, gsys::ModelResource::CreateArg const*) = &Lp::Sys::ModelArc::load;
    ModelArcInit::InstallAtFuncPtr(modelArcLoadPtr);
    ModelArcCheckIfResModel::InstallAtFuncPtr(&Lp::Sys::ModelArc::checkIfResModel);
    FieldLoadModerArcPtr::InstallAtPtr(reinterpret_cast<uintptr_t>(reinterpret_cast< void (*)(Game::Field*)>(&Game::Field::loadModelArc)) + 0x1DC);
    ObjCreateModelArc::InstallAtPtr(reinterpret_cast<uintptr_t>(reinterpret_cast< void (*)(Game::Obj*)>(&Game::Obj::createModelAndAnim_)) + 0x180);
    CollisionFix::InstallAtPtr(reinterpret_cast<uintptr_t>(reinterpret_cast< void (*)(Game::Lift*)>(&Game::Lift::reset_)) + 0x148);
    
    /* Hook to fix rocket bullets not being spawned*/
    BulletMgrCreateActorsRocketFix::InstallAtPtr(reinterpret_cast<uintptr_t>(reinterpret_cast< void (*)(Game::BulletMgr*)>(&Game::BulletMgr::createActors)) + 0x4048);
    
    /* Hook to fix controller disconnect crashing the game due to assert. */
    CtrlMgrChangeCtrlJoy::InstallAtFuncPtr(&Lp::Sys::CtrlMgr::changeCtrlJoy_);

    // f1(nullptr);
    // f2(nullptr);
    // f3(nullptr);
    // f4(nullptr);
    // f5(nullptr);
    // f6(nullptr);

    // fc1(nullptr);
    // fc2(nullptr);
    // fc3(nullptr);
    // fc4(nullptr);
    // fc5(nullptr);
    // fc6(nullptr);
    // fc7(nullptr);
    // fc8(nullptr);
    // fc9(nullptr);
    // fc10(nullptr);
    // fc11(nullptr);
    // fc12(nullptr);
}

extern "C" NORETURN void exl_exception_entry() {
    /* Note: this is only applicable in the context of applets/sysmodules. */
    EXL_ABORT("Default exception handler called!");
}
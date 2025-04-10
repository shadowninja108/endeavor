#pragma once

#include "data.h"
#include "enums.h"

#define TYPE_NAME(name) \
    nvn##name##PROC
#define FUNC_NAME(name) \
    nvn##name
#define POINTER_NAME(name)  \
    pfnc_nvn##name
#define STRING_NAME(name)   \
    pfnc_nvn##name##_name
    

#define FUNC(name, ret, ...)                        \
    typedef ret (*TYPE_NAME(name))(__VA_ARGS__);    \
    extern TYPE_NAME(name) POINTER_NAME(name);      \
    const char STRING_NAME(name)[] = "nvn" #name

// nvnDeviceBuilderSetDefaults
// nvnDeviceBuilderSetFlags
FUNC(DeviceInitialize, bool, NVNdevice*, NVNdeviceBuilder*);
// nvnDeviceFinalize
// nvnDeviceSetDebugLabel
FUNC(DeviceGetProcAddress, void*, NVNdevice*, const char*);
// nvnDeviceGetInteger
// nvnDeviceGetCurrentTimestampInNanoseconds
// nvnDeviceSetIntermediateShaderCache
// nvnDeviceGetTextureHandle
// nvnDeviceGetTexelFetchHandle
// nvnDeviceGetImageHandle
// nvnDeviceInstallDebugCallback
// nvnDeviceSetWindowOriginMode
// nvnDeviceSetDepthMode
// nvnDeviceRegisterFastClearColor
// nvnDeviceRegisterFastClearColori
// nvnDeviceRegisterFastClearColorui
// nvnDeviceRegisterFastClearDepth
// nvnDeviceGetWindowOriginMode
// nvnDeviceGetDepthMode
// nvnDeviceGetTimestampInNanoseconds
// nvnDeviceApplyDeferredFinalizes
// nvnDeviceFinalizeCommandHandle
// nvnDeviceWalkDebugDatabase
// nvnDeviceGetSeparateTextureHandle
// nvnDeviceGetSeparateSamplerHandle
// nvnQueueGetError
// nvnQueueGetTotalCommandMemoryUsed
// nvnQueueGetTotalControlMemoryUsed
// nvnQueueGetTotalComputeMemoryUsed
// nvnQueueResetMemoryUsageCounts
// nvnQueueBuilderSetDevice
// nvnQueueBuilderSetDefaults
// nvnQueueBuilderSetFlags
// nvnQueueBuilderSetCommandMemorySize
// nvnQueueBuilderSetComputeMemorySize
// nvnQueueBuilderSetControlMemorySize
// nvnQueueBuilderGetQueueMemorySize
// nvnQueueBuilderSetQueueMemory
// nvnQueueBuilderSetCommandFlushThreshold
// nvnQueueInitialize
// nvnQueueFinalize
// nvnQueueSetDebugLabel
// nvnQueueSubmitCommands
// nvnQueueFlush
// nvnQueueFinish
// nvnQueuePresentTexture
// nvnQueueAcquireTexture
// nvnWindowBuilderSetDevice
// nvnWindowBuilderSetDefaults
// nvnWindowBuilderSetNativeWindow
// nvnWindowBuilderSetTextures
// nvnWindowBuilderSetPresentInterval
// nvnWindowBuilderGetNativeWindow
// nvnWindowBuilderGetPresentInterval
// nvnWindowInitialize
// nvnWindowFinalize
// nvnWindowSetDebugLabel
// nvnWindowAcquireTexture
// nvnWindowGetNativeWindow
// nvnWindowGetPresentInterval
// nvnWindowSetPresentInterval
// nvnWindowSetCrop
// nvnWindowGetCrop
// nvnProgramInitialize
// nvnProgramFinalize
// nvnProgramSetDebugLabel
// nvnProgramSetShaders
// nvnMemoryPoolBuilderSetDevice
// nvnMemoryPoolBuilderSetDefaults
// nvnMemoryPoolBuilderSetStorage
// nvnMemoryPoolBuilderSetFlags
// nvnMemoryPoolBuilderGetMemory
// nvnMemoryPoolBuilderGetSize
// nvnMemoryPoolBuilderGetFlags
// nvnMemoryPoolInitialize
// nvnMemoryPoolSetDebugLabel
// nvnMemoryPoolFinalize
// nvnMemoryPoolMap
// nvnMemoryPoolFlushMappedRange
// nvnMemoryPoolInvalidateMappedRange
// nvnMemoryPoolGetBufferAddress
// nvnMemoryPoolMapVirtual
// nvnMemoryPoolGetSize
// nvnMemoryPoolGetFlags
// nvnTexturePoolInitialize
// nvnTexturePoolSetDebugLabel
// nvnTexturePoolFinalize
// nvnTexturePoolRegisterTexture
// nvnTexturePoolRegisterImage
// nvnTexturePoolGetMemoryPool
// nvnTexturePoolGetMemoryOffset
// nvnTexturePoolGetSize
// nvnSamplerPoolInitialize
// nvnSamplerPoolSetDebugLabel
// nvnSamplerPoolFinalize
// nvnSamplerPoolRegisterSampler
// nvnSamplerPoolRegisterSamplerBuilder
// nvnSamplerPoolGetMemoryPool
// nvnSamplerPoolGetMemoryOffset
// nvnSamplerPoolGetSize
// nvnBufferBuilderSetDevice
// nvnBufferBuilderSetDefaults
// nvnBufferBuilderSetStorage
// nvnBufferBuilderGetMemoryPool
// nvnBufferBuilderGetMemoryOffset
// nvnBufferBuilderGetSize
// nvnBufferInitialize
// nvnBufferSetDebugLabel
// nvnBufferFinalize
// nvnBufferMap
// nvnBufferGetAddress
// nvnBufferFlushMappedRange
// nvnBufferInvalidateMappedRange
// nvnBufferGetMemoryPool
// nvnBufferGetMemoryOffset
// nvnBufferGetSize
// nvnBufferGetDebugID
// nvnTextureBuilderSetDevice
// *nvnTextureBuilderSetDefaults
// nvnTextureBuilderSetFlags
// nvnTextureBuilderSetTarget
// nvnTextureBuilderSetWidth
// nvnTextureBuilderSetHeight
// nvnTextureBuilderSetDepth
// nvnTextureBuilderSetSize1D
// nvnTextureBuilderSetSize2D
// nvnTextureBuilderSetSize3D
// nvnTextureBuilderSetLevels
// nvnTextureBuilderSetFormat
// nvnTextureBuilderSetSamples
// nvnTextureBuilderSetSwizzle
// nvnTextureBuilderSetDepthStencilMode
// *nvnTextureBuilderGetStorageSize
// *nvnTextureBuilderGetStorageAlignment
// nvnTextureBuilderSetStorage
// nvnTextureBuilderSetPackagedTextureData
// nvnTextureBuilderSetPackagedTextureLayout
// nvnTextureBuilderSetStride
// nvnTextureBuilderSetGLTextureName
// nvnTextureBuilderGetStorageClass
// nvnTextureBuilderGetFlags
// nvnTextureBuilderGetTarget
// nvnTextureBuilderGetWidth
// nvnTextureBuilderGetHeight
// nvnTextureBuilderGetDepth
// nvnTextureBuilderGetLevels
// nvnTextureBuilderGetFormat
// nvnTextureBuilderGetSamples
// nvnTextureBuilderGetSwizzle
// nvnTextureBuilderGetDepthStencilMode
// nvnTextureBuilderGetPackagedTextureData
// nvnTextureBuilderGetStride
// nvnTextureBuilderGetSparseTileLayout
// nvnTextureBuilderGetGLTextureName
// nvnTextureBuilderGetZCullStorageSize
// nvnTextureBuilderGetMemoryPool
// nvnTextureBuilderGetMemoryOffset
// nvnTextureViewSetDefaults
// nvnTextureViewSetLevels
// nvnTextureViewSetLayers
// nvnTextureViewSetFormat
// nvnTextureViewSetSwizzle
// nvnTextureViewSetDepthStencilMode
// nvnTextureViewSetTarget
// nvnTextureViewGetLevels
// nvnTextureViewGetLayers
// nvnTextureViewGetFormat
// nvnTextureViewGetSwizzle
// nvnTextureViewGetDepthStencilMode
// nvnTextureViewGetTarget
// nvnTextureViewCompare
// nvnTextureInitialize
// nvnTextureGetZCullStorageSize
// nvnTextureFinalize
// nvnTextureSetDebugLabel
// nvnTextureGetStorageClass
// nvnTextureGetViewOffset
// nvnTextureGetFlags
// nvnTextureGetTarget
// nvnTextureGetWidth
// nvnTextureGetHeight
// nvnTextureGetDepth
// nvnTextureGetLevels
// nvnTextureGetFormat
// nvnTextureGetSamples
// nvnTextureGetSwizzle
// nvnTextureGetDepthStencilMode
// nvnTextureGetStride
// nvnTextureGetTextureAddress
// nvnTextureGetSparseTileLayout
// nvnTextureWriteTexels
// nvnTextureReadTexels
// nvnTextureFlushTexels
// nvnTextureInvalidateTexels
// nvnTextureGetMemoryPool
// nvnTextureGetMemoryOffset
// nvnTextureGetStorageSize
// nvnTextureCompare
// nvnTextureGetDebugID
// nvnSamplerBuilderSetDevice
// nvnSamplerBuilderSetDefaults
// nvnSamplerBuilderSetMinMagFilter
// nvnSamplerBuilderSetWrapMode
// nvnSamplerBuilderSetLodClamp
// nvnSamplerBuilderSetLodBias
// nvnSamplerBuilderSetCompare
// nvnSamplerBuilderSetBorderColor
// nvnSamplerBuilderSetBorderColori
// nvnSamplerBuilderSetBorderColorui
// nvnSamplerBuilderSetMaxAnisotropy
// nvnSamplerBuilderSetReductionFilter
// nvnSamplerBuilderGetMinMagFilter
// nvnSamplerBuilderGetWrapMode
// nvnSamplerBuilderGetLodClamp
// nvnSamplerBuilderGetLodBias
// nvnSamplerBuilderGetCompare
// nvnSamplerBuilderGetBorderColor
// nvnSamplerBuilderGetBorderColori
// nvnSamplerBuilderGetBorderColorui
// nvnSamplerBuilderGetMaxAnisotropy
// nvnSamplerBuilderGetReductionFilter
// nvnSamplerInitialize
// nvnSamplerFinalize
// nvnSamplerSetDebugLabel
// nvnSamplerGetMinMagFilter
// nvnSamplerGetWrapMode
// nvnSamplerGetLodClamp
// nvnSamplerGetLodBias
// nvnSamplerGetCompare
// nvnSamplerGetBorderColor
// nvnSamplerGetBorderColori
// nvnSamplerGetBorderColorui
// nvnSamplerGetMaxAnisotropy
// nvnSamplerGetReductionFilter
// nvnSamplerCompare
// nvnSamplerGetDebugID
// nvnBlendStateSetDefaults
// nvnBlendStateSetBlendTarget
// nvnBlendStateSetBlendFunc
// nvnBlendStateSetBlendEquation
// nvnBlendStateSetAdvancedMode
// nvnBlendStateSetAdvancedOverlap
// nvnBlendStateSetAdvancedPremultipliedSrc
// nvnBlendStateSetAdvancedNormalizedDst
// nvnBlendStateGetBlendTarget
// nvnBlendStateGetBlendFunc
// nvnBlendStateGetBlendEquation
// nvnBlendStateGetAdvancedMode
// nvnBlendStateGetAdvancedOverlap
// nvnBlendStateGetAdvancedPremultipliedSrc
// nvnBlendStateGetAdvancedNormalizedDst
// nvnColorStateSetDefaults
// nvnColorStateSetBlendEnable
// nvnColorStateSetLogicOp
// nvnColorStateSetAlphaTest
// nvnColorStateGetBlendEnable
// nvnColorStateGetLogicOp
// nvnColorStateGetAlphaTest
// nvnChannelMaskStateSetDefaults
// nvnChannelMaskStateSetChannelMask
// nvnChannelMaskStateGetChannelMask
// nvnMultisampleStateSetDefaults
// nvnMultisampleStateSetMultisampleEnable
// nvnMultisampleStateSetSamples
// nvnMultisampleStateSetAlphaToCoverageEnable
// nvnMultisampleStateSetAlphaToCoverageDither
// nvnMultisampleStateGetMultisampleEnable
// nvnMultisampleStateGetSamples
// nvnMultisampleStateGetAlphaToCoverageEnable
// nvnMultisampleStateGetAlphaToCoverageDither
// nvnMultisampleStateSetRasterSamples
// nvnMultisampleStateGetRasterSamples
// nvnMultisampleStateSetCoverageModulationMode
// nvnMultisampleStateGetCoverageModulationMode
// nvnMultisampleStateSetCoverageToColorEnable
// nvnMultisampleStateGetCoverageToColorEnable
// nvnMultisampleStateSetCoverageToColorOutput
// nvnMultisampleStateGetCoverageToColorOutput
// nvnMultisampleStateSetSampleLocationsEnable
// nvnMultisampleStateGetSampleLocationsEnable
// nvnMultisampleStateGetSampleLocationsGrid
// nvnMultisampleStateSetSampleLocationsGridEnable
// nvnMultisampleStateGetSampleLocationsGridEnable
// nvnMultisampleStateSetSampleLocations
// nvnPolygonStateSetDefaults
// nvnPolygonStateSetCullFace
// nvnPolygonStateSetFrontFace
// nvnPolygonStateSetPolygonMode
// nvnPolygonStateSetPolygonOffsetEnables
// nvnPolygonStateGetCullFace
// nvnPolygonStateGetFrontFace
// nvnPolygonStateGetPolygonMode
// nvnPolygonStateGetPolygonOffsetEnables
// nvnDepthStencilStateSetDefaults
// nvnDepthStencilStateSetDepthTestEnable
// nvnDepthStencilStateSetDepthWriteEnable
// nvnDepthStencilStateSetDepthFunc
// nvnDepthStencilStateSetStencilTestEnable
// nvnDepthStencilStateSetStencilFunc
// nvnDepthStencilStateSetStencilOp
// nvnDepthStencilStateGetDepthTestEnable
// nvnDepthStencilStateGetDepthWriteEnable
// nvnDepthStencilStateGetDepthFunc
// nvnDepthStencilStateGetStencilTestEnable
// nvnDepthStencilStateGetStencilFunc
// nvnDepthStencilStateGetStencilOp
// nvnVertexAttribStateSetDefaults
// nvnVertexAttribStateSetFormat
// nvnVertexAttribStateSetStreamIndex
// nvnVertexAttribStateGetFormat
// nvnVertexAttribStateGetStreamIndex
// nvnVertexStreamStateSetDefaults
// nvnVertexStreamStateSetStride
// nvnVertexStreamStateSetDivisor
// nvnVertexStreamStateGetStride
// nvnVertexStreamStateGetDivisor
// nvnCommandBufferInitialize
// nvnCommandBufferFinalize
// nvnCommandBufferSetDebugLabel
// nvnCommandBufferSetMemoryCallback
// nvnCommandBufferSetMemoryCallbackData
// nvnCommandBufferAddCommandMemory
// nvnCommandBufferAddControlMemory
// nvnCommandBufferGetCommandMemorySize
// nvnCommandBufferGetCommandMemoryUsed
// nvnCommandBufferGetCommandMemoryFree
// nvnCommandBufferGetControlMemorySize
// nvnCommandBufferGetControlMemoryUsed
// nvnCommandBufferGetControlMemoryFree
// nvnCommandBufferBeginRecording
// nvnCommandBufferEndRecording
// nvnCommandBufferCallCommands
// nvnCommandBufferCopyCommands
// nvnCommandBufferBindBlendState
// nvnCommandBufferBindChannelMaskState
// nvnCommandBufferBindColorState
// nvnCommandBufferBindMultisampleState                                                    
// nvnCommandBufferBindPolygonState
// nvnCommandBufferBindDepthStencilState
// nvnCommandBufferBindVertexAttribState
// nvnCommandBufferBindVertexStreamState
// nvnCommandBufferBindProgram
// nvnCommandBufferBindVertexBuffer
// nvnCommandBufferBindVertexBuffers
// nvnCommandBufferBindUniformBuffer
// nvnCommandBufferBindUniformBuffers
// nvnCommandBufferBindTransformFeedbackBuffer
// nvnCommandBufferBindTransformFeedbackBuffers
// nvnCommandBufferBindStorageBuffer
// nvnCommandBufferBindStorageBuffers
// nvnCommandBufferBindTexture
// nvnCommandBufferBindTextures
// nvnCommandBufferBindImage
// nvnCommandBufferBindImages
// nvnCommandBufferSetPatchSize
// nvnCommandBufferSetInnerTessellationLevels
// nvnCommandBufferSetOuterTessellationLevels
// nvnCommandBufferSetPrimitiveRestart
// nvnCommandBufferBeginTransformFeedback
// nvnCommandBufferEndTransformFeedback
// nvnCommandBufferPauseTransformFeedback
// nvnCommandBufferResumeTransformFeedback
// nvnCommandBufferDrawTransformFeedback
// nvnCommandBufferDrawArrays
// nvnCommandBufferDrawElements
// nvnCommandBufferDrawElementsBaseVertex
// nvnCommandBufferDrawArraysInstanced
// nvnCommandBufferDrawElementsInstanced
// nvnCommandBufferDrawArraysIndirect
// nvnCommandBufferDrawElementsIndirect
// nvnCommandBufferMultiDrawArraysIndirectCount
// nvnCommandBufferMultiDrawElementsIndirectCount                                               
FUNC(CommandBufferClearColor, void, NVNcommandBuffer*, int, const float*, int);
// nvnCommandBufferClearColori
// nvnCommandBufferClearColorui
// nvnCommandBufferClearDepthStencil
// nvnCommandBufferDispatchCompute
// nvnCommandBufferDispatchComputeIndirect
// nvnCommandBufferSetViewport
// nvnCommandBufferSetViewports
// nvnCommandBufferSetViewportSwizzles
// nvnCommandBufferSetScissor
// nvnCommandBufferSetScissors
// nvnCommandBufferSetDepthRange
// nvnCommandBufferSetDepthBounds
// nvnCommandBufferSetDepthRanges
// nvnCommandBufferSetTiledCacheAction
// nvnCommandBufferSetTiledCacheTileSize
// nvnCommandBufferBindSeparateTexture
// nvnCommandBufferBindSeparateSampler
// nvnCommandBufferBindSeparateTextures
// nvnCommandBufferBindSeparateSamplers
// nvnCommandBufferSetStencilValueMask
// nvnCommandBufferSetStencilMask
// nvnCommandBufferSetStencilRef
// nvnCommandBufferSetBlendColor
// nvnCommandBufferSetPointSize
// nvnCommandBufferSetLineWidth
// nvnCommandBufferSetPolygonOffsetClamp
// nvnCommandBufferSetAlphaRef
// nvnCommandBufferSetSampleMask
// nvnCommandBufferSetRasterizerDiscard
// nvnCommandBufferSetDepthClamp
// nvnCommandBufferSetConservativeRasterEnable
// nvnCommandBufferSetConservativeRasterDilate
// nvnCommandBufferSetSubpixelPrecisionBias
// nvnCommandBufferCopyBufferToTexture
// nvnCommandBufferCopyTextureToBuffer
// nvnCommandBufferCopyTextureToTexture
// nvnCommandBufferCopyBufferToBuffer
// nvnCommandBufferClearBuffer
// nvnCommandBufferClearTexture
// nvnCommandBufferClearTexturei
// nvnCommandBufferClearTextureui
// nvnCommandBufferUpdateUniformBuffer                                                              
// nvnCommandBufferReportCounter
// nvnCommandBufferResetCounter
// nvnCommandBufferReportValue
// nvnCommandBufferSetRenderEnable
// nvnCommandBufferSetRenderEnableConditional
// nvnCommandBufferSetRenderTargets
// nvnCommandBufferDiscardColor
// nvnCommandBufferDiscardDepthStencil
// nvnCommandBufferDownsample
// nvnCommandBufferTiledDownsample
// nvnCommandBufferBarrier
// nvnCommandBufferWaitSync
// nvnCommandBufferFenceSync
// nvnCommandBufferSetTexturePool
// nvnCommandBufferSetSamplerPool
// nvnCommandBufferSetShaderScratchMemory
// nvnCommandBufferSaveZCullData
// nvnCommandBufferRestoreZCullData
// nvnCommandBufferSetCopyRowStride
// nvnCommandBufferSetCopyImageStride
// nvnCommandBufferGetCopyRowStride
// nvnCommandBufferGetCopyImageStride
// nvnCommandBufferDrawTexture
// nvnProgramSetSubroutineLinkage
// nvnCommandBufferSetProgramSubroutines
// nvnCommandBufferBindCoverageModulationTable
// nvnCommandBufferResolveDepthBuffer
// nvnCommandBufferPushDebugGroupStatic
// nvnCommandBufferPushDebugGroupDynamic
// nvnCommandBufferPushDebugGroup
// nvnCommandBufferPopDebugGroup
// nvnCommandBufferPopDebugGroupId
// nvnCommandBufferInsertDebugMarker
// nvnCommandBufferGetMemoryCallback
// nvnCommandBufferGetMemoryCallbackData
// nvnCommandBufferIsRecording
// nvnSyncInitialize

#undef TYPE_NAME
#undef FUNC_NAME
#undef POINTER_NAME
#undef STRING_NAME

void* nvnBootstrapLoader(const char*);
void nvnLoadCProcs(NVNdevice*, nvnDeviceGetProcAddressPROC);
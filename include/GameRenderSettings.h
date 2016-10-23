#ifndef _FB_GAME_RENDER_SETTINGS_H_
#define _FB_GAME_RENDER_SETTINGS_H_

namespace fb
{	
	class GameRenderSettings //: public dice::DataContainer
	{
	public:
		enum 	
		{
			kVersion = 0x1
		};
		
		enum 	
		{
			field__Base = 0xFF,
			field_Renderer = 0x0,
			field_MultisampleCount = 0x1,
			field_MultisampleQuality = 0x2,
			field_Fullscreen = 0x3,
			field_ForceVSyncEnable = 0x4,
			field_Dx10PlusEnable = 0x5,
			field_Dx10Enable = 0x6,
			field_Dx10DebugInfoEnable = 0x7,
			field_Dx11Enable = 0x8,
			field_Dx11DebugInfoEnable = 0x9,
			field_NvPerfHUDEnable = 0xA,
			field_Dx9AdapterIndex = 0xB,
			field_Dx9RefreshRate = 0xC,
			field_XenonRingBufferSize = 0xD,
			field_XenonBufferTwoFramesEnable = 0xE,
			field_XenonPresentImmediateThreshold = 0xF,
			field_Ps3FrameMainBufferSize = 0x10,
			field_Ps3FrameLocalBufferSize = 0x11,
			field_Ps3LinearFrameCmdBufEnable = 0x12,
			field_Ps3CellMemoryTexturesEnable = 0x13,
			field_GcmHudEnable = 0x14,
			field_PerfOverlayEnable = 0x15,
			field_PerfOverlayVisible = 0x16,
			field_SkipMipmapCount = 0x17,
			field_DrawShaderStats = 0x18,
			field_DrawInfo = 0x19,
			field_JobEnable = 0x1A,
			field_JobThreadIndex = 0x1B,
			field_JobPriority = 0x1C,
			field_BuildJobSyncEnable = 0x1D,
			field_DecalsEnable = 0x1E,
			field_EmittersEnable = 0x1F,
			field_EntityRenderEnable = 0x20,
			field_DebugRendererEnable = 0x21,
			field_InitialClearEnable = 0x22,
			field_GpuProfilerEnable = 0x23,
			field_NearPlane = 0x24,
			field_ViewDistance = 0x25,
			field_ForceFov = 0x26,
			field_RigidMeshBatchingEnable = 0x27,
			field_CompositeMeshBatchingEnable = 0x28,
			field_EdgeModelsEnable = 0x29,
			field_EdgeModelCastShadowsEnable = 0x2A,
			field_EdgeModelScreenAreaScale = 0x2B,
			field_EdgeModelDefaultMinScreenArea = 0x2C,
			field_EdgeModelSpuInstancingEnable = 0x2D,
			field_EdgeModelUseMainLodEnable = 0x2E,
			field_EdgeModelForceLod = 0x2F,
			field_EdgeModelUseLodBox = 0x30,
			field_EdgeModelLodScale = 0x31,
			field_EdgeModelMaxVisibleInstanceCount = 0x32,
			field_EdgeModelCullEnable = 0x33,
			field_EdgeModelFrustumCullEnable = 0x34,
			field_EdgeModelOcclusionCullEnable = 0x35,
			field_EdgeModelAdditionalCullEnable = 0x36,
			field_EdgeModelDrawBoxes = 0x37,
			field_EdgeModelDrawStats = 0x38,
			field_StaticModelPartCullEnable = 0x39,
			field_StaticModelPartFrustumCullEnable = 0x3A,
			field_StaticModelPartOcclusionCullEnable = 0x3B,
			field_StaticModelPartShadowCullEnable = 0x3C,
			field_StaticModelDrawBoxes = 0x3D,
			field_StaticModelDrawStats = 0x3E,
			field_StaticModelPartOcclusionMaxScreenArea = 0x3F,
			field_StaticModelCullJobCount = 0x40,
			field_StaticModelCullSpuJobEnable = 0x41,
			field_LockView = 0x42,
			field_ResetLockedView = 0x43,
			field_FadeEnable = 0x44,
			field_FadeWaitingEnable = 0x45,
			field_ForceBlurAmount = 0x46,
			field_ForceWorldFadeAmount = 0x47,
			field_ForceGlobalFadeAmount = 0x48,
			field_ShadowsEnable = 0x49,
			field_ForegroundBlurEnable = 0x4A,
			field_BlurEnable = 0x4B,
			field__Count = 0x4C
		};

		char _pad[12];
		float m_viewDistance; 
		float m_nearPlane;
		float m_edgeModelScreenAreaScale;
		float m_forceFov; 
		unsigned int m_skipMipmapCount; 
		unsigned int m_ps3FrameLocalBufferSize;
		unsigned int m_jobPriority;
		unsigned int m_jobThreadIndex; 
		float m_edgeModelDefaultMinScreenArea; 
		float m_forceBlurAmount;
		unsigned int m_staticModelCullJobCount;
		float m_forceGlobalFadeAmount;
		float m_forceWorldFadeAmount;
		float m_edgeModelLodScale;
		int m_edgeModelForceLod;
		float m_staticModelPartOcclusionMaxScreenArea; 
		unsigned int m_edgeModelMaxVisibleInstanceCount; 
		unsigned int m_multisampleQuality; 
		unsigned int m_xenonPresentImmediateThreshold; 
		unsigned int m_dx9RefreshRate; 
		int m_dx9AdapterIndex; 
		unsigned int m_xenonRingBufferSize; 
		unsigned int m_multisampleCount; 
		unsigned int m_ps3FrameMainBufferSize; 
		int m_renderer;
		bool m_staticModelPartCullEnable;
		bool m_edgeModelDrawStats; 
		bool m_staticModelPartFrustumCullEnable; 
		bool m_edgeModelOcclusionCullEnable; 
		bool m_staticModelPartOcclusionCullEnable; 
		bool m_dx10PlusEnable; 
		bool m_edgeModelFrustumCullEnable;
		bool m_edgeModelCullEnable;
		bool m_edgeModelDrawBoxes; 
		bool m_dx10Enable; 
		bool m_edgeModelAdditionalCullEnable; 
		bool m_fadeWaitingEnable; 
		bool m_fadeEnable; 
		bool m_resetLockedView; 
		bool m_blurEnable; 
		bool m_foregroundBlurEnable;
		bool m_shadowsEnable; 
		bool m_lockView; 
		bool m_staticModelDrawStats; 
		bool m_staticModelDrawBoxes; 
		bool m_staticModelPartShadowCullEnable; 
		bool m_staticModelCullSpuJobEnable;
		bool m_fullscreen; 
		bool m_forceVSyncEnable; 
		bool m_buildJobSyncEnable;
		bool m_xenonBufferTwoFramesEnable;
		bool m_jobEnable; 
		bool m_entityRenderEnable;
		bool m_emittersEnable;
		bool m_decalsEnable; 
		bool m_drawInfo; 
		bool m_gcmHudEnable;
		bool m_ps3CellMemoryTexturesEnable; 
		bool m_ps3LinearFrameCmdBufEnable; 
		bool m_drawShaderStats; 
		bool m_perfOverlayVisible; 
		bool m_perfOverlayEnable;
		bool m_debugRendererEnable;
		bool m_edgeModelSpuInstancingEnable; 
		bool m_dx11Enable;
		bool m_dx11DebugInfoEnable; 
		bool m_edgeModelUseLodBox;
		bool m_dx10DebugInfoEnable;
		bool m_edgeModelUseMainLodEnable; 
		bool m_edgeModelCastShadowsEnable; 
		bool m_nvPerfHUDEnable; 
		bool m_gpuProfilerEnable; 
		bool m_initialClearEnable; 
		bool m_edgeModelsEnable;
		bool m_compositeMeshBatchingEnable; 
		bool m_rigidMeshBatchingEnable;
	};
}
#endif
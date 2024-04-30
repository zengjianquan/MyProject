#include "CTSceneViewExtension.h"
#include "CTGlobalShader.h"
#include "PixelShaderUtils.h"
#include "PostProcess/PostProcessing.h"

void FCTSceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
	if (!View.bIsViewInfo)
		return;

	//通过将 FViewInfo 类型进行强制转换, 来指定视口矩形 ViewPort
	const FIntRect ViewPort = static_cast<const FViewInfo&>(View).ViewRect;
	FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);

	RDG_EVENT_SCOPE(GraphBuilder, "CTRenderPass");
	
	FRHISamplerState* PointClampSampler = TStaticSamplerState<SF_Point, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI();
	Inputs.Validate();
	
	FScreenPassTexture SceneColor((*(Inputs.SceneTextures))->SceneColorTexture, ViewPort);

	TShaderMapRef<FCTGlobalShaderPS> CTGlobalShaderPS(GlobalShaderMap);
	FCTGlobalShaderPS::FParameters* CTGlobalShaderParameters = 
		GraphBuilder.AllocParameters<FCTGlobalShaderPS::FParameters>();

	CTGlobalShaderParameters->InputTexture = SceneColor.Texture;
	CTGlobalShaderParameters->SvPositionToInputTextureUV =
		FScreenTransform::ChangeTextureBasisFromTo(
			FScreenPassTextureViewport(SceneColor),
			FScreenTransform::ETextureBasis::TexelPosition,
			FScreenTransform::ETextureBasis::ViewportUV) *
		FScreenTransform::ChangeTextureBasisFromTo(
			FScreenPassTextureViewport(SceneColor),
			FScreenTransform::ETextureBasis::ViewportUV,
			FScreenTransform::ETextureBasis::TextureUV
		);
	CTGlobalShaderParameters->InputSampler = PointClampSampler;
	CTGlobalShaderParameters->InputColor = TintColor;
	CTGlobalShaderParameters->RenderTargets[0] = FRenderTargetBinding(
		SceneColor.Texture, ERenderTargetLoadAction::ELoad
	);

	FPixelShaderUtils::AddFullscreenPass(
		GraphBuilder,
		GlobalShaderMap,
		FRDGEventName(TEXT("CTPass")),
		CTGlobalShaderPS,
		CTGlobalShaderParameters,
		ViewPort
	);
}

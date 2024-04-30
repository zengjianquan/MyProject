#pragma once

#include "GlobalShader.h"
#include "Runtime/Renderer/Private/ScreenPass.h"

class FCTGlobalShaderPS : public FGlobalShader {
public:
	DECLARE_SHADER_TYPE(FCTGlobalShaderPS, Global, );
	SHADER_USE_PARAMETER_STRUCT(FCTGlobalShaderPS, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER(FScreenTransform, SvPositionToInputTextureUV)
		SHADER_PARAMETER_RDG_TEXTURE(Texture2D, InputTexture)
		SHADER_PARAMETER_SAMPLER(SamplerState, InputSampler)
		SHADER_PARAMETER(FLinearColor, InputColor)
		RENDER_TARGET_BINDING_SLOTS()
	END_SHADER_PARAMETER_STRUCT()
};
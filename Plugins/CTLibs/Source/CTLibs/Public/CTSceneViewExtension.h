#pragma once
#include "SceneViewExtension.h"

class CTLIBS_API FCTSceneViewExtension : public FSceneViewExtensionBase
{
private:
    FLinearColor TintColor;

public:
    FCTSceneViewExtension( const FAutoRegister& AutoRegister, const FLinearColor& color)
    : FSceneViewExtensionBase( AutoRegister ), TintColor(color)
    {
    }

    /**
     * Called on game thread when creating the view family.
     */
    virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override {};

    /**
     * Called on game thread when creating the view.
     */
    virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override {};

    /**
    * Called on game thread when view family is about to be rendered.
    */
    virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override {};

    /**
     * Called right before Post Processing rendering begins
     */
    virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs);
};
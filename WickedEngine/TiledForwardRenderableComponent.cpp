#include "TiledForwardRenderableComponent.h"
#include "wiRenderer.h"
#include "wiImage.h"
#include "wiImageEffects.h"
#include "wiHelper.h"

using namespace wiGraphicsTypes;

TiledForwardRenderableComponent::TiledForwardRenderableComponent() {
	ForwardRenderableComponent::setProperties();
	setShadowsEnabled(true);
}
TiledForwardRenderableComponent::~TiledForwardRenderableComponent() {
}

void TiledForwardRenderableComponent::RenderScene(GRAPHICSTHREAD threadID)
{
	rtMain.Activate(threadID, 0, 0, 0, 0, true); // depth prepass
	{
		wiRenderer::SetClipPlane(XMFLOAT4(0, 0, 0, 0), threadID);

		wiRenderer::EnableForwardShadowmaps(threadID);
		wiRenderer::DrawWorld(wiRenderer::getCamera(), getTessellationEnabled(), threadID
			, false, SHADERTYPE_ALPHATESTONLY
			, nullptr, false);
	}

	rtLinearDepth.Activate(threadID); {
		wiImageEffects fx;
		fx.blendFlag = BLENDMODE_OPAQUE;
		fx.sampleFlag = SAMPLEMODE_CLAMP;
		fx.quality = QUALITY_NEAREST;
		fx.process.setLinDepth(true);
		wiImage::Draw(rtMain.depth->GetTexture(), fx, threadID);
	}
	rtLinearDepth.Deactivate(threadID);
	dtDepthCopy.CopyFrom(*rtMain.depth, threadID);

	wiRenderer::UpdateDepthBuffer(dtDepthCopy.GetTexture(), rtLinearDepth.GetTexture(), threadID);

	wiRenderer::ComputeTiledLightCulling(threadID);

	wiRenderer::GetDevice()->UnBindResources(TEXSLOT_ONDEMAND0, 1, threadID);

	rtMain.Set(threadID);
	{
		wiRenderer::DrawWorld(wiRenderer::getCamera(), getTessellationEnabled(), threadID
			, false, SHADERTYPE_TILEDFORWARD
			, nullptr, false);
		wiRenderer::DrawSky(threadID);
	}
}
void TiledForwardRenderableComponent::RenderTransparentScene(wiRenderTarget& mainRT, wiRenderTarget& shadedSceneRT, GRAPHICSTHREAD threadID)
{
	rtTransparent.Activate(threadID, mainRT.depth); {
		wiRenderer::DrawWorldTransparent(wiRenderer::getCamera(), SHADERTYPE_TILEDFORWARD, shadedSceneRT.GetTexture(), rtReflection.GetTexture()
			, rtWaterRipple.GetTexture(), threadID, true);
		wiRenderer::DrawTrails(threadID, shadedSceneRT.GetTexture());
	}
}

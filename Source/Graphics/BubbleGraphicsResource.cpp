#include "Graphics/BubbleGraphicsResources.h"
#include "Graphics/CircleOutlineGraphicsResource.h"
#include "Graphics/CircleFIllGraphicsResource.h"
#include "Components/TransformComponent.h"

//---------------------------------------------------------------------------
// Name: BubbleGraphicsResource
// Desc: 
//---------------------------------------------------------------------------
BubbleGraphicsResource::BubbleGraphicsResource(float radius)
{
	this->radius = radius;

	bubbleCircle = new CircleOutlineGraphicsResource(radius, 1.0f, 0xff, 0xff, 0xff, 0xff);
	bubbleHighlight = new CircleFillGraphicsResource(radius / 5.0f, 0xff, 0x8f, 0x8f, 0x8f);
}
//---------------------------------------------------------------------------
// Name: ~BubbleGraphicsResource
// Desc: 
//---------------------------------------------------------------------------
BubbleGraphicsResource::~BubbleGraphicsResource()
{
	delete this->bubbleCircle;
	delete this->bubbleHighlight;
}
//---------------------------------------------------------------------------
// Name: Render
// Desc: 
//---------------------------------------------------------------------------
void BubbleGraphicsResource::Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent)
{
	this->bubbleCircle->Render(sdlRenderer, transformComponent);

	auto highlightTransformComponent = *transformComponent;

	highlightTransformComponent.position.x += 0.4f*this->radius;
	highlightTransformComponent.position.y -= 0.4f*this->radius;

	bubbleHighlight->Render(sdlRenderer, &highlightTransformComponent);
}

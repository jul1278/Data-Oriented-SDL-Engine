#include "Graphics/Camera.h"

//------------------------------------------------------------------------------------------------
// Name: Render
// Desc:
//------------------------------------------------------------------------------------------------
void Camera::Render()
{
	for (auto collection : this->renderCollections) {
		
		auto graphicComponents = this->componentRepository->Select<GraphicsComponent>(collection);
		auto transformComponents = this->componentRepository->Select<TransformComponent>(collection);

		if (graphicComponents.Size() == 0 || transformComponents.Size() == 0) {
			continue;
		}

		if (this->transform != nullptr) {
			this->graphics->UpdateGraphics(graphicComponents, transformComponents, this->transform->operator()());
		} else {
			this->graphics->UpdateGraphics(graphicComponents, transformComponents, &this->shakeTransform);
		}
	}
}

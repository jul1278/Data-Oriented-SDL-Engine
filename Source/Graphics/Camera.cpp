#include "Graphics/Camera.h"

//------------------------------------------------------------------------------------------------
// Name: Render
// Desc:
//------------------------------------------------------------------------------------------------
void Camera::Render()
{
	for (auto collection : this->renderCollections) {
		
		auto graphicComponents = this->componentCollectionRepository->SelectFromCollection<GraphicsComponent>(collection);
		auto transformComponents = this->componentCollectionRepository->SelectFromCollection<TransformComponent>(collection);

		if (graphicComponents == nullptr || transformComponents == nullptr ||
			graphicComponents->size() == 0 || transformComponents->size() == 0) {
			continue;
		}

		if (this->transform != nullptr) {
			this->graphics->UpdateGraphics(graphicComponents, transformComponents, this->transform->operator()());
		} else {
			this->graphics->UpdateGraphics(graphicComponents, transformComponents, &this->shakeTransform);
		}
	}
}

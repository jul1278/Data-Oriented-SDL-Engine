//
// Created by Julian  on 22/11/15.
//

#ifndef PROCEDURAL_ASTEROID_GRAPHICS_RESOURCE_H
#define PROCEDURAL_ASTEROID_GRAPHICS_RESOURCE_H

#include "GraphicsResources/IGraphicsResource.h"
#include "Graphics.h"
#include "GraphicsUtility.h"

#include "Utility/MathUtility.h"

// CircleGraphicsResource
class ProceduralAsteroidGraphicsResource : public IGraphicsResource
{
private:

	vector<Vector2D> points; 

public:

	ProceduralAsteroidGraphicsResource(const float radius, const unsigned int points)
	{
		const auto angleInc = (2 * M_PI) / points;
		auto angle = 0.0f;

		for (auto i = 0; i < points; i++) {
			auto d = radius + 0.5f*radius*MathUtility::RandomFloatUniformDist();
			auto x = d*cosf(angle);
			auto y = d*sinf(angle);

			this->points.push_back(Vector2D(x, y));

			angle += angleInc;
		}
	}

	virtual void Render(SDL_Renderer* sdlRenderer, TransformComponent* transformComponent) final
	{
		if (sdlRenderer == nullptr) {
			return; 
		}

		SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);

		for (auto i = 0; i < (this->points.size() - 1); i++) {

			auto point1 = this->points[i] + transformComponent->position; 
			auto point2 = this->points[i + 1]+ transformComponent->position; 

			//SDL_RenderDrawPoint(sdlRenderer, point1.x, point1.y); 

			SDL_RenderDrawLine(sdlRenderer, point1.x, point1.y, point2.x, point2.y); 
		}

		auto startPoint = this->points.front() + transformComponent->position; 
		auto endPoint = this->points.back() + transformComponent->position; 

		SDL_RenderDrawLine(sdlRenderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y); 
	}
};

#endif // PROCEDURAL_ASTEROID_GRAPHICS_RESOURCE_H
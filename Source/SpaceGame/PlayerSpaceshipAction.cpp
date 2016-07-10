#include "SpaceGame/PlayerSpaceshipAction.h"
#include "Graphics/Color.h"
#include <Physics/VelocityTask.h>

//-------------------------------------------------------------------------------------
// Name: PlayerSpaceshipAction
// Desc: 
//-------------------------------------------------------------------------------------
PlayerSpaceshipAction::PlayerSpaceshipAction(IStage* stage) : IAction(stage)
{
	auto graphics = stage->GetGameApp()->GetGraphics();

	this->width = graphics->WindowWidth();
	this->height = graphics->WindowHeight();
	this->sdlEventCollector = new SDLEventCollector(this->width, this->height);

	this->moveCounter = 0;

	//
	// Resources
	//
	this->projectileGraphicResId = graphics->AddGraphicsResource(new RectGraphicsResource(2.0f, 12.0f, Color(Color::Red)));
	auto spaceShipGraphicResId = graphics->LoadGraphicResource("Resources//space_ship.png", "spaceShip");

	//
	// Construct entities
	//
	SpaceGameEntityConstructor::ConstructPlayerSpaceShip(this->GetParentStage()->GetComponentCollectionRepository(), spaceShipGraphicResId, Vector2D(this->width / 2.0f, this->height - 60));
	//SpaceGameEntityConstructor::ConstructPlayerWeapons(this->GetParentStage()->GetComponentCollectionRepository());


	//
	// Event Handlers
	//
	auto buttonEventHandler = [this](const ButtonEventArgs& buttonEventArgs) { this->OnButtonEvent(buttonEventArgs); };
	auto asteroidCollisionHandler = [this](const CollisionEventArgs& collisionEventArgs) {this->OnPlayerAsteroidCollision(collisionEventArgs); };

	this->sdlEventCollector->RegisterListener<ButtonEventArgs>(bind(buttonEventHandler, placeholders::_1));

	auto task = new CollisionPhysicsTask("PlayerSpaceShip", "EnemyAsteroids");
	task->RegisterListener<CollisionEventArgs>(bind(asteroidCollisionHandler, placeholders::_1));

	this->GetParentStage()->GetPhysics()->AddPhysicsTask(task);
	this->GetParentStage()->GetPhysics()->AddPhysicsTask(new VelocityTask("PlayerSpaceShip")); 
	this->GetParentStage()->GetPhysics()->AddPhysicsTask(new VelocityTask("PlayerSpaceShipProjectiles")); 
}
//-------------------------------------------------------------------------------------
// Name: MoveSpaceShip
// Desc: 
//-------------------------------------------------------------------------------------
void PlayerSpaceshipAction::MoveSpaceShip(const ButtonEventArgs& buttonEventArgs) const
{
	auto componentCollectionRepository = this->GetParentStage()->GetComponentCollectionRepository();
	auto playerPhysicsComponents = componentCollectionRepository->SelectFromCollection<PhysicsComponent>("PlayerSpaceShip");

	for (auto& physicsComponent : *playerPhysicsComponents) {

		auto transformComponent = componentCollectionRepository->Select<TransformComponent>(physicsComponent.transformComponentId);

		if (transformComponent->position.y < (this->height - 60)) {
			physicsComponent.velocity.y = 1.0f;
		}
		else {
			physicsComponent.velocity.y = 0.0f;
		}

		if (!buttonEventArgs.Released()) {

			switch (buttonEventArgs.Key()) {
			case LEFT_ARROW:
			{
				if (transformComponent->position.x > 25) {
					physicsComponent.velocity = Vector2D(-4.0f, 0.0f);
				}
				break;
			}
			case RIGHT_ARROW:
			{
				if (transformComponent->position.x < (this->width - 50)) {
					physicsComponent.velocity = Vector2D(4.0f, 0.0f);
				}
				break;
			}
			case UP_ARROW:
			{
				if (transformComponent->position.y > 25) {
					physicsComponent.velocity = Vector2D(0.0f, -4.0f);
				}
				break;
			}
			case DOWN_ARROW:
			{
				if (transformComponent->position.y < (this->height - 60)) {
					physicsComponent.velocity = Vector2D(0.0f, 4.0f);
				}
				break;
			}
			case SPACE:
			{
				break;
			}

			default: break;
			}
		} else {
			physicsComponent.velocity.x = 0.0f;
		}
	}
}
//-------------------------------------------------------------------------------------
// Name: OnButtonEvent
// Desc: 
//-------------------------------------------------------------------------------------
void PlayerSpaceshipAction::FireWeapon(const ButtonEventArgs buttonEventArgs) const
{
	auto componentCollectionRepository = this->GetParentStage()->GetComponentCollectionRepository(); 
	auto playerTransform = componentCollectionRepository->SelectFromCollection<TransformComponent>("PlayerSpaceShip")->front(); 

	if (!buttonEventArgs.Released()) {

		auto entityId = componentCollectionRepository->NewEntityId();

		auto transformComponent = componentCollectionRepository->NewComponent<TransformComponent>("PlayerSpaceShipProjectiles", entityId); 
		auto graphicsComponent = componentCollectionRepository->NewComponent<GraphicsComponent>("PlayerSpaceShipProjectiles", entityId);
		auto physicsComponent = componentCollectionRepository->NewComponent<PhysicsComponent>("PlayerSpaceShipProjectiles", entityId);

		transformComponent->position = playerTransform.position; 

		graphicsComponent->transformComponentId = transformComponent->id; 
		physicsComponent->transformComponentId = transformComponent->id; 

		graphicsComponent->resourceId = this->projectileGraphicResId; 
		physicsComponent->velocity = Vector2D(0.0f, -8.0f); 
		physicsComponent->radius = 1.0f; 
	}
}
//-------------------------------------------------------------------------------------
// Name: OnButtonEvent
// Desc: 
//-------------------------------------------------------------------------------------
void PlayerSpaceshipAction::OnButtonEvent(const ButtonEventArgs& buttonEventArgs) const
{
	switch (buttonEventArgs.Key()) {
		case UP_ARROW:
		case LEFT_ARROW: 
		case RIGHT_ARROW:
		case DOWN_ARROW:
		{
			this->MoveSpaceShip(buttonEventArgs);
			break;
		}

		case SPACE:
		{
			this->FireWeapon(buttonEventArgs);
			break;
		}
			
		default: 
			break;
	}
}
//--------------------------------------------------------------------------------------
// Name: OnPlayerAsteroidCollision
// Desc: 
//--------------------------------------------------------------------------------------
void PlayerSpaceshipAction::OnPlayerAsteroidCollision(const CollisionEventArgs& collisionEventArgs) const
{
	
}
//--------------------------------------------------------------------------------------
// Name: OnProjectileAsteroidCollision
// Desc: 
//--------------------------------------------------------------------------------------
void PlayerSpaceshipAction::OnProjectileAsteroidCollision(const CollisionEventArgs& collisionEventArgs) const
{
	
}

#include "Demos/SpaceGame/PlayerSpaceshipAction.h"
#include "Graphics/Color.h"
#include "Graphics/TextGraphicsResource.h"
#include "Physics/VelocityTask.h"

//-------------------------------------------------------------------------------------
// Name: SpaceShipProjectile
//-------------------------------------------------------------------------------------
class SpaceShipProjectile
{
public:
	SpaceShipProjectile(ComponentRepository* componentRepository, TransformComponent& playerTransform, unsigned int projectileGraphicResId)
	{
		auto entityId = componentRepository->GenerateId();

		// Create the collection if it doesn't exist
		if (!componentRepository->ContainsCollection("PlayerSpaceShipProjectiles")) {
			componentRepository->NewCollection("PlayerSpaceShipProjectiles");
		}

		auto transformComponent = componentRepository->NewComponent<TransformComponent>("PlayerSpaceShipProjectiles", entityId);
		auto graphicsComponent = componentRepository->NewComponent<GraphicsComponent>("PlayerSpaceShipProjectiles", entityId);
		auto physicsComponent = componentRepository->NewComponent<PhysicsComponent>("PlayerSpaceShipProjectiles", entityId);

		transformComponent->position = playerTransform.position;

		graphicsComponent->transformComponentId = transformComponent->id;
		physicsComponent->transformComponentId = transformComponent->id;

		graphicsComponent->resourceId = projectileGraphicResId;
		physicsComponent->velocity = Vector2D(0.0f, -8.0f);
		physicsComponent->radius = 1.0f;
	}
};

//-------------------------------------------------------------------------------------
// Name: PlayerSpaceshipAction
// Desc: 
//-------------------------------------------------------------------------------------
PlayerSpaceshipAction::PlayerSpaceshipAction(IStage* stage) : IAction(stage)
{
	auto graphics = stage->GetGameApp()->GetGraphics();
	auto componentRepository = this->GetParentStage()->GetComponentRepository(); 
	this->width = graphics->WindowWidth();
	this->height = graphics->WindowHeight();
	this->sdlEventCollector = new SDLEventCollector(this->width, this->height);

	this->health = 10; 
	this->moveCounter = 0;

	//
	// Resources
	//
	this->projectileGraphicResId = graphics->AddGraphicsResource(new RectGraphicsResource(2.0f, 12.0f, Color(Color::Red)));
	auto spaceShipGraphicResId = graphics->LoadGraphicResource("Resources//space_ship.png");

	//
	// Construct entities
	//
	SpaceGameEntityConstructor::ConstructPlayerSpaceShip(componentRepository, spaceShipGraphicResId, Vector2D(this->width / 2.0f, this->height - 60));

	this->healthBarGraphic = new RectGraphicsResource(100.0f, 10.0f, Color(Color::Green)); 
	auto healthBarId = graphics->AddGraphicsResource(healthBarGraphic);
	
	componentRepository->NewCollection("PlayerHealthBar"); 
	auto transformComponent = componentRepository->NewComponent<TransformComponent>("PlayerHealthBar");
	auto graphicsComponent = componentRepository->NewComponent<GraphicsComponent>("PlayerHealthBar");

	graphicsComponent->transformComponentId = transformComponent->id; 
	graphicsComponent->resourceId = healthBarId; 

	transformComponent->position.x = 20.0f;
	transformComponent->position.y = this->height - 20.0f; 
	transformComponent->orientation = Vector2D(0.0f); 

	//
	// Event Handlers
	//
	auto buttonEventHandler = [this] (const ButtonEventArgs& buttonEventArgs) { this->OnButtonEvent(buttonEventArgs); };
	auto asteroidCollisionHandler = [this] (const CollisionEventArgs& collisionEventArgs) {this->OnPlayerAsteroidCollision(collisionEventArgs); };

	this->sdlEventCollector->RegisterListener<ButtonEventArgs>(bind(buttonEventHandler, placeholders::_1));
	this->sdlEventCollector->RegisterListener<QuitApplicationEventArgs>(bind(&PlayerSpaceshipAction::OnQuitApplication, this, placeholders::_1));

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
	auto componentRepository = this->GetParentStage()->GetComponentRepository();
	auto playerPhysicsComponents = componentRepository->Select<PhysicsComponent>("PlayerSpaceShip");

	for (auto& physicsComponent : playerPhysicsComponents) {

		auto transformComponent = componentRepository->SelectId<TransformComponent>(physicsComponent.transformComponentId);

		if (transformComponent->position.y < (this->height - 60)) {
			physicsComponent.velocity.y = 1.0f;
		
		} else {
		
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

				default: 
					break;
			}
		} else {
			physicsComponent.velocity.x = 0.0f;
		}
	}
}

//-------------------------------------------------------------------------------------
// Name: FireWeapon
// Desc: 
//-------------------------------------------------------------------------------------
void PlayerSpaceshipAction::FireWeapon(const ButtonEventArgs buttonEventArgs) const
{
	auto componentRepository = this->GetParentStage()->GetComponentRepository(); 
	auto playerComponents = componentRepository->Select<TransformComponent>("PlayerSpaceShip"); 
	auto& playerTransform = playerComponents.front();

	if (!buttonEventArgs.Released()) {
		SpaceShipProjectile spaceShipProjectile(componentRepository, playerTransform, this->projectileGraphicResId); 
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
void PlayerSpaceshipAction::OnPlayerAsteroidCollision(const CollisionEventArgs& collisionEventArgs)
{
	if (this->health > 0) 
	{
		this->health--; 
	}
	else 
	{
		// game over!!!
	}
}
//--------------------------------------------------------------------------------------
// Name: OnProjectileAsteroidCollision
// Desc: 
//--------------------------------------------------------------------------------------
void PlayerSpaceshipAction::OnProjectileAsteroidCollision(const CollisionEventArgs& collisionEventArgs) const
{
}

# ct-ecs 
[![Build Status](https://github.com/gilmarxd/ct-ecs/workflows/CMake/badge.svg)](https://github.com/gilmarxd/ct-ecs/actions/workflows/cmake.yml)
[![Coverage](https://codecov.io/gh/gilmarxd/ct-ecs/branch/master/graph/badge.svg)](https://codecov.io/gh/gilmarxd/ct-ecs)
header-only compile-time entity component system library

## Concept
**Entity-Component-System (ECS)** is a **software architectural** pattern mostly used on video game development for the storage of game world objects. An **ECS** follows the **pattern** of "entities" with "components" of data.
An **ECS** follows the principle of **composition** over **inheritance**, meaning that every entity is defined not by a "type", but by the components that are associated with it. The design of how components relate to entities depend upon the Entity Component System being used.[[wiki](https://en.wikipedia.org/wiki/Entity_component_system)]

## Design
### Entities
In the **ct-ecs** each entity is represented by a set of components, the components are related to the entity by a natural number as an ID.
The ID doesn't represent the entity all the time, just in a system iteration, the concrete entity is made only of components, an entity could change her ID during the run-time in order to manage the memory alignment.
### Components
Components are structures with only one purpose, store the entity data, doesn't have logic. For each entity there's a component with de the same ID that represents the relation between them.
### Tags
Tags are "empty" structures that can be added to an entity, it's usefull to differentiate behaviours of entities in the systems.
### Systems
Systems in the ct-ecs are **CRTP** classes with the registered entities, the update method and are observers of others systems.
### Manager
The manager is the class that orchestrate everything, resize the capacity, run the systems, forward components and track the memory alignment
## Future features
 - finish the documentation
 - compile-time multithreading specification
 - change the observer pattern to publish-subscriber (it's a better pattern for multithreading)

## Usage
### Set up the settings
First, you'll need to create the basic design of your game, components, tags and systems:

```cpp
using ComponentList = std::tuple<TransformComponent, MeshComponent, RigidBodyComponent, MaterialComponent>;
using TagList = std::tuple<PlayerTag, EnemyTag, BulletTag>;
using SystemList = std::tuple<CollisionSystem, PhysicsSystem, RenderSystem, PlayerSystem, ShootSystem>;
```

### Components implementation
Since the first design is complete, start the implementation of the components, as the transform example:

```cpp
struct TransformComponent {
        glm::vec3 position = {0, 0, 0};
        glm::vec3 scale = {1, 1, 1};
        glm::vec3 rotation = {0, 0, 0};
};
```

### Systems foundation
After implementing the components, you could start implementing the systems, each system will have their signature, a
signature is a bitset that identifies which components the system will need to run, for example, the collision system will
need of the transform and rigid body components:

```cpp
class CollisionSystem : public BaseSystem<CollisionSystem> {
public:
    using Signature = std::tuple<TransformComponent, RigidBodyComponent>;
}
```
After defining the signature, all entities that have these components will be automatically registered to the system,
and to work on these entities is simple: just iterate over:
```cpp
class CollisionSystem : public BaseSystem<CollisionSystem> {
public:
    using Signature = std::tuple<TransformComponent, RigidBodyComponent>;
    
    CollisionSystem() = default;
    
    ~CollisionSystem() = default;
    
    template<typename Settings>
    void update(Manager<Settings>* manager) {
        for (EntityID entity : m_registered_entites) {
            // do collision detection
        }
    }
}
```

### Communication between systems
If a system depend on an event made by other system? for example the physics system depends on events of the collisions detected by the collision system.
In the ct-ecs you could communicate between systems with the observer pattern, the implementation is made in compile-time,
then you could define observers with a tuple in the CRTP like:
```cpp
class CollisionSystem : public BaseSystem<CollisionSystem, std::tuple<PhysicsSytem>>
```
Now in the collision system you could notify all observers that have the method **receive** with an specific event:
```cpp
struct CollisionEvent {
    EntityID entity;
    EntityID collider;
};
```
In the update method, when the collision is detected, just **notify** all observers
```cpp
class CollisionSystem : public BaseSystem<CollisionSystem, std::tuple<PhysicsSytem>> {
    template<typename Settings>
    void update(Manager<Settings>* manager) {
        // do collision calculations
        CollisionEvent collision_event = { entity, other}; 
        void notify(manager, collision_event);
    }
};
```
On the observer system, you could implement the **receive** method with the `CollisionEvent` and handle collisions inside the `PhysicsSystem`
```cpp
class PhysicsSytem : public BaseSystem<PhysicsSytem> {
    template<typename Settings>
    void receive(Manager<Settings>* manager, CollisionEvent event) {
        // do things to handle collisions
    }
};
```
### 
After the systems implementation you're able to complete the Manager Settings and could start running the game:

```cpp
using ComponentList = std::tuple<TransformComponent, MeshComponent, RigidBodyComponent, MaterialComponent>;
using TagList = std::tuple<PlayerTag, EnemyTag, BulletTag>;
using SystemList = std::tuple<CollisionSystem, PhysicsSystem, RenderSystem, PlayerSystem, ShootSystem>;
using Settings = ecs::Settings<ComponentList, TagList, SystemList>;
using ECSManager = ecs::Manager<Settings>;

ECSManager manager = ECSManager(<initial_size>);

manager.update();
```


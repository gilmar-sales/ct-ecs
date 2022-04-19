# ct-ecs
[![Build Status](https://github.com/gilmarxd/ct-ecs/workflows/CMake/badge.svg)](https://github.com/gilmarxd/ct-ecs/actions/workflows/cmake.yml)
[![Coverage](https://codecov.io/gh/gilmarxd/ct-ecs/branch/master/graph/badge.svg)](https://codecov.io/gh/gilmarxd/ct-ecs)
[![License](https://img.shields.io/github/license/gilmarxd/ct-ecs)]()
[![Repo Size](https://img.shields.io/github/repo-size/gilmarxd/ct-ecs)]()
[![Last Commit](https://img.shields.io/github/last-commit/gilmarxd/ct-ecs)]()

header-only compile-time entity component system library


## Concept
**Entity-Component-System (ECS)** is a **software architectural** pattern mostly used in real-time simulation software like video games, acting in the storage of game world objects. An **ECS** follows the **pattern** of "entities" with "components" of data.
An **ECS** follows the principle of **composition** over **inheritance**, meaning that every entity is defined not by a **class**, but by the **components** that are associated with it [[wiki](https://en.wikipedia.org/wiki/Entity_component_system)].
Components are structures that only store the entity data that serves to systems.
Systems processes the components, giving behaviour for the entities, and adding or removing components can change the systems that will work on an entity making the entity behaviour change in the run-time. 

### Pros
 - Data Oriented
   * Data tends to be stored linearly, optimizing the access to it
   * With contiguous data allocation the processor have less idle-times and works faster
 - Friendly to parallel-processing
   * Systems that don't depend on other systems can be processed in parallel 
   * By the way of the system is structured, many entities and components don't have conflicts and can be processed in parallel by two or more systems
 - Dynamic Behaviour
   * An entity can change its behaviour in run-time without recompiling
   * Just add or remove a component of an entity to change its behaviour

### Cons 
 - Overkill designing unique entities
   * If in your game have some unique creatures, some systems will be dedicated just for only one entity
 - More complex to implement and understand
   * Make your own ECS will require so much time for understand completely the architecture, and much more for the implementation and testing the trade-offs 
 - Aren't widely spread, most people don't know the pattern
   * Actually almost or none of academic institutes teaches this pattern
   * Mostly people interested in this pattern are self-taught and rarely spread their insights
   
### Relevant things to know
 - Entities are sets of components, in the most ecs design the entity is represented by an ID that make the relation with the components, but never forget, the entity is just a set of components.
 - Components only store the entity data, the entity behaviour is work for the systems
 - The design of how components relate to entities depend upon the Entity Component System being used.

## Design

### Entities
In the **ct-ecs** each entity is represented by a set of components, the components are related to the entity by a natural number as an ID.
The ID doesn't represent the entity all the time, just in a system iteration, the concrete entity is made only of components, an entity could change its ID during the run-time in order to manage the memory alignment.

### Components
Components are structures with only one purpose, store the entity data, doesn't have logic. In the **ct-ecs** the components are store in arrays of structures (AoS) with the same size of the entities count and for each entity there's a component with de the same ID that represents the relation between them.

### Tags
Tags are "empty" structures that can be added to an entity, they're usefull to differentiate behaviours of entities in the systems.

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
After defining the system signature, all entities that have these components will be automatically registered to the system by the `Manager`,
and to work on these entities is simple: just iterate over
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
If a system depend on an event made by other system? for example the physics system depend on events of the collisions detected by the collision system.
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
        for (EntityID entity : m_registered_entites) {
            // ...do collision detection
            CollisionEvent collision_event = { entity, other}; 
            notify(manager, collision_event);
            // ...
        }
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
If an observer doesn't implement that method, the empty function **receive** of the `BaseSystem` class will be called, compiling this code on the -O3 flag for optimization, the compiler ignores all functions with empty body preserving the system of useless function calls.
### 
After the systems implementation you're able to complete the Manager Settings and could start running the game:
```cpp
using ComponentList = std::tuple<TransformComponent, MeshComponent, RigidBodyComponent, MaterialComponent>;
using TagList = std::tuple<PlayerTag, EnemyTag, BulletTag>;
using SystemList = std::tuple<CollisionSystem, PhysicsSystem, RenderSystem, PlayerSystem, ShootSystem>;
using Settings = ecs::Settings<ComponentList, TagList, SystemList>;
using ECSManager = ecs::Manager<Settings>;

ECSManager manager = ECSManager(<initial_size>);

// can be inside the game loop update method
manager.update();
```


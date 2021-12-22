# ct-ecs
header-only compile-time entity component system library

## Concept
**Entity-Component-System (ECS)** is a **software architectural** pattern mostly used on video game development for the storage of game world objects. An **ECS** follows the **pattern** of "entities" with "components" of data.
An **ECS** follows the principle of **composition** over **inheritance**, meaning that every entity is defined not by a "type", but by the components that are associated with it. The design of how components relate to entities depend upon the Entity Component System being used.[[wiki](https://en.wikipedia.org/wiki/Entity_component_system)]

## Design
### Entities
In the **ct-ecs** each entity is represented by a natural number as an ID.
### Components
Components are structures with only one purpose, store the entity data, doesn't have logic. For each entity there's a component with de the same ID that represents the relation between them.
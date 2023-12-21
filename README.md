# Bulb
CA3 for C++ by Anthony O'Keeffe (20093999)

## Trello Link
https://trello.com/b/lFrbW7cX/bulb-trello-board

## GDD Link
https://wit-my.sharepoint.com/:b:/g/personal/20093999_wit_ie/ESV2pIpd9zJPupbO5z2EDn0BiHqjegKfN_7hQMi7n_XMXw?e=vYEgfT

## Youtube Demo Link
https://youtu.be/49emRFfWzq8

## Installation

### Download Repo
If starting on a new computer or redownloading the repo from scratch and lib/sfml and/or lib/b2d is empty. Open git bash shell in drop-pod-game directory and run command:

git submodule update --init --recursive

This will download the submodules for the project.
To check if that has worked correctly run command:

git submodule status

Results should show:

Then compile with CMake. This will show an error for developers just ignore.

CMake Warning (dev) at C:/Program Files/CMake/share/cmake-3.22/Modules/FindPackageHandleStandardArgs.cmake:438 (message):
  The package name passed to `find_package_handle_standard_args` (VORBIS)
  does not match the name of the calling package (Vorbis).  This can lead to
  problems in calling code that expects `find_package` result variables
  (e.g., `_FOUND`) to follow a certain pattern.
Call Stack (most recent call first):
  lib/sfml/cmake/Modules/FindVorbis.cmake:25 (find_package_handle_standard_args)
  lib/sfml/cmake/Macros.cmake:279 (find_package)
  lib/sfml/src/SFML/Audio/CMakeLists.txt:70 (sfml_find_package)
This warning is for project developers.  Use -Wno-dev to suppress it.

IGNORE THIS IT SHOULD STILL COMPILE.

## Technical Documentation

### Dependencies
Before diving into the technical details, it's essential to ensure that the required dependencies are installed on your system. Bulb relies on the following libraries:

- SFML (Simple and Fast Multimedia Library)
- Box2D (Physics engine)

Please refer to the documentation of these libraries for installation instructions.

### Custom Components 

#### cmp_light

The LightComponent in Bulb manages in-game lights, contributing to simulated light mechanics. Key features include dynamic size changes, collision detection with the player, and integration with physics and rendering systems.

##### Implementation Highlights
- Constructor: Initializes the component with parameters, creating a yellow, transparent circle representing the light.

- Update Method: Controls pulsating light size and manages player-light interactions.

- isColliding Method: Determines if the light collides with a specified entity, crucial for player interaction.

##### Usage
###### Include Headers:

``````
#include "cmp_light.h"
#include "system_renderer.h"
#include "system_physics.h"
// ... other includes
``````
- Instantiate Light Components:

``````
auto lightEntity = EntityManager::get().addEntity();
auto lightComponent = lightEntity->addComponent<LightComponent>(lightEntity.get(), sf::Vector2f(20.f, 20.f), playerEntity, 1);
``````

###### Compile and Run:
Configure the project to compile the LightComponent and run the game to observe dynamic light behavior.


#### cmp_path_follow
The PathComponent in Bulb facilitates path-following behavior for entities, enabling them to traverse a predefined path. Key features include smooth movement along the path, dynamic direction adjustments, and support for reverse mode.

##### Implementation Highlights
Constructor: Initializes the component with a path, speed, and a follower entity. Places the follower at the first point on the path.

- Update Method: Manages the continuous movement of the follower along the path. Adjusts direction, detects target reach, and supports reverse mode for continuous traversal.

##### Usage
###### Include Headers:
``````
#include "cmp_path_follow.h"
#include "cmp_physics.h"
#include "cmp_sprite.h"
// ... other includes
``````
###### Instantiate Path Components:
``````
auto pathEntity = EntityManager::get().addEntity();
auto pathComponent = pathEntity->addComponent<PathComponent>(pathEntity.get(), pathVector, speedValue, followerEntity);
``````
###### Compile and Run:
Configure the project to compile the PathComponent and run the game to observe entities smoothly following predefined paths.

#### cmp_bullet
The ShootingComponent and Bullet classes in Bulb manage the firing and behavior of in-game bullets. Key features include bullet initialization, dynamic updating, rendering, and firing based on player input.

##### Implementation Highlights
###### ShootingComponent:

- Constructor: Initializes the shooting component.
- update Method: Updates the bullet system.
- render Method: Renders bullets on screen.
- Fire Method: Initiates the firing sequence.
###### Bullet:

- init Method: Initializes bullet properties and loads textures.
- setAngle Method: Sets the firing angle of a bullet with a slight variance.
- update Method: Updates bullet positions and animation.
- render Method: Renders visible bullets on the screen.
- fire Method: Fires a bullet from the player's position toward the mouse cursor.
- _update Method: Manages the continuous movement of bullets, ensuring visibility and boundaries.
##### Usage
###### Include Headers:
``````
#include "cmp_bullet.h"
#include "cmp_physics.h"
#include "cmp_sprite.h"
#include "system_resources.h"
#include "system_renderer.h"
#include <LevelSystem.h>
#include <engine.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <math.h>
``````
###### Instantiate Bullet Components:
``````
auto bulletEntity = EntityManager::get().addEntity();
auto bulletComponent = bulletEntity->addComponent<ShootingComponent>(bulletEntity.get());
``````
###### Compile and Run:
Configure the project to compile the ShootingComponent and Bullet classes. Run the game to observe dynamic bullet firing and movement.

##### Additional Notes
- Bullets are managed in a pool of 256 instances.
- Bullet firing and movement are influenced by player input and mouse position.
- Developers can customize bullet properties, such as appearance and speed, for varied gameplay experiences.

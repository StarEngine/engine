StarEngine: 2D Game Engine
==========

_Note:_ This project has been abandonned.

StarEngine is a Game Engine to develop 2D Games fast and easy. It is written in C++11, but also allows you to write your games in C and ChaiScript. The goal is to allow very fast development, which is often needed in prototyping. Thanks to the many embedded opensource libraries we can provide you with all the features you might need. Keep in mind that we aim for a miniamlistic and compact game engine.

You can find more information at [our wiki](https://github.com/StarEngine/engine/wiki).

The current version number and patch notes for this patch and the previous versions can be found [here](https://github.com/StarEngine/engine/wiki/Patchnotes).

## Index
1. [Features](#features)
2. [Bootstrap](#bootstrap)
3. [Examples](#examples)
4. [Further documentation](#further-documentation)
5. [Project organization](#project-organization)
6. [Continuous Integration status](#continuous-integration-status)
7. [Legal notices](#legal-notices)

## Features

  * Deploy games on Windows, Linux and Android
  * Develop quick prototypes or advanced 2D Games
  * A component system to boost code reusability and improve code organisation
  * State of the art 2D physics thanks to [Box2D](http://box2d.org/) intgration
  * Crossplatform input support via [SDL2](http://www.libsdl.org/)
  * Support for several Graphic APIS, giving you te freedom to choose 
  * Better code organisation via scenes and objects
  * Support for unit testing via [Catch](https://github.com/philsquared/Catch), which is also used for the engine code
  * Develop games in C++(11), C, Go and Chaiscript
  * Replay System for input and time intervals
  * Multithreading support to keep your games performant
  * Garbage Collection system to manage your memory
  * Boost integration for containers and other small things
  * Quick and compact way to serialize your game data via Google's [protobuf](https://code.google.com/p/protobuf/)
  * Application: Generate an empty game project or start from a template
  * [Premake](http://industriousone.com/premake) integration to generate projects and compile your game easy and fast

## Examples

_The engine is still in the alpha base, come back later when the engine reaches a beta stage. At that point we'll have several example applications and a big interactive tutorial to help you getting started!_

## Further Documentation

The documentation of our engine is generated via [Doxygen](http://www.stack.nl/~dimitri/doxygen/). You can download the latest documentation our the StarEngine [here](#todo) (_comming soon_). You can also read our documentation in the header files of the engine code that allows you to write your game once, and deploy it on several desktop and mobile platforms.

## Project Organization

This project is the successor of an engine made as a University project. The main developers and maintainers of the StarEngine are Cedric Van de Walle, Glen De Cauwsemaecker and Pieter Vantorre.

We would love to hear your feedback and suggestions, which you can post as an issue, next to the bug reports. Please read [our contribution guide](https://github.com/StarEngine/engine/wiki/contributor-guide) in case you would like to help in the development or file bugs.

## Continuous Integration status

This project is tested with [Travis CI](http://travis-ci.org/). [![Build Status](https://travis-ci.org/StarEngine/engine.svg?branch=develop)](https://travis-ci.org/StarEngine/engine)

## Legal notices
The Star 2D Game Engine is licensed under the MIT License.
[Click here for the full license details](https://github.com/StarEngine/engine/blob/develop/LICENSE).

When using our engine, you are not obligated to give our credits, although it is appriciated. We also provide introductary ingame Flash menus for our engine that you can use, to show how proud you are at using the StarEngine.

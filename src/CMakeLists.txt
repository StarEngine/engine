# StarEngine static library
# -------------------------

# --- Collect source files ---

# Core engine sources
set(STARENGINE_CORE_SOURCES
    StarEngine.cpp
    definesCrossPlatform.cpp
    Entity.cpp
    EventLoop.cpp
    Logger.cpp
    TimeManager.cpp
)

# Console is Windows-only (uses WinAPI)
if(WIN32)
    list(APPEND STARENGINE_CORE_SOURCES Console.cpp)
endif()

# Actions
set(STARENGINE_ACTIONS_SOURCES
    Actions/Action.cpp
    Actions/DelayedAction.cpp
    Actions/DelayedFramesAction.cpp
    Actions/LoopedAction.cpp
    Actions/ScaleAction.cpp
    Actions/TimedAction.cpp
    Actions/TimedFadeAction.cpp
    Actions/TimedMoveAction.cpp
    Actions/TimedScaleAction.cpp
)

# AI
set(STARENGINE_AI_SOURCES
    AI/Pathfinding/PathFindManager.cpp
    AI/Pathfinding/SearchCell.cpp
)

# Components
set(STARENGINE_COMPONENTS_SOURCES
    Components/BaseComponent.cpp
    Components/CameraComponent.cpp
    Components/TransformComponent.cpp
    Components/AI/PathFindNodeComponent.cpp
    Components/Graphics/SpriteComponent.cpp
    Components/Graphics/SpritesheetComponent.cpp
    Components/Graphics/TextComponent.cpp
    Components/Physics/BaseColliderComponent.cpp
    Components/Physics/CircleColliderComponent.cpp
    Components/Physics/RectangleColliderComponent.cpp
)

# Graphics
set(STARENGINE_GRAPHICS_SOURCES
    Graphics/Color.cpp
    Graphics/Font.cpp
    Graphics/FontManager.cpp
    Graphics/GraphicsManager.cpp
    Graphics/ScaleSystem.cpp
    Graphics/Shader.cpp
    Graphics/SpriteAnimationManager.cpp
    Graphics/SpriteBatch.cpp
    Graphics/Texture2D.cpp
    Graphics/TextureManager.cpp
)

# Resource.cpp is Android-only (AAsset)
if(ANDROID)
    list(APPEND STARENGINE_GRAPHICS_SOURCES Graphics/Resource.cpp)
endif()

# Graphics UI
set(STARENGINE_UI_SOURCES
    Graphics/UI/UIAnimatedButton.cpp
    Graphics/UI/UIAnimatedImage.cpp
    Graphics/UI/UIAnimatedTextButton.cpp
    Graphics/UI/UIBaseCursor.cpp
    Graphics/UI/UIButton.cpp
    Graphics/UI/UICursor.cpp
    Graphics/UI/UIDock.cpp
    Graphics/UI/UIImage.cpp
    Graphics/UI/UIObject.cpp
    Graphics/UI/UISimpleTextButton.cpp
    Graphics/UI/UISlider.cpp
    Graphics/UI/UIStaticButton.cpp
    Graphics/UI/UIStaticTextButton.cpp
    Graphics/UI/UITextButton.cpp
    Graphics/UI/UITextField.cpp
    Graphics/UI/UIUserElement.cpp
)

# Helpers
set(STARENGINE_HELPERS_SOURCES
    Helpers/AARect.cpp
    Helpers/Debug/DebugDraw.cpp
    Helpers/Filepath.cpp
    Helpers/FPS.cpp
    Helpers/GameData.cpp
    Helpers/HashTag.cpp
    Helpers/Helpers.cpp
    Helpers/HelpersCrossplatform.cpp
    Helpers/Math.cpp
    Helpers/Rect.cpp
    Helpers/SerializedData.cpp
    Helpers/SpriteAnimation.cpp
    Helpers/Spritesheet.cpp
    Helpers/State.cpp
    Helpers/StateManager.cpp
    Helpers/Stopwatch.cpp
    Helpers/Time.cpp
    Helpers/Timer.cpp
    Helpers/TimerManager.cpp
    Helpers/2D/pos.cpp
)

# Input
set(STARENGINE_INPUT_SOURCES
    Input/InputManager.cpp
    Input/XMLContainer.cpp
    Input/XMLFileParser.cpp
    Input/XMLFileSerializer.cpp
    Input/Gestures/BaseGesture.cpp
    Input/Gestures/DoubleTapGesture.cpp
    Input/Gestures/GestureManager.cpp
    Input/Gestures/SwipeGesture.cpp
    Input/Gestures/TapGesture.cpp
)

# Objects
set(STARENGINE_OBJECTS_SOURCES
    Objects/BaseCamera.cpp
    Objects/FreeCamera.cpp
    Objects/Object.cpp
)

# Physics
set(STARENGINE_PHYSICS_SOURCES
    Physics/Collision/CollisionManager.cpp
)

# Scenes
set(STARENGINE_SCENES_SOURCES
    Scenes/BaseScene.cpp
    Scenes/SceneManager.cpp
    Scenes/SlideScene.cpp
    Scenes/SplashScreen.cpp
    Scenes/TiledScene.cpp
)

# Sound
set(STARENGINE_SOUND_SOURCES
    Sound/AudioManager.cpp
    Sound/BaseSound.cpp
    Sound/SoundEffect.cpp
    Sound/SoundFile.cpp
)

# Bundled third-party (PugiXML)
set(STARENGINE_THIRDPARTY_SOURCES
    Input/PugiXML/src/pugixml.cpp
)

# --- Platform-specific sources ---

if(WIN32)
    set(STARENGINE_PLATFORM_SOURCES
        Platforms/Windows/Window.cpp
        Helpers/glm/core/dummy.cpp
    )
elseif(ANDROID)
    set(STARENGINE_PLATFORM_SOURCES
        Helpers/HelpersAndroid.cpp
        Helpers/glm/core/dummy.cpp
    )
else()
    # Linux / other Unix
    set(STARENGINE_PLATFORM_SOURCES
        Helpers/glm/core/dummy.cpp
    )
endif()

# --- Combine all sources ---
set(STARENGINE_ALL_SOURCES
    ${STARENGINE_CORE_SOURCES}
    ${STARENGINE_ACTIONS_SOURCES}
    ${STARENGINE_AI_SOURCES}
    ${STARENGINE_COMPONENTS_SOURCES}
    ${STARENGINE_GRAPHICS_SOURCES}
    ${STARENGINE_UI_SOURCES}
    ${STARENGINE_HELPERS_SOURCES}
    ${STARENGINE_INPUT_SOURCES}
    ${STARENGINE_OBJECTS_SOURCES}
    ${STARENGINE_PHYSICS_SOURCES}
    ${STARENGINE_SCENES_SOURCES}
    ${STARENGINE_SOUND_SOURCES}
    ${STARENGINE_THIRDPARTY_SOURCES}
    ${STARENGINE_PLATFORM_SOURCES}
)

# --- Create the static library ---
add_library(starengine STATIC ${STARENGINE_ALL_SOURCES})

# --- Include directories ---
target_include_directories(starengine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Helpers/glm>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Input/PugiXML/src>
)

# --- Compile definitions ---

# Platform defines
if(WIN32)
    target_compile_definitions(starengine PUBLIC DESKTOP)
elseif(ANDROID)
    target_compile_definitions(starengine PUBLIC MOBILE)
else()
    # Linux: treat as desktop platform
    target_compile_definitions(starengine PUBLIC DESKTOP)
endif()

# Feature defines
if(STAR2D)
    target_compile_definitions(starengine PUBLIC STAR2D=1)
endif()

target_compile_definitions(starengine PUBLIC LOGGER_MIN_LEVEL=1)

# --- Find and link dependencies ---

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(starengine PUBLIC OpenGL::GL)

# GLEW (desktop only)
if(NOT ANDROID)
    find_package(GLEW REQUIRED)
    target_link_libraries(starengine PUBLIC GLEW::GLEW)
endif()

# SDL2
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
target_link_libraries(starengine PUBLIC PkgConfig::SDL2)

# SDL2_mixer
pkg_check_modules(SDL2_MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)
target_link_libraries(starengine PUBLIC PkgConfig::SDL2_MIXER)

# Freetype
find_package(Freetype REQUIRED)
target_link_libraries(starengine PUBLIC Freetype::Freetype)

# PNG
find_package(PNG REQUIRED)
target_link_libraries(starengine PUBLIC PNG::PNG)

# --- Compiler warnings and features ---
target_compile_features(starengine PUBLIC cxx_std_11)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(starengine PRIVATE
        -Wall
        -Wextra
        -Wno-unused-parameter
        -Wno-reorder
        -fexceptions
        -frtti
    )
endif()

if(MSVC)
    target_compile_options(starengine PRIVATE /W3 /EHsc)
endif()

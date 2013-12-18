#pragma once

#include "SpriteComponent.h"
#include <list>
#include "../../Helpers/SpriteAnimation.h"
#include "../../Helpers/SpriteSheet.h"

namespace star
{
	/// <summary>
	/// Graphics component used to draw animated sprites. 
	/// Sprite animations can be defined in an xml file
	/// and are parsed by the <see cref="SpriteSheet"/>
	/// </summary>
	class SpriteSheetComponent final : public SpriteComponent
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="SpriteSheetComponent"/>
		/// </summary>
		/// <param name="filePath">
		/// Path to the asset, starting from the path 
		/// defined in <see cref="DirectoryMode::assets"/>.</param>
		/// <param name="spriteName">Name of the sprite.</param>
		/// <param name="spritesheet">Name of the spritesheet.</param>
		/// <returns></returns>
		SpriteSheetComponent(const tstring& filePath, const tstring& spriteName, const tstring & spritesheet);

		/// <summary>
		/// Finalizes an instance of the <see cref="SpriteSheetComponent"/> class.
		/// </summary>
		~SpriteSheetComponent();

		/// <summary>
		/// Updates this instance.
		/// </summary>
		/// <param name="context"><see cref="Context"/> containing usefull information.</param>
		void Update(const Context& context);

		/// <summary>
		/// Plays the current animation.
		/// </summary>
		void Play();

		/// <summary>
		/// Restarts the current animation.
		/// </summary>
		void Restart();

		/// <summary>
		/// Pauses the current animation.
		/// </summary>
		void Pause();

		/// <summary>
		/// Stops the current animation.
		/// </summary>
		void Stop();

		/// <summary>
		/// Queues an animation into the play list.
		/// </summary>
		/// <param name="animation">Animation name, as defined in the SpriteSheet.</param>
		/// <param name="callback">
		/// An optional user defined callback, 
		/// called when this animation is completed.
		/// </param>
		void PushAnimation(
			const tstring & animation,
			const std::function<void()> & callback = nullptr
			);

		/// <summary>
		/// Plays the animation.
		/// </summary>
		/// <param name="animation">Animation name, as defined in the SpriteSheet.</param>
		/// <param name="callback">
		/// An optional user defined callback, 
		/// called when this animation is completed.
		/// </param>
		void PlayAnimation(
			const tstring & animation,
			const std::function<void()> & callback = nullptr
			);

		/// <summary>
		/// Plays the animation.
		/// </summary>
		/// <param name="animation">Animation name, as defined in the SpriteSheet.</param>
		/// <param name="startFrame">The start frame.</param>
		/// <param name="callback">
		/// A user defined callback, 
		/// called when this animation is completed. 
		/// Default the callback is empty
		/// </param>
		void PlayAnimation(
			const tstring & animation,
			int32 startFrame,
			const std::function<void()> & callback = nullptr
			);

		/// <summary>
		/// Plays the next animation in the queue.
		/// </summary>
		void PlayNextAnimation();

		/// <summary>
		/// Plays the next animation in the queue, starting from startFrame.
		/// </summary>
		/// <param name="startFrame">The start frame.</param>
		void PlayNextAnimation(int32 startFrame);

		/// <summary>
		/// Resets The animation queue
		/// </summary>
		void Reset();

		/// <summary>
		/// Sets the spritesheet.
		/// </summary>
		/// <param name="spritesheet">The spritesheet.</param>
		void SetSpritesheet(const tstring & spritesheet);

		/// <summary>
		/// Gets the current animation.
		/// </summary>
		/// <returns>Name of the current animation.</returns>
		const tstring & GetCurrentAnimation() const;

		/// <summary>
		/// Gets the current spritesheet.
		/// </summary>
		/// <returns>The current spritesheet.</returns>
		const tstring & GetCurrentSpritesheet() const;

		/// <summary>
		/// Gets the current frame.
		/// </summary>
		/// <returns>The current frame.</returns>
		int32 GetCurrentFrame() const;

		/// <summary>
		/// Gets the amount of horizontal frames.
		/// </summary>
		/// <returns>The number of frames.</returns>
		int32 GetFramesHorizontal() const;

		/// <summary>
		/// Gets the amount of vertical frames.
		/// </summary>
		/// <returns>The number of frames.</returns>
		int32 GetFramesVertical() const;

		/// <summary>
		/// Sets the callback for all animations in the queue. 
		/// The callback will be triggered when the animation ends.
		/// </summary>
		/// <param name="callback">The callback.</param>
		void SetCallbackAnimations(const std::function<void()> & callback);

		/// <summary>
		/// Determines whether an animation is playing.
		/// </summary>
		/// <returns>True if an animation is playing.</returns>
		bool IsPlaying();

	protected:
		void InitializeComponent();
		tstring m_SpritesheetName;
		SpriteSheet m_Spritesheet;

		std::list<SpriteAnimation> m_Animations;

	private:

		/// <summary>
		/// Queues an animation into the play list.
		/// This method has no safety checks.
		/// </summary>
		/// <param name="animation">Animation name, as defined in the SpriteSheet.</param>
		/// <param name="callback">
		///	A user defined callback, 
		/// called when this animation is completed. 
		/// Default the callback is empty
		/// </param>
		void PushAnimationUnSafe(
			const tstring & animation,
			const std::function<void()> & callback = nullptr
			);

		/// <summary>
		/// Plays the animation.
		/// This method has no safety checks.
		/// </summary>
		/// <param name="animation">Animation name, as defined in the SpriteSheet.</param>
		/// <param name="callback">
		/// A user defined callback, 
		/// called when this animation is completed. 
		/// Default the callback is empty
		/// </param>
		void PlayAnimationUnSafe(
			const tstring & animation,
			const std::function<void()> & callback = nullptr
			);

		/// <summary>
		/// Plays the animation.
		/// This method has no safety checks.
		/// </summary>
		/// <param name="animation">Animation name, as defined in the SpriteSheet.</param>
		/// <param name="startFrame">The start frame.</param>
		/// <param name="callback">
		/// A user defined callback, 
		/// called when this animation is completed. 
		/// Default the callback is empty
		/// </param>
		void PlayAnimationUnSafe(
			const tstring & animation,
			int32 startFrame,
			const std::function<void()> & callback = nullptr
			);

		SpriteSheetComponent(const SpriteSheetComponent &);
		SpriteSheetComponent(SpriteSheetComponent &&);
		SpriteSheetComponent& operator=(const SpriteSheetComponent &);
		SpriteSheetComponent& operator=(SpriteSheetComponent &&);
	};
}

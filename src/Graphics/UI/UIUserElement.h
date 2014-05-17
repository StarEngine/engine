#pragma once
#include "UIObject.h"
#include <functional>

namespace star
{
	class UIUserElement : public UIObject
	{
	public:
		enum class ElementStates : byte
		{
			IDLE = 0,
			HOVER = 1,
			CLICK = 2,
			DISABLED = 3,
			LOCKED = 4
		};

		UIUserElement(const tstring & name);
		virtual ~UIUserElement();

		virtual void Reset();

		void SetReleasedCallback(std::function<void()> callback);
		void SetDownCallback(std::function<void()> callback);

		void SetHoverCallback(std::function<void()> callback);
		void SetUnhoverCallback(std::function<void()> callback);

		bool IsIdle() const;
		bool IsHover() const;
		bool IsDown() const;

		void SetLocked(bool locked);
		void SetUIDisabled(bool disable);

		void SetHoverSoundEffect(const tstring & name);
		void SetHoverSoundEffect(const tstring & name, float32 volume);

		void SetClickSoundEffect(const tstring & name);
		void SetClickSoundEffect(const tstring & name, float32 volume);

	protected:
		struct EffectInfo
		{
			tstring name;
			float32 volume;
		};

		virtual void Update(const Context& context);

		virtual void GoIdle();
#ifdef DESKTOP
		virtual void GoHover();
#endif
		virtual void GoDown();
		virtual void GoUp();
		virtual void GoDisable();

		bool IsFingerWithinRange() const;

		std::function<void()>
			m_ReleasedCallback;
		std::function<void()>
			m_DownCallback;
		std::function<void()>
			m_HoverCallback,
			m_UnhoverCallback;

		ElementStates m_ElementState;

		EffectInfo m_Effects[2];

	private:
		static const uint8 HOVER_EFFECT = 0;
		static const uint8 CLICK_EFFECT = 1;

		UIUserElement(const UIUserElement &);
		UIUserElement(UIUserElement &&);
		UIUserElement & operator=(const UIUserElement &);
		UIUserElement & operator=(UIUserElement &&);
	};
}

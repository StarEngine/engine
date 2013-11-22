#pragma once
#include "../../defines.h"
#include "../../Context.h"
#include "../../Objects/Object.h"

namespace star
{
	enum class HorizontalAlignment : byte
	{
		Left = 0,
		Center,
		Right
	};

	enum class VerticalAlignment : byte
	{
		Bottom = 0,
		Center,
		Top
	};

	class UIDock;

	class UIObject : public Object
	{
	public:
		UIObject(const tstring & name);
		virtual ~UIObject();

		virtual void Initialize();
		
		void Translate(const vec2& translation);
		void Translate(float32 x, float32 y);
		void Translate(const vec2& translation, lay l);
		void Translate(float32 x, float32 y, lay l);
		void Translate(const pos & pos2D);
		void TranslateX(float32 x);
		void TranslateY(float32 y);
		void TranslateL(lay l);

		void SetUIDock(UIDock * pDock);
		UIDock * GetUIDock() const;

		virtual void SetHorizontalAlignment(HorizontalAlignment alignment);
		virtual void SetVerticalAlignment(VerticalAlignment alignment);

		void SetAlignmentCentered();

		virtual void Reset();

	protected:
		virtual void Update(const Context& context);
		virtual void Draw();

		UIDock * GetRootDock() const;

		vec2 GetDockDimensions() const;

		void UITranslate();
		void UITranslateX(float32 x, const vec2 & dimensions);
		void UITranslateY(float32 y, const vec2 & dimensions);

		pos m_Position;
		HorizontalAlignment m_HorizontalAlignment;
		VerticalAlignment m_VerticalAlignment;

		UIDock *m_pDock;

	private:
		UIObject(const UIObject &);
		UIObject(UIObject &&);
		UIObject & operator=(const UIObject &);
		UIObject & operator=(UIObject &&);
	};
}

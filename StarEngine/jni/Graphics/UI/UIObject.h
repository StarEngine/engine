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
		virtual void AfterInitialized();
		
		void Translate(const vec2& translation);
		void Translate(float32 x, float32 y);
		void Translate(const vec2& translation, lay l);
		void Translate(float32 x, float32 y, lay l);
		void Translate(const pos & pos2D);
		void TranslateX(float32 x);
		void TranslateY(float32 y);
		void TranslateL(lay l);

		void SetUIParent(UIObject * pParent);
		UIObject * GetUIParent() const;

		const pos & GetPosition() const;

		virtual void SetHorizontalAlignment(
			HorizontalAlignment alignment,
			bool redefineCenter = true
			);
		virtual void SetVerticalAlignment(
			VerticalAlignment alignment,
			bool redefineCenter = true
			);

		void SetAlignmentCentered(bool redefineCenter = true);

		virtual void Reset();
		void Reposition();
		
		virtual void AddChild(Object* pObject);

		void SetUIDisabledChildren(bool disable);

		void SetDebugDrawColor(const Color& color);
		const Color& GetDebugDrawColor() const;

		void SetDebugDrawStyle(bool filled);
		bool GetDebugDrawStyle() const;

		void SetCanDebugDraw(bool canDraw);
		bool GetCanDebugDraw() const;


	protected:
		static uint64 UNIQUE_ID_COUNTER;

		virtual void Update(const Context& context);
		virtual void Draw();

		virtual vec2 GetDimensions() const;

		UIObject * GetRootParent() const;

		vec2 GetDockDimensions() const;

		void UITranslate();
		void UITranslateX(float32 x, const vec2 & dimensions);
		void UITranslateY(float32 y, const vec2 & dimensions);

		void RepositionChildren();

		pos m_Position;
		HorizontalAlignment m_HorizontalAlignment;
		VerticalAlignment m_VerticalAlignment;
		const tstring m_UniqueUIObjectID;

		UIObject *m_pParent;

	private:
		void DebugDraw();

		Color m_DebugDrawColor;
		bool m_bDebugDrawFilled;
		bool m_bCanDebugDraw;

		UIObject(const UIObject &);
		UIObject(UIObject &&);
		UIObject & operator=(const UIObject &);
		UIObject & operator=(UIObject &&);
	};
}

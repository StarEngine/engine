#pragma once
#include "../../defines.h"
#include "../../Context.h"
#include "../../Objects/Object.h"

namespace star
{
	class UIDock : public Object
	{
	public:
		UIDock(void);
		virtual ~UIDock(void);

		virtual void Initialize();

	protected:
		virtual void BaseUpdate(const Context& context);
		virtual void BaseDraw();

		vec2 m_ScreenScale;

	private:
		UIDock(const UIDock &);
		UIDock(UIDock &&);
		UIDock & operator=(const UIDock &);
	};
}

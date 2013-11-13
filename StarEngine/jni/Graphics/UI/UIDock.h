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
		virtual void Update(const Context& context);
		virtual void Draw();

	private:
		UIDock(const UIDock &);
		UIDock(UIDock &&);
		UIDock & operator=(const UIDock &);
		UIDock & operator=(UIDock &&);
	};
}

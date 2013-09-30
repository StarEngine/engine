#include "Dictionary.h"

namespace star
{
	template < typename TKey, typename TValue >
	void swap( Dictionary<TKey, TValue>& lhs,
		Dictionary<TKey, TValue>& rhs)
	{
		std::swap(lhs.m_MultiMap, rhs.m_MultiMap);
	}

	template < typename TKey, typename TValue >
	bool operator== ( Dictionary<TKey, TValue>& lhs,
		Dictionary<TKey, TValue>& rhs)
	{
		return (lhs.m_MultiMap == rhs.m_MultiMap);
	}

	template < typename TKey, typename TValue >
	bool operator!= ( Dictionary<TKey, TValue>& lhs,
		Dictionary<TKey, TValue>& rhs)
	{
		return (lhs.m_MultiMap != rhs.m_MultiMap);
	}
}

#include "Dictionary.h"

namespace star
{
	template < typename TKey, typename TValue >
	Dictionary<TKey, TValue>::Dictionary()
		: m_MultiMap()
	{

	}

	template < typename TKey, typename TValue >
	Dictionary<TKey, TValue>::Dictionary(const Dictionary & yRef)
		: m_MultiMap(yRef.m_MultiMap)
	{

	}

	template < typename TKey, typename TValue >
	Dictionary<TKey, TValue>::Dictionary(Dictionary && yRef)
		: m_MultiMap(yRef.m_MultiMap)
	{

	}

	template < typename TKey, typename TValue >
	Dictionary<TKey, TValue>::Dictionary(iterator begin, iterator end)
		: m_MultiMap(begin, end)
	{

	}

	template < typename TKey, typename TValue >
	Dictionary<TKey, TValue>::~Dictionary()
	{
		clear();
	}

	template < typename TKey, typename TValue >
	Dictionary<TKey, TValue> & Dictionary<TKey, TValue>::operator=(const Dictionary<TKey, TValue>& yRef)
	{
		m_MultiMap = yRef.m_MultiMap;
	}

	template < typename TKey, typename TValue >
	TValue & Dictionary<TKey, TValue>::operator[](const TKey & key)
	{
		return at(ki_pair(key, 0));
	}

	template < typename TKey, typename TValue >
	TValue & Dictionary<TKey, TValue>::operator[]
		(const typename Dictionary<TKey, TValue>::dki_pair & ki_pair)
	{
		return at(ki_pair);
	}

	template < typename TKey, typename TValue >
	TValue & Dictionary<TKey, TValue>::at(const TKey & key)
	{
		return at(ki_pair(key, 0));
	}

	template < typename TKey, typename TValue >
	TValue & Dictionary<TKey, TValue>::at
		(const typename typename Dictionary<TKey, TValue>::dki_pair & ki_pair)
	{
		auto range = m_MultiMap.equal_range(ki_pair.first);
		return (range.first + ki_pair.second)->second;
	}

	template < typename TKey, typename TValue >
	TValue & Dictionary<TKey, TValue>::at(const TKey & key, size_type index)
	{
		return at(ki_pair(key, index));
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator Dictionary<TKey, TValue>::begin()
	{
		return m_MultiMap.begin();
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator Dictionary<TKey, TValue>::end()
	{
		return m_MultiMap.end();
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::const_interator Dictionary<TKey, TValue>::cbegin() const
	{
		return m_MultiMap.cbegin();
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::const_interator Dictionary<TKey, TValue>::cend() const
	{
		return m_MultiMap.cend();
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator Dictionary<TKey, TValue>::find
		(const TKey & key) const
	{
		return m_MultiMap.find(key);
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::size_type Dictionary<TKey, TValue>::count
		(const TKey & key) const
	{
		return m_MultiMap.count(key);
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::dictionary_pair Dictionary<TKey, TValue>::equal_range
		(const TKey & key) const
	{
		return m_MultiMap.equal_range(key);
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::const_interator
		Dictionary<TKey, TValue>::lower_bound(const TKey & key) const
	{
		return m_MultiMap.lower_bound(key);
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::const_interator
		Dictionary<TKey, TValue>::upper_bound(const TKey & key) const
	{
		return m_MultiMap.upper_bound(key);
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator Dictionary<TKey, TValue>::insert(const TValue & value)
	{
		return m_MultiMap.insert(value);
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator Dictionary<TKey, TValue>::insert(TValue && value)
	{
		return m_MultiMap.insert(value);
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator 
		Dictionary<TKey, TValue>::insert(const_interator hint, const value_type & value)
	{
		return m_MultiMap.insert(hint, value);
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator
		Dictionary<TKey, TValue>::insert(const_interator hint, value_type && value)
	{
		return m_MultiMap.insert(hint, value);
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator
		Dictionary<TKey, TValue>::insert
			(const typename Dictionary<TKey, TValue>::dkv_pair & kv_pair)
	{
		return m_MultiMap.insert(kv_pair);
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator
		Dictionary<TKey, TValue>::erase(const_interator position)
	{
		return m_MultiMap.erase(position);
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::size_type
		Dictionary<TKey, TValue>::erase(const key_type& key)
	{
		return m_MultiMap.erase(key);
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator
		Dictionary<TKey, TValue>::erase(const_interator first, const_interator last)
	{
		return m_MultiMap.erase(first, last);
	}

	template < typename TKey, typename TValue >
	void Dictionary<TKey, TValue>::clear()
	{
		m_MultiMap.clear();
	}

	template < typename TKey, typename TValue >
	void Dictionary<TKey, TValue>::swap(Dictionary<TKey, TValue> & yRef)
	{
		m_MultiMap.swap(yRef.m_MultiMap);
	}

	template < typename TKey, typename TValue >
	bool Dictionary<TKey, TValue>::empty() const
	{
		return m_MultiMap.empty();
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::size_type Dictionary<TKey, TValue>::size() const
	{
		return m_MultiMap.size();
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::size_type Dictionary<TKey, TValue>::max_size() const
	{
		return m_MultiMap.max_size();
	}

	template < typename TKey, typename TValue >
	void swap( Dictionary<TKey, TValue>& lhs,
		Dictionary<TKey, TValue>& rhs)
	{
		std::swap(lhs.m_MultiMap, rhs.m_MultiMap)
	}

	template < typename TKey, typename TValue >
	bool operator== ( Dictionary<TKey, TValue>& lhs,
		Dictionary<TKey, TValue>& rhs)
	{
		return lhs.m_MultiMap == rhs.m_MultiMap;
	}

	template < typename TKey, typename TValue >
	bool operator!= ( Dictionary<TKey, TValue>& lhs,
		Dictionary<TKey, TValue>& rhs)
	{
		return lhs.m_MultiMap != rhs.m_MultiMap;
	}
}

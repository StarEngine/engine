#pragma once

#include "..\defines.h"
#include <unordered_map>
#include "Helpers.h"

namespace star
{
	template < class TKey, class TValue >
	class Dictionary
	{
	public:
		typedef typename std::unordered_multimap<TKey, TValue> dictionary;
		typedef typename dictionary::iterator iterator;
		typedef typename dictionary::const_iterator const_interator;
		typedef TKey key_type;
		typedef TValue value_type;
		typedef uint32 size_type;
		typedef typename dictionary::reference reference;
		typedef typename dictionary::const_reference const_reference;
		typedef typename dictionary::difference_type difference_type;
		typedef typename dictionary::allocator_type allocator_type;
		typedef typename dictionary::mapped_type mapped_type;
		typedef typename std::pair<TKey, TValue> dkv_pair;
		typedef typename std::pair<TKey, size_type> dki_pair;
		typedef std::pair<
				typename dictionary::iterator,
				typename dictionary::iterator
				> dictionary_pair;

		Dictionary();
		Dictionary(const Dictionary & yRef);
		Dictionary(Dictionary && yRef);
		Dictionary(iterator begin, iterator end);
		~Dictionary();

		Dictionary<TKey, TValue> &
			operator=(const Dictionary<TKey, TValue>& yRef);
		Dictionary<TKey, TValue> &
			operator=(Dictionary<TKey, TValue>&& yRef);
		TValue & operator[](const TKey & key);
		TValue & operator[](dki_pair & ki_pair);

		TValue & at(const TKey & key);
		TValue & at(dki_pair & ki_pair);
		TValue & at(const TKey & key, size_type index);

		iterator begin();
		iterator end();

		const_interator cbegin() const;
		const_interator cend() const;

		iterator find(const TKey & key) const;
		size_type count(const TKey & key) const;

		const_interator lower_bound(const TKey & key) const;
		const_interator upper_bound(const TKey & key) const;

		iterator insert(const TValue & value);
		iterator insert(TValue && value);
		iterator insert(const_interator hint, const value_type & value);
		iterator insert(const_interator hint, value_type && value);
		iterator insert(const dkv_pair & kv_pair);

		iterator erase(const_interator position);
		size_type erase(const key_type& key);
		iterator erase(const_interator first, const_interator last);

		void clear();
		void swap(Dictionary<TKey, TValue> & yRef);
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

	protected:
		dictionary m_MultiMap;

	private:
		template < typename TFriendKey, typename TFriendValue >
		friend void swap( Dictionary<TFriendKey, TFriendValue>& lhs,
			Dictionary<TFriendKey, TFriendValue>& rhs);

		template < typename TFriendKey, typename TFriendValue >
		friend bool operator== ( Dictionary<TFriendKey, TFriendValue>& lhs,
			Dictionary<TFriendKey, TValue>& rhs);

		template < typename TFriendKey, typename TFriendValue >
		friend bool operator!= ( Dictionary<TFriendKey, TFriendValue>& lhs,
			Dictionary<TFriendKey, TValue>& rhs);
	};

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
	Dictionary<TKey, TValue>::Dictionary
		(	typename Dictionary<TKey, TValue>::iterator begin,
			typename Dictionary<TKey, TValue>::iterator end )
		: m_MultiMap(begin, end)
	{

	}

	template < typename TKey, typename TValue >
	Dictionary<TKey, TValue>::~Dictionary()
	{
		clear();
	}

	template < typename TKey, typename TValue >
	Dictionary<TKey, TValue> &
		Dictionary<TKey, TValue>::operator=(const Dictionary<TKey, TValue>& yRef)
	{
		m_MultiMap = yRef.m_MultiMap;
		return (*this);
	}
	
	template < typename TKey, typename TValue >
	Dictionary<TKey, TValue> &
		Dictionary<TKey, TValue>::operator=(Dictionary<TKey, TValue>&& yRef)
	{
		m_MultiMap = yRef.m_MultiMap;
		return (*this);
	}

	template < typename TKey, typename TValue >
	TValue & Dictionary<TKey, TValue>::operator[](const TKey & key)
	{
		return (at(key));
	}

	template < typename TKey, typename TValue >
	TValue & Dictionary<TKey, TValue>::operator[](dki_pair & ki_pair)
	{
		return (at(ki_pair));
	}

	template < typename TKey, typename TValue >
	TValue & Dictionary<TKey, TValue>::at(const TKey & key)
	{
		auto it = m_MultiMap.find(key);
		ASSERT( it != m_MultiMap.end(), (_T("Couldn't find key '") +
				string_cast<tstring>(key) + _T("'.")).c_str());
		return ((*it).second);
	}

	template < typename TKey, typename TValue >
	TValue & Dictionary<TKey, TValue>::at
		(dki_pair & ki_pair)
	{
		return (at(ki_pair.first, ki_pair.second));
	}

	template < typename TKey, typename TValue >
	TValue & Dictionary<TKey, TValue>::at(const TKey & key, size_type index)
	{
		std::pair<iterator, iterator> range = m_MultiMap.equal_range(key);
		auto it = range.first;
		size_type i(0);
		while(i < index && it != range.second)
		{
			++i;
			++it;
			ASSERT(it != range.second, (_T("The value with key '") +
					string_cast<tstring>(key) + _T("' and index '") +
					string_cast<tstring>(index) + _T("' couldn't be found.")).c_str());
		}
		return ((*it).second);
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator Dictionary<TKey, TValue>::begin()
	{
		return (m_MultiMap.begin());
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator Dictionary<TKey, TValue>::end()
	{
		return (m_MultiMap.end());
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::const_interator Dictionary<TKey, TValue>::cbegin() const
	{
		return (m_MultiMap.cbegin());
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::const_interator Dictionary<TKey, TValue>::cend() const
	{
		return (m_MultiMap.cend());
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator Dictionary<TKey, TValue>::find
		(const TKey & key) const
	{
		return (m_MultiMap.find(key));
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::size_type Dictionary<TKey, TValue>::count
		(const TKey & key) const
	{
		return (m_MultiMap.count(key));
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::const_interator
		Dictionary<TKey, TValue>::lower_bound(const TKey & key) const
	{
#ifdef DESKTOP
		return (m_MultiMap.lower_bound(key));
#else
		return m_MultiMap.equal_range(key).first;
#endif
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::const_interator
		Dictionary<TKey, TValue>::upper_bound(const TKey & key) const
	{
#ifdef DESKTOP
		return (m_MultiMap.upper_bound(key));
#else
		return m_MultiMap.equal_range(key).second;
#endif
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator
		Dictionary<TKey, TValue>::insert(const TValue & value)
	{
		return (m_MultiMap.insert(value));
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator
		Dictionary<TKey, TValue>::insert(TValue && value)
	{
		return (m_MultiMap.insert(value));
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator
		Dictionary<TKey, TValue>::insert(
			typename Dictionary<TKey, TValue>::const_interator hint,
			const typename Dictionary<TKey, TValue>::value_type & value)
	{
		return (m_MultiMap.insert(hint, value));
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator
		Dictionary<TKey, TValue>::insert(
			typename Dictionary<TKey, TValue>::const_interator hint,
			typename Dictionary<TKey, TValue>::value_type && value)
	{
		return (m_MultiMap.insert(hint, value));
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator
		Dictionary<TKey, TValue>::insert
		(const dkv_pair & kv_pair)
	{
		return (m_MultiMap.insert(kv_pair));
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator
		Dictionary<TKey, TValue>::erase
		(typename Dictionary<TKey, TValue>::const_interator position)
	{
		return (m_MultiMap.erase(position));
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::size_type
		Dictionary<TKey, TValue>::erase
			(const typename Dictionary<TKey, TValue>::key_type& key)
	{
		return (m_MultiMap.erase(key));
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::iterator
		Dictionary<TKey, TValue>::erase(
			typename Dictionary<TKey, TValue>::const_interator first,
			typename Dictionary<TKey, TValue>::const_interator last )
	{
		return (m_MultiMap.erase(first, last));
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
		return (m_MultiMap.empty());
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::size_type
		Dictionary<TKey, TValue>::size() const
	{
		return (m_MultiMap.size());
	}

	template < typename TKey, typename TValue >
	typename Dictionary<TKey, TValue>::size_type
		Dictionary<TKey, TValue>::max_size() const
	{
		return (m_MultiMap.max_size());
	}
}

#pragma once

#include "..\defines.h"
#include <unordered_map>

namespace star
{
	template < typename TKey, typename TValue >
	class Dictionary
	{
	protected:
		typedef typename std::unordered_multimap<TKey, TValue> dictionary;
		typedef std::pair<typename dictionary::iterator, typename dictionary::iterator> dictionary_pair;

	public:
		typedef typename dictionary::iterator iterator;
		typedef typename dictionary::const_iterator const_interator;
		typedef typename dictionary::reverse_iterator reverse_iterator;
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

		Dictionary()
			: m_MultiMap()
		{

		}

		Dictionary(const Dictionary & yRef)
			: m_MultiMap(yRef.m_MultiMap)
		{

		}

		Dictionary(Dictionary && yRef)
			: m_MultiMap(yRef.m_MultiMap)
		{

		}

		Dictionary(iterator begin, iterator end)
			: m_MultiMap(begin, end)
		{

		}

		~Dictionary()
		{
			clear();
		}

		Dictionary<TKey, TValue> & operator=(const Dictionary<TKey, TValue>& yRef)
		{
			m_MultiMap = yRef.m_MultiMap;
			return (*this);
		}

		TValue & operator[](const TKey & key)
		{
			return (at(key));
		}

		TValue & operator[](dki_pair & ki_pair)
		{
			return (at(ki_pair));
		}

		TValue & at(const TKey & key)
		{
			auto it = m_MultiMap.find(key);
			ASSERT( it != m_MultiMap.end(), _T("Couldn't find this key."));
			return ((*it).second);
		}

		TValue & at
			(dki_pair & ki_pair)
		{
			return (at(ki_pair.first, ki_pair.second));
		}

		TValue & at(const TKey & key, size_type index)
		{
			std::pair<iterator, iterator> range = m_MultiMap.equal_range(key);
			auto it = range.first;
			size_type i(0);
			while(i < index && it != range.second)
			{
				++i;
				++it;
				ASSERT(it != range.second, _T("The value with this index and key couldn't be found!"));
			}
			return ((*it).second);
		}

		iterator begin()
		{
			return (m_MultiMap.begin());
		}

		iterator end()
		{
			return (m_MultiMap.end());
		}

		const_interator cbegin() const
		{
			return (m_MultiMap.cbegin());
		}

		const_interator cend() const
		{
			return (m_MultiMap.cend());
		}

		iterator find
			(const TKey & key) const
		{
			return (m_MultiMap.find(key));
		}

		size_type count
			(const TKey & key) const
		{
			return (m_MultiMap.count(key));
		}

		const_interator
			lower_bound(const TKey & key) const
		{
			return (m_MultiMap.lower_bound(key));
		}

		const_interator
			upper_bound(const TKey & key) const
		{
			return (m_MultiMap.upper_bound(key));
		}

		iterator insert(const TValue & value)
		{
			return (m_MultiMap.insert(value));
		}

		iterator insert(TValue && value)
		{
			return (m_MultiMap.insert(value));
		}

		iterator
			insert(const_interator hint, const value_type & value)
		{
			return (m_MultiMap.insert(hint, value));
		}

		iterator
			insert(const_interator hint, value_type && value)
		{
			return (m_MultiMap.insert(hint, value));
		}

		iterator
			insert
			(const dkv_pair & kv_pair)
		{
			return (m_MultiMap.insert(kv_pair));
		}

		iterator
			erase(const_interator position)
		{
			return (m_MultiMap.erase(position));
		}

		size_type
			erase(const key_type& key)
		{
			return (m_MultiMap.erase(key));
		}

		iterator
			erase(const_interator first, const_interator last)
		{
			return (m_MultiMap.erase(first, last));
		}

		void clear()
		{
			m_MultiMap.clear();
		}

		void swap(Dictionary<TKey, TValue> & yRef)
		{
			m_MultiMap.swap(yRef.m_MultiMap);
		}

		bool empty() const
		{
			return (m_MultiMap.empty());
		}

		size_type size() const
		{
			return (m_MultiMap.size());
		}

		size_type max_size() const
		{
			return (m_MultiMap.max_size());
		}

	protected:
		dictionary m_MultiMap;

	private:
		friend void swap(	Dictionary<TKey, TValue>& lhs,
			Dictionary<TKey, TValue>& rhs);

		friend bool operator== (	Dictionary<TKey, TValue>& lhs,
			Dictionary<TKey, TValue>& rhs);

		friend bool operator!= (	Dictionary<TKey, TValue>& lhs,
			Dictionary<TKey, TValue>& rhs);
	};
}

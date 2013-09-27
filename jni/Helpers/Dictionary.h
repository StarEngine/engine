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

		Dictionary();
		Dictionary(const Dictionary<TKey, TValue> & yRef);
		Dictionary(Dictionary<TKey, TValue> && yRef);
		Dictionary(iterator begin, iterator end);
		virtual ~Dictionary();

		Dictionary<TKey, TValue> & operator=(const Dictionary<TKey, TValue>& yRef);
		TValue & operator[](const TKey & key);
		TValue & operator[](const dki_pair & ki_pair);

		TValue & at(const TKey & key);
		TValue & at(const dki_pair & ki_pair);
		TValue & at(const TKey & key, size_type index);

		typename iterator begin();
		typename iterator end();
		typename const_interator cbegin() const;
		typename const_interator cend() const;

		typename iterator find(const TKey & key) const;
		typename size_type count(const TKey & key) const;
		typename dictionary_pair equal_range(const TKey & key) const;
		typename const_interator lower_bound(const TKey & key) const;
		typename const_interator upper_bound(const TKey & key) const;

		typename iterator insert(const TValue & value);
		typename iterator insert(TValue && value);
		typename iterator insert(const_interator hint, const value_type & value);
		typename iterator insert(const_interator hint, value_type && value);
		typename iterator insert(const dkv_pair & kv_pair);

		typename iterator erase(const_interator position);
		typename size_type erase(const key_type& key);
		typename iterator erase(const_interator first, const_interator last);

		virtual void clear();
		virtual void swap(Dictionary<TKey, TValue> & yRef);

		bool empty() const;
		typename size_type size() const;
		typename size_type max_size() const;

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

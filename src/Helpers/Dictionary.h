#pragma once

#include "..\defines.h"
#include <unordered_map>
#include "Helpers.h"
#include "..\Logger.h"

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

		const_interator find(const TKey & key) const;
		size_type count(const TKey & key) const;
		
		std::pair<
			const_interator,
			const_interator
			>
			equal_range(const TKey & key) const;
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
}

#include "Dictionary.inl"

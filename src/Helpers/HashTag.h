#pragma once

#include "../defines.h"
#include "../Logger.h"

namespace star
{
#define HASH uint32

	class HashTag final
	{
	public:
		HashTag(const tstring & tag); 

		HashTag(const HashTag & yRef);
		HashTag(HashTag && yRef);

		HashTag & operator=(const HashTag & yRef);
		HashTag & operator=(HashTag && yRef);

		bool operator==(const HashTag & other) const;
		bool operator!=(const HashTag & other) const;
		bool operator==(HashTag && other) const;
		bool operator!=(HashTag && other) const;
		bool operator==(const tstring & tag) const;
		bool operator!=(const tstring & tag) const;
		bool operator==(HASH hash) const;
		bool operator!=(HASH hash) const;

		void SetTag(const tstring & tag);
		const tstring & GetTag() const;

		friend bool operator==(const tstring & tag, const HashTag & other);
		friend bool operator!=(const tstring & tag, const HashTag & other);
		friend bool operator==(HASH hash, const HashTag & other);
		friend bool operator!=(HASH hash, const HashTag & other);

		HASH GetHash() const;

		static void GenerateHash(const tstring & tag, HASH & hash);

	private:
		void GenerateHash();

		tstring m_Tag;
		HASH m_Hash;
	};

#undef HASH
}
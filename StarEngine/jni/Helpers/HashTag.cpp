#include "HashTag.h"
#include "Helpers.h"

namespace star
{
#define HASH uint32

	HashTag::HashTag(const tstring & tag)
		: m_Tag(tag)
		, m_Hash()
	{
		GenerateHash();
	}
	
	HashTag::HashTag(const HashTag & yRef)
		: m_Tag(yRef.m_Tag)
		, m_Hash(yRef.m_Hash)
	{

	}
	
	HashTag::HashTag(HashTag && yRef)
		: m_Tag(yRef.m_Tag)
		, m_Hash(yRef.m_Hash)
	{

	}
	
	HashTag & HashTag::operator=(const HashTag & yRef)
	{
		m_Tag = yRef.m_Tag;
		m_Hash = yRef.m_Hash;

		return *this;
	}
	
	HashTag & HashTag::operator=(HashTag && yRef)
	{
		m_Tag = yRef.m_Tag;
		m_Hash = yRef.m_Hash;

		return *this;
	}
	
	bool HashTag::operator==(const HashTag & other) const
	{
		return m_Hash == other.m_Hash;
	}
	
	bool HashTag::operator!=(const HashTag & other) const
	{
		return m_Hash != other.m_Hash;
	}
	
	bool HashTag::operator==(HashTag && other) const
	{
		return m_Hash == other.m_Hash;
	}
	
	bool HashTag::operator!=(HashTag && other) const
	{
		return m_Hash != other.m_Hash;
	}
	
	bool HashTag::operator==(const tstring & tag) const
	{
		return m_Hash == star::GenerateHash(tag);
	}
	
	bool HashTag::operator!=(const tstring & tag) const
	{
		return m_Hash != star::GenerateHash(tag);
	}
	
	bool HashTag::operator==(HASH hash) const
	{
		return m_Hash == hash;
	}
	
	bool HashTag::operator!=(HASH hash) const
	{
		return m_Hash == hash;
	}
	
	void HashTag::SetTag(const tstring & tag)
	{
		m_Tag = tag;
		GenerateHash();
	}
	
	const tstring & HashTag::GetTag() const
	{
		return m_Tag;
	}
	
	bool operator==(const tstring & tag, const HashTag & other)
	{
		return other.GetHash() == star::GenerateHash(tag);
	}
	
	bool operator!=(const tstring & tag, const HashTag & other)
	{
		return other.GetHash() != star::GenerateHash(tag);
	}
	
	bool operator==(HASH hash, const HashTag & other)
	{
		return hash == other.m_Hash;
	}
	
	bool operator!=(HASH hash, const HashTag & other)
	{
		return hash != other.m_Hash;
	}
	
	HASH HashTag::GetHash() const
	{
		return m_Hash;
	}
	
	void HashTag::GenerateHash()
	{
		GenerateHash(m_Tag, m_Hash);
	}
	
	void HashTag::GenerateHash(const tstring & tag, HASH & hash)
	{
		hash = star::GenerateHash(tag);
	}

#undef HASH
}

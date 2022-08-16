#include "pch.h"
#include "StringPtr.h"


namespace
{
	std::shared_mutex gSynchronizer;
	std::unordered_set<std::string> gStringToId = { std::string() };
	const std::string* EMPTY_PTR = &*gStringToId.begin();
}

namespace
{
	const std::string* CreatePtrFromString(const std::string& st)
	{
		std::lock_guard<std::shared_mutex> lock(gSynchronizer);
		auto it = gStringToId.find(st);
		if (gStringToId.end() != it)
		{
			return &*it;
		}

		const auto it2 = gStringToId.emplace(st);
		it = it2.first;
		const std::string* result = &*it;
		return result;
	}

	const std::string* GetOrCreatePtrFromString(const std::string& st)
	{
		{
			std::shared_lock<std::shared_mutex> lock(gSynchronizer);
			const auto it = gStringToId.find(st);
			if (gStringToId.end() != it)
			{
				return &*it;
			}
		}
		return CreatePtrFromString(st);
	}
}

StringPtr::StringPtr()
	: _st(EMPTY_PTR)
{
}

StringPtr::StringPtr(const std::string& st)
	: _st(GetOrCreatePtrFromString(st))
{
}

StringPtr::StringPtr(const char* st)
	: _st(GetOrCreatePtrFromString(st))
{
}

StringPtr StringPtr::Empty()
{
	return StringPtr();
}

const std::string& StringPtr::ToString() const
{
	return *_st;
}

bool operator == (const StringPtr first, const StringPtr second)
{
	return first._st == second._st;
}

bool operator != (const StringPtr first, const StringPtr second)
{
	return first._st != second._st;
}

bool operator <= (const StringPtr first, const StringPtr second)
{
	return first._st <= second._st;
}

bool operator >= (const StringPtr first, const StringPtr second)
{
	return first._st >= second._st;
}

bool operator < (const StringPtr first, const StringPtr second)
{
	return first._st < second._st;
}

bool operator > (const StringPtr first, const StringPtr second)
{
	return first._st > second._st;
}

std::ostream& operator << (std::ostream& stream, const StringPtr value)
{
	stream << value.ToString();
	return stream;
}

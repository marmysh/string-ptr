#pragma once

class StringPtr
{
public:
	StringPtr();
	StringPtr(const std::string& st);
	StringPtr(const char* st);

public:
	const std::string& ToString() const;

public:
	static StringPtr Empty();

private:
	const std::string* _st = nullptr;

private:
	friend bool operator == (StringPtr first, StringPtr second);
	friend bool operator != (StringPtr first, StringPtr second);
	friend bool operator <= (StringPtr first, StringPtr second);
	friend bool operator >= (StringPtr first, StringPtr second);
	friend bool operator < (StringPtr first, StringPtr second);
	friend bool operator > (StringPtr first, StringPtr second);
};

namespace std
{
	template<> struct hash<StringPtr>
	{
		size_t operator() (const StringPtr& value) const noexcept
		{
			const hash<const void*> helper;
			const size_t result = helper(&value.ToString());
			return result;
		}
	};
}

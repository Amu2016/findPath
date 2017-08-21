#ifndef _COMMON_UTILS_H_
#define _COMMON_UTILS_H_
#include "Singleton.h"
#include "cocos2d.h"
#include "CommonEnum.h"
#include <thread>
#include <mutex>
#include <functional>
#include <map>
#include <initializer_list>

using namespace cocos2d;

class ObjectBase;

class CommonUtils :public Singleton<CommonUtils>
{
public:
	std::map<string,ValueMap> _config;
	
	bool hasCommonTypeIn(ObjectBase* A, ObjectBase* B, const int& ty);

	void plusType(int& typeFlag, const int& ty);

	void removeType(int& typeFlag, const int& ty);

	bool hasType(const int& typeFlag, const int& ty);

	int getAttackPriority(const int& typeFlag);

	float transformHeadingToRotation(const Vec2& heading);

	void loadConfigAsync(function<void()> callback);

	Value getConfigByKey(const string& name,const std::string& key);

	void assertInRelease(bool judgement, const string& errorCode);

	static void SplitString(const string& s, vector<string>& v, const string& c)
	{
		string::size_type pos1, pos2;
		pos2 = s.find(c);
		pos1 = 0;
		while (string::npos != pos2)
		{
			v.push_back(s.substr(pos1, pos2 - pos1));

			pos1 = pos2 + c.size();
			pos2 = s.find(c, pos1);
		}
		if (pos1 != s.length())
			v.push_back(s.substr(pos1));
	}

	template<class T>
	T multiMin(T arg, ...)
	{
		va_list argArr;
		T temp;
		T minArg = arg;

		va_start(argArr, arg);
		while (temp)
		{
			temp = va_arg(argArr, T);

			if (minArg > temp)
			{
				minArg = temp;
			}
		}
		va_end(argArr);

		return minArg;
	}

	template<class T>
	T multiMax(T arg, ...)
	{
		va_list argArr;
		T temp;
		T maxArg = arg;

		va_start(argArr, arg);
		while (temp)
		{
			temp = va_arg(argArr, T);

			if (maxArg < temp)
			{
				maxArg = temp;
			}
		}
		va_end(argArr);

		return maxArg;
	}
private:
	mutex _mut;

//public:
//	vector<float> testNumArr;
};

#define ASSERT_IN_RELEASE(_JUDGEMENT_,_ERROR_CODE_) CommonUtils::instance()->assertInRelease(_JUDGEMENT_,_ERROR_CODE_)

#define CU CommonUtils::instance()

#endif // ! _COMMON_UTILS_H_

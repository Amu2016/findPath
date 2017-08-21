#include "CommonUtils.h"
#include "tinyxml2\tinyxml2.h"
#include "ObjectBase.h"

bool CommonUtils::hasCommonTypeIn(ObjectBase * A, ObjectBase * B, const int & ty)
{
	return hasType(A->typeFlag(), ty) && hasType(B->typeFlag(), ty);
}

void CommonUtils::plusType(int & typeFlag, const int & ty)
{
	typeFlag |= ty;
}

void CommonUtils::removeType(int & typeFlag, const int & ty)
{
	if (hasType(typeFlag, ty))
		typeFlag ^= ty;
}

bool CommonUtils::hasType(const int & typeFlag, const int & ty)
{
	return (typeFlag&ty) == ty;
}

int CommonUtils::getAttackPriority(const int & typeFlag)
{
	if (hasType(typeFlag, creep))
	{
		return hatred_creep;
	}
	
	if (hasType(typeFlag, hero))
	{
		return hatred_hero;
	}

	if (hasType(typeFlag, tower))
	{
		return hatred_tower;
	}

	return 0;
}

float CommonUtils::transformHeadingToRotation(const Vec2 & heading)
{
	return 90 - heading.getAngle() * 180 / PI;
}

void CommonUtils::loadConfigAsync(function<void()> callback)
{
	thread loadAsync = thread([this,&callback]() {
		_mut.lock();
		//加载文件目录
		auto filevmap = FileUtils::getInstance()->getValueMapFromFile("gameData.plist");
		
		//加载每个文件
		for (auto iter = filevmap.begin(); iter != filevmap.end(); ++iter)
		{
			string eachfile = iter->second.asString();

			string typeName = "";
			for (int i = 0; i < eachfile.size()-6; ++i)
			{
				typeName += eachfile[i];
			}

			auto fileMap = FileUtils::getInstance()->getValueMapFromFile(eachfile + ".plist");

			_config.insert(make_pair(typeName, fileMap));
		}

		_mut.unlock();

		callback();
	});

	loadAsync.join();
}

Value CommonUtils::getConfigByKey(const string& name,const std::string & key)
{
	auto configMap = _config[name];
	
	return configMap[key];
}

void CommonUtils::assertInRelease(bool judgement, const string & errorCode)
{
	if (!judgement)
	{
		CCLOG("assert error occured: %s", errorCode.c_str());
		exit(0);
	}
}

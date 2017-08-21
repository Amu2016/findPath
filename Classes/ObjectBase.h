#ifndef _OBJECT_BASE_H_
#define _OBJECT_BASE_H_

#include "cocos2d.h"
#include "CommonEnum.h"
#include "CommonUtils.h"

using namespace cocos2d;
using namespace std;

class ObjectBase
{
public:
	ObjectBase(int id_) :_id(id_),_type(0x0000) {}
	virtual ~ObjectBase() {}
public:
	const int id()const { return _id; }
	const int typeFlag()const { return _type; }

	virtual void update() = 0;
	virtual void clear() = 0;

	bool hasType(const ObjectType& ty) { return CU->hasType(_type, ty); }
	void plusType(const ObjectType& ty) { CU->plusType(_type, ty); }
public:
	int _id;
	string _name;
private:
	int _type;
};



#endif
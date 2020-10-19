#pragma once
#include "allEnums.h"

class GameObject
{
protected:
	Synthesize(OBJECT_TEAM, _team, Team)
	/*
	protected: string mName;
	public: inline string GetName()const{return mName;}
	public: inline void SetName(string value){mName = value;}
	*/
	Synthesize(Vector3, _position, Position) // x, y, z
	Synthesize(Vector3, _size,Size)
	Synthesize(FloatRect, _rect,Rect)
	Synthesize(bool, _active,Active)
public:
	GameObject();
	virtual ~GameObject();

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render();
};


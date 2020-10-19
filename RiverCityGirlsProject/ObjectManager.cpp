#include "stdafx.h"
#include "ObjectManager.h"
#include "AllObjects.h"
#include "StageManager.h"

void ObjectManager::init()
{
}

void ObjectManager::release()
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->release();
		delete _objects[i];
	}
	_objects.clear();
}

void ObjectManager::update()
{
	for (int i = 0; i < _objects.size();)
	{
		_objects[i]->update();
		if (_objects[i]->getState() == OBJECT_STATE::INACTIVE)
		{
			_objects[i]->release();
			delete _objects[i];
			_objects.erase(_objects.begin() + i);
		}
		else
		{
			i++;
		}
	}
}

void ObjectManager::render()
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->render();
	}
}

void ObjectManager::collision(Vector3 * pos, GameObject* gameObject)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->collision(pos, gameObject);
	}
}

void ObjectManager::spawnObject(OBJECT_TYPE type, Vector3 pos, DIRECTION direction)
{
	switch (type)
	{
		case OBJECT_TYPE::DESK01: 
		{ _objects.push_back(new DeskObject(pos, direction, 1)); }
		break;

		case OBJECT_TYPE::DESK02:
		{ _objects.push_back(new DeskObject(pos, direction, 2)); }
		break;

		case OBJECT_TYPE::DESK03:
		{ _objects.push_back(new DeskObject(pos, direction, 3)); }
		break;

		case OBJECT_TYPE::DESK04:
		{ _objects.push_back(new DeskObject(pos, direction, 4)); }
		break;

		case OBJECT_TYPE::DESK05:
		{ _objects.push_back(new DeskObject(pos, direction, 6)); }
		break;

		case OBJECT_TYPE::TABLE01:
		{ _objects.push_back(new TableObject(pos, direction, 1)); }
		break;

		case OBJECT_TYPE::TABLE02:
		{ _objects.push_back(new TableObject(pos, direction, 2)); }
		break;

		case OBJECT_TYPE::TABLE03:
		{ _objects.push_back(new TableObject(pos, direction, 3)); }
		break;

		case OBJECT_TYPE::TABLE04:
		{ _objects.push_back(new TableObject(pos, direction, 4)); }
		break;

		case OBJECT_TYPE::TABLE05:
		{ _objects.push_back(new TableObject(pos, direction, 5)); }
		break;

		case OBJECT_TYPE::TABLE06:
		{ _objects.push_back(new TableObject(pos, direction, 6)); }
		break;

		case OBJECT_TYPE::TABLE07:
		{ _objects.push_back(new TableObject(pos, direction, 7)); }
		break;

		case OBJECT_TYPE::TABLE08:
		{ _objects.push_back(new TableObject(pos, direction, 8)); }
		break;

		case OBJECT_TYPE::BOX:	
		{ _objects.push_back(new BoxObject(pos, direction));  }
		break;

		case OBJECT_TYPE::FALL_CHAIR01:
		{ _objects.push_back(new ChairObject(pos, direction, 1));  }
		break;

		case OBJECT_TYPE::FALL_CHAIR02:
		{ _objects.push_back(new ChairObject(pos, direction, 2));  }
		break;

		case OBJECT_TYPE::TABLE_CHAIR01:
		{ _objects.push_back(new ChairObject(pos, direction, 3));  }
		break;

		case OBJECT_TYPE::TABLE_CHAIR02:
		{ _objects.push_back(new ChairObject(pos, direction, 4));  }
		break;

		case OBJECT_TYPE::TEACHER_TABLE:
		{ _objects.push_back(new TeacherTableObject(pos, direction)); }
		break;

		case OBJECT_TYPE::SNACKMACHINE:
		{ 
			SnackMachineObject* snackObject = new SnackMachineObject(pos, direction);
			snackObject->setObjectManager(this);
			_objects.push_back(snackObject);
		}
		break;

		case OBJECT_TYPE::mrRudis: 
		{ _objects.push_back(new MrRudis(pos, direction)); }
		break;

		case OBJECT_TYPE::schoolBoyA_idle01: 
		{ _objects.push_back(new SchoolStudent(pos, direction, 1)); }
		break;

		case OBJECT_TYPE::schoolBoyA_idle02:
		{ _objects.push_back(new SchoolStudent(pos, direction, 2)); }
		break;

		case OBJECT_TYPE::schoolBoyB_idle01:
		{ _objects.push_back(new SchoolStudent(pos, direction, 3)); }
		break;

		case OBJECT_TYPE::schoolBoyB_idle02:
		{ _objects.push_back(new SchoolStudent(pos, direction, 4)); }
		break;

		case OBJECT_TYPE::schoolBoyE_idle01:
		{ _objects.push_back(new SchoolStudent(pos, direction, 5)); }
		break;

		case OBJECT_TYPE::schoolBoyE_idle02:
		{ _objects.push_back(new SchoolStudent(pos, direction, 6)); }
		break;

		case OBJECT_TYPE::schoolGirlA_idle01:
		{ _objects.push_back(new SchoolStudent(pos, direction, 7)); }
		break;

		case OBJECT_TYPE::schoolGirlA_idle02:
		{ _objects.push_back(new SchoolStudent(pos, direction, 8)); }
		break;

		case OBJECT_TYPE::schoolGirlB_idle01:
		{ _objects.push_back(new SchoolStudent(pos, direction, 9)); }
		break;

		case OBJECT_TYPE::schoolGirlB_idle02:
		{ _objects.push_back(new SchoolStudent(pos, direction, 10)); }
		break;

		case OBJECT_TYPE::schoolGirlE_idle01:
		{ _objects.push_back(new SchoolStudent(pos, direction, 11)); }
		break;

		case OBJECT_TYPE::schoolGirlE_idle02:
		{ _objects.push_back(new SchoolStudent(pos, direction, 12)); }
		break;

		case OBJECT_TYPE::workingFemaleA:
		{ _objects.push_back(new WorkingFemaleA(pos, direction)); }
		break;
		
		case OBJECT_TYPE::workingMaleD:
		{ _objects.push_back(new WorkingMaleD(pos, direction)); }
		break;

		case OBJECT_TYPE::PILLAR:
		{ 
			PillarObject* pillarObject = new PillarObject(pos, direction);
			pillarObject->setObjectManager(this);
			_objects.push_back(pillarObject);
		}
		break;
	}
}

void ObjectManager::makeParticle(PARTICLE_TYPE type, int num, Vector3 minPos, Vector3 maxPos, Vector2 minAngle, Vector2 maxAngle, float minSpeed, float maxSpeed, float minTime, float maxTime)
{
	for (int i = 0; i < num; i++)
	{
		Vector3 pos = Vector3(RANDOM->getFromFloatTo(minPos.x, maxPos.x),
			RANDOM->getFromFloatTo(minPos.y, maxPos.y),
			RANDOM->getFromFloatTo(minPos.z, maxPos.z));
		Vector2 angle = Vector2(RANDOM->getFromFloatTo(minAngle.x, maxAngle.x),
			RANDOM->getFromFloatTo(minAngle.y, maxAngle.y));
		float speed = RANDOM->getFromFloatTo(minSpeed, maxSpeed);
		float time = RANDOM->getFromFloatTo(minTime, maxTime);

		ParticleObject* particle = new ParticleObject(type, pos, angle, speed, time);
		particle->setObjectManager(this);
		_objects.push_back(particle);
	}
	
}

void ObjectManager::spawnFood(Vector3 pos)
{
	FoodObject* food = new FoodObject(pos);
	food->setObjectManager(this);
	_objects.push_back(food);
}

void ObjectManager::spawnMoney(Vector3 pos)
{
	MoneyObject* money = new MoneyObject(pos);
	money->setObjectManager(this);
	_objects.push_back(money);
}

void ObjectManager::isEat(Player* player)
{
	for (int i = 0; i < _objects.size(); i++)
	{
		_objects[i]->isEat(player);
	}
}

bool ObjectManager::getHit(Vector3 pos, Vector3 size, OBJECT_TEAM team, FloatRect attackRc, float damage, ATTACK_TYPE type)
{
	bool result = false;
	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i]->getHit(pos, size, team, attackRc, damage, type))
		{
			result = true;
		}
		
	}
	return result;
}

float ObjectManager::getCenterBottom(Vector2 pos)
{
	float result = 0;
	for (int i = 0; i < _objects.size(); i++)
	{
		result = min(result, _objects[i]->getCenterBottom(pos));
	}

	return result;
}

void ObjectManager::moveGameObject(GameObject * gameObject, Vector3 move)
{
	_stageManager->moveGameObject(gameObject, move);
}

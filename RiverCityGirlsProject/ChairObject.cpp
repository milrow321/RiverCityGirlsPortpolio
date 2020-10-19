#include "stdafx.h"
#include "ChairObject.h"


ChairObject::ChairObject(Vector3 position, DIRECTION direction, int imageType)
{
	_direction = direction;
	_size = Vector3(40, 100, 20);
	_position = Vector3(position.x, -(_size.y / 2), position.z);

	switch (imageType)
	{
		case 1:
		{ _img = IMAGE_MANAGER->findImage("OBJECT_CHAIR01"); }
		break;

		case 2:
		{ _img = IMAGE_MANAGER->findImage("OBJECT_CHAIR02"); }
		break;

		case 3:
		{ _img = IMAGE_MANAGER->findImage("OBJECT_CHAIR03"); }
		break;

		case 4:
		{ _img = IMAGE_MANAGER->findImage("OBJECT_CHAIR04"); }
		break;
	}
}

void ChairObject::update()
{
}

void ChairObject::release()
{
}

void ChairObject::render()
{
	Object::render();

	_img->setScale(3);
	CAMERA_MANAGER->renderZ(_img, _position, _size, false);

}

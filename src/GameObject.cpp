#include "GameObject.h"

GameObject* GameObject::Create(ObjectType type)
{
    switch(type){
        case ObjectType::ASTEROID: return new AsteroidObject;

    }
}

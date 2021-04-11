#pragma once
//Singleton2.h

#pragma once
#include "config.h"

template <typename T>
class Singleton2
{
protected:
	static T* instance;

	Singleton2() {};
	~Singleton2() {};

public:
	static T* GetSingleton();
	void ReleaseSingleton();

};

//영역 밖에서 초기화 -> static 멤버 변수 사용 전에 해야하는 문법
template<typename T>
T* Singleton2<T>::instance = nullptr;

template<typename T>
inline T* Singleton2<T>::GetSingleton()
{
	if (instance == nullptr)
	{
		instance = new T;
	}
	return instance;
}

template<typename T>
inline void Singleton2<T>::ReleaseSingleton()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

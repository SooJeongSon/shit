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

//���� �ۿ��� �ʱ�ȭ -> static ��� ���� ��� ���� �ؾ��ϴ� ����
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

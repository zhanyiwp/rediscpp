#ifndef MUTEXLOCK_H
#define MUTEXLOCK_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define TINY_CHECK(exp)\
if (!exp)\
{ \
	fprintf(stderr, "File : %s, Line : %d Exp : ["#exp"] is true, abort.\n", __FILE__, __LINE__); abort(); \
}

class noncopyable
{
protected:
	noncopyable() {}
	~noncopyable() {}
private:  // emphasize the following members are private
	noncopyable(const noncopyable&);
	const noncopyable& operator=(const noncopyable&);
};

class MutexLock : noncopyable
{
	friend class Condition;
public:
	MutexLock()
	:_isLock(false)
	{
		TINY_CHECK(!pthread_mutex_init(&_mutex, NULL));
	}

	~MutexLock()
	{
		assert(!isLocked());
		TINY_CHECK(!pthread_mutex_destroy(&_mutex));
	}
	void lock()
	{
		TINY_CHECK(!pthread_mutex_lock(&_mutex));
		_isLock = true;
	}
	void unlock()
	{
		_isLock = false;
		TINY_CHECK(!pthread_mutex_unlock(&_mutex));
	}

	bool isLocked() const { return _isLock; }
	pthread_mutex_t *getMutexPtr() { return &_mutex; }

private:
	void restoreMutexStatus()
	{
		_isLock = true;
	}

	pthread_mutex_t _mutex;
	bool _isLock;
};


class MutexLockGuard : noncopyable            //������װ��MutexLockGuard�У�
{                                            //����ֻ�趨��һ�����󣬱��
public:                                        //����Զ���������������ʱ�Զ�����
	MutexLockGuard(MutexLock &mutex)
		:_mutex(mutex)
	{
		_mutex.lock();
	}

	~MutexLockGuard()
	{
		_mutex.unlock();
	}

private:
	MutexLock &_mutex;
};

#define MutexLockGuard(x) error "Missing guard object name"
#endif
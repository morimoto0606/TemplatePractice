#ifndef TRAITSANDTAGDISPATCHER_H_INCLUDED
#define TRAITSANDTAGDISPATCHER_H_INCLUDED

#include <iostream>

namespace study {
	struct TagA {};
	struct TagB {};
	class Hoge{
	};

	template <class T>
	struct TagTrait {
		typedef TagA tag_trait;
	};

	template <>
	struct TagTrait<Hoge> 
	{
		typedef TagB tag_trait;
	};

	template <class T>
	void run(const T& x, TagA) {
		std::cout << "TagA is called." << std::endl;
	}
	template <class T>
	void run(const T&x, TagB) {
		std::cout << "TagB is called." << std::endl;
	}
	template <class T>
	void run(const T& x) 
	{
			run(x, typename TagTrait<T>::tag_trait());
	}
}
#endif
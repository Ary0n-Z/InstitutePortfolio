#pragma once
#include<functional>


template <typename T> Maybe<T> maybe(T* context)
{
	return Maybe<T>(context);
}


template <typename T> struct Maybe
{
	T* context;
	explicit Maybe(T* const context)
		: context{ context }
	{
	}	
	template <typename Func>
	auto With(Func evaluator)
	{
		if (context == nullptr)
		{
			return
				Maybe<typename remove_pointer<decltype(evaluator(context))>::type>(nullptr);
		}
		else
		{
			return maybe(evaluator(context));
		}
	}
	template <typename Func>
	auto Do(Func action)
	{
		if (context != nullptr) action(context);
		return *this;
	}
};

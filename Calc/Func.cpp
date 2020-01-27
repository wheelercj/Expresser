#include "Func.h"

template<class T, class ...Ts>
Func<T, Ts...>::Func(std::string newParams, T(*newFuncPtr)(Ts...))
{
	params = newParams;
	funcPtr = newFuncPtr;
}

template<class T, class ...Ts>
std::string Func<T, Ts...>::getParams()
{
	return params;
}

template<class T, class ...Ts>
void Func<T, Ts...>::operator()(std::string& input, int namePos, int nameSize)
{
	call(funcPtr, input, namePos, nameSize);
}

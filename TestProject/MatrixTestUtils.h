#pragma once

#include "MatrixFloat.h"

#include <algorithm>
#include <sstream>

namespace TestUtils
{
	void AreEqual(const MatrixFloat& matrix1, const MatrixFloat& matrix2, float tolerance);
	
	template<typename Argument1Type, typename... ArgumentType>
	void AddArguments(std::wstringstream& ss, Argument1Type&& argument1)
	{
		ss << argument1;
	}

	template<typename Argument1Type, typename... ArgumentType>
	void AddArguments(std::wstringstream& ss, Argument1Type&& argument1, ArgumentType&&... arguments)
	{
		ss << argument1;
		AddArguments(ss, arguments...);
	}

	template<typename... ArgumentType>
	std::wstring MakeString(const std::wstring& message, ArgumentType&&... arguments)
	{
		std::wstringstream ss(message);

		AddArguments(ss, arguments...);

		return ss.str();
	}
}

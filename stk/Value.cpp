#include "Value.h"

bool Value::asBool() const
{
	switch (type)
	{
	case ValueType::Boolean:
		return data.bValue;

	case ValueType::Integer:
		return data.iValue != 0;

	case ValueType::Float:
		return data.fValue != 0.0f;
	}

	return false;
}

int Value::asInt() const
{
	switch (type)
	{
	case ValueType::Boolean:
		return data.bValue ? -1 : 0;

	case ValueType::Integer:
		return data.iValue;

	case ValueType::Float:
		return static_cast<int>(data.fValue);
	}
	return 0;
}

float Value::asFloat() const
{
	switch (type)
	{
	case ValueType::Boolean:
		return data.bValue ? -1.0f : 0.0f;

	case ValueType::Integer:
		return static_cast<float>(data.iValue);

	case ValueType::Float:
		return data.fValue;
	}

	return 0.0f;
}

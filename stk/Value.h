#ifndef _VALUE_H
#define _VALUE_H

class Value
{
public:
	enum ValueType
	{
		Unknown,
		Boolean,
		Integer,
		Float
	};

	Value() { type = ValueType::Unknown; }
	explicit Value(bool value) { type = ValueType::Boolean; data.bValue = value; }
	explicit Value(int value) { type = ValueType::Integer; data.iValue = value; }
	explicit Value(float value) { type = ValueType::Float; data.fValue = value; }

	bool asBool() const;
	int asInt() const;
	float asFloat() const;

	void set(bool value) { type = ValueType::Boolean; data.bValue = value; }
	void set(int value) { type = ValueType::Integer; data.iValue = value; }
	void set(float value) { type = ValueType::Float; data.fValue = value; }

private:
	ValueType type;
	union
	{
		bool bValue;
		int iValue;
		float fValue;
	} data;
};

#endif


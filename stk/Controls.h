#ifndef _CONTROLS_H
#define _CONTROLS_H

#define MAX_FLAGS 4
#define MAX_VALUES 8

class Controls
{
public:
	Controls();

	bool getFlag(int index) const { return flags[index]; }
	void setFlag(int index, bool flag) { flags[index] = flag; }

	double getValue(int index) const { return values[index]; }
	void setValue(int index, double value) { values[index] = value; }

private:
	bool flags[MAX_FLAGS];
	double values[MAX_VALUES];
};

#endif // _CONTROLS_H

#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstdio>

using namespace std;

template <typename T>

void printer(T x)
{
	cout << x << endl;
}

class Data
{
public:
	int x;

	Data()
	:x(0)
	{}

	Data(int x)
	:x(x)
	{}

	string toString() const
	{
		string retval;
		char *number = (char*)malloc(20);
		sprintf(number, "%d", x);
		//sprintf(number, "%d", this->x);
		retval = number;
		free(number);
		return retval;
	}
};

ostream & operator<<(ostream & out, const Data & rhs)
{
	out << rhs.toString();
	return out;
}

int main(int argc, char **argv)
{
	int x;
	cin >> x;
	//fscanf(stdin, "%d", &x);

	string y;
	cin >> y;

	cout << x << ": " << y << endl;

	printer(x);
	printer(y);
	printer('a');
	printer(4545.233);

	Data a;
	printer(a);

	vector<int> nums;
	for(int i = 0; i < 10; i++)
	{
		int x = (i*13)%8;
//		Data a;
//		a.x = x;
		nums.push_back(x);
	}

	for(size_t i = 0; i < nums.size(); i++)
	{
		cout << i << ": " << nums[i] << endl;
	}

	return 0;

}

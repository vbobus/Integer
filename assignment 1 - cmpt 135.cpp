#include <iostream>
#include <ctime>

using namespace std;

class Integer
{
private: //Private member variables
	char sign;
	int length;
	char* magnitude;

private: //Private member functions
	//These member functions are utilities useful inside the class definition ONLY.
	//We do not want them to be accessible outside the class definition.
	void appendDigit(const char& digit);
	void prependDigit(const char& digit);
	void resize(const int& new_length);
	void trim();

	static int compare_magnitudes(const Integer& A, const Integer& B);
	static Integer add_magnitudes(const Integer& A, const Integer& B);
	static Integer subtract_magnitudes(const Integer& A, const Integer& B);

public: //Public member functions
	Integer();
	Integer(const int&);
	Integer(const Integer&);

	~Integer();

	Integer& operator = (const Integer&);

	Integer abs() const;

	Integer operator - () const;
	Integer& operator ++ ();
	Integer& operator -- ();
	Integer operator ++ (int);
	Integer operator -- (int);

	Integer operator + (const Integer&) const;
	Integer operator - (const Integer&) const;
	Integer operator * (const Integer&) const;
	Integer operator / (const Integer&) const;
	Integer operator % (const Integer&) const;

	Integer operator += (const Integer&);
	Integer operator -= (const Integer&);
	Integer operator *= (const Integer&);
	Integer operator /= (const Integer&);
	Integer operator %= (const Integer&);

	bool operator == (const Integer&) const;
	bool operator != (const Integer&) const;
	bool operator > (const Integer&) const;
	bool operator < (const Integer&) const;
	bool operator >= (const Integer&) const;
	bool operator <= (const Integer&) const;

	friend Integer operator + (const int&, const Integer&);
	friend Integer operator - (const int&, const Integer&);
	friend Integer operator * (const int&, const Integer&);
	friend Integer operator / (const int&, const Integer&);
	friend Integer operator % (const int&, const Integer&);

	friend bool operator == (const int&, const Integer&);
	friend bool operator != (const int&, const Integer&);
	friend bool operator > (const int&, const Integer&);
	friend bool operator < (const int&, const Integer&);
	friend bool operator >= (const int&, const Integer&);
	friend bool operator <= (const int&, const Integer&);

	friend ostream& operator << (ostream&, const Integer&);
};
/////The following function definitions are provided for you. Use them without any modification./////

void Integer::appendDigit(const char& digit)
{

	Integer x = *this;
	Integer y;
	y.length = x.length + 1;
	y.magnitude = new char[y.length];
	for (int i = x.length - 1; i >= 0; i--)
	{
		y.magnitude[i] = x.magnitude[i];
	}
	y.magnitude[length - 1] = digit;
	y.sign = x.sign;
	*this = y;
}

void Integer::prependDigit(const char& digit)
{
	
	Integer x = *this;
	Integer y;

	y.length = x.length + 1;
	y.magnitude = new char[y.length];

	for (int i = x.length - 1; i >= 0; i--)
	{
		y.magnitude[i + 1] = x.magnitude[i];
	}
	y.magnitude[0] = digit;
	y.sign = x.sign;

	*this = y;

}

void Integer::resize(const int& new_length)
{
	int len = this->length;
	if (new_length <= len)
		return;
	for (int i = len; i < new_length; i++)
	{
		prependDigit('0');
	}
}

void Integer::trim()
{
	Integer A = *this;
	int x, a= 0, decimal=1;
	for (int i = A.length - 1; i >= 0; i--)   
	{
		x = A.magnitude[i] - '0';
		a = a + (x * decimal);
		decimal *= 10;
	}

	*this = a;
}

int Integer::compare_magnitudes(const Integer& A, const Integer& B)
{
	
	int a=0, b=0;
	int x,decimal;

	decimal = 1;
	for (int i = A.length-1; i >= 0; i--)      //find magnitude of A
	{
		x = A.magnitude[i] - '0';
		a = a + (x * decimal);
		decimal *= 10;
	}

	decimal = 1;
	for (int i = B.length-1; i >= 0; i--)     //find magnitude of B
	{
		x = B.magnitude[i] - '0';
		b = b + (x * decimal);
		decimal *= 10;
	}

	if (a == b)
		return 0;
	else if (a > b)
		return 1;
	else
		return -1;	
}

Integer Integer::add_magnitudes(const Integer& A, const Integer& B)
{
	Integer add,new_A=A,new_B=B;
	
	int rem = 0,len;
	int intdigit;
	char chardigit;

	add.length = 0;
	int comp = compare_magnitudes(A,B);   
	if (comp == 1)    //a>b
	{
		new_B.resize(new_A.length);
		len = new_A.length;
	}
	else if (comp == -1)   //a<b
	{
	
		new_A.resize(new_B.length);
		len = new_B.length;
	}
	else
		len = new_A.length;


	add.magnitude = new char[len];
	for (int i = len-1; i >= 0; i--)
	{		
		intdigit = (new_A.magnitude[i] -'0' )+ (new_B.magnitude[i]-'0')+rem;    //takes ASCII value
		rem = 0;
		if (intdigit > 9)
		{
			rem = 1;
			intdigit = intdigit % 10;
		}
		chardigit = '0' + intdigit;
		add.prependDigit(chardigit);
		//add.length++;
		if (i == 0 && rem == 1) 
		{
			add.prependDigit('1');
			//add.length++;
		}
	}
	//add.length = len;
	add.sign = '+';
	add.trim();
	return add;
}


Integer Integer::subtract_magnitudes(const Integer& A, const Integer& B)
{
	Integer sub, new_A = A, new_B = B;

	int len, a, b, rem = 0;
	int var_9,var_0=1,c9;

	int intdigit;
	char chardigit;

	new_B.resize(new_A.length);
	len = new_A.length;
	sub.length = len;
	sub.magnitude = new char[sub.length];

	for (int i = 0; i < len; i++)
		var_0 *= 10;               //eg, 1000
	var_9 = var_0 - 1;              // eg, 999

	for (int i = len-1; i >= 0; i--)           //999-B
	{
		b = new_B.magnitude[i] - '0';
		c9 = var_9 % 10;
		intdigit = c9 - b;
		chardigit = '0' + intdigit;
		sub.magnitude[i] = chardigit;
		var_9 = var_9 / 10;
	}

	for (int i = len - 1; i >= 0; i--)            //A+(999-B)
	{
		a = new_A.magnitude[i] - '0';
		intdigit = a + (sub.magnitude[i] - '0') + rem;
		rem = 0;
		if (intdigit > 9)
		{
			rem = 1;
			intdigit %= 10;
		}			
		chardigit = '0' + intdigit;
		sub.magnitude[i] = chardigit;
	}
	sub.magnitude[len - 1] += 1;             //A+(999-B)-1000+1
	sub.sign = '+';
	sub.trim();
	return sub;	
} 

Integer::Integer()
{
	sign = '+';
	length = 0;
	//No other initialization. Do not change this function definition.
}

Integer::Integer(const int& a)
{
    if(a == 0) 
	{
		length = 1;
		magnitude = new char[1];
		magnitude[0] = '0';
		sign = '+';
	}
	else 
	{
		int n = a;
		int rev = 0, ld, fd, len = 0;
		char x;
		length = 0;
		if (n < 0)
			n = -n;

		while (n > 0)                 //reversing the integer
		{
			ld = n % 10;
			rev = (rev * 10) + ld;
			n = n / 10;
			len++;
		}

		length = len;          //creating integer
		magnitude = new char[len];
		for (int i = 0; i < len; i++)
		{
			fd = rev % 10;
			x = '0' + fd;
			magnitude[i] = x;
			rev = rev / 10;
		}
		if (a >= 0)            //assigning sign
			sign = '+';
		else
			sign = '-';
	}
}

Integer::Integer(const Integer &x)           //copy constructor
{
	this->length = x.length;
	if (this->length > 0)
	{
		this->magnitude = new char[this->length];
		for (int i = 0; i < this->length; i++)
		{
			this->magnitude[i] = x.magnitude[i];
		}		
	}
	this->sign = x.sign;
}

Integer::~Integer()
{
	if (this->length > 0)
	{
		delete[] this->magnitude;
		this->length = 0;
	}
}

Integer& Integer::operator = (const Integer& x)
{
	this->~Integer();  //delete left hand object
	this->length = x.length;
	if (x.sign == '+')
		this->sign = '+';
	else
		this->sign = '-';
	this->magnitude = new char[this->length];
	for (int i = 0; i < this->length; i++)
	{
		this->magnitude[i] = x.magnitude[i];
	}
	return *this;
}

Integer Integer::abs() const     //absolute value
{
	Integer x=(*this);
	x.sign = '+';
	return x;		
}

bool Integer::operator == (const Integer& x) const
{
	int ans = compare_magnitudes(*this, x);
	
	if (ans == 0 && (this->sign==x.sign))
		return true;
	else
		return false;
}
bool operator == (const int& y, const Integer& x)
{
	return x == y;
}

bool Integer::operator != (const Integer& x) const
{
	int ans = compare_magnitudes(*this, x);

	if (ans != 0 || (this->sign != x.sign))
		return true;
	else
		return false;
}
bool operator != (const int& y, const Integer& x)
{
	return x != y;
}

bool Integer::operator > (const Integer& x) const
{
	int ans = compare_magnitudes(*this, x);

	if (this->sign == '+' && x.sign == '-')
		return true;
	else if (this->sign == '+' && x.sign == '+')
	{
		if (ans == 1)
			return true;
		else
			return false;
	}
	else if (this->sign == '-' && x.sign == '-')
	{
		if (ans == -1)
			return true;
		else
			return false;
	}
	else
		return false;
}
bool operator > (const int& y, const Integer& x)
{
	if ((x > y) == true)
		return false;
	else
		return true;
}

bool Integer::operator < (const Integer& x) const
{
	bool ans = *this > x;
	if (ans == true)
		return false;
	else
		return true;
}
bool operator < (const int& y, const Integer& x)
{
	if ((x < y) == true)
		return false;
	else
		return true;
}

bool Integer::operator >= (const Integer& x) const
{
	if ((*this == x) || (*this > x))
		return true;
	else
		false;
}
bool operator >= (const int& y, const Integer& x)
{
	if ((x >= y) == true )
		return false;
	else
		return true;
}

bool Integer::operator <= (const Integer& x) const
{
	if ((*this == x) || (*this < x))
		return true;
	else
		return false;
}
bool operator <= (const int& y, const Integer& x)
{
	if ((x <= y) == true )
		return false;
	else
		return true;
}

Integer Integer::operator - () const
{
	Integer x;
	x = *this;
	if (x.sign == '+')
		x.sign = '-';
	else
		x.sign = '+';		
	return x;
	//return subtract_magnitudes(*this, 2 * (*this));
	//return add_magnitudes(*this, 2 * (*this));
}

Integer& Integer::operator ++ ()
{
	if (this->sign == '+')
	{
		*this=add_magnitudes(*this, 1);
		this->sign = '+';
	}
	else
	{
		*this=subtract_magnitudes(*this, 1);
		this->sign = '-';
	}
	return *this;
}

Integer& Integer::operator -- ()
{
	if (this->sign == '+')
	{
		*this = subtract_magnitudes(*this, 1);
		this->sign = '+';
	}
	else
	{
		*this = add_magnitudes(*this, 1);
		this->sign = '-';
	}
	return *this;
}

Integer Integer::operator ++ (int DUMMY)
{
	Integer temp = *this;
	if (this->sign == '+')
	{
		*this = add_magnitudes(*this, 1);
		this->sign = '+';
	}
	else
	{
		*this = subtract_magnitudes(*this, 1);
		this->sign = '-';
	}
	return temp;
}

Integer Integer::operator -- (int DUMMY)
{
	Integer temp = *this;
	if (this->sign == '+')
	{
		*this = subtract_magnitudes(*this, 1);
		this->sign = '+';
	}
	else
	{
		*this = add_magnitudes(*this, 1);
		this->sign = '-';
	}
	return temp;
}

Integer Integer::operator + (const Integer& x) const
{
	Integer A = *this, ans;
	Integer B = x;
	int check = compare_magnitudes(A, B);
	ans = B;
	if (A.sign == '+' && B.sign == '+')
	{
		ans=add_magnitudes(A, B);
		ans.sign = '+';
	}
	else if (A.sign == '-' && B.sign == '-') 
	{
		ans = add_magnitudes(A, B);
		ans.sign = '-';
	}
	else 
	{
		if (check == 1)
		{
			ans=subtract_magnitudes(A, B);
			ans.sign = A.sign;
		}
		else if (check == -1)
		{
			ans=subtract_magnitudes(B, A);
			ans.sign = B.sign;
		}
		else
		{
			ans = 0;
			ans.sign = '+';
		}
	}
	return ans;
}
Integer operator + (const int& A, const Integer& B)
{
	return B + A;
}

Integer Integer::operator - (const Integer& x) const
{
	Integer A = *this;
	Integer B = x;

	return A + (-B);
}
Integer operator - (const int& A, const Integer& B)
{
	return -(B - A);
}

Integer Integer::operator * (const Integer& X) const
{
	Integer A = *this;
	Integer B = X;
	Integer ans=0;
	 
	int x, decimal,b = 0;

	decimal = 1;
	for (int i = B.length - 1; i >= 0; i--)     //find magnitude of B
	{
		x = B.magnitude[i] - '0';
		b = b + (x * decimal);
		decimal *= 10;
	}

	for (int i = 0; i < b; i++)
	{
		ans = ans + A;
	}

	if (A.sign == B.sign)
		ans.sign = '+';
	else
		ans.sign = '-';

	return ans;
}
Integer operator * (const int& A, const Integer& B)
{
	return B * A;
}

Integer Integer::operator / (const Integer& x) const
{
	Integer A = *this;
	Integer B = x;
	Integer ans=0;
	int mag = compare_magnitudes(A, B);
	if ( mag == -1)
		return ans;
	
	while(mag!=-1)
	{
		A = subtract_magnitudes(A, B);
		mag = compare_magnitudes(A, B);
		ans++;
	}

	if ((this->sign == '+' && x.sign == '+') || (this->sign == '-' && x.sign == '-'))
		ans.sign = '+';
	else
		ans.sign = '-';

	return ans;
}
Integer operator / (const int& x, const Integer& B)
{
	Integer A = x;
	return (A/B);
}

Integer Integer::operator % (const Integer& x) const
{
	Integer A = *this;
	Integer B = x;
	Integer ans;
	
	ans = A - (A / B) * B;

	return ans;
}
Integer operator % (const int& x, const Integer& B)
{
	Integer A = x;
	return A % B;
}

Integer Integer::operator += (const Integer& x)
{
	Integer A = *this;
	Integer B = x;
	Integer ans;

	*this = A + B;
	return *this;
}
Integer Integer::operator -= (const Integer& x)
{
	Integer A = *this;
	Integer B = x;
	Integer ans;

	*this = A - B;
	return *this;
}
Integer Integer::operator *= (const Integer& x)
{
    Integer A = *this;
	Integer B = x;
	Integer ans;

	*this = A * B;
	return *this;
}
Integer Integer::operator /= (const Integer& x)
{
	Integer A = *this;
	Integer B = x;
	Integer ans;

	*this = A / B;
	return *this;
}
Integer Integer::operator %= (const Integer& x)
{
	Integer A = *this;
	Integer B = x;
	Integer ans;

	*this = A % B;
	return *this;
}

ostream& operator << (ostream& out, const Integer& d)
{
	if (d.length == 0)
		out << "Not Initialized";
	else
	{
		if (d.sign == '-')
			out << '-';
		for (int i = 0; i < d.length; i++)
			out << d.magnitude[i];
	}
	return out;
}
////////////End of provided function definitions. Use them without any modification.///////////////
int main()
{
	//Test constructors
	Integer n1, n2(-10023);
	Integer n3(n2);
	cout << "Default Integer object n1 is " << n1 << endl;
	cout << "Non-default Integer object n2 is " << n2 << endl;
	cout << "Non-default Integer object n3 is " << n3 << endl;

	//Test destructor
	n2.~Integer();
	cout << "After destructing it, n2 is now " << n2 << endl;

	//Test assignment operators
	n1 = n3;
	cout << "After assigning n1 the value of n3, n1 is now " << n1 << endl;
	n2 = 8;
	cout << "After assigning n2 the integer value 8, n2 is now " << n2 << endl;  

	//Test absolute value
	cout << "The absolute value of n1 is " << n1.abs() << endl;
	cout << "The absolute value of n2 is " << n2.abs() << endl;
	cout << "The absolute value of n3 is " << n3.abs() << endl;

	//Test arithmetic operations with relatively small values in order to validate the correctness of our program
	int x, y, z;
	Integer d1, d2, d3, d4;
	bool success = true;
	srand(time(0)); //Comment this line of code to get same random numbers on repeated runs of the program
	for (int i = 0; i < 25; i++) //You may loop more iterations to test thoroughly
	{
		cout << "========================================================" << endl;
		//Test equality comparison
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		x == y ? cout << x << " == " << y << endl : cout << x << " is not ==  " << y << endl;
		d1 == d2 ? cout << d1 << " == " << d2 << endl : cout << d1 << " is not == " << d2 << endl;
		x == d2 ? cout << x << " == " << d2 << endl : cout << x << " is not == " << d2 << endl;
		if (((x == y) == (d1 == d2)) && ((x == y) == (x == d2)))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;                                                
		
		//Test not equality comparison
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		x != y ? cout << x << " != " << y << endl : cout << x << " is not != " << y << endl;
		d1 != d2 ? cout << d1 << " != " << d2 << endl : cout << d1 << " is not != " << d2 << endl;
		x != d2 ? cout << x << " != " << d2 << endl : cout << x << " is not != " << d2 << endl;
		if (((x != y) == (d1 != d2)) && ((x != y) == (x != d2)))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;                                         

		//Test greater than comparison
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		x > y ? cout << x << " > " << y << endl : cout << x << " is not > " << y << endl;
		d1 > d2 ? cout << d1 << " > " << d2 << endl : cout << d1 << " is not > " << d2 << endl;
		x > d2 ? cout << x << " > " << d2 << endl : cout << x << " is not > " << d2 << endl;
		if (((x > y) == (d1 > d2)) && ((x > y) == (x > d2)))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;                                                   

		//Test less than comparison
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		x < y ? cout << x << " < " << y << endl : cout << x << " is not < " << y << endl;
		d1 < d2 ? cout << d1 << " < " << d2 << endl : cout << d1 << " is not < " << d2 << endl;
		x < d2 ? cout << x << " < " << d2 << endl : cout << x << " is not < " << d2 << endl;
		if (((x < y) == (d1 < d2)) && ((x < y) == (x < d2)))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;                                                   

		//Test greater than or equal comparison
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		x >= y ? cout << x << " >= " << y << endl : cout << x << " is not >= " << y << endl;
		d1 >= d2 ? cout << d1 << " >= " << d2 << endl : cout << d1 << " is not >= " << d2 << endl;
		x >= d2 ? cout << x << " >= " << d2 << endl : cout << x << " is not >= " << d2 << endl;
		if (((x >= y) == (d1 >= d2)) && ((x >= y) == (x >= d2)))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;                                                

		//Test less than or equal comparison
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		x <= y ? cout << x << " <= " << y << endl : cout << x << " is not <= " << y << endl;
		d1 <= d2 ? cout << d1 << " <= " << d2 << endl : cout << d1 << " is not <= " << d2 << endl;
		x <= d2 ? cout << x << " <= " << d2 << endl : cout << x << " is not <= " << d2 << endl;
		if (((x <= y) == (d1 <= d2)) && ((x <= y) == (x <= d2)))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;                                                      

		//Test arithmetic negation operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		cout << "x = " << x << " and -x is " << -x << endl;
		cout << "d1 = " << d1 << " and -d1 is " << -d1 << endl;
		if (-d1 == -x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;                                                      

		//Test pre-increment operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		cout << "x = " << x << " and ";
		cout << "++x is " << ++x << endl;
		cout << "d1 = " << d1 << " and ";
		cout << "++d1 is " << ++d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test pre-decrement operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		cout << "x = " << x << " and ";
		cout << "--x is " << --x << endl;
		cout << "d1 = " << d1 << " and ";
		cout << "--d1 is " << --d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;                        

		//Test post-increment operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		cout << "x = " << x << " and ";
		x++;
		cout << "x++ is " << x << endl;
		cout << "d1 = " << d1 << " and ";
		d1++;
		cout << "d1++ is " << d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;                    

		//Test post-decrement operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		cout << "x = " << x << " and ";
		x--;
		cout << "x-- is " << x << endl;
		cout << "d1 = " << d1 << " and ";
		d1--;
		cout << "d1-- is " << d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test addition operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		z = x + y;
		d3 = d1 + d2;
		d4 = x + d2;
		cout << x << " + " << y << " = " << z << endl;
		cout << d1 << " + " << d2 << " = " << d3 << endl;
		cout << x << " + " << d2 << " = " << d4 << endl;
		if ((d3 == z) && (d4 == z))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;                                    

		//Test subtraction operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		z = x - y;
		d3 = d1 - d2;
		d4 = x - d2;
		cout << x << " - " << y << " = " << z << endl;
		cout << d1 << " - " << d2 << " = " << d3 << endl;
		cout << x << " - " << d2 << " = " << d4 << endl;
		if ((d3 == z) && (d4 == z))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;                                   

		//Test multiplication operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		z = x * y;
		d3 = d1 * d2;
		d4 = x * d2;
		cout << x << " * " << y << " = " << z << endl;
		cout << d1 << " * " << d2 << " = " << d3 << endl;
		cout << x << " * " << d2 << " = " << d4 << endl;
		if ((d3 == z) && (d4 == z))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;                        

		//Test division operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		z = x / y;
		d3 = d1 / d2;
		d4 = x / d2;
		cout << x << " / " << y << " = " << z << endl;
		cout << d1 << " / " << d2 << " = " << d3 << endl;
		cout << x << " / " << d2 << " = " << d4 << endl;
		if ((d3 == z) && (d4 == z))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test modulo operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		z = x % y;
		d3 = d1 % d2;
		d4 = x % d2;
		cout << x << " % " << y << " = " << z << endl;
		cout << d1 << " % " << d2 << " = " << d3 << endl;
		cout << x << " % " << d2 << " = " << d4 << endl;
		if ((d3 == z) && (d4 == z))
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;                                                

		///Test compound addition operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		cout << "x = " << x << ", y = " << y << " and ";
		x += y;
		cout << "x += y gives x = " << x << endl;
		cout << "d1 = " << d1 << ", d2 = " << d2 << " and ";
		d1 += d2;
		cout << "d1 += d2 gives d1 = " << d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test compound subtraction operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		cout << "x = " << x << ", y = " << y << " and ";
		x -= y;
		cout << "x -= y gives x = " << x << endl;
		cout << "d1 = " << d1 << ", d2 = " << d2 << " and ";
		d1 -= d2;
		cout << "d1 -= d2 gives d1 = " << d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test compound multiplication operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		cout << "x = " << x << ", y = " << y << " and ";
		x *= y;
		cout << "x *= y gives x = " << x << endl;
		cout << "d1 = " << d1 << ", d2 = " << d2 << " and ";
		d1 *= d2;
		cout << "d1 *= d2 gives d1 = " << d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test compound division operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		cout << "x = " << x << ", y = " << y << " and ";
		x /= y;
		cout << "x /= y gives x = " << x << endl;
		cout << "d1 = " << d1 << ", d2 = " << d2 << " and ";
		d1 /= d2;
		cout << "d1 /= d2 gives d1 = " << d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << endl;

		//Test compound modulo operation
		x = rand() % 2 ? rand() : -rand();
		d1 = x;
		y = rand() % 2 ? rand() : -rand();
		d2 = y;
		cout << "x = " << x << ", y = " << y << " and ";
		x %= y;
		cout << "x %= y gives x = " << x << endl;
		cout << "d1 = " << d1 << ", d2 = " << d2 << " and ";
		d1 %= d2;
		cout << "d1 %= d2 gives d1 = " << d1 << endl;
		if (d1 == x)
			cout << "Correct computation." << endl;
		else
		{
			cout << "Wrong computation. Something went wrong. Check your work." << endl;
			success = false;
			break;
		}
		cout << "========================================================" << endl;
		cout << endl << endl;

		//system("Pause"); //You may comment this line of code depending on your desire to pause after every iteration 
	}

	if (success)
		cout << endl << "Looks like all your computations were correct. Congratulations!" << endl; 

	system("Pause");
	return 0;
}

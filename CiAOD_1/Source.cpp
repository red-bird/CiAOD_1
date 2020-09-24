#include <iostream>
#include <string>
#include <stack>
using namespace std;

template<typename T>
class QueueList
{
	struct Node
	{
		T info = 0;
		Node* next;
	};

	int amount = 0;
	int max;
	Node* first = nullptr;
	Node* last = nullptr;
public:
	
	void setMax(int value)
	{
		max = value;
	}

	int getMax()
	{
		return max;
	}

	// Конструктор, задающий максимум
	QueueList(int max)
	{
		this->max = max;
	}

	~QueueList()
	{
		while (amount)
		{
			this->pop();
		}
	}
	
	// Добавление элемента
	void push(T info)
	{
		if (amount >= max)
			return;

		Node* newElem = new Node;
		newElem->info = info;
		if (first == nullptr)
		{
			first = newElem;
			last = newElem;
		}
		else
		{
			last->next = newElem;
			last = newElem;
		}
		++amount;
	}

	bool empty()
	{
		return amount == 0;
	}

	bool full()
	{
		return amount == max;
	}

	// Удаление первого в очереди элемента
	void pop()
	{
		Node* tmp = first;
		first = first->next;
		delete tmp;
		--amount;
	}

	// Получение значения первого в очереди элемента
	T head()
	{
		if (first!=nullptr)
			return first->info;
	}

	// Получение длины очереди
	int getLength()
	{
		return amount;
	}
};

//////////////////////////////////////////////////////
template<typename T>
class QueueArray
{
	int amount = 0;
	int max = 10;
	T *arr;
public:
	void setMax(int value)
	{
		max = value;
	}

	int getMax()
	{
		return max;
	}

	// Конструктор, задающий максимум
	QueueArray(int max)
	{
		this->max = max;
		arr = new T[max];
		for (size_t i = 0; i < max; i++)
		{
			arr[i] = 0;
		}
	}

	bool empty()
	{
		return amount == 0;
	}

	bool full()
	{
		return amount == max;
	}

	void push(int info)
	{
		if (amount >= max)
			return;
		arr[amount] = info;		
		++amount;
	}

	// Удаление первого в очереди элемента
	void pop()
	{
		for (size_t i = 1; i < amount; i++)
		{
			arr[i - 1] = arr[i];
		}
		arr[amount] = 0;
		--amount;
	}

	// Получение значения первого в очереди элемента
	int head()
	{
		return arr[0];
	}

	// Получение длины очереди
	int getLength()
	{
		return amount;
	}

};

enum OrdersList
{
	List = 1,
	DynArray,
	Stop

};

void printRules()
{
	cout << "Please enter prefix expression\nRules:\n1) First input - is amount of operands\n2) Write your expression: each operand and operator you must split by space, in the end of expression write \"end\")\nAttention overflow will truncate string\n";
}


int main()
{
	cout << "Please, enter the code of queue type" << endl << "enter \'1\' to choose queue on list" << endl << "enter \'2\' to choose queue on dynamic array" << endl << "enter \'3\' to stop the program" << endl;
	int input;
	cin >> input;
	switch (input)
	{
	case Stop:
		cout << "Stop program" << endl;
		
		return 0;
		break;

	case List:
	{
		cout << "You choose list" << endl;
		printRules();
		cin >> input;

		if (input < 1)
		{
			cout << "Unallowable amount, you must choose at least >0" << endl;
			return -1;
		}

		QueueList<int> operands(input);
		stack<char> operators;
		string tmp;
		while (true)
		{
			cin >> tmp;
			if (tmp == "end")
				break;
			try
			{
				// Проверка, можно ли "кусок" ввода представить в виде int
				operands.push(stoi(tmp));
			}
			catch (const std::exception&)
			{
				// Если прошлая не сработала, проверяем, является ли это оператором
				if (tmp.length() == 1 & ((tmp == "+") | (tmp == "-") | (tmp == "/") | (tmp == "*")))
					operators.push(tmp[0]);
				else
				{
					cout << "Expression error" << endl;
					
					return -1;
				}
			}
		}

		if (operands.empty() & operators.empty())
		{
			cout << "Lack of operators and operands" << endl;
			
			return -1;
		}

		double tmp_num;
		double summary = operands.head();
		operands.pop();
		char op;
		while (!operands.empty() & !operators.empty())
		{
			op = operators.top();
			operators.pop();
			try
			{
				tmp_num = operands.head();
				operands.pop();
				switch (op)
				{
				case('+'):
					summary += tmp_num;
					break;
				case('-'):
					summary -= tmp_num;
					break;
				case('*'):
					summary *= tmp_num;
					break;
				case('/'):
					summary /= tmp_num;
					break;
				default:
					cout << "calculation error" << endl;
					return -1;
				}
			}
			catch (const std::exception&)
			{
				cout << "not enough operators" << endl;
			}
		}

		cout << "Result of calculations = " << summary << endl;
		
		
		//for (size_t i = 0; i < exp.length(); ++i)
		//{
		//	if (exp[i] != ' ')
		//		//знаю что это не хороший тон, не хочу нагружать подключением stringstream
		//		tmp += exp[i];
		//	else 
		//	{
		//		if (tmp != " ")
		//		{
		//			try
		//			{
		//				// Проверка, можно ли 1 "кусок" ввода представить в виде int
		//				operands.push(stoi(tmp));
		//			}
		//			catch (const std::exception&)
		//			{
		//				// Если прошлая не сработала, проверяем, является ли это оператором
		//				if (tmp.length() == 1 & ((tmp == "+") | (tmp == "-") | (tmp == "/") | (tmp == "*")))
		//					operators.push(tmp[0]);
		//				else
		//				{
		//					cout << "Expression error" << endl;
		//					return -1;
		//				}

		//			}
		//		}

		//	}
		//}
		break;
	}
	case DynArray:
	{
		cout << "You choose dynamic array" << endl;
		printRules();
		cin >> input;

		if (input < 1)
		{
			cout << "Unallowable amount, you must choose at least >0" << endl;
			
			return -1;
		}

		QueueArray<int> operands(input);
		stack<char> operators;
		string tmp;
		while (true)
		{
			cin >> tmp;
			if (tmp == "end")
				break;
			try
			{
				// Проверка, можно ли "кусок" ввода представить в виде int
				operands.push(stoi(tmp));
			}
			catch (const std::exception&)
			{
				// Если прошлая не сработала, проверяем, является ли это оператором
				if (tmp.length() == 1 & ((tmp == "+") | (tmp == "-") | (tmp == "/") | (tmp == "*")))
					operators.push(tmp[0]);
				else
				{
					cout << "Expression error" << endl;
					
					return -1;
				}
			}
		}

		if (operands.empty() & operators.empty())
		{
			cout << "Lack of operators and operands" << endl;
			
			return -1;
		}

		double tmp_num;
		double summary = operands.head();
		operands.pop();
		char op;
		while (!operands.empty() & !operators.empty())
		{
			op = operators.top();
			operators.pop();
			try
			{
				tmp_num = operands.head();
				operands.pop();
				switch (op)
				{
				case('+'):
					summary += tmp_num;
					break;
				case('-'):
					summary -= tmp_num;
					break;
				case('*'):
					summary *= tmp_num;
					break;
				case('/'):
					summary /= tmp_num;
					break;
				default:
					cout << "calculation error" << endl;
					return -1;
				}
			}
			catch (const std::exception&)
			{
				cout << "not enough operators" << endl;
			}
		}
		cout << "Result of calculations = " << summary << endl;
		
		break;
	}
	default:
		cout << "Something went wrong.. incorrect input data, stop program" << endl;
		
		return -1;
		break;
	}
		
}
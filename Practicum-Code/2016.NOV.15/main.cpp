#include<iostream>
#include"list.h"
#include"linked_list.cpp"
#include"double_linked_list.cpp"

// 1. задача - Да се залепи на края на даден списък втори даден списък.
template <typename T, typename I>
void append(List<T, I>& L1, List<T, I> const& L2)
{
	for (I it = L2.begin(); it; ++it)
		L1.insertEnd(*it);
}

// 2. задача - Да се обърне реда на елементите в даден списък.
template <typename T, typename I>
void reverse(List<T, I>& L)
{
	I bit = L.begin();
	T x;
	while (L.deleteAfter(x, bit))
		L.insertBegin(x);
}

// 3. задача - Да се раздели даден списък на два други с приблизително равна дължина.
template <typename T, typename I>
void split(List<T, I>& L, List<T, I>& L1, List<T, I>& L2)
{
	bool first = true;
	for (I it = L.begin(); it; ++it)
	{
		if (first)
			L1.insertEnd(*it);
		else
			L2.insertEnd(*it);
		first = !first;
	}
}

// 4. задача - Да се слеят два възходящо подредени списъка в един.Резултата да е възходящо подреден.
template <typename T, typename I>
void merge(List<T, I>& L1, List<T, I>& L2, List<T, I>& L)
{
	I i1 = L1.begin(), i2 = L2.begin();
	while (i1 && i2)
	{
		if (*i1 < *i2)
			L.insertEnd(*(i1++));
		else
			L.insertEnd(*(i2++));
	}
	while (i1)
		L.insertEnd(*(i1++));
	while (i2)
		L.insertEnd(*(i2++));
}

// 5. задача - Да се сортира даден списък чрез сливане.
/*typedef DoubleLinkedList<int> TestList;
TestList sort(TestList const& l) // recursive
{
	if (!++l.begin())
		return l;
	TestList l1, l2;
	split(l, l1, l2);
	TestList result;
	merge(sort(l1), sort(l2), result);
	return result;
}*/

// 6. задача - Реализирайте функцията foldr, която изпълнява дадена операция с два аргумента над елементите на списъка, като започва от дясно на ляво.
template <typename T>
using binop = T(*)(T, T); // указател към функция, която връща тип Т, и приема два аргумента от тип Т !!!

template <typename T, typename I, typename binop>
T foldr(binop op, T nv, I it) // binop = T(*op)(T,T)
{
	if (!it)
		return nv;
	T x = *it++;
	return op(x, foldr(op, nv, it));
}

// 7. задача - Реализирайте функцията foldl. Аналогична на предишната задача. Същите аргументи, но свива списъка от ляво.
template <typename T, typename I, typename binop>
T foldl(binop op, T nv, I it)
{
	T result = nv;
	while (it)
		result = op(result, *it++);
	return result;
}

// 8. задача - Реализирайте функцията map, която прилага дадена функция с един аргумент над елементите от списъка.
template <typename T>
using unop = T(*)(T); // указател към функция, която връща тип Т, и приема един аргумент от тип Т !!!

template <typename I, typename unop>
void map(unop f, I it)
{
	for (; it; ++it)
		*it = f(*it);
}

// 9. задача - Релизирайте функцията filter, която премахва елементите, които не удовлетворяват дадено условие, от списъка.
template <typename T>
using pred = bool(*)(T); // указател към функция, която връща тип bool, и приема един аргумент от тип Т !!!

template <typename T, typename I, typename pred>
void filter(pred p, List<T, I>& l)
{
	I it = l.begin();
	while (it) {
		if (!p(*it)) {
			T tmp;
			I toDelete = it;
			++it;
			l.deleteAt(tmp, toDelete);
		}
		else
			++it;
	}
}

int main()
{
	return 0;
}
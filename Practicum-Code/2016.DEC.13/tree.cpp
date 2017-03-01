#include <list>
#include <iostream>
using std::list;
using std::ostream;

class Tree {
private:
	int root;
	// ñïèñúê îò äåöàòà (íàñëåäíèöèòå íà êîðåíà)
	list<Tree> subtrees;

public:
	// ïðè êîíñòðóèðàíåòî íà äúðâî çàäàâàìå ñàìî êîðåíà
	// çà äîáàâÿíå íà äåöà èçïîëçâàìå addChild
	Tree(int _root = 0) : root(_root) {}

	// äîáàâÿ ïîääúðâî child êúì ñïèñúêà ñ ïîääúðâåòàòà subtrees
	// âðúùà ðåôåðåíöèÿ êúì äúðâîòî,
	// çà äà ìîæåì äà âèêàìå addChild íÿêîëêî ïúòè çà äúðâîòo, ò.å òàêà:
	// tree.addChild(1).addChild(2).addChild(3);
	Tree& addChild(Tree const& child)
	{
		subtrees.push_back(child);
		return *this;
	}

	// âðúùà ñòîéíîñòòà íà êîðåíà
	int getRoot() const { return root; }

	// âðúùà ðåôåðåíöèÿ êúì ñïèñúêà îò ïîääúðâåòà
	list<Tree> const& getSubtrees() const { return subtrees; }

	// èçâåæäà äúðâîòî
	friend ostream& operator<<(ostream& os, Tree const& tree)
	{
		os << '(' << tree.getRoot();
		for (list<Tree>::const_iterator it = tree.getSubtrees().begin(); it != tree.getSubtrees().end(); it++)
		{
			os << ' ' << *it;
		}
		return os << ')';
	}
};
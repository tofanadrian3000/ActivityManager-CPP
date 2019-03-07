#pragma once
#include <vector>
#include <string>
using namespace std;

template<class elemT>
class Repository
{
private:
	vector<elemT> elems;
public:
	Repository() = default;
	virtual void add(const elemT elem);
	virtual void remove(const elemT elem);
	virtual void update(const elemT elem, const elemT newElem);
	int size() noexcept;
	vector<elemT> getAll()const noexcept;
	elemT find(const elemT elem);
	bool exist(const elemT elem)noexcept;
	~Repository() = default;
	void setElems(vector<elemT> elemens) {
		elems = elemens;
	}
};

class RepositoryException {
	string msg;
public:
	RepositoryException(string m) :msg{ m } {}
	string getMsg() { return msg; }
};

template<class elemT>
bool Repository<elemT>::exist(const elemT elem) noexcept {
	for (auto elemCurent : this->elems)
		if (elemCurent == elem)
			return true;
	return false;
}

template<class elemT>
elemT Repository<elemT>::find(const elemT elem) {
	for (auto elemCurent : this->elems)
		if (elemCurent == elem)
			return elemCurent;
	throw RepositoryException("Element inexistent!");
}

template<class elemT>
void Repository<elemT>::add(const elemT elem) {
	if (this->exist(elem) == false)
		this->elems.push_back(elem);
	else throw RepositoryException("Element existent!");
}

template<class elemT>
void Repository<elemT>::remove(const elemT elem) {
	for (int i = 0; i<this->elems.size(); i++)
		if (this->elems[i] == elem) {
			this->elems.erase(this->elems.begin() + i);
			return;
		}
	throw RepositoryException("Element inexistent!");
}

template<class elemT>
void Repository<elemT>::update(const elemT elem, const elemT newElem) {
	for (int i = 0; i<this->elems.size(); i++)
		if (this->elems[i] == elem) {
			this->elems[i] = newElem;
			return;
		}
	throw RepositoryException("Element inexistent!");
}

template<class elemT>
int Repository<elemT>::size() noexcept {
	return this->elems.size();
}

template<class elemT>
vector<elemT> Repository<elemT>::getAll()const noexcept {
	return this->elems;
}
#pragma once
#include <Repository.h>

template<class elemT>
class FileRepository :public Repository<elemT>
{
private:
	string filename;
public:
	FileRepository() {}
	FileRepository<elemT>(string filename) : filename{ filename } {
		this->setElems(elemT::readFromFile(filename));
	}
	void add(const elemT elem) override;
	void update(const elemT elem, const elemT newElem) override;
	void remove(const elemT elem) override;
	~FileRepository() = default;
};

template<class elemT>
void FileRepository<elemT>::add(const elemT elem) {
	Repository<elemT>::add(elem);
	elemT::writeToFile(this->getAll(), this->filename);
}

template<class elemT>
void FileRepository<elemT>::remove(const elemT elem) {
	Repository<elemT>::remove(elem);
	elemT::writeToFile(this->getAll(), this->filename);
}

template<class elemT>
void FileRepository<elemT>::update(const elemT elem, const elemT newElem) {
	Repository<elemT>::update(elem, newElem);
	elemT::writeToFile(this->getAll(), this->filename);
}
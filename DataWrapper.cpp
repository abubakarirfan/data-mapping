#include "DataWrapper.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

const char DataMap::getAsChar() const
{
	return static_cast<const char>(fDatum);
}

DataWrapper::DataWrapper()  : fSize(0), fData(nullptr) {}

DataWrapper::~DataWrapper()
{
	delete [] fData;
}

bool DataWrapper::load(const std::string& aFileName)
{
	ifstream lInput(aFileName);

	if (lInput.good())
	{
		lInput >> fSize;
		
		fData = new DataMap[fSize];

		for (size_t i = 0; i < fSize; i++)
		{
			lInput >> fData[i].fIndex >> fData[i].fDatum;
		}

		lInput.close();

		return true;
	}
	return false;
}

size_t DataWrapper::size() const
{
	return fSize;
}


const DataMap& DataWrapper::operator[](size_t aIndex) const
{
	if (aIndex < fSize)
	{
		return fData[aIndex];
	}
	else 
	{
		throw out_of_range("Illegal index value");
	}
}

const char DataWrapper::get(size_t aIndex, Callable aSelector)
{
	return aSelector(aIndex);
}
#include "DataModel.h"
DataModel::DataModel()
{

}

DataModel::~DataModel()
{

}

DataModel* DataModel::getInstance()
{
	static DataModel dataModel;
	return &dataModel;
}


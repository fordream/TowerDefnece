#ifndef _DATA_MODEL_h

#define _DATA_MODEL_h

#include "cocos2d.h"
USING_NS_CC;

class UIPanGestureRecognizer;

class DataModel : public Ref
{
public:
	static DataModel* getInstance();
	virtual ~DataModel();

protected:
	DataModel();

private:
	Layer* _gameLayer;
	Vector<Ref*> _vectTargets;
	Vector<Ref*> _wayPoints;
	Vector<Ref*> _waves;
	UIPanGestureRecognizer* _gestureRecognizer;
};
#endif // !_DATA_MODEL_h

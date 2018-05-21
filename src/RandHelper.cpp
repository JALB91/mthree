#include "RandHelper.h"

#include <stdlib.h>
#include <time.h>

using namespace std;

namespace mthree {

RandHelper* RandHelper::_instance = nullptr;

RandHelper* RandHelper::getInstance()
{
    if (!_instance)
    {
        _instance = new RandHelper();
    }

    return _instance;
}

RandHelper::RandHelper()
{
    this->createNewSeed();
}

RandHelper::~RandHelper()
{

}


void RandHelper::createNewSeed()
{
    this->seed = static_cast<int>(time(NULL));
    srand(this->seed);
}


int RandHelper::getNextRandom() const
{
    return static_cast<int>(rand());
}

} // namespace mthree
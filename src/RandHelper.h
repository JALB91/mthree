#ifndef RAND_HELPER_H
#define RAND_HELPER_H

namespace mthree {

class RandHelper
{
public:
    static RandHelper* getInstance();
    ~RandHelper();

    inline int getCurrentSeed() const { return this->seed; }

    void createNewSeed();

    int getNextRandom() const;

private:
    RandHelper();

    int seed = 0;
    
    static RandHelper* _instance;

};

} // namespace mthree

#endif /* RAND_HELPER_H */
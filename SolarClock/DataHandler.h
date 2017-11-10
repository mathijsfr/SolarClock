#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

class DataHandler
{
public:
    DataHandler();

    void StoreLength(int length, int motorIndex);
    void RetreiveLengths(int* lengths, int* motorIndexes, int count);

private:

};


#endif
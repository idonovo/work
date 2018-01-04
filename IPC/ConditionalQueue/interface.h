
#include "queue.h"
#include "producers.h"
#include "consumer.h"

typedef struct Input Input;

typedef struct CommunucationChannels CommunucationChannels;

typedef struct ParticipationsData ParticipationsData;

/******************************************************************/

void GetInputParameters(Input* _input, int argc, char **argv);

CommunucationChannels* CreateCommunicationChannel(size_t _sizeOfChannel);

ParticipationsData* CreateParticipations(size_t _numOfProducers, size_t _numOfConsumers, size_t _numOfProducersCycls, CommunucationChannels* _channels);

void ExecuteCommunication(ParticipationsData* _data);

void DestroyChannelsAdnData(CommunucationChannels* _channels, ParticipationsData* _data);




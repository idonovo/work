#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

#define MAGIC 0xDADDAADA
#define NEXT_JUMP (sizeof(Chunk)) + _chunckSize - 4

struct Chunk
{
	void* 		    m_next;
	unsigned int 	m_magic;
	char 			m_data;
};

struct Buffer
{
	void* 	m_free;
	size_t  m_numOfChunks;
	size_t 	m_numOfAllocChunks;
};

/***********************************************************************/
Buffer* CreateBuffer(size_t _chunckSize, size_t _numOfChunks)
{
	size_t i;
	void* nextChunk;
	void* startBuffer;
	
	if(_chunckSize <= 0 || _numOfChunks <= 0)
	{
		return NULL;
	}
	
	startBuffer = malloc((((sizeof(Chunk)-4) +_chunckSize)*_numOfChunks) + sizeof(Buffer));
	if(!startBuffer)
	{
		return NULL;
	}
	
	((Buffer*)startBuffer)->m_numOfChunks = _numOfChunks;
	((Buffer*)startBuffer)->m_numOfAllocChunks = 0;
	
	nextChunk = startBuffer + sizeof(Buffer);
	((Buffer*)startBuffer)->m_free = nextChunk;

	for(i = 1; i <=_numOfChunks; ++i)
	{ 

		((Chunk*)nextChunk)->m_next = nextChunk + NEXT_JUMP;
		((Chunk*)nextChunk)->m_magic = MAGIC;
		nextChunk = nextChunk+ NEXT_JUMP;
	}
	nextChunk = NULL; 
	
	return (Buffer*)startBuffer;	
}

void DestroyBuffer(Buffer* _buffer)
{
	if(!_buffer)
	{
		return;
	}
	free(_buffer);
	return;

}

void* MyMalloc(Buffer* _buffer)
{
	void* dataLocation;
	
	if(!_buffer || ((Buffer*)_buffer)->m_numOfAllocChunks == ((Buffer*)_buffer)-> m_numOfChunks)
	{
		return NULL;
	}
	
	dataLocation = &(((Chunk*)_buffer->m_free)->m_data);
	_buffer->m_free = ((Chunk*)_buffer->m_free)->m_next;
	++((Buffer*)_buffer)->m_numOfAllocChunks;
	
	return dataLocation;			
}

void MyFree(Buffer* _buffer, void* _data)
{
	void* chunkLocation;
	if(!_buffer || !_data)
	{
		return;
	}
	
	chunkLocation = _data - ((sizeof(Chunk)-sizeof(_data)));

	if(((Chunk*)chunkLocation)->m_magic == 1)
	{
		return;
	}
	
	((Chunk*)chunkLocation)->m_next = ((Chunk*)_buffer->m_free)->m_next;
	_buffer->m_free = chunkLocation;
	((Chunk*)chunkLocation)->m_magic = 1;
	
	return;
}   


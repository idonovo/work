#ifndef __ALLOC_H__
#define __ALLOC_H__


typedef struct Chunk Chunk;

typedef struct Buffer Buffer;


/** 
 * @brief a function to create a buffer for memory allocation in the heap. The buffer can returns only single chunks with a fixed size.    
 * @param[in] _chunckSize : the fixed size of chunks in the buffer.
 * @param[in] _numOfChunks : the total number of chunks which the bufer will hold.
 * @return[in] Buffer* on success or NULL if allocaion failed or if  _chunckSize/ numOfChunks were less than 1.
 */
 
Buffer* CreateBuffer(size_t _chunckSize, size_t _numOfChunks);    

/** 
 * 
 * @brief a function to destroy a buffer.
 * @param[in] _buffer* : pointer to buffer for destroy.
 */ 
void DestroyBuffer(Buffer* _buffer); 

/** 
 * 
 * @brief a function to allocate a single fixed size chunk of memory from a buffer to user.
 * @param[in] _buffer : buffer* to allocate from.
* @return[in] void* to the a chunk of memory on success or NULL buffer is null or if it reached the end of total buffer size.
 */
void* MyMalloc(Buffer* _buffer); 

/** 
 * 
 * @brief a function to free a single fixed size chunk of memory from a buffer returned by user.
 * @param[in] _buffer : buffer* to free from.
 */
void MyFree(Buffer* _buffer, void* _data); 


#endif /*__ALLOC_H__ */


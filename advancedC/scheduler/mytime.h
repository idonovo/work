#ifndef __MYTIME__
#define __MYTIME__

#include <time.h>

/*************************/
/*TIME API FUNCTIONS*/
/*************************/

typedef struct Time Time;

/**  
 * @brief a function which create time object which can hold accurate  time according to a clockid_t;
 * @param[in] clockid_t;
 * @return pointer to time object / NULL on fail;
 *
 */

Time* CreateTime(const clockid_t _clockID);
/**  
 * @brief a function which calculate a next interval of a task according to milliSecs parameter recivied from user. 
 * @param[in] time object.
 * @param[in] _millliSecs of next interval.
 * @return 1 if succeed / 0 on fail.
 *
 */
int TimeGetNextInterval(Time* _intervalTime, int _milliSecs);


/**  
 * @brief a function to destroy time object.
 * @param[in] time pointer object.
 */
void TimeDestroy(Time* _time);

/**  
 * @brief a function to compare the time included in two time objects. 
 * @param[in] _first time object.
 * @param[in] _secondtime object.
 * @return 1 if the tome in the first object is the earliest or 0 if time in the second is earlieast. 
 */
int	TimeCompare(const Time* _first, const Time* _second);

/**  
 * @brief a 'sleep' function for the time interval between current time and the time held by Timeo bject
 * @param[in] _time object which holds next interval time.
 */
void TimeSleepUntil(const Time* _time);


	
#endif /*__MYTIME__*/	




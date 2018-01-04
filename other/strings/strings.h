
#ifndef __STRINGS_H__
#define __STRINGS_H__

#include <stddef.h>

/*Desc.: Itterative function to calculate the length of a string.
Input: pointer to a string;
Output: size_t  length of the string.
Error: return -1 if the  string is NULL.*/
size_t StrLen(const char* _str);

/*Desc.: Rec.function to calculate the length of a string.
Input: pointer to a string;
Output: size_t length of the string.
Error: return -1 if the  string is NULL.*/
size_t StrLenRec(const char* _str);

/*Desc.: Itter. function for comparing the first character of each string. If they are equal to each other, it continues with the following pairs until the characters differ or until a terminating null-character is reached.
Input: two pointers to strings;
Output:return value	indicates
<0	the first character that does not match has a lower value in ptr1 than in ptr2
0	the contents of both strings are equal
>0	the first character that does not match has a greater value in ptr1 than in ptr2
Error: no error.*/
int StrCompare(const char* _s1, const char* _s2);

/*Desc.: Rec. function for comparing the first character of each string. If they are equal to each other, it continues with the following pairs until the characters differ or until a terminating null-character is reached.
Input: two pointers to strings;
Output:return value	indicates
<0	the first character that does not match has a lower value in ptr1 than in ptr2
0	the contents of both strings are equal
>0	the first character that does not match has a greater value in ptr1 than in ptr2
Error: no error.*/
int StrCompareRec(const char* _s1, const char* _s2);

/*Desc.: Itter. function to copy a string pointed by source into the array pointed by destination, including the terminating null character (and stopping at that point).
Input: Source string pointer and Dest. string pointer.
Output: pointer to the destination string.
Error: NULL pointer if copy  failed.*/
char* StrCopy(char* _destination, const char* _source);

/*Desc.: Rec. Fnction to copy a string pointed by source into the array pointed by destination, including the terminating null character (and stopping at that point).
Input: Source string pointer and Dest. string pointer.
Output: pointer to the destination string.
Error: NULL pointer if copy  failed.*/
char* StrCopyRec(char* _destination, const char* _source);

/*Desc.: Itter function copy the first num characters of source to destination.
Input: Source string pointer and Dest. string pointer.
Output:pointer to the destination string.
Error: NULL pointer if copy failed.*/
char* StrNCopy(char* _destination, const char* _source, size_t _num);

/*Desc.: Rec. function copy the first num characters of source to destination.
Input: Source string pointer and Dest. string pointer.
Output:pointer to the destination string.
Error: NULL pointer if copy failed.*/
char* StrNCopyRec(char* _destination, const char* _source, size_t _num);

/*Desc.: Function to append a copy of the source string to the destination string.
Input: Source string pointer and Dest. string pointer.
Output: pointer to the destination string.
Error: NULL pointer if appending the copy failed.*/
char* StrConcat(char* _destination, const char* _source);

/*Desc.: Function which returns a pointer to the first occurrence of str2 in str1, or a null pointer if str2 is not part of str1.
Input: A string to be scanned and a string containing the sequence of characters to match
Output: Pointer to the first occurrence of str2 in str1, or a null pointer if str2 is not part of str1.
Error: NULL pointer if copy failed.*/
char* StrSubString(const char* _str, const char* _search);

#endif /* __STRINGS_H__ */

#ifndef __MYBOOKS_H__
#define __MYBOOKS_H__

#include "libarary_info_system.h"
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;


class Book
{
	public:
	
    Book(const string& _ISBN, const string& _author, const string&	m_name);
	~Book ();
	
	const string GetISBN() const;
	const string GetAuthor() const;
	const string GetName() const;
	
	bool operator==(const Book& _book);
        
private:
	Book (Book& _book);
    Book&operator=(const Book& _book);

private:    
	const string 	m_ISBN;
	const string 	m_author;
	const string	m_name;
};


class BookRecord: public Record
{
public:
    BookRecord(Book* const _book, size_t _copies);
	~BookRecord ();
    
    bool 			IsAvailable()const;
    bool 			IsBorrowed()const; /* to check before remove */
    unsigned int	NumOfCopeies()const;
    bool			BorrowBook();
    void			ReturnBook();
    
    void			InsertToWaitingList(const string& _wait);
    const string&   GetNextOnWaitingList()const;
    
    virtual void    Report(ostream& _os)const;
         
private:

	BookRecord (BookRecord& _book);
    BookRecord&operator=(const BookRecord& _record);
    
private:    
	Book* 			m_book;
	unsigned int 	m_bookCopies;
	unsigned int 	m_bookBorrowed;
	queue<string> 	m_waitingList;
	
};


class BooksAdmin: public RecordsAdmin
{

public:
    BooksAdmin();
    virtual ~BooksAdmin();
    
    virtual bool AddRecord(const Record& _record);
    virtual bool RemoveRecord(const string& _identifier);
    virtual RecordsList SearchBookByISBN(const string& _ISBN)const; 
    virtual RecordsList SearchBookByAuthor(const string& _author)const;
    virtual RecordsList SearchBookByName(const string& _name)const;
    virtual bool Report() const;
        
private:
    map<string, BookRecord*> m_ISBNRecords;
    map<string, BookRecord*> m_AuthorRecords;
    map<string, BookRecord*> m_NameRecords;
};


#endif /* __MYBOOKS_H__ */


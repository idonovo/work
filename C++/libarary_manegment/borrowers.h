#ifndef __BORROWER_H__
#define __BORROWER_H__

#include "libarary_info_system.h"
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

class Borrower
{
	public:
	
    Borrower(const string& _ID, const string& _name, const string&	_phone);
	virtual ~Borrower();
	
	const string GetID()const;
	const string GetName()const;
	const string GetPhone()const;
	
	bool operator==(const Borrower& _borrower) const;
        
private:
	Borrower (Borrower& _book);
    Borrower&operator=(const Borrower& _borrower);

private:    
	const string 	m_ID;
	const string 	m_name;
	const string	m_phone;
};

class BorrowerRecord: public Record
{

public:    
	BorrowerRecord(Borrower* const _borrower);
	virtual~BorrowerRecord();
	
	bool 	AddBorrowedBook(const string& _ISBN);
	void 	ReturnBook(const string& _ISBN);
	
	virtual void  Report(ostream& _os);
			
private:
	BorrowerRecord (BorrowerRecord& _borrowerRecord);
	BorrowerRecord&operator=(const BorrowerRecord& _borrowerRecord);
            
private:
	Borrower* m_borrower;
	list<string> m_borrowedBooks;
};

class BorrowersAdmin: public RecordsAdmin 
{
public:
    BorrowersAdmin (arguments);
    virtual ~BorrowersAdmin();
    
    virtual bool AddRecord(const Record& _record);
    virtual bool RemoveRecord(const string& _identifier);
    virtual bool BorrowBook(const Record& _borrowerRecord, const Record& _bookRecord);
    virtual bool ReturnBook(const Record& _borrowerRecord, const Record& _bookRecord);
    virtual bool Report()const;
    virtual RecordsList SearchBorrowerByName(const string& _name)const;
    virtual RecordsList SearchBorrowerByID(const string& _id)const;
    
private:
    map<string, BorrowerRecord*> m_IDRecords;
    map<string, BorrowerRecord*> m_NameRecords;
    
};

#endif /* __BORROWER_H__ */


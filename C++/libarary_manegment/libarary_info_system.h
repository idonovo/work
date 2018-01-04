#ifndef __LIBARARYMAN_H__
#define __LIBARARYMAN_H__


class Record
{
    public:
        Record(){};
        virtual ~Record (){};
        virtual void Report(ostream& _os) const = 0;
     
};

class RecordsList
{

public:
    RecordsList ();
    virtual ~RecordsList ();
    
    RecordsList (RecordsList& _record);
    RecordsList&operator=(const RecordsList& _record);
    
    bool AddRecord(const Record& _record);
    bool RemoveRecord(const Record& _record);

private:
    vector<Record> m_vec;
};


class  RecordsAdmin
{

public:
    RecordsAdmin ();
    virtual ~  RecordsAdmin ();

    virtual bool AddRecord(const Record& _record) = 0;
    virtual bool RemoveRecord(const string& _identifier) = 0;
    virtual bool Report()const = 0;

private:
    RecordsAdmin(RecordsAdmin&  _admin);
    RecordsAdmin&operator=(const RecordsAdmin&  _admin);
    
};


class LibararyManager
{
public:

    LibararyManager ();
    virtual ~LibararyManager ();
    
    virtual bool AddBook(const Book& _book);
    virtual bool RemoveBook(const Book& _book);
    
    virtual bool AddBorrower(const Borrower& _borrower);
    virtual bool RemoveBorrower(const string& _identifier);
    
    virtual bool BorrowBook(const Record& _borrowerRecord, const Record& _bookRecord);
    virtual bool ReturnBook(const Record& _borrowerRecord, const Record& _bookRecord);
    
    virtual RecordsList SearchBorrowerByName(const string& _name)const;
    virtual RecordsList SearchBorrowerByID(const string& _id)const;
    virtual RecordsList SearchBookByISBN(const string& _ISBN)const; 
    virtual RecordsList SearchBookByAuthor(const string& _author)const;
    virtual RecordsList SearchBookByName(const string& _name)const;
    virtual void Report(ostream& _os) const;

private:
   BorrowerAdmin*   m_borrowersAdmin;
   BooksAdmin*      m_booksAdmin;
};

#endif /* __LIBARARYMAN_H__ */


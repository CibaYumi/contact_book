#ifndef contact_book_h
#define contact_book_h

typedef struct sBook {
	char name[50];
	char fone[15];
  struct sBook *prev, *next;
} BookList;

typedef struct sIndex {
	char letter;
  struct sIndex *prev, *next;
  BookList *init;
} Index;

Index *searchLetter(Index *ind, char letter);
BookList *searchContactOnList(BookList *l, char name[]);
BookList *searchOneContact(Index *l, char name[]);
Index *insertLetter( char l );
BookList *insertContact(char name[]);
void signUpContact(Index **l, char name[]);
void showContact(Index *l, char name[]);
void showAll(Index *l);
void deleteAll(Index **l);

#endif

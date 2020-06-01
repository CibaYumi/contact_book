#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "contact-book.h"

Index *searchLetter( Index *i, char l ) {
  Index *aux = i;
  while ( aux->letter <= l )
  {
    if ( aux->letter == l ) {
      return aux;
    } else if ( aux->next == i ) {
      break;
    } else {
      aux = aux->next;
    }
  }
  return NULL;
}
BookList *searchContactOnList( BookList *l, char name[] ) {
  BookList *aux = l;
  do {
    if ( strcmp(name, aux->name) == 0 ) {
      return aux;
    } else {
      aux = aux->next;
    }
  } while ( aux != l );
  return NULL;
}
BookList *searchOneContact( Index *l, char name[] ) {
  char letter = toupper(name[0]);
  Index *inContacts;
  inContacts = searchLetter(l, letter);
  if ( inContacts == NULL ) {
    return NULL;
  } else {
    return searchContactOnList(inContacts->init, name);
  }
}

Index *insertLetter( char l ) {
  Index *newLetter;
  newLetter = (Index *) malloc(sizeof(Index));
  newLetter->letter = l;
  newLetter->prev = NULL;
  newLetter->next = NULL;
  newLetter->init = NULL;
  return newLetter;
}
BookList *insertContact(char name[]) {
  BookList *newContact;
  newContact = (BookList *) malloc(sizeof(BookList));
  strcpy(newContact->name, name);
  printf("Informe o telefone: ");
  gets(newContact->fone);
  fflush(stdin);
  newContact->prev = NULL;
  newContact->next = NULL;
  return newContact;
}


void signUpContact(Index **l, char name[]) {
  Index *inIndex, *newIndex;
  BookList *inContact, *newIn;
  char letter = toupper( name[0] );
  if ( *l == NULL ) {
    newIndex = insertLetter(letter);
    (*l) = newIndex;
    newIndex->prev = newIndex;
    newIndex->next = newIndex;
    newIn = insertContact(name);
    (*l)->init = newIn;
    newIn->next = newIn;
    newIn->prev = newIn;
    printf("Novo contato inserido\n");
  } else {
    inIndex = searchLetter(*l, letter);
    if ( inIndex == NULL ) {
      inIndex = *l;
      if ( inIndex->letter > letter ) {
        newIndex = insertLetter(letter);
        newIndex->prev = (*l)->prev;
        newIndex->next = *l;
        (*l)->prev->next = newIndex;
        (*l) = newIndex;
        newIn = insertContact(name);
        newIndex->init = newIn;
        newIn->next = newIn;
        newIn->prev = newIn;
        printf("Novo contato inserido\n");
      } else {
        do {
          if ( inIndex->next->letter > letter ) {
            newIndex = insertLetter(letter);
            newIndex->next = inIndex->next;
            newIndex->prev = inIndex;
            newIndex->prev->next = newIndex;
            newIndex->next->prev = newIndex;
            newIn = insertContact(name);
            newIndex->init = newIn;
            newIn->next = newIn;
            newIn->prev = newIn;
            printf("Novo contato inserido\n");
            return;
          } else {
            inIndex = inIndex->next;
          }
        } while (inIndex != *l);
        newIndex = insertLetter(letter);
        newIndex->next = inIndex;
        newIndex->prev = inIndex->prev;
        inIndex->prev->next = newIndex;
        inIndex->prev = newIndex;
        newIn = insertContact(name);
        newIndex->init = newIn;
        newIn->next = newIn;
        newIn->prev = newIn;
        printf("Novo contato inserido\n");
      }
    }
    else {
      inContact = searchContactOnList(inIndex->init, name);
      if (inContact != NULL)
      {
        printf("Esse contato já existe\n");
      }
      else
      {
        inContact = inIndex->init;
        if ( strcmp(inContact, name) > 0 ) {
          newIn = insertContact(name);
          newIn->next = inContact;
          newIn->prev = inContact->prev;
          inContact->prev->next = newIn;
          inContact->prev = newIn;
          inIndex->init = newIn;
        } else {
          do {
            if ( strcmp(inContact->next->name, name) > 0 ) {
              newIn = insertContact(name);
              newIn->next = inContact->next;
              newIn->prev = inContact;
              newIn->prev->next = newIn;
              newIn->next->prev = newIn;
              printf("Novo contato inserido\n");
              ;
              return;
            } else {
              inContact = inContact->next;
            }
          } while (inContact != inIndex->init);
          newIn = insertContact(name);
          newIn->next = inContact;
          newIn->prev = inContact->prev;
          inContact->prev->next = newIn;
          inContact->prev = newIn;
          printf("Novo contato inserido\n");
          ;
        }
      }
    }
  }
}
void showContact( Index *l, char name[] ) {
  BookList *aux;
  if ( l == NULL ) {
    printf("Agenda Vazia\n");
  } else {
    aux = searchContactOnList(l, name);
    if ( aux == NULL ) {
      printf("Contato não encontrado\n");
    } else {
      printf("Nome: %s\n", aux->name);
      printf("Telefone: %s\n\n", aux->fone);
    }
  }
}
void showAll( Index *l ) {
  Index *i;
  BookList *x;
  if (l == NULL) {
    printf("Agenda vazia\n");
  } else {
    i = l;
    do {
      x = i->init;
      do {
        printf("Nome: %s\n", x->name);
        printf("Telefone: %s\n\n", x->fone);
        x = x->next;
      } while ( x != i->init );
      i = i->next;
    } while ( i != l );
  }
}
void removeAll( Index **l ) {
  if (l == NULL) {
    printf("Agenda vazia\n");
  }
}

int main() {
  Index *contactBook = NULL;
  char name[100], op, fone[100], letter;
  do {
    printf("\t\tEscolha uma opção\n\n");
    printf("1 - Inserir novo contato\n");
    printf("2 - Exibir um contato\n");
    printf("3 - Exibir toda agenda\n");
    printf("4 - Remover todos os contatos\n");
    op = getche();
    printf("\n");
    fflush(stdin);
    printf("\n");
    switch (op) {
    case '1':
      printf("Informe o nome do novo contato:");
      gets(name);
      fflush(stdin);
      signUpContact(&contactBook, name);
      break;
    case '2':
      printf("Informe o nome do contato que deseja exibir:");
      gets(name);
      fflush(stdin);
      showContact(contactBook, name);
      break;
    case '3':
      showAll(contactBook);
      break;
    case '4':
      removeAll(contactBook);
      break;
    default:
      printf("Opcao Invalida \n");
    }
  } while ( op != '4' );
  return 0;
}

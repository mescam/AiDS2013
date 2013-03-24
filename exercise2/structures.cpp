/*-*- tab-width:2; indent-tabs-mode:nil;c-basic-offset:2; -*-*/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * Copyright (C) Jakub Woźniak, Marcin Zaremba, 2013
 */

#include <iostream>
#include <cstdio>

// Dynamic list implementation
namespace List {
  struct ListElement {
    int key;
    ListElement *next;
  };

  typedef ListElement* PListElement;

  PListElement initElement(int);
  void insertElement(PListElement &, int);
  PListElement searchList(PListElement &, int);
  void printList(PListElement &);
  void freeList(PListElement &);  

  PListElement initElement(int key) {
    PListElement el = new ListElement;
    el->key = key;
    el->next = NULL;

    return el;
  }

  void freeList(PListElement &head) {
    PListElement el, toDel;

    el = head;

    while(el != NULL) {
      toDel = el;
      el = el->next;
      delete toDel;
    }
  }

// version to just test,
// self-sorting list algorithm will be applied
  void insertElement(PListElement &head, int key) {
    PListElement el = initElement(key);

    if(head != NULL) 
      el->next = head;
    head = el;
  }

  PListElement searchList(PListElement &head, int key) {
    PListElement el;

    for(el = head; el != NULL && el->key != key; el = el->next);

    return el;
  }

  void printList(PListElement &head) {
    PListElement el = head;

    while(el != NULL) {
      std::cout << el->key << " ";
      el = el->next;
    }
  }
}

int main() {
  using namespace List;
  
  PListElement head = NULL;

  insertElement(head, 12);
  insertElement(head, 20);
  insertElement(head, 2312);

  PListElement se = searchList(head, 231);

  printList(head);
  freeList(head);
  return 0;
}

/* vim: set ts=2 sw=2 tw=0 et :*/

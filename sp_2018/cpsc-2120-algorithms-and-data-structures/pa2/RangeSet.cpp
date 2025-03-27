// Dylan Mumm

#include "RangeSet.h"
#include "RNode.h"

/* constructor */
RangeSet::RangeSet() {
  head = new RNode();
}

/* destructor */
RangeSet::~RangeSet() {

  // iterates through list, deleting each node
  // until reaching nullptr

  while(head != nullptr )
  {
      RNode *cursor = head->next;
      delete head;
      head = cursor;
  }
}


void      /* destructor */
RangeSet::addLonelyRange(int min, int max) {

    // Returns function on detection of error
    if(errorDetect(min, max) == true)
      return;

    // If an empty list, creates first range
    if(ifEmptyAdd(min, max) == true)
      return;

    // Initializing cursur to head
    RNode *cursor = head->next;

    // Initializing new range node with min and max
    RNode *insertPtr = new RNode(min, max);

    // Loops until cursor points to nullptr
    while(cursor->next != nullptr)
    {
       // If the minimum value is lesser than the next set's start,
       // it inserts the node set before it
       if(min < cursor->next->start){
          insertPtr->next = cursor->next;
          insertPtr->prev = cursor;
          cursor->next = insertPtr;
          return;
       }

       // Iterating
       cursor = cursor->next;
    }

    // Linking insertion pointer to lesser node
    insertPtr->prev = cursor;

    // Linking lesser node to insertion pointer
    cursor->next = insertPtr;
}

void
RangeSet::addRange(int min, int max) {

  // Deletes all values from set between min and max
  deleteRange(min, max);

  // Adds range
  addLonelyRange(min, max);

  // Combines connected ranges
  createMinimalForm(min, max);

}



bool
RangeSet::deleteValue(int val) {

  // if value is not in set of ranges, return false
  if(isInSet(val) == false)
    return false;

  // Iterating through list until cursor is null
  for(RNode *cursor = head->next; cursor != nullptr; cursor=cursor->next) {

    // If value belongs to a single integer range...
    if(val == cursor->start && val == cursor->end) {
      if(val == head->next->start && val == head->next->end) {
         RNode *hold = head->next;
         delete head;
         head = hold;
         return true;
      }
      if(cursor->next != nullptr) {
        // Links greater range to lesser range
        cursor->next->prev = cursor->prev;
      }
      if(cursor->prev != nullptr) {
        // Links lesser range to greater range
        cursor->prev->next = cursor->next;
      }
      // Deletes value
      delete cursor;
      return true;
    }

    // If value is the beginning of a range, increment start by 1
    else if(val == cursor->start && val != cursor->end) {
      cursor->start = val+1;
      return true;
    }

    // If value is the end of a range, decrement end by 1
    else if(val == cursor->end && val != cursor->start) {
      cursor->end = val-1;
      return true;
    }

    // If value is in the middle of a range...
    else if(val >= cursor->start && val <= cursor->end) {

      // Initialize insertion node 1 above value, ranging to end
      RNode *insertPtr = new RNode(val+1, cursor->end);

      // Decrement previous range's end by 1
      cursor->end = val-1;

      // Link insertion node to greater range
      insertPtr->next = cursor->next;

      // Link insertion node to lesser range
      insertPtr->prev = cursor;

      // Link greater range to insertion node
      if(cursor->next != nullptr)
        cursor->next->prev = insertPtr;

      // Link lesser node to insertion node
      cursor->next = insertPtr;

      return true;
    }
  }
  return false;
}


bool
RangeSet::isInSet(const int val) const {

  // Iterates through set until it finds value, and returns true if it does
  for(RNode *cursor = head->next; cursor != nullptr; cursor=cursor->next)
    if(val >= cursor->start && val <= cursor->end)
      return true;

  // And false if it does not
  return false;

}

void
RangeSet::dump() const {

  if(head->next == nullptr)
    cout << "Empty";

  // Iterates through set, printing each range node
  for(RNode *cursor = head->next; cursor != nullptr; cursor=cursor->next) {
    cout << *cursor << ",";
  }

  cout << endl;

}

bool
RangeSet::operator==(const RangeSet &r) const {

  // Iterates through both ranges
  RNode* c1; RNode* c2;
  for(c1=head->next, c2=r.head->next;
    c1!=nullptr && c2!=nullptr; c1=c1->next, c2=c2->next)
  {
    // Checks to see if this set has every value from other set, returns false
    // if not
    for(int i = c2->start; i <= c2->end; i++)
      if(!isInSet(i)) {
        return false;
      }

    // Checks to see if other set has every value from this set, returns false
    // if not
    for(int i = c1->start; i <= c1->end; i++)
      if(!r.isInSet(i)) {
        return false;
      }
  }

  // Returns false if both functions have not reached nullptr, true if they have
  return (c1 == nullptr && c2 == nullptr);
}


ostream&
operator<<(ostream & out, const RNode& right) {

    // Prints 1 value if range of 1, prints range if range of greater than 1
    (right.end - right.start > 0) ?
        (out << right.start << "-" << right.end) : (out << right.start);

    return out;

}

bool
RangeSet::errorDetect(int min, int max) {
  if(min > max) {
    cout << "ERROR: Empty Range" << endl;
    return true;
  }
  if(min < 0 || max < 0) {
    cout << "ERROR: Contains negative integer(s)" << endl;
    return true;
  }
  return false;
}

bool
RangeSet::ifEmptyAdd(int min, int max) {
  // If head points to nothing...
  if(head->next == nullptr)
  {
    // Creates insertion node and links head to it
    RNode *insertPtr = new RNode(min, max);
    head->next = insertPtr;
    return true;
  }
  return false;
}

void
RangeSet::deleteRange(int min, int max) {

  // Deletes all values in between given range
  for(int i = min; i <= max; i++)
    deleteValue(i);
}

void
RangeSet::createMinimalForm(int min, int max)
{
  RNode *c = head->next;
  while(c->next != nullptr)
  {
    // If inserted range is just one above lesser range, joins them
    if(c->prev != nullptr && min == c->start && c->start - c->prev->end == 1)
    {
      min = c->prev->start;
      deleteRange(min, max);
      addLonelyRange(min, max);
    }
    // If inserted range is just one below greater, joins them
    if(c->next != nullptr && max == c->end && c->next->start - c->end == 1)
    {

      max = c->next->end;
      deleteRange(min, max);
      addLonelyRange(min, max);
      return;
    }
    c = c->next;
  }
}

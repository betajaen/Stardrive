
List
====

List provides a set of functions through 'template duck-typing' to handle doubley linked lists.

There are two ways, to implement this:

Through inheritance;

```
  struct Thing  : ListItem<T> {};
  struct Things : List<Thing> {};
```
List
====

List provides a set of functions through 'template duck-typing' to handle doubley linked lists.

Implementation
---------------------

There are two ways, to implement this:

Through inheritance;

```
struct Thing  : ListItem<T> {};
struct Things : List<Thing> {};
```
Through composition:
```
struct Thing  { Thing *next, *prev;  };
struct Things { Thing *first, *last; };
```

All of the linked list functions will use these as long as there is `next` and `prev` pointers in item class, and `first` and `last` in the container class.

Basic Usage
--------------

Adding and Removing are easy.

```
Things things;
Thing* thing = make_thing();
list::Add(things, thing);
	
Thing* first = things->first;
list::Remove(things, first);
```

As well as clearing and counting.

```
if (list::Count(things) > 5))
{
	list::Clear(things);
}
```		

Iteration
----

To iterate through the list you can use a for or while, loop. Here is a standard example of using a while loop:

```
Thing* thing = things->first;
while(thing != nullptr)
{
	Thing* nextThing = thing->next;
	...
	thing = nextThing;
}
```

Warning: As with all while loops, be careful with 'continue', make sure you set your iterate to the next item before continuing. Speaking from experience this is difficult to debug!


```
Thing* thing = things->first;
while(thing != nullptr)
{
	Thing* nextThing = thing->next;
	if (nextThing->x == 5)
	{
		thing = nextThing;
		continue;
	}
	...
	thing = nextThing;
}
```


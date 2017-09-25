Variadic Foreach
================

The variadic foreach macros allow you to iterate through arguments in a given macro. Each argument is then passed to another macro which can be used to construct code.

For example, this is a simple enum;

```
#define enum_value(e) e,
enum Animals
{
  SMetaForeach(enum_value, Dog, Cat, Monkey);
};
```

Each argument `Dog, Cat and Monkey` is passed to the `enum_value` macro individually, which resolves to:

```
enum Animals
{
  Dog,
  Cat,
  Monkey,
};
```

Of course we can expand on that and give each argument, the index-of that argument `0, 1, 2`

```
#define enum_value(i, e) e = i,
enum Animals
{
  MetaForeachIndexed(enum_value, Dog, Cat, Monkey);
};
```

Which resolves to;

```
enum Animals
{
  Dog = 0,
  Cat = 1,
  Monkey = 2,
};
```

Finally, let's make this a bit more useful. 
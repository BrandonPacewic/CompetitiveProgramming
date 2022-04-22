## DBG

The complex ostream logic is to redefine what it means to output a pair or iterable data type,
insted of throwing an error if you try to output a pair or iterable type it will output the list of elements stored in them,
this is just to simplfy what I need for the testArgs(...) function, as the one function can output all data types.
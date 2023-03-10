================================
 non-owning view of a contiguous character sequence. [Test](https://godbolt.org/z/x6db8W7GM)

string_view allows you to create a constant, non-owning view of a contiguous character sequence.
You can manipulate that view and pass it around without the need to copy the referenced data.
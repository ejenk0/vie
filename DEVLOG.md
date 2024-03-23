### 20/03/24 - ncurses

The first, and hopefully *only* dependancy has been added: `ncurses`. While I was hoping to have a totally dependancy free project and write everything from scratch myself using the standard C libraries, it seems that writing an application which intends to occupy the entire console and control each character on it can only really be done with `ncurses` or a similar solution. Rewriting its systems and extensive functionality would be impractical and severely hinder my progress. 

In the interest of finishing this project to the scope I am hoping for I will concede this library is necessary. It is an acceptable concession though. One of the great things about developing a compiled application as opposed to a python script as I am used to, is that I do not need to require any extra work from the user, fighting with `pip` or `conda` to use my solution. Everything gets bundled together in a neat little executable.

### 23/03/24 - strtok

While developing the code required to parse the buffer line by line I encountered a problem with my usage of the c library's `strtok`. This function cannot be used if you need to detect tokens of length 0. That is, it considers consecutive delimiters as one delimiter. This means it is impossible to parse a file line by line using "\n" as the delimiting string. For example, take the following file, where I have written in the newline characters for clarity:

```
0th\n
\n
2nd\n
```

Flattened into a string this becomes: `"0th\n\n2nd\n"`. `strtok` considers `"\n\n"` to be a single delimiter, and therefore will not notice the 1st line at all.

Researching a solution I implemented a `strtok_single` function, inspired by a number of answers to this problem found online.

**Interesting takeaway** 
POSIX defines a "line" as a number of non-newline characters followed by a newline. Therefore, in a POSIX compliant system, the contents of a brand new file is actually: `\n`, or when represented in c as a null-terminated byte string: `"\n\0"`. This means that the number of lines in a file is simply the number of newline characters.


# Poor Man Copy

A much less featureful version of gnu coreutils cp that copies just files, not directories, not using the [copy_file_range](https://man7.org/linux/man-pages/man2/copy_file_range.2.html) syscall used by GNU Coreutil cp, only [read] (https://man7.org/linux/man-pages/man2/read.2.html) and [write] (https://man7.org/linux/man-pages/man2/write.2.html)

I made this primarily to learn about file copying at the lower level, and using buffers and also as a curiousity

Testing performance:

### GNU Coreutils copy:

```
┌──(alyssa㉿T440p)-[~/learningC/poormancopy]
└─$ date && cp 'These Are The Voyages.mp4' voyages_copy.mp4 && date
Tue  6 Aug 12:59:48 BST 2024
Tue  6 Aug 13:00:11 BST 2024
```
23 Seconds
```
┌──(alyssa㉿T440p)-[~/learningC/poormancopy]
└─$ date && cp 'These Are The Voyages.mp4' voyages_copy.mp4 && date
Tue  6 Aug 13:03:37 BST 2024
Tue  6 Aug 13:04:10 BST 2024
```
33 Seconds
```
┌──(alyssa㉿T440p)-[~/learningC/poormancopy]
└─$ date && cp 'These Are The Voyages.mp4' voyages_copy.mp4 && date
Tue  6 Aug 13:05:22 BST 2024
Tue  6 Aug 13:05:57 BST 2024
```
34 Seconds

### PoorMan copy:
```
┌──(alyssa㉿T440p)-[~/learningC/poormancopy]
└─$ date && ./pmcp.o 'These Are The Voyages.mp4' voyages_copy.mp4 && date
Tue  6 Aug 13:01:05 BST 2024
Tue  6 Aug 13:01:42 BST 2024
```
37 Seconds
```
┌──(alyssa㉿T440p)-[~/learningC/poormancopy]
└─$ date && ./pmcp.o 'These Are The Voyages.mp4' voyages_copy.mp4 && date
Tue  6 Aug 13:02:30 BST 2024
Tue  6 Aug 13:03:05 BST 2024
```
35 Seconds
```
┌──(alyssa㉿T440p)-[~/learningC/poormancopy]
└─$ date && ./pmcp.o 'These Are The Voyages.mp4' voyages_copy.mp4 && date
Tue  6 Aug 13:04:31 BST 2024
Tue  6 Aug 13:05:05 BST 2024
```
36 Seconds

As expected gnu coreutils cp is faster, but other times pmcp holds up. A smarter algorithm for block size picking could do well.

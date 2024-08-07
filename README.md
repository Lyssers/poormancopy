# Poor Man Copy

A much less featureful version of gnu coreutils cp that copies just files, not directories, not using the [copy_file_range](https://man7.org/linux/man-pages/man2/copy_file_range.2.html) syscall used by GNU Coreutil cp, only [read] (https://man7.org/linux/man-pages/man2/read.2.html) and [write] (https://man7.org/linux/man-pages/man2/write.2.html)

I made this primarily to learn about file copying at the lower level, and using buffers and also as a curiousity

Also, you might see some commented out printf statements such as on line 49, feel free to uncomment them to produce yourself a progress bar!

Testing performance:

### GNU Coreutils copy:

```
┌──(alyssa㉿T440p)-[~/learningC/poormancopy]
└─$ date && cp  'These Are The Voyages.mp4' voyages_copy.mp4 && date
Wed  7 Aug 22:31:03 BST 2024
Wed  7 Aug 22:31:20 BST 2024
```
17 Seconds

```
┌──(alyssa㉿T440p)-[~/learningC/poormancopy]
└─$ date && cp  'These Are The Voyages.mp4' voyages_copy.mp4 && date
Wed  7 Aug 22:32:25 BST 2024
Wed  7 Aug 22:32:43 BST 2024
```
18 Seconds

```
┌──(alyssa㉿T440p)-[~/learningC/poormancopy]
└─$ date && cp  'These Are The Voyages.mp4' voyages_copy.mp4 && date
Wed  7 Aug 22:33:47 BST 2024
Wed  7 Aug 22:34:05 BST 2024
```
18 Seconds


### PoorMan copy:

```
┌──(alyssa㉿T440p)-[~/learningC/poormancopy]
└─$ date && ./pmcp.o These\ Are\ The\ Voyages.mp4 voyages_copy.mp4 && date
Wed  7 Aug 22:30:12 BST 2024
Wed  7 Aug 22:30:38 BST 2024
```
26 Seconds

```
┌──(alyssa㉿T440p)-[~/learningC/poormancopy]
└─$ date && ./pmcp.o These\ Are\ The\ Voyages.mp4 voyages_copy.mp4 && date
Wed  7 Aug 22:31:50 BST 2024
Wed  7 Aug 22:32:08 BST 2024
```

18 Seconds

```
┌──(alyssa㉿T440p)-[~/learningC/poormancopy]
└─$ date && ./pmcp.o These\ Are\ The\ Voyages.mp4 voyages_copy.mp4 && date
Wed  7 Aug 22:33:14 BST 2024
Wed  7 Aug 22:33:34 BST 2024

```

20 Seconds

### Conclusion

As expected gnu coreutils cp is quite a bit faster, but occasionally the times of pmcp hold up. 
In some tests for unknown reasons it was faster, but they were occasional so I did not include them above. The testing methodology is also uhmm... not exactly scientific, but it was a fun exercise. A smarter algorithm for block size picking could probably improve performance, but a utility that reads and writes in this manner shouldn't be faster than one that uses more appropriate syscalls.


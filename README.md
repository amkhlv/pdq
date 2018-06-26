Description
===========

A minimalistic PDF viewer with ergonomic keyboard shortcuts, bookmarks and annotations.

Known bug
=========

When run forwarded over `ssh -X`, incorrect rendering __at first run__ (see [bug report](https://bugreports.qt.io/browse/QTBUG-61976)).
I don't know how to fix this...

Invocation
==========

    pdq filename.pdf

Command line options
--------------------

    -p <n>   open on page <n>

Keyboard Shortcuts
==================

<table>
<tr>
<td><b><u>Action</u></b></td><td><b><u>Keyboard Shortcut</u></b>&nbsp;&nbsp;</td><td><b><u>Button</u></b></td>
</tr><tr>
<td>Reload file</td><td>Ctrl-l</td><td>↺</td>
</tr><tr>
<td>Next Page</td><td>n</td><td>⇨</td>
</tr><tr>
<td>Previous Page</td><td>p</td><td>⇦</td>
</tr><tr>
<td>Scroll Up Slow</td><td>k</td><td></td>
</tr><tr>
<td>Scroll Up Fast</td><td>Shift-k</td><td></td>
</tr><tr>
<td>Scroll Down Slow</td><td>j</td><td></td>
</tr><tr>
<td>Scroll Down Fast</td><td>Shift-j</td><td></td>
</tr><tr>
<td>Scroll Left Slow</td><td>h</td><td></td>
</tr><tr>
<td>Scroll Left Fast</td><td>Shift-h</td><td></td>
</tr><tr>
<td>Scroll Right Slow</td><td>l</td><td></td>
</tr><tr>
<td>Scroll Right Fast</td><td>Shift-l</td><td></td>
</tr><tr>
<td>Zoom In</td><td>.</td><td>⊕</td>
</tr><tr>
<td>Zoom Out</td><td>,</td><td>⊖</td>
</tr><tr>
<td>Go back after link jump</td><td>b</td><td>↩</td>
</tr><tr>
<td>Search Forward</td><td>Ctrl-s</td><td>𝒮</td>
</tr><tr>
<td>Search Back</td><td>Ctrl-r</td><td>ℛ</td>
</tr><tr>
<td>Give Up Searching</td><td>Ctrl-g</td><td>𝒢</td>
</tr><tr>
<td>Stop Searching</td><td>Return</td><td>⏎</td>
</tr><tr>
<td>Open bookmarks</td><td>Ctrl-b</td><td>ℬ</td>
</tr><tr>
<td>Add bookmark</td><td>a</td><td>a</td>
</tr><tr>
<td>Go to page</td><td>g</td><td>go</td>
</tr><tr>
<td>Extract text</td><td>t</td><td>txt</td>
</tr>
</table>

Bookmarks for the file `filename.pdf` (or just `fielname`) are stored in the XML file `filename.pdq`;
the file is created when you add a new bookmarks (press `a`), or just open the bookmarks manager (press `Ctrl-b`).

Using the bookmarks manager
===========================

It lists bookmarks with charhints (a,b,c,d,...). Pressing the corresponding
letter navigates to that bookmarked page. Pressing the letter with `Shift`
(as if a capital letter) removes that bookmark.

Making annotations
==================

Right click with mouse on the place where you want to place the anchor. The dialog for entering annotation will pop up.


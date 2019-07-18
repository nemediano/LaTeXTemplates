# CS and Math Homework template
A LaTeX template for making homeworks for courses in
Computer Science and Mathematics areas.

This template is aimed for simple homeworks in your classes.
The ones you deliver every week or so. Therefore, is nothing
fancy but very practical, elegant and tries to maximize
the space on a page.

![View PDF](report.pdf)

Contains simple elegant margings with space for your personals and
course particulars. As well as a simple mechanism for numbering the pages.

Most of the documentation is in the `*.tex` source files rather than in the produced pdf.

Some of the features are

* Uses modern LateX:

  * The engine is XeLaTex instead of pdfLaTeX. Therefore supports
    UTF8 by default (no need of package `inputec`)

  * Uses Biber instead of Bibtex for managing the bibliography

  * Uses new package [`polyglossia`](https://ctan.org/pkg/polyglossia?lang=en) instead of old
    standard [`babel`](https://ctan.org/pkg/babel) for internationalization

* It uses package [minted](https://ctan.org/pkg/minted?lang=en) for code syntax
  highlighting, therefore **requires** a [python](https://www.python.org/)
  installation with [pygments](http://pygments.org/)

It has usage examples of the following:

* A simple equation and how to reference it in the text.

* Insert clean looking links to web pages for reference.

* How to make a mathematical function defined in cases. Typical in pdf's for probability.

* Automatic sizing parenthesis.

* An equation solved in several steps.

* How to insert figures from image files and reference them in the text.

  * How to create a figure composed of several subfigures.

* How to write an algorithm in pseudocode, where you can use mathematical syntax.

* How to uses the package `booktabs` for creating complex tables with a very simple and elegant
  looking.

* How to write source code in several programming languages using `minted`:

  * Source code paragraph.

  * Inlined code (Source code inside a normal text paragraph).

  * Include selected lines of an external source code file.

* How to include a very simple reference list, and how to put there a book that you do not
  explicitly cited in the text.

## Usage

You need to have a working installation of modern LaTeX.

In order to compile a document from this template it needs be build like this:

1. XeLaTeX
2. Biber
3. XeLaTex
4. XeLateX
5. Optionally ViewPDF (Command to invoque your pdf viewer)

And since we use `minted`, XeLaTex need to be executed with the option:

```
$xelatex -shell-escape input.tex
```

I have tested it in [TeX Live](https://www.tug.org/texlive/), from an standard Ubuntu 18.04 installation. And of course, you can configure Kile to do it all using the GUI.
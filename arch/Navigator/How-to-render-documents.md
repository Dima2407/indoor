How to render PlantUML and MarkDown documents
========================
This simple manual suggests few ways of myriad others.

Quick overview
-----------

1. Render PlantUML  
    - on servers like [plantuml.com]() and [planttext.com]() manually
    - pushing encoded text to [server](http://www.plantuml.com/plantuml/uml/SyfFKj2rKt3CoKnELR1Io4ZDoSa70000)
    - with `plantuml.jar` **locally** 
    - with `plantuml.war` on **your server**
2. Store rendered pictures (png,svg) near markdown file.
3. Render MarkDown
    - using Git server like *Bitbucket* or *GitHub*
    - using many-many services on internet like [stackedit.io](https://stackedit.io) 
    or [jbt.github.io](http://jbt.github.io/markdown-editor/)
    - **locally** using cmd-line tool [`pandoc`](http://pandoc.org/demos.html)
    - **locally** using graphic tool *Laverna*


Best way to generate locally **locally**
--------
1. Run `java -jar plantuml.jar -charset UTF-8 -gui` and set source folder. Wait.. Tool will
    render all `*.puml` to `.png` to the same folder. See more instructions on official site. 
    Let program running and it will rerender pictures once the source files changed.
2. There is no GUI for `pandoc`, see paragraph Automated.


Automated
---------
This is achievable with command-line tools [plantuml.jar](http://plantuml.com/command-line) and
[pandoc](http://pandoc.org)
```
cd prj/documentation-folder
java -jar plantuml.jar -recurse -charset UTF-8 ./*.puml
pandoc -f markdown -o README.html --smart --toc README.md --self-contained
```

`-charset UTF-8` is important on Windows platforms if you will render non-latin files.

Result `README.html` contains images embedded. It is possible to transfer only it.  
 
 
Notes. Did you know? 
-------
> PlantUML sources stored PNG's metadata. Use `-metadata` flag to retrieve PlantUML sources from 
PNG images.    

> PlantUML by default uses system charset. If UTF-8 or other non-win encoding is used on Windows, 
charset must be specified explicitly with flag `-charset UTF-8`.

> Pandoc uses the UTF-8 character encoding for both input and output. If your local character 
> encoding is not UTF-8, you should pipe input and output through `iconv`:  
> `iconv -t utf-8 input.txt | pandoc | iconv -f utf-8`

> Pandoc does not make images inline in output .html. Use flag `--self-contained`
 
> Pandoc allows conversation between a lot of file types and formats.

> It is cool to have a cool branded `.CSS` for Pandoc conversations.
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


Preview
-------
Use your favorite IDE with corresponding plugins. For example Intelij Idea or Eclipse.

Best way to generate **locally**
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
java -jar plantuml.jar -recurse -charset UTF-8 -output rendered/ *.puml
pandoc -f markdown --smart --toc --self-contained --css=style/buttondown.css README.md -o rendered/README.html 
```

`-charset UTF-8` is important on Windows platforms if you will render non-latin files.

Result `README.html` contains images embedded. It is possible to transfer by oneself, 
no external css or images need.  
 
 
Notes. Did you know? 
-------
> By default **PlantUML** sources are stored in PNG's metadata section. Use `-metadata` flag to retrieve PlantUML sources from 
PNG images.    

> **PlantUML** by default uses system charset. For example if source file encoded in UTF-8 and you are 
on Windows, charset must be specified explicitly with flag `-charset UTF-8`.

> **PlantUML** can generate PDFs or SVGs instead of PNGs.

> **PlantUML** does not restrict file types. It is possible to extract and render pictures from
> any file, i.e. code sources. The only requirement is `@startuml` and `@enduml` tags.

> **Pandoc** uses the UTF-8 character encoding for both input and output. If your local character 
> encoding is not UTF-8, you should pipe input and output through `iconv`:  
> `iconv -t utf-8 input.txt | pandoc | iconv -f utf-8`

> By default **Pandoc** does not store images in output .html, only relative links.   
> Use flag `--self-contained` to inline images.
 
> **Pandoc** allows conversation between a lot of file types and formats. See official site to learn more.

> [`buttondown.css`](https://gist.githubusercontent.com/ryangray/1882525/raw/2a6e53f645b960f0bed16d686ba3df36505f839f/buttondown.css) 
> was found on [github](https://gist.github.com/ryangray/1882525) and also could be passed by remote
> URL as `--css=https://gist.githubusercontent.com/ryangray/1882525/raw/2a6e53f645b960f0bed16d686ba3df36505f839f/buttondown.css`

> It is cool to have a nice branded `.CSS` for Pandoc conversations.
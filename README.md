# AutoNoteMD
## AutoNoteMD v1.0.0
-----------------------------------
## Description
An project that helps create, search tags, and auto push to git for your note.
Using VS code as editor and default format is markdown language.

## How to use
1. **note.exe**: create a .md file and use current date as file name
2. **search.exe**: search input tag and open all files contain the tag.  
    This step must run in terminal and input tag as an argument  
    e.g.  
        ```>> ./search myTag ```
3. **create tag**: using `<###### >` (six '#' and a '\space'), and the word after `<###### >` is tag  
    e.g.  
        ```###### myTag ```
  
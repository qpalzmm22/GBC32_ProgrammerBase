# SURROUND.VIM

>**Surround.vim** is all about "surroundings" : 

parentheses, brackets, quotes, XML tags, and more. The plugin provides mappings to easily delete, change and add such surroundings in pairs.

- cs + A B
    - ex) [ cs'" ] 'Hello' -> "Hello" 
  
- ds + A
    - ex) [ ds" ] "Hello" -> Hello

- ys+ A B
    - ex) [ ysiw] ] Hello -> \[Hello] (iw = test object)

<br>

>**History**

![version](info.PNG)

<br>

>**Installation**

1. home directory의 최상위에서 $ vi ~/.vimrc

<br>

2. Plug 'tpope/vim-surround' 추가


![customize](plug.PNG)


<br>
3. home directory의 최상위에서 아래 **commandLines** 입력


![capturqe](install1.PNG)

<br>

>**Example**

# cli: cs'"

Before


![customize](before.PNG)

After


![customize](before.PNG)

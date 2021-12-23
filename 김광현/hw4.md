# YCM(YouCompleteMe) vim 플러그인 알아보기

![rank](https://user-images.githubusercontent.com/61617997/147203771-36c0e21d-d37a-4d42-8f0b-1401e0beb91f.PNG)

## 탄생
10년전에 처음 만들어졌고 최근 업데이트는 5개월 전이다.

## 기능
vim에는 visual studio 같은 코드 작성 프로그램과 달리 코드 작성중 자동 완성 기능이 기본적으로 포함되지 않는다. 그렇기에 작성 시간이 필연적으로 오래 걸릴 수 밖에 없는데, 이 플러그인은 자동 완성 기능을 지원해주는 기능을 가졌다.

## 설치 방법

1. vim 패키지 관리자인 Vundle을 설치한다.

$ git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim

2. .vimrc에 YCM플러그인인 Plugin 'Valloric/YouCompleteMe' 추가

command창에서 vim +PluginInstall +qall로 플러그인 설치

3. python3로 컴파일

cd ~/.vim/bundle/YouCompleteMe
$ python3 install.py --go-completer

이 순서대로 하면 vim을 이용해 코드를 작성하면 자동 완성기능이 생긴 것을 확인 할 수 있다.

## 커맨드

이 플러그인은 디버그 정보를 알려주는 :YcmDebugInfo나 프로그램이 갑자기 멈췄을 시 재시작하는 :YcmRestartServer 커맨드도 지원할 뿐만 아니라 다양한 서브커맨드도 포함하고 있어 vim으로 코드 작성할 때 매우 유용한 것을 알 수 있다.

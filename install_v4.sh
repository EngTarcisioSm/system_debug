#!/bin/bash

nameLibSO="libsystem_log.so"
pathLibSO="$PWD/$nameLibSO"
nameFileC="system_log.c"
nameFileO="system_log.o"

# verifica se usuario deseja compilar a biblioteca
read -p "Do you want to compile the librarie [yes / no]?: " compile

if [ "$compile" = "yes" ] || [ "$compile" = "YES" ]; then
    # recompila a biblioteca
    gcc -fPIC -c "$nameFileC" -o "$nameFileO"
    gcc -shared -o "$nameLibSO" "$nameFileO"
    rm "$nameFileO"
fi

# verifica se usuario deseja compilar a biblioteca
read -p "Do you want to create a symbolic link [yes / no]?: " compile


if [ "$compile" = "yes" ] || [ "$compile" = "YES" ]; then
    # solicita input ao usuario e armazena na variavel path
    read -p "Write a path for the symbolic link: " path
    
    # verifica se a variavel path se encontra vazia
    if [ -z "$path" ]; then
        echo "Path is NULL"
    else
        # verifica se o caminho informado é valido
        if [ -d "$path" ];then
            # criado link simbolico no path passado pelo usuario
            sudo ln -s "$pathLibSO" "$path/$nameLibSO" 2>/dev/null
            # mensagem ao usuario
            echo "Sucess creating the symbolic link"
        else
            # mensagem ao usuario
            echo "Path not found"
        fi
    fi
fi
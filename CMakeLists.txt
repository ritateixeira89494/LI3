cmake_minimum_required(VERSION 3.15)
project(li3 C)

set(CMAKE_C_STANDARD 99)

add_executable(li3 main.c catalogos.c  vendas.c vendas.h catalogos.h main.h faturacao.c faturacao.h filiais.c filiais.h)
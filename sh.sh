#!/usr/bin/env bash
##
## EPITECH PROJECT, 2019
## sh
## File description:
## point sh
##

gcc -o my_hunter $1 my_putchar.c my_putstr.c -l csfml-window -l csfml-system -l csfml-audio -l csfml-network -l csfml-graphics

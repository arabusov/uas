#!/bin/sh

echo "movw %ax, %bx"
echo "movw %ax, %bx" | ./as
echo
echo " here : movw %ax, %es"
echo " here : movw %ax, %es" | ./as
echo
echo "movw %ax, %es:0x89 (%bx, %si)"
echo "movw %ax, %es:0x89 (%bx, %si)" | ./as
echo
echo "here: movw %ax, %es:0x89 (%bx, %si)"
echo "here: movw %ax, %es:0x89 (%bx, %si)" | ./as
echo
echo "here: movw %es:0x89 (%bx, %si), %ax"
echo "here: movw %es:0x89 (%bx, %si), %ax" | ./as
echo

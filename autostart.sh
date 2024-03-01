#!/bin/bash 
$HOME/.local/bin/scripts/screen.sh &
$HOME/.local/bin/scripts/changer & 
dwmblocks &
xrdb -merge ~/.config/Xresources/Xresources &
discord &
export _JAVA_AWT_WM_NONREPARENTING=1 
export AWT_TOOLKIT=MToolkit 
wmname LG3D

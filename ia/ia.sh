#!/bin/bash

clear
make

gnome-terminal -- bash -c "python zappy_ai -p 4242 -n team1 -h 127.0.0.1; exec bash"
gnome-terminal -- bash -c "python zappy_ai -p 4242 -n team1 -h 127.0.0.2; exec bash"
gnome-terminal -- bash -c "python zappy_ai -p 4242 -n team1 -h 127.0.0.3; exec bash"
gnome-terminal -- bash -c "python zappy_ai -p 4242 -n team1 -h 127.0.0.4; exec bash"
gnome-terminal -- bash -c "python zappy_ai -p 4242 -n team2 -h 127.0.0.5; exec bash"
gnome-terminal -- bash -c "python zappy_ai -p 4242 -n team2 -h 127.0.0.6; exec bash"
gnome-terminal -- bash -c "python zappy_ai -p 4242 -n team2 -h 127.0.0.7; exec bash"
gnome-terminal -- bash -c "python zappy_ai -p 4242 -n team2 -h 127.0.0.8; exec bash"

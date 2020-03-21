#!/bin/bash


tabview <(sed -e "s/&ndash;/-/g" <(cut -f1,3-9,11- <(./out <(wget -i url -O-))))

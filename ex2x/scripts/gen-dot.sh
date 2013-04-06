#!/bin/bash

for name in dot/*.dot; do
		dot -Tpng -Otree.png $name
done

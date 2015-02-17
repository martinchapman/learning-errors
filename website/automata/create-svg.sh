#!/bin/bash
for f in *.dot; do
  dot -Tsvg $f >"${f%.*}.svg"
  dot -Tpng $f >"${f%.*}.png"
done

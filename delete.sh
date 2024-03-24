#!/bin/bash
echo "Running $0..."
echo "Move $# files to recyclebin."
mv $* -t ~/pp/recyclebin
exit 0


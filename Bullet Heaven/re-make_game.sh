#!/bin/bash

echo "Cleaning..."

cd src/

make clean
cd ..
rm -rf BulletHeaven
cd src/

echo "Done cleaning."
echo "Make-ing game..."

make

echo "Done making game."

cd ..

echo "Running game."

./BulletHeaven
